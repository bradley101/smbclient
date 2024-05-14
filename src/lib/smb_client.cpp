//
// Created by Administrator on 14-05-2024.
//

#include <iostream>
#include <netdb.h>
#include "../../include/smb_client.h"

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

smb_client::smb_client(const std::string server, const int port, const std::string share)
    : m_server(server), m_port(port), m_share(share)
{
}

smb_client::~smb_client()
{
}


int smb_client::connect(std::string domain, std::string username, std::string password)
{
    int connection_socket = create_socket(m_server.c_str(), m_port);
    if (connection_socket < 0) {
        return 1;
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