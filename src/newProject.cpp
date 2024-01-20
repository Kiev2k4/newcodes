#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <regex>
#include <numeric>
using namespace std;

#include "../include/Member.h"
#include "../include/NonMember.h"
#include "../include/System.h"
#include "../include/Admin.h"

const int REGISTRATION_FEE = 20;
const int CREDIT_POINTS_PER_DOLLAR = 1;

vector<Member*> System::members;
vector<string> split(const string& s, char delimiter);  // Function declaration

// Now define the methods
Member::Member(string username, string fullName, string password, string phoneNumber, string email, string homeAddress, vector<string> skills, vector<pair<string, pair<string, pair<string, string>>>> availability, string city)
    : username(username), fullName(fullName), password(password), phoneNumber(phoneNumber), email(email), homeAddress(homeAddress), skills(skills), availability(availability), city(city) {
}

string Member::getUsername() { return username; }
string Member::getFullName() { return fullName; }
string Member::getPassword() { return password; }
string Member::getPhoneNumber() { return phoneNumber; }
string Member::getEmail() { return email; }
string Member::getHomeAddress() { return homeAddress; }
vector<string> Member::getSkills() { return skills; }
vector<pair<string, pair<string, pair<string, string>>>> Member::getAvailability() { return availability; }
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

void Member::setAvailability(vector<pair<string, pair<string, pair<string, string>>>> newAvailability) {
    availability = newAvailability;
}

void Member::setPointsPerHour(int newPointsPerHour) { 
    pointsPerHour = newPointsPerHour; 
}

void Member::setMinHostRating(float newMinHostRating) { 
    minHostRating = newMinHostRating; 
}

void Member::setRequestAccepted(bool status) { requestAccepted = status; }

void Member::setCity(string newCity) {
    city = newCity;
}

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
                cout << skill << ", ";
            }
            cout << "\n";
            cout << "> Availability: ";
            for (const auto& slot : member->getAvailability()) {
                cout << slot.first << " - " << slot.second.first << " from " << slot.second.second.first << " to " << slot.second.second.second << ", ";
            }
            cout << "\n";
            cout << "> Points per hour: " << member->getPointsPerHour() << "\n";
            cout << "> Minimum host rating: " << member->getMinHostRating() << "\n";
            cout << "> City: " << member->getCity() << "\n\n";
            cout << "> Host Rating: " << member->getHostRating() << "\n";
            cout << "> Supporter Rating: " << member->getSupporterRating() << "\n";
            // Display the average skill ratings
            cout << "> Skill Ratings: ";
            for (const string& skill : member->getSkills()) {
                float avgRating = member->getAverageSkillRating(skill);
                cout << skill << " (average rating: " << (avgRating != 0.0 ? to_string(avgRating) : "not available") << "), ";
            }
            cout << "\n";
        }
    }
}

Member* NonMember::registerMember(string username, string fullName, string password, string phoneNumber, string email, string homeAddress, vector<string> skills, vector<pair<string, pair<string, pair<string, string>>>> availability, string city) {
    char acceptFee;
    // Add code here to get skills from the user
    string skillsInput;
    do {
        cout << "Enter your skills (format: skill1, skill2, skill3): ";
        getline(cin, skillsInput);
    } while (skillsInput.empty());
    vector<string> skillsList = split(skillsInput, ',');
    while (true) {
        cout << "There is an initial entry fee of $" << REGISTRATION_FEE << " to register as a member. Do you accept this (y/n)? ";
        cin >> acceptFee;
        if (acceptFee == 'y' || acceptFee == 'Y' || acceptFee == 'n' || acceptFee == 'N') {
            break;
        } else {
            cout << "Invalid input. Please enter 'y' or 'n'.\n";
        }
    }
    if (acceptFee == 'y' || acceptFee == 'Y') {
        cout << "You have been charged $20 for the registration fee.\n";
        if (city == "Ha Noi" || city == "Sai Gon") {
            Member* newMember = new Member(username, fullName, password, phoneNumber, email, homeAddress, skillsList, availability, city);
            newMember->setCreditPoints(REGISTRATION_FEE * CREDIT_POINTS_PER_DOLLAR);  // Use the constants here
            System::addMember(newMember);  // Add the new member to the system
            System::saveData();
            return newMember;
        } else {
            cout << "Registration failed. The application is only available to users in Ha Noi and Sai Gon.\n";
            return nullptr;
        }
    } else {
        cout << "Registration aborted.\n";
        return nullptr;
    }
}

void System::addMember(Member* member) {
    members.push_back(member);
}

