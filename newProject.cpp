#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

#include "Member.h"
#include "NonMember.h"
#include "System.h"
#include "Admin.h"

vector<Member*> System::members;

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
int Member::getPointsPerHour() { return pointsPerHour; }
float Member::getMinHostRating() { return minHostRating; }
bool Member::getRequestAccepted() { return requestAccepted; }

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

void Member::setPointsPerHour(int points) { 
    pointsPerHour = points; 
}

void Member::setMinHostRating(float rating) { 
    minHostRating = rating; 
}

void Member::setRequestAccepted(bool status) { requestAccepted = status; }

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
void Member::topUpPoints(int cash, string inputPassword) {
    if (password == inputPassword) {
        credit_points += cash;
    } else {
        cout << "Incorrect password. Cannot authorize transaction.\n";
    }
}

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

// Method to list availability
void Member::listAvailability(vector<string> newAvailability, int newPointsPerHour, float newMinHostRating) {
    availability = newAvailability;
    pointsPerHour = newPointsPerHour;
    minHostRating = newMinHostRating;
}

// Method to unlist availability
void Member::unlistAvailability() {
    availability.clear();
    pointsPerHour = 0;
    minHostRating = 0;
}

// Method to book a supporter
bool Member::bookSupporter(Member* supporter) {
    if (credit_points >= supporter->getPointsPerHour() && hostRating >= supporter->getMinHostRating()) {
        credit_points -= supporter->getPointsPerHour();
        return true;  // Booking successful
    } else {
        return false;  // Not enough points or host rating too low
    }
}

// Method to view all requests for their skills
void Member::viewRequests(vector<Member*> requests) {
    for (Member* request : requests) {
        if (find(skills.begin(), skills.end(), request->getSkills()[0]) != skills.end()) {
            cout << "Request from: " << request->getUsername() << "\n";
            cout << "Host rating: " << request->getHostRating() << "\n";
        }
    }
}

// Method to accept or reject a request
bool Member::respondToRequest(Member* request, bool accept) {
    if (requestAccepted) {
        cout << "Cannot cancel because the request is already accepted.\n";
        return false;
    } else {
        if (accept) {
            // Add code here to handle accepting the request
            requestAccepted = true;
            return true;
        } else {
            // Add code here to handle rejecting the request
            return false;
        }
    }
}

// Method to block a member
void Member::blockMember(Member* member) {
    blockedMembers.push_back(member);
}

// Method to check if a member is blocked
bool Member::isBlocked(Member* member) {
    return std::find(blockedMembers.begin(), blockedMembers.end(), member) != blockedMembers.end();
}

Admin::Admin(string username, string password)
    : username(username), password(password) {}

bool Admin::login(string username, string password) {
    return this->username == username && this->password == password;
}

void Admin::resetMemberPassword(Member* member, string newPassword) {
    member->setPassword(newPassword);
}

// Method to search for all available suitable supporters for a specified city
vector<Member*> System::searchSupporters(string city) {
    vector<Member*> suitableSupporters;
    for (Member* member : members) {
        if (member->getHomeAddress() == city && member->isAvailable()) {
            suitableSupporters.push_back(member);
        }
    }
    return suitableSupporters;
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
    testMember.topUpPoints(20, "testPass");
    cout << "After topping up 20 points with cash: " << testMember.getCreditPoints() << "\n";

    // Create two Member objects for testing
    Member hostMember("hostUser", "hostName", "hostPass", "1234567890", "host@email.com", "123 Host St", {"cooking", "cleaning"}, {"Monday", "Tuesday"});
    Member supporterMember("supporterUser", "supporterName", "supporterPass", "0987654321", "supporter@email.com", "123 Supporter St", {"cleaning", "gardening"}, {"Wednesday", "Thursday"});

    // Test the rating system
    hostMember.rateSupporter(&supporterMember, 4.5);
    cout << "\nSupporter's skill rating after being rated by host: " << supporterMember.getSkillRating() << "\n";

    supporterMember.rateHost(&hostMember, 4.0);
    cout << "Host's host rating after being rated by supporter: " << hostMember.getHostRating() << "\n";

    // Test the availability listing feature
    testMember.listAvailability({"Wednesday", "Thursday"}, 5, 4.0);
    cout << "\nAfter listing availability:\n";
    cout << "> Availability: ";
    for (const string& period : testMember.getAvailability()) {
        cout << period << " ";
    }
    cout << "\n";
    cout << "> Points per hour: " << testMember.getPointsPerHour() << "\n";
    cout << "> Minimum host rating: " << testMember.getMinHostRating() << "\n";

    testMember.unlistAvailability();
    cout << "After unlisting availability:\n";
    cout << "> Availability: ";
    for (const string& period : testMember.getAvailability()) {
        cout << period << " ";
    }
    cout << "\n";
    cout << "> Points per hour: " << testMember.getPointsPerHour() << "\n";
    cout << "> Minimum host rating: " << testMember.getMinHostRating() << "\n";

     // Test the supporter booking feature
    if (hostMember.bookSupporter(&supporterMember)) {
        cout << "\nBooking successful!\n";
    } else {
        cout << "\nBooking failed.\n";
    }

    // Test the request management feature
    vector<Member*> requests = {&hostMember};  // Replace with actual requests
    supporterMember.viewRequests(requests);
    if (supporterMember.respondToRequest(&hostMember, false)) {
        cout << "\nRequest accepted.\n";
    } else {
        cout << "\nRequest rejected.\n";
    }

    // Create two Member objects for testing
    Member member2("user2", "name2", "pass2", "0987654321", "email2", "456 St", {"cleaning", "gardening"}, {"Wednesday", "Thursday"});

    // Test the blocking feature
    member1.blockMember(&member2);
    if (member1.isBlocked(&member2)) {
        cout << "Member2 is blocked by Member1.\n";
    } else {
        cout << "Member2 is not blocked by Member1.\n";
    }

    return 0;
}