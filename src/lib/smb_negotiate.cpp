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

    for (auto bit_idx = 0 ; bit_idx < 16 ; ++bit_idx) {
        negotiate_request.client_guid[bit_idx] = rand() % 256;
    }




    return nullptr;
}
