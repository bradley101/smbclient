//
// Created by Administrator on 14-05-2024.
//

#include <cstring>
#include <exception>

#include "../../include/smb_base.h"

smb2_sync_header create_new_smb2_sync_header(
        byte2 command,
        byte4 flags,
        byte8 &message_id,
        byte4 tree_id,
        byte8 session_id,
        byte8 signature[2])
{
    smb2_sync_header header;

    memset(&header, 0, sizeof(smb2_sync_header));
    header.protocol_id = SMB2_PROTOCOL_ID;
    header.structure_size = SMB2_SYNC_HEADER_STRUCTURE_SIZE;
    header.credit_charge = 1;
    header.channel_sequence = 0;
    header.command = command;
    header.credit_request_response = 10;
    header.flags = flags;
    header.next_command = 0;
    header.message_id = message_id++;
    header.tree_id = tree_id;
    header.session_id = session_id;
    memcpy(header.signature, signature, 2 * sizeof(byte8));

    return header;
}

