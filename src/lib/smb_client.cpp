//
// Created by Administrator on 14-05-2024.
//

#include <cstring>
#include <errno.h>
#include <iostream>
#include <netdb.h>

#include "../../include/smb_client.h"
#include "../../include/smb_negotiate.h"
#include "../../include/transport.h"

static int create_socket(const char *, const int);

const std::string& smb_client::get_server()
{
    return m_server;
}

const int smb_client::get_port()
{
    return m_port;
}

const std::string& smb_client::get_share()
{
    return m_share;
}

smb_client::smb_client(const std::string& server, const int port, const std::string& share)
    : m_server(server), m_port(port), m_share(share), m_connection_socket(-1)
{
    for (auto byte_idx = 0; byte_idx < 32; ++byte_idx) {
        m_salt[byte_idx] = rand() % 256;
    }

    memset(m_signature, 0, sizeof(m_signature));
}

smb_client::~smb_client()
{
}


int smb_client::connect(const std::string& domain, const std::string& username, std::string password)
{
    m_connection_socket = create_socket(m_server.c_str(), m_port);
    if (m_connection_socket < 0) {
        return 1;
    }

    iovec* negotiate_request_iovecs = create_new_negotiate_request(
            m_message_id,
            &m_salt[0],
            (byte1 *) m_server.c_str(),
            (byte2) m_server.size(),
            m_signature); // 5 iovecs

    iovec transport_header;
    transport_header.iov_len = 4;
    transport_header.iov_base = operator new(1 + transport_header.iov_len);

    memset(transport_header.iov_base, 0, 1);
    byte4 total_msg_size = htonl(
            negotiate_request_iovecs[0].iov_len +
            negotiate_request_iovecs[1].iov_len +
            negotiate_request_iovecs[2].iov_len +
            negotiate_request_iovecs[3].iov_len +
            negotiate_request_iovecs[4].iov_len);
    memcpy(transport_header.iov_base + 1, &total_msg_size, 3);

    try {
        send_vec(m_connection_socket, transport_header);
        send(m_connection_socket, negotiate_request_iovecs, 5);
    } catch (const std::runtime_error& exp) {
        return 1;
    }

    smb2_negotiate_response response;
    memset(&response, 0, sizeof(response));


    {
        int total_recv = 0;
        while (total_recv < sizeof(response)) {
            int r = recv(m_connection_socket, (char *) &response + total_recv, sizeof(response) - total_recv, 0);
            if (r < 0) {
                std::cerr << "error during receive = " << errno << '\n';
                exit(1);
            }
            total_recv += r;
        }
    }

    return 0;
}


static int create_socket(const char * server, const int port)
{
    struct addrinfo hint;
    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_protocol = IPPROTO_TCP;

    struct addrinfo *res = NULL;

    int retval = getaddrinfo(server, std::to_string(port).c_str(), &hint, &res);
    if (retval) {
        std::cerr << "Cannot addrinfo to the server";
        return retval;
    }

    int connection_socket = -1;
    struct addrinfo * res_itr;
    for (res_itr = res ; res_itr ; res_itr = res_itr->ai_next) {
        connection_socket = socket(res_itr->ai_family, res_itr->ai_socktype, res_itr->ai_protocol);

        if (connection_socket < 0) {
            continue;
        }

        if (connect(connection_socket, res_itr->ai_addr, res_itr->ai_addrlen) < 0) {
            continue;
        }

        break;
    }

    if (!res_itr) {
        connection_socket = -1;
        std::cerr << "Could not establish the socket connection to the server";
    }

    freeaddrinfo(res);
    return connection_socket;
}