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
vector<string> split(const string& s, char delimiter);  // Function declaration

// Now define the methods
Member::Member(string username, string fullName, string password, string phoneNumber, string email, string homeAddress, vector<string> skills, vector<string> availability, string city)
    : username(username), fullName(fullName), password(password), phoneNumber(phoneNumber), email(email), homeAddress(homeAddress), skills(skills), availability(availability), city(city) {
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
string Member::getCity(){ return city; }

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

void Member::setCity(string newCity) {
    city = newCity;
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
            cout << "\n";
            cout << "> City: " << member->getCity() << "\n\n";
        }
    }
}

Member* NonMember::registerMember(string username, string fullName, string password, string phoneNumber, string email, string homeAddress, vector<string> skills, vector<string> availability, string city) {
    if (city == "Ha Noi" || city == "Sai Gon") {
        Member* newMember = new Member(username, fullName, password, phoneNumber, email, homeAddress, skills, availability, city);
        System::addMember(newMember);  // Add the new member to the system
        System::saveData();
        return newMember;
    } else {
        cout << "Registration failed. The application is only available to users in Ha Noi and Sai Gon.\n";
        return nullptr;
    }
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
    cout << "City: " << city << "\n";
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
        if (member->getCity() == city && member->isAvailable()) {
            suitableSupporters.push_back(member);
        }
    }
    return suitableSupporters;
}

void System::saveData() {
    ofstream outFile("data.txt", ios::trunc);
    if (!outFile) {
        cout << "Error: Could not open file for writing.\n";
        return;
    }
    for (Member* member : members) {
        outFile << member->getUsername() << "|"
                << member->getFullName() << "|"
                << member->getPassword() << "|"
                << member->getPhoneNumber() << "|"
                << member->getEmail() << "|"
                << member->getHomeAddress() << "|"
                << member->getCity() << "|";
        for (const string& skill : member->getSkills()) {
            outFile << skill << " ";
        }
        outFile << "|";
        for (const string& period : member->getAvailability()) {
            outFile << period << " ";
        }
        outFile << "\n";
    }
    outFile.close();
}

void System::loadData() {
    members.clear();
    ifstream inFile("data.txt");
    if (!inFile) {
        cout << "Error: Could not open file for reading.\n";
        return;
    }
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string username, fullName, password, phoneNumber, email, homeAddress, city, skills, availability;
        getline(ss, username, '|');
        getline(ss, fullName, '|');
        getline(ss, password, '|');
        getline(ss, phoneNumber, '|');
        getline(ss, email, '|');
        getline(ss, homeAddress, '|');
        getline(ss, city, '|');
        getline(ss, skills, '|');
        getline(ss, availability, '|');
        vector<string> skillVector = split(skills, ' ');
        vector<string> availabilityVector = split(availability, ' ');
        Member* newMember = new Member(username, fullName, password, phoneNumber, email, homeAddress, skillVector, availabilityVector, city);
        members.push_back(newMember);
    }
    inFile.close();
}

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    System system;

    // Load data from file when the program starts
    system.loadData();

    cout << "EEET2482/COSC2082 ASSIGNMENT\n";
    cout << "\"TIME BANK\" APPLICATION\n";
    cout << "Instructor: Mr. Tran Duc Linh\n";
    cout << "Group: Group No.\n";
    cout << "sXXXXXXX, Student Name\n";
    cout << "sXXXXXXX, Student Name\n";
    cout << "sXXXXXXX, Student Name\n";
    cout << "sXXXXXXX, Student Name\n";
    cout << "Use the app as 1. Guest 2. Member 3. Admin\n";

    int choice;
    cin >> choice;

    string username;
    switch (choice) {
        case 1:  // Guest
            NonMember guest;
            int guestChoice;
            do {
                cout << "\nThis is your menu:\n";
                cout << "0. Exit\n";
                cout << "1. View Supporters\n";
                cout << "2. Register as Member\n";
                cout << "Enter your choice: ";
                cin >> guestChoice;

                switch (guestChoice) {
                    case 1:  // View Supporters
                        guest.viewSupporters();
                        break;
                    case 2:  // Register as Member
                        string username, fullName, password, phoneNumber, email, homeAddress, city;
                        vector<string> skills, availability;
                        // Add code here to get the necessary information from the user
                        cout << "Enter username: ";
                        cin.ignore();
                        getline(cin, username);
                        cout << "Enter full name: ";
                        getline(cin, fullName);
                        cout << "Enter password: ";
                        getline(cin, password);
                        do {
                            cout << "Enter phone number: ";
                            cin >> phoneNumber;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore the newline character
                        } while (!all_of(phoneNumber.begin(), phoneNumber.end(), ::isdigit));
                        cout << "Enter email: ";
                        getline(cin, email);
                        cout << "Enter home address: ";
                        getline(cin, homeAddress);
                        do {
                            cout << "Enter city (Ha Noi or Sai Gon): ";
                            getline(cin, city);
                            if (city != "Ha Noi" && city != "Sai Gon") {
                                cout << "This application is only available to users in Ha Noi or Sai Gon.\n";
                            }
                        } while (city != "Ha Noi" && city != "Sai Gon");
                        // Add code here to get skills and availability from the user
                        Member* newMember = guest.registerMember(username, fullName, password, phoneNumber, email, homeAddress, skills, availability, city);
                        if (newMember != nullptr) {
                            cout << "> Registration successful! Welcome, " << newMember->getFullName() << "!\n\n";
                        }
                        break;
                }
            } while (guestChoice != 0);
            break;

    // Save data to file before the program ends
    system.saveData();

    return 0;
    }
}