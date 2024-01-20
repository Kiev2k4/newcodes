#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
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
    vector<float> supporterRatings;
    vector<float> hostRatings;
    float averageHostRating;
    float averageSupporterRating;
    float averageSkillRating;
    vector<pair<string, pair<string, pair<string, string>>>> availability;
    vector<Member*> blockedMembers;
    map<string, pair<float,int>> skillRatings;
    int hostRatingCount;
    int supporterRatingCount;
    int pointsPerHour;
    float minHostRating;
    bool requestAccepted = false;
    string city;
public:
    // Constructor
    Member(string username = "", string fullName = "", string password = "", string phoneNumber = "", string email = "", string homeAddress = "", vector<string> skills = {}, vector<pair<string, pair<string, pair<string, string>>>> availability = {}, string city = "");

    // Getter methods
    string getUsername();
    string getFullName();
    string getPassword();
    string getPhoneNumber();
    string getEmail();
    string getHomeAddress();

    float getAverageSkillRating(const string& skill);
    float getSupporterRating();
    float getHostRating();

    int getHostRatingCount();
    int getSupporterRatingCount();

    vector<string> getSkills();
    vector<pair<string, pair<string, pair<string, string>>>> getAvailability();
    int getPointsPerHour();
    float getMinHostRating();
    bool getRequestAccepted();
    string getCity();
    vector<Member*>& getBlockedMembers();

    //Setter methods
    void setUsername(string newUsername);
    void setFullName(string newFullName);
    void setPassword(string newPassWord);
    void setPhoneNumber(string newPhoneNumber);
    void setEmail(string newEmail);
    void setHomeAddress(string newHomeAddress);
    void setSkills(vector<string> newSkills);
    void setAvailability(vector<pair<string, pair<string, pair<string, string>>>> newAvailability);
    void setPointsPerHour(int points);
    void setMinHostRating(float rating);
    void setRequestAccepted(bool status);
    void setCity(string newCity);
    void setAverageHostRating(float rating, int count);
    void setAverageSupporterRating(float rating, int count);

    void setAverageSkillRating(const string& skill, float averageRating); 

    void addSkillRating(const string& skill, float rating);
    void addSupporterRating(float rating);
    void addHostRating(float rating);

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
    void rateSkill(Member* supporter, const string& skill, float rating);
    float getAverage(vector<float>& ratings);

    //Availability method
    void listAvailability(vector<pair<string, pair<string, pair<string, string>>>> newAvailability, int newPointsPerHour, float newMinHostRating);
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