vector<Member*> System::getMembers() {
    return members;
}

Member* System::findMemberByUsername(string username) {
    for (Member* member : members) {
        if (member->getUsername() == username) {
            return member;
        }
    }
    return nullptr;  // Return nullptr if no member with the given username is found
}

bool Member::login(string inputUsername, string inputPassword) {
    return username == inputUsername && password == inputPassword;
}

void Member::viewInformation() {
    cout << "> Username: " << username << "\n";
    cout << "> Full Name: " << fullName << "\n";
    cout << "> Phone Number: " << phoneNumber << "\n";
    cout << "> Email: " << email << "\n";
    cout << "> Home Address: " << homeAddress << "\n";
    cout << "> Credit Points: " << creditPoints << "\n";
    // Display the skills
    cout << "> Skills: ";
    for (const string& skill : skills) {
        cout << skill << ", ";
    }
    cout << "\n";
    cout << "> Availability: ";
    for (const auto& slot : availability) {
        cout << slot.first << " - " << slot.second.first << " from " << slot.second.second.first << " to " << slot.second.second.second << ", ";
    }
    cout << "\n";
    cout << "> Points per hour: " << pointsPerHour << "\n";
    cout << "> Minimum host rating: " << minHostRating << "\n";
    cout << "> City: " << city << "\n";
    cout << "> Host Rating: " << this->getHostRating() << "\n";
    cout << "> Supporter Rating: " << this->getSupporterRating() << "\n";
    
    // Display the average skill ratings
    cout << "> Skill Ratings: ";
    for (const string& skill : skills) {
        float avgRating = getAverageSkillRating(skill);
        cout << skill << " (average rating: " << (avgRating != 0.0 ? to_string(avgRating) : "not available") << "), ";
    }
    cout << "\n";
}

// Getter and setter for credit points
int Member::getCreditPoints() { return creditPoints; }
void Member::setCreditPoints(int points) { creditPoints = points; }

// Method to earn points by helping others
void Member::earnPoints(int points) { creditPoints += points; }

// Method to use points to book help from other members
bool Member::usePoints(int points) {
    if (creditPoints >= points) {
        creditPoints -= points;
        return true;  // Booking successful
    } else {
        return false;  // Not enough points
    }
}

// Method to top up points with cash
void Member::topUpPoints(int cash, string inputPassword) {
    if (password == inputPassword) {
        creditPoints += cash * CREDIT_POINTS_PER_DOLLAR;  // Use the constant here
        this->setCreditPoints(creditPoints);
        System::saveData();
        cout << "Top up successfully. Your credit points: " << creditPoints;
    } else {
        cout << "Incorrect password. Cannot authorize transaction.\n";
    }
}

// Getter and setter for ratings
float Member::getAverageSkillRating(const string& skill) {
    if (skillRatings.count(skill) > 0) {
        return skillRatings[skill].first / skillRatings[skill].second;
    } else {
        return 0.0;  // Default value
    }
}
void Member::addSkillRating(const string& skill, float rating) {
    if (skillRatings.count(skill) > 0) {
        skillRatings[skill].first += rating;
        skillRatings[skill].second++;
    } else {
        skillRatings[skill] = make_pair(rating, 1);
    }
}
void Member::setAverageSkillRating(const string& skill, float averageRating, int count) {
    if (skillRatings.count(skill) > 0) {
        skillRatings[skill].first = averageRating * count;
        skillRatings[skill].second = count;
    } else {
        skillRatings[skill] = make_pair(0.0, 0);
    }
}
int Member::getSkillRatingCount(const string& skill) {
    return skillRatings[skill].second;
}

float Member::getSupporterRating() { return this->averageSupporterRating; }
void Member::addSupporterRating(float rating) { 
    supporterRatings.push_back(rating);
    supporterRatingCount++;
    averageSupporterRating = getAverage(supporterRatings); 
}
void Member::setAverageSupporterRating(float rating, int count){ 
    this->averageSupporterRating = rating;
    this->supporterRatingCount = count; 
}
int Member::getSupporterRatingCount(){
    return supporterRatingCount;
}

float Member::getHostRating() { return this->averageHostRating; }
void Member::addHostRating(float rating) { 
    hostRatings.push_back(rating);
    hostRatingCount++;
    averageHostRating = getAverage(hostRatings); 
}
void Member::setAverageHostRating(float rating, int count){ 
    this->averageHostRating = rating;
    this->hostRatingCount = count; 
}
int Member::getHostRatingCount(){
    return hostRatingCount;
}

