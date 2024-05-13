//
// Created by Shantanu Banerjee on 14/05/24.
//

#ifndef SMBCLIENT_SMB_COMMANDS_H
#define SMBCLIENT_SMB_COMMANDS_H

#include "defines.h"

constexpr byte2 SMB_NEGOTIATE          = 0x0000;
constexpr byte2 SMB_SESSION_SETUP      = 0x0001;
constexpr byte2 SMB_LOGOFF             = 0x0002;
constexpr byte2 SMB_TREE_CONNECT       = 0x0003;
constexpr byte2 SMB_TREE_DISCONNECT    = 0x0004;
constexpr byte2 SMB_CREATE             = 0x0005;
constexpr byte2 SMB_CLOSE              = 0x0006;
constexpr byte2 SMB_FLUSH              = 0x0007;
constexpr byte2 SMB_READ               = 0x0008;
constexpr byte2 SMB_WRITE              = 0x0009;
constexpr byte2 SMB_LOCK               = 0x000A;
constexpr byte2 SMB_IOCTL              = 0x000B;
constexpr byte2 SMB_CANCEL             = 0x000C;
constexpr byte2 SMB_ECHO               = 0x000D;
constexpr byte2 SMB_QUERY_DIRECTORY    = 0x000E;
constexpr byte2 SMB_CHANGE_NOTIFY      = 0x000F;
constexpr byte2 SMB_QUERY_INFO         = 0x0010;
constexpr byte2 SMB_SET_INFO           = 0x0011;
constexpr byte2 SMB_OPLOCK_BREAK       = 0x0012;

#endif //SMBCLIENT_SMB_COMMANDS_H
