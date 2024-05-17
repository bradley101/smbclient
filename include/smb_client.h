//
// Created by Administrator on 14-05-2024.
//

#ifndef SMB_CLIENT_H
#define SMB_CLIENT_H

#include <string>
#include "defines.h"

class smb_client
{
    public:
        // smb_client();
        smb_client(const std::string& server, const int port, const std::string& share);
        smb_client(const smb_client&) = delete;
        smb_client& operator=(const smb_client&) = delete;
        ~smb_client();

        int connect(const std::string& domain, const std::string& username, std::string password);

        const std::string&  get_server();
        const int           get_port();
        const std::string&  get_share();

    private:
        const std::string   m_server;
        const int           m_port;
        const std::string   m_share;

        byte8               m_message_id = 1;
        int                 m_connection_socket;
        byte1               m_salt[32];
        byte1               m_signature[16];

};

#endif //SMB_CLIENT_H
