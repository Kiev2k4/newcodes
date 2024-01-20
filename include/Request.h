#ifndef REQUEST_H
#define REQUEST_H

#include "Member.h"

class Request {
    Member* requester;
    Member* responder;
    bool isAccepted;
    int pointsPerHour;

public:
    Request(Member* requester, Member* responder, int pointsPerHour);

    Member* getRequester();
    Member* getResponder();
    bool getIsAccepted();
    int getPointsPerHour();

    void setIsAccepted(bool accept);
};

#endif //REQUEST_H