// Method for a member (as a host) to rate their supporter
void Member::rateSupporter(Member* supporter, float rating) {
    supporter->addSupporterRating(rating);
}

//Method for a member (as a host) to rate the skills of their supporters
void Member::rateSkill(Member* supporter, const string& skill, float rating){
    supporter->addSkillRating(skill, rating);
}

// Method for a member (as a supporter) to rate their host
void Member::rateHost(Member* host, float rating) {
    host->addHostRating(rating);
}

float Member::getAverage(std::vector<float>& ratings) {
    if (ratings.empty()) return 0.0;
    float sum = std::accumulate(ratings.begin(), ratings.end(), 0.0);
    return sum / ratings.size();
}

// Method to list availability
void Member::listAvailability(vector<pair<string, pair<string, pair<string, string>>>> newAvailability, int newPointsPerHour, float newMinHostRating) {
    availability = newAvailability;
    setPointsPerHour(newPointsPerHour);
    setMinHostRating(newMinHostRating);
}

// Method to unlist availability
void Member::unlistAvailability() {
    availability.clear();
    pointsPerHour = 0;
    minHostRating = 0;
}

// Method to book a supporter
bool Member::bookSupporter(Member* supporter) {
    if (supporter->isBlocked(this)) {
        return false;  // Current member is blocked by the supporter
    } else if (creditPoints >= supporter->getPointsPerHour() && this->getHostRating() >= supporter->getMinHostRating()) {
        creditPoints -= supporter->getPointsPerHour();
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
    System::saveData();
}

vector<Member*>& Member::getBlockedMembers(){ return blockedMembers; }

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
    System::saveData();
}

// Method to search for all available suitable supporters for a specified city
vector<Member*> System::searchSupporters(Member* currentMember, string city, int creditPoints, float hostRating) {
    vector<Member*> suitableSupporters;
    for (Member* member : members) {
        if (!member->isBlocked(currentMember) && member->getCity() == city && member->getPointsPerHour() <= creditPoints && member->getMinHostRating() <= hostRating) {
            suitableSupporters.push_back(member);
        }
    }
    return suitableSupporters;
}

pair<string, string> System::loadAdminData() {
    ifstream inFile("../data/adminData.txt");
    if (!inFile) {
        cout << "Error: Could not open file for reading.\n";
        return {"", ""};
    }
    string username, password;
    inFile >> username >> password;
    inFile.close();
    return {username, password};
}

void System::saveData() {
    ofstream outFile("../data/data.txt", ios::trunc);
    if (!outFile) {
        cout << "Error: Could not open file for writing.\n";
        return;
    }
    outFile << "username|fullName|password|phoneNumber|email|homeAddress|city|creditPoints|skills|availability|pointsPerHour|minHostRating|blockedMembers|hostRating,hostRatingCount|supporterRating,supporterRatingCount|skill:skillRating,skillRatingCount" << "\n";
    for (Member* member : members) {
        outFile << member->getUsername() << "|"
                << member->getFullName() << "|"
                << member->getPassword() << "|"
                << member->getPhoneNumber() << "|"
                << member->getEmail() << "|"
                << member->getHomeAddress() << "|"
                << member->getCity() << "|"
                << member->getCreditPoints() << "|"; // Save the credit points
        // Save the skills
        for (const string& skill : member->getSkills()) {
            outFile << skill << ",";
        }
        outFile << "|";
        for (const auto& slot : member->getAvailability()) {
            outFile << slot.first << "," << slot.second.first << "," << slot.second.second.first << "," << slot.second.second.second << ";";
        }
        outFile << "|";
        outFile << member->getPointsPerHour() << "|";
        outFile << member->getMinHostRating() << "|";
        for (Member* blockedMember : member->getBlockedMembers()) {
            outFile << blockedMember->getUsername() << ",";
        }
        outFile << "|";
        outFile << member->getHostRating() << "," << member->getHostRatingCount() << "|";  // Save the average host rating and the count of ratings
        outFile << member->getSupporterRating() << "," << member->getSupporterRatingCount() << "|";  // Save the average supporter rating and the count of ratings
        // Save the average skill ratings
        for (const string& skill : member->getSkills()) {
            outFile << skill << ":" << member->getAverageSkillRating(skill) << "," << member->getSkillRatingCount(skill) << ";";
        }
        outFile << "\n";  // End of member data
    }
    outFile.close();
}

