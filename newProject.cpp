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
    float getSkillRating();
    float getSupporterRating();
    float getHostRating();
    vector<string> getSkills();
    vector<string> getAvailability();

    //Setter methods
    void setUsername(string newUsername);
    void setFullName(string newFullName);
    void setPassword(string newPassWord);
    void setPhoneNumber(string newPhoneNumber);
    void setEmail(string newEmail);
    void setHomeAddress(string newHomeAddress);
    void setSkillRating(float rating);
    void setSupporterRating(float rating);
    void setHostRating(float rating);
    void setSkills(vector<string> newSkills);
    void setAvailability(vector<string> newAvailability);

    // Method to check if a member is available
    bool isAvailable();

    bool login(string inputUsername, string inputPassword);

    void viewInformation();

    //Credit points method
    int getCreditPoints();
    void setCreditPoints(int points);
    void earnPoints(int points);
    bool usePoints(int points);
    void topUpPoints(int cash);

    //Rating method
    void rateSupporter(Member* supporter, float rating);
    void rateHost(Member* host, float rating);
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

bool Member::login(string inputUsername, string inputPassword) {
    return username == inputUsername && password == inputPassword;
}

void Member::viewInformation() {
    cout << "Username: " << username << "\n";
    cout << "Full Name: " << fullName << "\n";
    cout << "Phone Number: " << phoneNumber << "\n";
    cout << "Email: " << email << "\n";
    cout << "Home Address: " << homeAddress << "\n";
    cout << "Skills: ";
    for (const string& skill : skills) {
        cout << skill << " ";
    }
    cout << "\n";
    cout << "Availability: ";
    for (const string& period : availability) {
        cout << period << " ";
    }
    cout << "\n";
}

// Getter and setter for credit points
int Member::getCreditPoints() { return credit_points; }
void Member::setCreditPoints(int points) { credit_points = points; }

// Method to earn points by helping others
void Member::earnPoints(int points) { credit_points += points; }

// Method to use points to book help from other members
bool Member::usePoints(int points) {
    if (credit_points >= points) {
        credit_points -= points;
        return true;  // Booking successful
    } else {
        return false;  // Not enough points
    }
}

// Method to top up points with cash
void Member::topUpPoints(int cash) { credit_points += cash; }

// Getter and setter for ratings
float Member::getSkillRating() { return skillRating; }
void Member::setSkillRating(float rating) { skillRating = rating; }

float Member::getSupporterRating() { return supporterRating; }
void Member::setSupporterRating(float rating) { supporterRating = rating; }

float Member::getHostRating() { return hostRating; }
void Member::setHostRating(float rating) { hostRating = rating; }

// Method for a member (as a host) to rate their supporter
void Member::rateSupporter(Member* supporter, float rating) {
    supporter->setSkillRating(rating);
}

// Method for a member (as a supporter) to rate their host
void Member::rateHost(Member* host, float rating) {
    host->setHostRating(rating);
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

    // Create a Member object for testing
    Member testMember("testUser", "testName", "testPass", "1234567890", "test@email.com", "123 Test St", {"cooking", "cleaning"}, {"Monday", "Tuesday"});

    // Test the login feature
    if (testMember.login("testUser", "testPass")) {
        cout << "Login successful!\n";
        testMember.viewInformation();
    } else {
        cout << "Login failed.\n";
    }

    // Test the credit points system
    cout << "\nInitial credit points: " << testMember.getCreditPoints() << "\n";
    testMember.earnPoints(10);
    cout << "After earning 10 points: " << testMember.getCreditPoints() << "\n";
    if (testMember.usePoints(15)) {
        cout << "After using 15 points: " << testMember.getCreditPoints() << "\n";
    } else {
        cout << "Not enough points to book help.\n";
    }
    testMember.topUpPoints(20);
    cout << "After topping up 20 points with cash: " << testMember.getCreditPoints() << "\n";

    // Create two Member objects for testing
    Member hostMember("hostUser", "hostName", "hostPass", "1234567890", "host@email.com", "123 Host St", {"cooking", "cleaning"}, {"Monday", "Tuesday"});
    Member supporterMember("supporterUser", "supporterName", "supporterPass", "0987654321", "supporter@email.com", "123 Supporter St", {"cleaning", "gardening"}, {"Wednesday", "Thursday"});

    // Test the rating system
    hostMember.rateSupporter(&supporterMember, 4.5);
    cout << "\nSupporter's skill rating after being rated by host: " << supporterMember.getSkillRating() << "\n";

    supporterMember.rateHost(&hostMember, 4.0);
    cout << "Host's host rating after being rated by supporter: " << hostMember.getHostRating() << "\n";

    return 0;
}

