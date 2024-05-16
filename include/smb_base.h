//
// Created by Shantanu Banerjee on 14/05/24.
//

#ifndef SMBCLIENT_SMB_BASE_H
#define SMBCLIENT_SMB_BASE_H

#include "defines.h"

constexpr byte4 SMB2_PROTOCOL_ID = 0x424D53FE;
constexpr byte2 SMB2_SYNC_HEADER_STRUCTURE_SIZE = 64;

enum smb2_header_flags
{
    SMB2_FLAGS_SERVER_TO_REDIR      = 0x00000001,
    SMB2_FLAGS_ASYNC_COMMAND        = 0x00000002,
    SMB2_FLAGS_RELATED_OPERATIONS   = 0x00000004,
    SMB2_FLAGS_SIGNED               = 0x00000008,
    SMB2_FLAGS_PRIORITY_MASK        = 0x00000070,
    SMB2_FLAGS_DFS_OPERATIONS       = 0x10000000,
    SMB2_FLAGS_REPLAY_OPERATION     = 0x20000000
};

struct smb2_sync_header
{
    byte4 protocol_id = SMB2_PROTOCOL_ID;
    byte2 structure_size = SMB2_SYNC_HEADER_STRUCTURE_SIZE;
    byte2 credit_charge;
    byte2 channel_sequence;
    byte2 reserved = 0;
    byte2 command;
    byte2 credit_request_response;
    byte4 flags;
    byte4 next_command;     // Also mentioned as Chain Offset in Wireshark
    byte8 message_id;
    byte4 reserved2 = 0;
    byte4 tree_id;
    byte8 session_id;
    byte8 signature[2];
} PACKED ;

struct smb2_sync_header create_new_smb2_sync_header(
        byte2 command,
        byte4 flags,
        byte8 &message_id,
        byte4 tree_id,
        byte8 session_id,
        byte8 signature[2]);

#endif //SMBCLIENT_SMB_BASE_H
