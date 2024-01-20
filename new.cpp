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
void Member::setAverageSkillRating(const string& skill, float averageRating) {
    if (skillRatings.count(skill) > 0) {
        skillRatings[skill].first = averageRating * skillRatings[skill].second;
    } else {
        skillRatings[skill] = make_pair(averageRating, 1);
    }
}