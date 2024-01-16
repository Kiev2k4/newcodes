#ifndef SYSTEM_H
#define SYSTEM_H

#include "Member.h"
#include <vector>

class System {
private:
    // Global list of members
    static vector<Member*> members;
public:
    // Method to add a member
    static void addMember(Member* member);

    //Method to find a member
    Member* findMemberByUsername(string username);

    // Getter for members
    static vector<Member*> getMembers();

    pair<string, string> loadAdminData();
    
    //Method to search for supporters
    vector<Member*> searchSupporters(string city);

    //Load data method
    void loadData();

    //Save data method
    static void saveData();
};

#endif  // SYSTEM_H