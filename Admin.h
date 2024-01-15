#ifndef ADMIN_H
#define ADMIN_H

#include "Member.h"

class Admin {
private:
    string username;
    string password;
public:
    // Constructor
    Admin(string username, string password);

    // Method to check login
    bool login(string username, string password);

    // Method to reset a member's password
    void resetMemberPassword(Member* member, string newPassword);
};

#endif  // ADMIN_H