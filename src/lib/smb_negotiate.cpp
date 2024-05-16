//
// Created by Administrator on 14-05-2024.
//

#include <new>
#include <cstring>
#include <cstdlib>
#include "../../include/smb_base.h"
#include "../../include/smb_commands.h"
#include "../../include/smb_negotiate.h"

smb2_negotiate_request* create_new_smb2_negotiate_request(
        byte8 message_id
        )
{
    smb2_negotiate_request negotiate_request;
    memset(&negotiate_request, 0, sizeof(smb2_negotiate_request));

    negotiate_request.base_header =
            create_new_smb2_sync_header(
                SMB_NEGOTIATE,  // command
                0,                  // flags
                message_id,            // message id
                0,                 // tree id
                0,              // session id
                0                // signature
            );

    negotiate_request.structure_size = 65;
    negotiate_request.dialect_count = 1;
    negotiate_request.security_mode = SMB2_NEGOTIATE_SIGNING_ENABLED;
    negotiate_request.capabilities =
            SMB2_GLOBAL_CAP_DFS |
            SMB2_GLOBAL_CAP_ENCRYPTION;

    for (auto byte_idx = 0 ; byte_idx < 16 ; ++byte_idx) {
        negotiate_request.client_guid[byte_idx] = rand() % 256;
    }

    negotiate_request.negotiate_context_offset = 40;    // no of bytes till the context list is 8-byte aligned
    negotiate_request.negotiate_context_count = 4;      // no of supported negotiate contexts
    negotiate_request.dialects = SMB_3_1_1;

    return nullptr;
}
