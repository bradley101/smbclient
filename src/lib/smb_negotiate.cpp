//
// Created by Administrator on 14-05-2024.
//

#include <new>
#include "../../include/smb_base.h"
#include "../../include/smb_commands.h"
#include "../../include/smb_negotiate.h"

smb2_negotiate_request* create_new_smb2_negotiate_request(
        byte8 message_id
        )
{
    smb2_negotiate_request* negotiateRequest;
    smb2_sync_header*       header =
            create_new_smb2_sync_header(
                SMB_NEGOTIATE,  // command
                0,                  // flags
                message_id,            // message id
                0,                 // tree id
                0,              // session id
                0                // signature
            );
    if (!header) {
        return nullptr;
    }

    try {
        negotiateRequest = new smb2_negotiate_request;
    } catch (const std::bad_alloc& exp) {
        free_smb2_sync_header(header);
        return nullptr;
    }

    return negotiateRequest;
}
