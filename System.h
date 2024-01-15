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

    // Getter for members
    static vector<Member*> getMembers();

    
    //Method to search for supporters
    vector<Member*> searchSupporters(string city);

    //Load data method
    void loadData();

    //Save data method
    void saveData();
};

#endif  // SYSTEM_H