//
// Created by Shantanu Banerjee on 14/05/24.
//

#ifndef SMBCLIENT_SMB_NEGOTIATE_H
#define SMBCLIENT_SMB_NEGOTIATE_H

#include <sys/uio.h>

#include "smb_base.h"
#include "smb_negotiate_contexts.h"

constexpr byte2 SMB2_NEGOTIATE_REQ_STRUCTURE_SIZE = 36;

enum smb2_security_modes
{
    SMB2_NEGOTIATE_SIGNING_ENABLED  = 0x0001,
    SMB2_NEGOTIATE_SIGNING_REQUIRED = 0x0002
};

enum smb2_capabilities
{
    SMB2_GLOBAL_CAP_DFS                 = 0x00000001,
    SMB2_GLOBAL_CAP_LEASING             = 0x00000002,
    SMB2_GLOBAL_CAP_LARGE_MTU           = 0x00000004,
    SMB2_GLOBAL_CAP_MULTI_CHANNEL       = 0x00000008,
    SMB2_GLOBAL_CAP_PERSISTENT_HANDLES  = 0x00000010,
    SMB2_GLOBAL_CAP_DIRECTORY_LEASING   = 0x00000020,
    SMB2_GLOBAL_CAP_ENCRYPTION          = 0x00000040,
    SMB2_GLOBAL_CAP_NOTIFICATIONS       = 0x00000080
};

enum smb2_dialects
{
    SMB_2_0_2   = 0x0202,
    SMB_2_1     = 0x0210,
    SMB_3_0     = 0x0300,
    SMB_3_0_2   = 0x0302,
    SMB_3_1_1   = 0x0311
};

enum smb2_negotiate_contexts
{
    SMB2_PREAUTH_INTEGRITY_CAPABILITIES = 0x0001,
    SMB2_ENCRYPTION_CAPABILITIES = 0x0002,
    SMB2_COMPRESSION_CAPABILITIES = 0x0003,
    SMB2_NETNAME_NEGOTIATE_CONTEXT_ID = 0x0005,
    SMB2_TRANSPORT_CAPABILITIES = 0x0006,
    SMB2_RDMA_TRANSFORM_CAPABILITIES = 0x0007,
    SMB2_SIGNING_CAPABILITIES = 0x0008,
    SMB2_CONTEXTTYPE_RESERVED = 0x0100
};

struct smb2_negotiate_request
{
    struct smb2_sync_header base_header;    // Size = 64 bytes

    byte2 structure_size = SMB2_NEGOTIATE_REQ_STRUCTURE_SIZE;
    byte2 dialect_count = 1;
    byte2 security_mode = SMB2_NEGOTIATE_SIGNING_ENABLED;
    byte2 reserved = 0;
    byte4 capabilities = SMB2_GLOBAL_CAP_ENCRYPTION;
    byte1 client_guid[16];
    byte4 negotiate_context_offset;
    byte2 negotiate_context_count;
    byte2 reserved2 = 0;
    byte2 dialects = SMB_3_1_1;
    byte2 padding;
} PACKED ;

iovec * create_new_negotiate_request(
        byte8 message_id,
        byte1 *salt,
        byte1 *server,
        byte2 server_len);

struct smb2_negotiate_response
{
    struct smb2_sync_header base_header;

    byte2 structure_size = 65;
    byte2 dialect_count;
    byte2 security_mode;
    byte2 dialect_revision;
    byte2 negotiate_context_count;
    byte8 server_guid[2];
    byte4 capabilities;
    byte4 max_transact_size;
    byte4 max_read_size;
    byte4 max_write_size;
    byte8 system_time;
    byte8 server_start_time;
    byte2 security_buffer_offset;
    byte2 security_buffer_length;
    byte4 negotiate_context_offset;
//    byte1 *buffer;
//    byte1 *padding;
//
//    struct negotiate_context_list *negotiate_context_list;
} PACKED ;

#endif //SMBCLIENT_SMB_NEGOTIATE_H
