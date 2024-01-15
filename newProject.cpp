#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

// Forward declarations
class Member;
class NonMember;
class System;
class Admin;

// Class for individual members
class Member {
private:
    string username;
    string fullName;
    string password;
    string phoneNumber;
    string email;
    string homeAddress;
    vector<string> skills;
    int credit_points = 20;
    float skillRating;
    float supporterRating;
    float hostRating;
    vector<string> availability;
    vector<Member*> blockedMembers;
public:
    // Constructor
    Member(string username = "", string fullName = "", string password = "", string phoneNumber = "", string email = "", string homeAddress = "", vector<string> skills = {}, vector<string> availability = {});

    // Getter methods
    string getUsername();
    string getFullName();
    string getPassword();
    string getPhoneNumber();
    string getEmail();
    string getHomeAddress();
    vector<string> getSkills();
    vector<string> getAvailability();

    //Setter methods
    void setUsername(string newUsername);
    void setFullName(string newFullName);
    void setPassword(string newPassWord);
    void setPhoneNumber(string newPhoneNumber);
    void setEmail(string newEmail);
    void setHomeAddress(string newHomeAddress);
    void setSkills(vector<string> newSkills);
    void setAvailability(vector<string> newAvailability);

    // Method to check if a member is available
    bool isAvailable();
};

// Class for non-members
class NonMember {
private:
    bool viewOnlyAccess;
public:
    void viewSupporters();
    Member* registerMember(string username, string fullName, string password, string phoneNumber, string email, string homeAddress, vector<string> skills, vector<string> availability);
};

class System {
private:
    // Global list of members
    static vector<Member*> members;
public:
    // Method to add a member
    static void addMember(Member* member);

    // Getter for members
    static vector<Member*> getMembers();
};
vector<Member*> System::members;

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

// Now define the methods
Member::Member(string username, string fullName, string password, string phoneNumber, string email, string homeAddress, vector<string> skills, vector<string> availability)
    : username(username), fullName(fullName), password(password), phoneNumber(phoneNumber), email(email), homeAddress(homeAddress), skills(skills), availability(availability) {
    System::addMember(this);
}

string Member::getUsername() { return username; }
string Member::getFullName() { return fullName; }
string Member::getPassword() { return password; }
string Member::getPhoneNumber() { return phoneNumber; }
string Member::getEmail() { return email; }
string Member::getHomeAddress() { return homeAddress; }
vector<string> Member::getSkills() { return skills; }
vector<string> Member::getAvailability() { return availability; }

void Member::setUsername(string newUsername)
{
    username = newUsername;
}

void Member::setFullName(string newFullName)
{
    fullName = newFullName;
}

void Member::setPassword(string newPassword) {
    password = newPassword;
}

void Member::setPhoneNumber(string newPhoneNumber) {
    phoneNumber = newPhoneNumber;
}

void Member::setEmail(string newEmail) {
    email = newEmail;
}

void Member::setHomeAddress(string newHomeAddress) {
    homeAddress = newHomeAddress;
}

void Member::setSkills(vector<string> newSkills) {
    skills = newSkills;
}

void Member::setAvailability(vector<string> newAvailability) {
    availability = newAvailability;
}

bool Member::isAvailable() { return !availability.empty(); }

void NonMember::viewSupporters() {
    for (Member* member : System::getMembers()) {
        if (1) {
            // Print member details but not their reviews, credit points, or ratings
            cout << "> Username: " << member->getUsername() << "\n";
            cout << "> Full name: " << member->getFullName() << "\n";
            cout << "> Phone number: " << member->getPhoneNumber() << "\n";
            cout << "> Email: " << member->getEmail() << "\n";
            cout << "> Home address: " << member->getHomeAddress() << "\n";
            cout << "> Skills: ";
            for (const string& skill : member->getSkills()) {
                cout << skill << " ";
            }
            cout << "\n";
            cout << "> Availability: ";
            for (const string& period : member->getAvailability()) {
                cout << period << " ";
            }
            cout << "\n\n";
        }
    }
}

Member* NonMember::registerMember(string username, string fullName, string password, string phoneNumber, string email, string homeAddress, vector<string> skills, vector<string> availability) {
    Member* new_member = new Member(username, fullName, password, phoneNumber, email, homeAddress, skills, availability);
    return new_member;
}

void System::addMember(Member* member) {
    members.push_back(member);
}

vector<Member*> System::getMembers() {
    return members;
}

Admin::Admin(string username, string password)
    : username(username), password(password) {}

bool Admin::login(string username, string password) {
    return this->username == username && this->password == password;
}

void Admin::resetMemberPassword(Member* member, string newPassword) {
    member->setPassword(newPassword);
}

int main() {
    System system;

    // Create some Member objects and add them to the vector
    vector<string> availability1 = {"Monday morning", "Tuesday afternoon"};
    Member member1("username1", "full name1", "password1", "phone number1", "email1", "home address1", {"cleaning", "reading"}, availability1);

    // Create a NonMember instance
    NonMember non_member;

    // Non-member views all supporters' details
    cout << "Non-member views all supporters' details:\n";
    non_member.viewSupporters();

    // Non-member registers to become a member
    cout << "Non-member registers to become a member:";
    Member* new_member = non_member.registerMember("username4", "full name4", "password4", "phone number4", "email4", "home address4", {}, {});

    // Print the new member's details
    cout << "\nNew member's details:\n";
    cout << "> Username: " << new_member->getUsername() << "\n";
    cout << "> Full name: " << new_member->getFullName() << "\n\n";
    // Print other details...

    // Non-member views all supporters' details again
    cout << "Non-member views all supporters' details again:\n";
    non_member.viewSupporters();

    // Create an Admin object
    Admin admin("adminUsername", "adminPassword");

    // Print the member's username and password before the change
    cout << "Before password change:\n";
    cout << "> Username: " << member1.getUsername() << "\n";
    cout << "> Password: " << member1.getPassword() << "\n\n";

    // Admin logs in and changes the member's password
    if (admin.login("adminUsername", "adminPassword")) {
        admin.resetMemberPassword(&member1, "newPassword");
    }

    // Print the member's username and password after the change
    cout << "After password change:\n";
    cout << "> Username: " << member1.getUsername() << "\n";
    cout << "> Password: " << member1.getPassword() << "\n\n";

    return 0;
}

