//
// Created by root on 16/5/24.
//

#include "../include/smb_client.h"

#define SERVER "10.210.230.90"
#define SHARE "shantanu_pr_test"
#define PORT 445

const std::string USER = "svc.rainbow";
const std::string DOMAIN = "vxindia";
const std::string PASSWORD = "P@ssw0rdVtas345#$%";

int main() {
    smb_client client(SERVER, 445, SHARE);
    client.connect(DOMAIN, USER, PASSWORD);
    return 0;
}