#ifndef NONMEMBER_H
#define NONMEMBER_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Member.h"
using namespace std;

class NonMember {
    private:
    bool viewOnlyAccess;
public:
    void viewSupporters();
    Member* registerMember(string username, string fullName, string password, string phoneNumber, string email, string homeAddress, vector<string> skills, vector<pair<string, pair<string, pair<string, string>>>> availability, string city);
};

#endif  // NONMEMBER_H