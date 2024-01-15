#ifndef NONMEMBER_H
#define NONMEMBER_H

#include <string>
#include <vector>
#include "Member.h"
using namespace std;

class NonMember {
    private:
    bool viewOnlyAccess;
public:
    void viewSupporters();
    Member* registerMember(string username, string fullName, string password, string phoneNumber, string email, string homeAddress, vector<string> skills, vector<string> availability);
};

#endif  // NONMEMBER_H