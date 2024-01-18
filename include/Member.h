#ifndef MEMBER_H
#define MEMBER_H

#include <vector>
#include <string>
using namespace std;

// Forward declaration of System class
class System;

class Member {
private:
    string username;
    string fullName;
    string password;
    string phoneNumber;
    string email;
    string homeAddress;
    vector<string> skills;
    int creditPoints = 20;
    float skillRating;
    float supporterRating;
    float hostRating;
    vector<string> availability;
    vector<Member*> blockedMembers;
    int pointsPerHour;
    float minHostRating;
    bool requestAccepted = false;
    string city;
public:
    // Constructor
    Member(string username = "", string fullName = "", string password = "", string phoneNumber = "", string email = "", string homeAddress = "", vector<string> skills = {}, vector<string> availability = {}, string city = "");

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
    int getPointsPerHour();
    float getMinHostRating();
    bool getRequestAccepted();
    string getCity();

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
    void setPointsPerHour(int points);
    void setMinHostRating(float rating);
    void setRequestAccepted(bool status);
    void setCity(string newCity);

    // Method to check if a member is available
    bool isAvailable();

    bool login(string inputUsername, string inputPassword);

    void viewInformation();

    //Credit points method
    int getCreditPoints();
    void setCreditPoints(int points);
    void earnPoints(int points);
    bool usePoints(int points);
    void topUpPoints(int cash, string inputPassword);

    //Rating method
    void rateSupporter(Member* supporter, float rating);
    void rateHost(Member* host, float rating);

    //Availability method
    void listAvailability(vector<string> newAvailability, int newPointsPerHour, float newMinHostRating);
    void unlistAvailability();

    //Booking and request method
    bool bookSupporter(Member* supporter);
    void viewRequests(vector<Member*> requests);
    bool respondToRequest(Member* request, bool accept);

    //Blocking methods
    void blockMember(Member* member);
    bool isBlocked(Member* member);
};

#endif  // MEMBER_H