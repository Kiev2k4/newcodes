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
    
    //Method to search for supporters
    vector<Member*> searchSupporters(Member* currentMember, string city, int creditPoints, float hostRating);

    //Load data method
    void loadData();

    pair<string, string> loadAdminData();

    //Save data method
    static void saveData();
};

#endif  // SYSTEM_H