void System::loadData() {
    members.clear();
    ifstream inFile("../data/data.txt");
    if (!inFile) {
        cout << "Error: Could not open file for reading.\n";
        return;
    }
    string line;
    getline(inFile, line);// Skip the first line

    // First pass: Create all the Member objects and store the blocked member usernames for later
    map<Member*, std::vector<std::string>> blockedUsernamesMap;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string username, fullName, password, phoneNumber, email, homeAddress, city, skills, availability;
        int creditPoints, pointsPerHour;
        float minHostRating;
         // Variable to store the credit points
        getline(ss, username, '|');
        getline(ss, fullName, '|');
        getline(ss, password, '|');
        getline(ss, phoneNumber, '|');
        getline(ss, email, '|');
        getline(ss, homeAddress, '|');
        getline(ss, city, '|');
        ss >> creditPoints; // Load the credit points
        ss.ignore(numeric_limits<streamsize>::max(), '|');

        // Load the skills
        getline(ss, skills, '|');
        vector<string> skillVector = split(skills, ',');
        // Load the availability
        getline(ss, availability, '|');

        vector<pair<string, pair<string, pair<string, string>>>> availabilityVector;
        stringstream ss_availability(availability);
        string slot;

        while (getline(ss_availability, slot, ';')) {
            stringstream ss_slot(slot);
            string day, skill, startTime, endTime;
            getline(ss_slot, day, ',');
            getline(ss_slot, skill, ',');
            getline(ss_slot, startTime, ',');
            getline(ss_slot, endTime, ',');

            availabilityVector.push_back(make_pair(day, make_pair(skill, make_pair(startTime, endTime))));
        }

        ss >> pointsPerHour;
        ss.ignore(numeric_limits<streamsize>::max(), '|');

        string minHostRatingStr;
        getline(ss, minHostRatingStr, '|');
        if (!minHostRatingStr.empty()) {
            minHostRating = stof(minHostRatingStr);
        } else {
            minHostRating = 0;  // Default value
        }

        Member* newMember = new Member(username, fullName, password, phoneNumber, email, homeAddress, skillVector, availabilityVector, city);
        newMember->setCreditPoints(creditPoints); // Set the credit points for the member
        newMember->setPointsPerHour(pointsPerHour);
        newMember->setMinHostRating(minHostRating);
        members.push_back(newMember);

        // Store the blocked member usernames for later
        string blockedMembersStr;
        getline(ss, blockedMembersStr, '|');
        vector<string> blockedMembersUsernames = split(blockedMembersStr, ',');
        blockedUsernamesMap[newMember] = blockedMembersUsernames;

        string hostRatingStr, supporterRatingStr, skillRatingStr;
        string hostRatingCountStr, supporterRatingCountStr;

        getline(ss, hostRatingStr, ',');
        getline(ss, hostRatingCountStr, '|');
        if (!hostRatingStr.empty() && !hostRatingCountStr.empty()) {
            float hostRating = stof(hostRatingStr);
            int hostRatingCount = stoi(hostRatingCountStr);
            newMember->setAverageHostRating(hostRating, hostRatingCount);
        }

        getline(ss, supporterRatingStr, ',');
        getline(ss, supporterRatingCountStr, '|');
        if (!supporterRatingStr.empty() && !supporterRatingCountStr.empty()) {
            float supporterRating = stof(supporterRatingStr);
            int supporterRatingCount = stoi(supporterRatingCountStr);
            newMember->setAverageSupporterRating(supporterRating, supporterRatingCount);
        }

        getline(ss, skillRatingStr, '|');
        if (!skillRatingStr.empty()) {
            stringstream ss_skillRating(skillRatingStr);
            string skillRating;
            while (getline(ss_skillRating, skillRating, ';')) {
                stringstream ss_skill(skillRating);
                string skill;
                getline(ss_skill, skill, ':');
                string averageRatingStr, ratingCountStr;
                getline(ss_skill, averageRatingStr, ',');
                getline(ss_skill, ratingCountStr, ':');
                if (!averageRatingStr.empty() && !ratingCountStr.empty()) {
                    float averageRating = stof(averageRatingStr);
                    int ratingCount = stoi(ratingCountStr);
                    newMember->setAverageSkillRating(skill, averageRating, ratingCount);
                }
            }
        }
    }

    // Second pass: Set up the blocked relationships
    for (auto& pair : blockedUsernamesMap) {
        Member* member = pair.first;
        vector<string>& blockedMembersUsernames = pair.second;
        for (const string& blockedMemberUsername : blockedMembersUsernames) {
            Member* blockedMember = findMemberByUsername(blockedMemberUsername);
            if (blockedMember) {
                member->blockMember(blockedMember);
            }
        }
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

bool isValidEmail(string email) {
    int atPosition = email.find('@');
    int dotPosition = email.find('.', atPosition);
    return atPosition != string::npos && dotPosition != string::npos;
}

bool isValidName(string name) {
    for (char c : name) {
        if (!isalpha(c) && !isspace(c)) {
            return false;
        }
    }
    return true;
}

bool isValidTime(const string& str) {
    regex r("^([0-1]?[0-9]|2[0-3]):[0-5][0-9]$");
    return regex_match(str, r);
}

int main() {
    System system;

    // Load data from file when the program starts
    system.loadData();

    // Load admin data
    pair<string, string> adminData = system.loadAdminData();
    Admin admin(adminData.first, adminData.second);

    cout << "EEET2482/COSC2082 ASSIGNMENT\n";
    cout << "\"TIME BANK\" APPLICATION\n";
    cout << "Instructor: Mr. Tran Duc Linh\n";
    cout << "Group: Group No.15\n";
    cout << "s3978175, Nguyen Pham Tan Hau\n";
    cout << "s3977739, Lee Jae Sung\n";
    cout << "s3914412, Nguyen Duong Truong Thinh\n";
    cout << "s3986423, Nguyen Huu Quoc Huy\n";

    int choice;
    do {
        cout << "Use the app as 1. Guest 2. Member 3. Admin\n";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();  // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore the rest of the line
            choice = 0;  // Set choice to an invalid value so the loop continues
        }
    } while (choice < 1 || choice > 3);

    string detectedUsername;
    switch (choice) {
        case 1: // Guest
        {
            NonMember guest;
            int guestChoice;
            do {
                cout << "\nThis is your menu:\n";
                cout << "0. Exit\n";
                cout << "1. View Supporters\n";
                cout << "2. Register as Member\n";
                cout << "Enter your choice: ";
                cin >> guestChoice;
                while(cin.fail() || guestChoice < 0 || guestChoice > 2) {
                    cin.clear(); // clear input buffer to restore cin to a usable state
                    cin.ignore(INT_MAX, '\n'); // ignore last input
                    cout << "You can only enter numbers 0 - 2. Please enter a valid choice: ";
                    cin >> guestChoice;
                }
                switch (guestChoice) {
                    case 1:  // View Supporters
                        guest.viewSupporters();
                        break;
                    case 2:  // Register as Member
                        string username, fullName, password, phoneNumber, email, homeAddress, city;
                        vector<string> skills;
                        bool validEmail = false;
                        bool validName = false;
                        bool validUsername = false;
                        // Add code here to get the necessary information from the user
                        while (!validUsername) {
                            cout << "Enter username: ";
                            cin.ignore();
                            getline(cin, username);
                            for (Member* member : System::getMembers()) {
                                if (member->getUsername() == username) {
                                    cout << "Registration failed. The username " << username << " is already taken.\n";
                                    validUsername = false;
                                    break;
                                } else {
                                    validUsername = true;
                                }
                            }
                        }
                        //Enter and check fullName
                        while (!validName) {
                            cout << "Enter full name: ";
                            getline(cin, fullName);
                            if (isValidName(fullName)) {
                                validName = true;
                            } else {
                                cout << "The full name " << fullName << " is not valid. Please enter a valid full name.\n";
                            }
                        }
                        cout << "Enter password: ";
                        getline(cin, password);
                        //Enter and check phone number format
                        do {
                            cout << "Enter phone number: ";
                            cin >> phoneNumber;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore the newline character
                        } while (!all_of(phoneNumber.begin(), phoneNumber.end(), ::isdigit));
                        //check email format
                        while (!validEmail) {
                            cout << "Enter email: ";
                            getline(cin, email);
                            if (isValidEmail(email)) {
                                validEmail = true;
                            } else {
                                cout << "The email " << email << " is not valid. Please enter a valid email.\n";
                            }
                        }
                        cout << "Enter home address: ";//home address input
                        getline(cin, homeAddress);
                        do {
                            cout << "Enter city (Ha Noi or Sai Gon): ";
                            getline(cin, city);
                            if (city != "Ha Noi" && city != "Sai Gon") {
                                cout << "This application is only available to users in Ha Noi or Sai Gon.\n";
                            }
                        } while (city != "Ha Noi" && city != "Sai Gon");
                        // Add code here to get skills and availability from the user
                        vector<pair<string, pair<string, pair<string, string>>>> availability = {};
                        Member* newMember = guest.registerMember(username, fullName, password, phoneNumber, email, homeAddress, skills, availability, city);
                        if (newMember != nullptr) {
                            cout << "> Registration successful! Welcome, " << newMember->getFullName() << "!\n\n";
                        }
                        break;
                }
            } while (guestChoice != 0);
            break;
        }
        case 2:  // Member
        {
            int memberLoginAttempts = 0;
            while (memberLoginAttempts < 3)
            {
                string username, password;
                cout << "Enter username: ";
                cin.ignore();
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                Member* member = system.findMemberByUsername(username);
                if (member != nullptr && member->login(username, password)) 
                {
                    cout << "Login successful! Welcome, " << member->getFullName() << "!\n\n";
                    int memberChoice;
                    do {
                        cout << "\nThis is your menu:\n";
                        cout << "0. Exit\n";
                        cout << "1. View Information\n";
                        cout << "2. List Availability (brand new)\n";
                        cout << "3. Unlist Availability\n";
                        cout << "4. Search Supporters\n";
                        cout << "5. Book a Supporter\n";
                        cout << "6. View Requests\n";
                        cout << "7. Respond to a Request\n";
                        cout << "8. Block a Member\n";
                        cout << "9. Rate a Supporter\n";
                        cout << "10. Rate a Host\n";
                        cout << "11. Top up Credit Points\n";
                        cout << "Enter your choice: ";
                        cin >> memberChoice;
                        while(cin.fail() || memberChoice < 0 || memberChoice > 11) {
                            cin.clear(); // clear input buffer to restore cin to a usable state
                            cin.ignore(INT_MAX, '\n'); // ignore last input
                            cout << "You can only enter numbers 0 - 10. Please enter a valid choice: ";
                            cin >> memberChoice;
                        }
                        switch (memberChoice) {
                            case 1:  // View Information
                                member->viewInformation();
                                break;
                            case 2:  // List Availability
                            {
                                vector<pair<string, pair<string, pair<string, string>>>> newAvailability;
                                int newPointsPerHour;
                                float newMinHostRating;
                                string day, skill, startTime, endTime;
                                cout << "Enter the number of availability slots: ";
                                int numSlots;
                                while (!(cin >> numSlots)) {
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    cout << "Invalid input. Please enter a number: ";
                                }
                                for (int i = 0; i < numSlots; i++) {
                                    do {
                                        cout << "Enter day of the week for slot " << i+1 << " (e.g., Monday): ";
                                        if (i==0)
                                        {
                                            cin.ignore();
                                        }
                                        getline(cin, day);
                                    } while (day != "Monday" && day != "Tuesday" && day != "Wednesday" && day != "Thursday" && day != "Friday" && day != "Saturday" && day != "Sunday");
                                    do {
                                        cout << "Enter skill for slot " << i+1 << " (";
                                        for (const string& skill : member->getSkills()) {
                                            cout << skill << ", ";
                                        }
                                        cout << "): ";
                                        getline(cin, skill);
                                    } while (find(member->getSkills().begin(), member->getSkills().end(), skill) == member->getSkills().end());
                                    do {
                                        cout << "Enter start time for slot " << i+1 << " (format: HH:MM): ";
                                        getline(cin, startTime);
                                    } while (!isValidTime(startTime));
                                    do {
                                        cout << "Enter end time for slot " << i+1 << " (format: HH:MM): ";
                                        getline(cin, endTime);
                                    } while (!isValidTime(endTime));
                                    newAvailability.push_back(make_pair(day, make_pair(skill, make_pair(startTime, endTime))));
                                }
                                cout << "Enter minimum required host-rating score (optional, press Enter to skip): ";
                                string minHostRatingStr;
                                getline(cin, minHostRatingStr);
                                if (!minHostRatingStr.empty()) {
                                    newMinHostRating = stof(minHostRatingStr);
                                }

                                cout << "Enter points required per hour: ";
                                cin >> newPointsPerHour;

                                member->listAvailability(newAvailability, newPointsPerHour, newMinHostRating);
                                cout << "Availability listed successfully!\n";
                                system.saveData();
                                break;
                            }
                            case 3:  // Unlist Availability
                            {
                                member->unlistAvailability();
                                cout << "Availability unlisted successfully!\n";
                                system.saveData();  // Remember to save the data after making changes
                                break;
                            }
                            case 4:  // Search Supporters
                            {
                                string city;
                                int creditPoints;
                                float hostRating;
                                cout << "Enter your city: ";
                                cin.ignore();
                                getline(cin, city);
                                creditPoints = member->getCreditPoints();
                                cout << "Your credit points: " << creditPoints << "\n";
                                hostRating = member->getHostRating();
                                cout << "Your host rating: " << hostRating << "\n";
                                vector<Member*> suitableSupporters = system.searchSupporters(member, city, creditPoints, hostRating);
                                cout << "List of suitable supporters: \n";  
                                for (Member* supporter : suitableSupporters)
                                {
                                    supporter->viewInformation();
                                }
                                break;
                            }
                            case 5:  // Book a Supporter
                            {
                                string supporterUsername;
                                cout << "Enter the username of the supporter you want to book: ";
                                cin.ignore();  // Ignore the newline left in the buffer by the previous input operation
                                getline(cin, supporterUsername);
                                // Assuming you have a method to get a member by username
                                Member* supporter = system.findMemberByUsername(supporterUsername);
                                if (supporter) {
                                    if (member->bookSupporter(supporter)) {
                                        cout << "You have successfully booked " << supporterUsername << ".\n";
                                    } else {
                                        cout << "You cannot book this supporter. Either you are blocked by them, or you do not have enough credit points, or your host rating is too low.\n";
                                    }
                                } else {
                                    cout << "No supporter found with the username " << supporterUsername << ".\n";
                                }
                                break;
                            }
                            case 6:  // View Requests
                                // Add your code here...
                                break;
                            case 7:  // Respond to a Request
                                // Add your code here...
                                break;
                            case 8:  // Block a Member
                            {
                                string usernameToBlock;
                                cout << "Enter the username of the member you want to block: ";
                                cin.ignore();
                                getline(cin, usernameToBlock);
                                // Assuming you have a method to get a member by username
                                Member* memberToBlock = system.findMemberByUsername(usernameToBlock);
                                if (memberToBlock) {
                                    member->blockMember(memberToBlock);
                                    cout << "You have successfully blocked " << usernameToBlock << ".\n";
                                } else {
                                    cout << "No member found with the username " << usernameToBlock << ".\n";
                                }
                                break;
                            }
                            case 9:  // Rate a Supporter
                            {
                                Member* supporterToRate = nullptr;
                                int supporterRating, skillRating;
                                string supporterUsername;
                                while (supporterToRate == nullptr) {
                                    cout << "Enter the name of the supporter you want to rate: ";
                                    cin.ignore();
                                    getline(cin, supporterUsername);
                                    supporterToRate = system.findMemberByUsername(supporterUsername);
                                    if (supporterToRate == nullptr) {
                                        cout << "No member found with the username " << supporterUsername << ". Please try again.\n";
                                    }
                                }
                                while (true) {
                                    cout << "Enter a rating for the supporter (1-5): ";
                                    cin >> supporterRating;
                                    if (cin.fail()) {
                                        cin.clear();  // clear the error state of the cin object
                                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // ignore the rest of the line
                                        cout << "Invalid input. Please enter a number between 1 and 5.\n";
                                    } else if (supporterRating < 1 || supporterRating > 5) {
                                        cout << "Invalid supporter rating. Please enter a number between 1 and 5.\n";
                                    } else {
                                        break;  // exit the loop if the input is valid
                                    }
                                }
                                member->rateSupporter(supporterToRate, supporterRating);
                                cout << "New supporter rating from " << member->getUsername() << " to " << supporterToRate->getUsername() << " is " << supporterRating << ", which makes " << supporterToRate->getUsername() << " average supporter rating become " << supporterToRate->getSupporterRating() << "\n";

                                //Must be fixed
                                for (const string& skill : supporterToRate->getSkills()){
                                    while (true) {
                                        cout << "Enter a skill rating for the supporter for " << skill << " (1-5): ";
                                        cin >> skillRating;
                                        if (cin.fail()) {
                                            cin.clear();  // clear the error state of the cin object
                                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // ignore the rest of the line
                                            cout << "Invalid input. Please enter a number between 1 and 5.\n";
                                        } else if (skillRating < 1 || skillRating > 5) {
                                            cout << "Invalid rating. Please enter a number between 1 and 5.\n";
                                        } else {
                                            break;  // exit the loop if the input is valid
                                        }
                                    }
                                    member->rateSkill(supporterToRate, skill, skillRating);
                                    cout << "New rating of " << skill << " from " << member->getUsername() << " to " << supporterToRate->getUsername() << " is " << skillRating << ", which makes " << supporterToRate->getUsername() << " average " << skill << " rating become " << supporterToRate->getAverageSkillRating(skill) << "\n";
                                }
                                system.saveData();
                                break;
                            }
                            case 10:  // Rate a Host
                            {
                                Member* hostToRate = nullptr;
                                int hostRating;
                                string hostUsername;
                                while (hostToRate == nullptr) {
                                    cout << "Enter the name of the host you want to rate: ";
                                    cin.ignore();
                                    getline(cin, hostUsername);
                                    hostToRate = system.findMemberByUsername(hostUsername);
                                    if (hostToRate == nullptr) {
                                        cout << "No member found with the username " << hostUsername << ". Please try again.\n";
                                        continue;
                                    }
                                }
                                while (true) {
                                    cout << "Enter a rating for the host (1-5): ";
                                    cin >> hostRating;
                                    if (cin.fail()) {
                                        cin.clear();  // clear the error state of the cin object
                                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // ignore the rest of the line
                                        cout << "Invalid input. Please enter a number between 1 and 5.\n";
                                    } else if (hostRating < 1 || hostRating > 5) {
                                        cout << "Invalid rating. Please enter a number between 1 and 5.\n";
                                    } else {
                                        break;  // exit the loop if the input is valid
                                    }
                                }
                                member->rateHost(hostToRate, hostRating);
                                cout << "New host rating from " << member->getUsername() << " to " << hostToRate->getUsername() << " is " << hostRating << ", which makes " << hostToRate->getUsername() << " average host rating become " << hostToRate->getHostRating() << "\n";
                                system.saveData();
                                break;
                            }
                            case 11:  // Top up Credit Points
                            {
                                int cash;
                                string inputPassword;
                                cout << "Enter the amount of cash you want to top up: ";
                                cin >> cash;
                                // Check if the input is valid
                                while(cin.fail() || cash < 0) {
                                    cin.clear(); // clear input buffer to restore cin to a usable state
                                    cin.ignore(INT_MAX, '\n'); // ignore last input
                                    cout << "You can only enter a positive integer. Please enter a valid amount: ";
                                    cin >> cash;
                                }
                                cout << "Enter your password to authorize the transaction: ";
                                cin.ignore();
                                getline(cin, inputPassword);
                                member->topUpPoints(cash, inputPassword);
                                break;
                            }
                        }
                        if (memberChoice == 0) {
                            return 0;  // This will exit the current function immediately
                        }
                    } while (memberChoice != 0);
                } else {
                    cout << "Login failed. Please check your username and password.\n";
                    memberLoginAttempts++;
                    if (memberLoginAttempts == 3) {
                        cout << "You have exceeded the maximum number of login attempts. The program will now exit.\n";
                        exit(0);
                    }
                }
            }
            break;
        }
        case 3:  // Admin
        {
            string adminUsername, adminPassword;
            int adminLoginAttempts = 0;
            while (adminLoginAttempts < 3) {
                cout << "Enter admin username: ";
                cin.ignore();
                getline(cin, adminUsername);
                cout << "Enter admin password: ";
                cin >> adminPassword;
                if (admin.login(adminUsername, adminPassword)) {
                    cout << "Login successful! Welcome, admin!\n";
                    break;
                } else {
                    cout << "Login failed. Please check your username and password.\n";
                    adminLoginAttempts++;
                    if (adminLoginAttempts == 3) {
                        cout << "You have exceeded the maximum number of login attempts. The program will now exit.\n";
                        exit(0);
                    }
                }
            }
            int adminChoice;
            do {
                cout << "\nThis is your menu:\n";
                cout << "0. Exit\n";
                cout << "1. Reset member password\n";
                cout << "Enter your choice: ";
                cin >> adminChoice;
                while(cin.fail() || adminChoice < 0 || adminChoice > 1) {
                    cin.clear(); // clear input buffer to restore cin to a usable state
                    cin.ignore(INT_MAX, '\n'); // ignore last input
                    cout << "You can only enter numbers 0 - 1. Please enter a valid choice: ";
                    cin >> adminChoice;
                }
                switch (adminChoice) {
                    case 1:  // Reset member password
                        cout << "Enter the username of the member whose password you want to reset: ";
                        cin >> detectedUsername;
                        Member* member = system.findMemberByUsername(detectedUsername);  // You'll need to implement this method
                        if (member != nullptr) {
                            cout << "Enter the new password: ";
                            string newPassword;
                            cin >> newPassword;
                            admin.resetMemberPassword(member, newPassword);
                            cout << "Password reset successful!\n";
                        } else {
                            cout << "Member not found.\n";
                        }
                        break;
                }
            } while (adminChoice != 0);
            break;
        }
    // Save data to file before the program ends
    system.saveData();

    return 0;
    }
}