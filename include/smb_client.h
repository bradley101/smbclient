//
// Created by Administrator on 14-05-2024.
//

#ifndef SMB_CLIENT_H
#define SMB_CLIENT_H

#include <string>

class smb_client
{
    public:
        // smb_client();
        smb_client(std::string server, int port, std::string share);
        smb_client(const smb_client&) = delete;
        smb_client& operator=(const smb_client&) = delete;
        ~smb_client();

        int connect(std::string domain, std::string username, std::string password);

        const std::string&  get_server();
        const int           get_port();
        const std::string&  get_share();

    private:
        const std::string   m_server;
        const int           m_port;
        const std::string   m_share;

};

#endif //SMB_CLIENT_H
