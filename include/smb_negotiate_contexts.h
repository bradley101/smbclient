//
// Created by Shantanu Banerjee on 14/05/24.
//

#ifndef SMBCLIENT_SMB_NEGOTIATE_CONTEXTS_H
#define SMBCLIENT_SMB_NEGOTIATE_CONTEXTS_H

#include "defines.h"

enum preauth_hash_algorithms {
    SHA_512 = 0x0001
};

enum ecryption_ciphers {
    AES_128_CCM = 0x0001,
    AES_128_GCM = 0x0002,
    AES_256_CCM = 0x0003,
    AES_256_GCM = 0x0004
};

enum signing_algorithms {
    HMAC_SHA256 = 0x0000,
    AES_CMAC    = 0x0001,
    AES_GMAC    = 0x0002
};

struct SMB2_PREAUTH_INTEGRITY_CAPABILITIES {
    byte2 hash_algorithm_count = 1;
    byte2 salt_length;
    byte2 hash_algorithms = SHA_512;
    byte1 salt[64];
};

struct SMB2_ENCRYPTION_CAPABILITIES {
    byte2 cipher_count = 1;
    byte2 ciphers = AES_256_GCM;
};

// SMB2_COMPRESSION_CAPABILITIES -> WIll not implement

struct SMB2_NETNAME_NEGOTIATE_CONTEXT_ID {
    byte1 *net_name;
};

// SMB2_TRANSPORT_CAPABILITIES -> Will not implement
// SMB2_RDMA_TRANSFORM_CAPABILITIES -> Will not implement

struct SMB2_SIGNING_CAPABILITIES {
    byte2 signing_algorithm_count = 1;
    byte2 signing_algorithm = AES_GMAC;
};

#endif //SMBCLIENT_SMB_NEGOTIATE_CONTEXTS_H
