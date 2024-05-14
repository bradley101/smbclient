//
// Created by Administrator on 14-05-2024.
//

#include "../../include/smb_client.h"

const std::string& smb_client::get_server()
{
    return m_server;
}

const int smb_client::get_port()
{
    return m_port;
}

const std::string& smb_client::get_share()
{
    return m_share;
}

smb_client::smb_client(const std::string server, const int port, const std::string share)
    : m_server(server), m_port(port), m_share(share)
{
}

smb_client::~smb_client()
{
}


void smb_client::connect(std::string domain, std::string username, std::string password)
{

}


