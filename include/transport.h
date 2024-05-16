//
// Created by root on 16/5/24.
//

#ifndef SMBCLIENT_TRANSPORT_H
#define SMBCLIENT_TRANSPORT_H

#include <sys/uio.h>

int send_vec(int, iovec);
int send(int, iovec *, int);

#endif //SMBCLIENT_TRANSPORT_H
