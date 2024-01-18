#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
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
    char acceptFee;
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
            Member* newMember = new Member(username, fullName, password, phoneNumber, email, homeAddress, skills, availability, city);
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
    if (creditPoints >= supporter->getPointsPerHour() && hostRating >= supporter->getMinHostRating()) {
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
    System::saveData();
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
    for (Member* member : members) {
        outFile << member->getUsername() << "|"
                << member->getFullName() << "|"
                << member->getPassword() << "|"
                << member->getPhoneNumber() << "|"
                << member->getEmail() << "|"
                << member->getHomeAddress() << "|"
                << member->getCity() << "|"
                << member->getCreditPoints() << "|"; // Save the credit points
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
    ifstream inFile("../data/data.txt");
    if (!inFile) {
        cout << "Error: Could not open file for reading.\n";
        return;
    }
    string line;
    getline(inFile, line);// Skip the first line
    while (getline(inFile, line)) {
        stringstream ss(line);
        string username, fullName, password, phoneNumber, email, homeAddress, city, skills, availability;
        int creditPoints; // Variable to store the credit points
        getline(ss, username, '|');
        getline(ss, fullName, '|');
        getline(ss, password, '|');
        getline(ss, phoneNumber, '|');
        getline(ss, email, '|');
        getline(ss, homeAddress, '|');
        getline(ss, city, '|');
        ss >> creditPoints; // Load the credit points
        getline(ss, skills, '|');
        getline(ss, availability, '|');
        vector<string> skillVector = split(skills, ' ');
        vector<string> availabilityVector = split(availability, ' ');
        Member* newMember = new Member(username, fullName, password, phoneNumber, email, homeAddress, skillVector, availabilityVector, city);
        newMember->setCreditPoints(creditPoints); // Set the credit points for the member
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
                        vector<string> skills, availability;
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
                        cout << "2. List Availability\n";
                        cout << "3. Unlist Availability\n";
                        cout << "4. Search Supporters\n";
                        cout << "5. Book a Supporter\n";
                        cout << "6. View Requests\n";
                        cout << "7. Respond to a Request\n";
                        cout << "8. Block a Member\n";
                        cout << "9. Rate a Supporter\n";
                        cout << "10. Rate a Host\n";
                        cout << "Enter your choice: ";
                        cin >> memberChoice;
                        while(cin.fail() || memberChoice < 0 || memberChoice > 10) {
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
                                // Add your code here...
                                break;
                            case 3:  // Unlist Availability
                                // Add your code here...
                                break;
                            case 4:  // Search Supporters
                                // Add your code here...
                                break;
                            case 5:  // Book a Supporter
                                // Add your code here...
                                break;
                            case 6:  // View Requests
                                // Add your code here...
                                break;
                            case 7:  // Respond to a Request
                                // Add your code here...
                                break;
                            case 8:  // Block a Member
                                // Add your code here...
                                break;
                            case 9:  // Rate a Supporter
                                // Add your code here...
                                break;
                            case 10:  // Rate a Host
                                // Add your code here...
                                break;
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