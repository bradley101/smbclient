//
// Created by root on 16/5/24.
//

#include <sys/socket.h>
#include <stdexcept>

#include "../../include/transport.h"

int send_vec(int socket, iovec vec)
{
    int total_sent = 0;
    while (vec.iov_len > 0)
    {
        int sent = ::send(socket, (char *) vec.iov_base + total_sent, vec.iov_len, 0);

        if (sent < 0) {
            throw std::runtime_error("Unable to sent through socket");
        }

        total_sent += sent;
        vec.iov_len -= sent;
    }

    return total_sent;
}

int send(int socket, iovec *vec, int num_vec)
{
    for (auto vec_i = 0; vec_i < num_vec; ++vec_i) {
        send_vec(socket, vec[vec_i]);
    }
    return num_vec;
}