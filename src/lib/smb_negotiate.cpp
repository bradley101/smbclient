//
// Created by Administrator on 14-05-2024.
//

#include <cstdlib>
#include <cstring>
#include <new>
#include <sys/uio.h>

#include "../../include/smb_base.h"
#include "../../include/smb_commands.h"
#include "../../include/smb_negotiate.h"

iovec* create_new_smb2_negotiate_request(
        byte8 message_id,
        byte1 *salt,
        byte1 *server,
        byte2 server_len
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

    negotiate_request.structure_size = SMB2_NEGOTIATE_REQ_STRUCTURE_SIZE;
    negotiate_request.dialect_count = 1;
    negotiate_request.security_mode = SMB2_NEGOTIATE_SIGNING_ENABLED;
    negotiate_request.capabilities =
            SMB2_GLOBAL_CAP_DFS |
            SMB2_GLOBAL_CAP_ENCRYPTION;

    for (auto byte_idx = 0 ; byte_idx < 16 ; ++byte_idx) {
        negotiate_request.client_guid[byte_idx] = rand() % 256;
    }

    negotiate_request.negotiate_context_offset = 40 + 64;    // no of bytes till the context list is 8-byte aligned
    negotiate_request.negotiate_context_count = 4;      // no of supported negotiate contexts
    negotiate_request.dialects = SMB_3_1_1;
    negotiate_request.padding = 0;

    iovec *contexts;

    try {
        contexts = new iovec[5];
    } catch (const std::bad_alloc& exp) {
        return nullptr;
    }

    {
        struct SMB2_PREAUTH_INTEGRITY_CAPABILITIES context;
        context.hash_algorithm_count = 1;
        context.salt_length = 32;
        context.hash_algorithms = SHA_512;
        memcpy(context.salt, salt, 32);

        negotiate_context_list context_list1;
        context_list1.context_type = SMB2_PREAUTH_INTEGRITY_CAPABILITIES;
        context_list1.data_length = sizeof(context);
        context_list1.reserved = 0;

        contexts[1].iov_len = sizeof(context) + sizeof(context_list1);
        try {
            contexts[1].iov_base = operator new(contexts[1].iov_len);
        } catch (const std::bad_alloc& exp) {
            goto free_heap_memory;
        }
        memcpy(contexts[1].iov_base, &context_list1, sizeof(context_list1));
        memcpy((char *) contexts[1].iov_base + sizeof(context_list1), &context, sizeof(context));
    }
    {
        struct SMB2_ENCRYPTION_CAPABILITIES context;
        context.cipher_count = 1;
        context.ciphers = AES_256_GCM;

        negotiate_context_list context_list1;
        context_list1.context_type = SMB2_ENCRYPTION_CAPABILITIES;
        context_list1.data_length = sizeof(context);
        context_list1.reserved = 0;

        contexts[2].iov_len = sizeof(context) + sizeof(context_list1);
        try {
            contexts[2].iov_base = operator new(contexts[2].iov_len);
        } catch (const std::bad_alloc& exp) {
            goto free_heap_memory;
        }
        memcpy(contexts[2].iov_base, &context_list1, sizeof(context_list1));
        memcpy((char *) contexts[2].iov_base + sizeof(context_list1), &context, sizeof(context));
    }
    {
        negotiate_context_list context_list1;
        context_list1.context_type = SMB2_NETNAME_NEGOTIATE_CONTEXT_ID;
        context_list1.data_length = server_len;
        context_list1.reserved = 0;

        contexts[3].iov_len = server_len + sizeof(context_list1);
        try {
            contexts[3].iov_base = operator new(contexts[3].iov_len);
        } catch (const std::bad_alloc& exp) {
            goto free_heap_memory;
        }
        memcpy(contexts[3].iov_base, &context_list1, sizeof(context_list1));
        memcpy((char *) contexts[3].iov_base + sizeof(context_list1), server, server_len);
    }
    {
        struct SMB2_SIGNING_CAPABILITIES context;
        context.signing_algorithm_count = 1;
        context.signing_algorithm = AES_GMAC;

        negotiate_context_list context_list1;
        context_list1.context_type = SMB2_SIGNING_CAPABILITIES;
        context_list1.data_length = sizeof(context);
        context_list1.reserved = 0;

        contexts[4].iov_len = sizeof(context) + sizeof(context_list1);
        try {
            contexts[4].iov_base = operator new(contexts[4].iov_len);
        } catch (const std::bad_alloc& exp) {
            goto free_heap_memory;
        }
        memcpy(contexts[4].iov_base, &context_list1, sizeof(context_list1));
        memcpy((char *) contexts[4].iov_base + sizeof(context_list1), &context, sizeof(context));
    }

    // Setting the final iovec to store the negotiate request
    {
        contexts[0].iov_len = sizeof(negotiate_request);
        try {
            contexts[0].iov_base = operator new(contexts[0].iov_len);
        } catch (const std::bad_alloc& exp) {
            goto free_heap_memory;
        }
        memcpy(contexts[0].iov_base, &negotiate_request, contexts[0].iov_len);
    }

    return contexts;

free_heap_memory:
    for (auto ptr_idx = 0; ptr_idx < 5; ++ptr_idx) {
        if (contexts[ptr_idx].iov_base) {
            delete contexts[ptr_idx].iov_base;
        }
    }
    delete[] contexts;
    return nullptr;
}
