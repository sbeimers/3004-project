#ifndef LOG_H
#define LOG_H

#include <string>

using namespace std;

class Log
{
public:
    Log(string date, int challengeLevel, int breathInterval, int lengthOfSession, float averageCoherance, float lowPercentage, float mediumPercentage, float highPercentage, float achievementScore);
    string getDate();
    int getChallengeLevel();
    int getBreathInterval();
    int getLengthOfSession();
    float getAverageCoherance();
    float getLowPercentage();
    float getMediumPercentage();
    float getHighPercentage();
    float getAchievementScore();


private:
    string date; // in format mm/dd/yyyy eg. 03/21/2023
    int challengeLevel; // from 0-3 (ui will show level 1-4)
    int breathInterval; // breathinterval
    int lengthOfSession; // total length of session in seconds
    float averageCoherance; // calculated average coherance
    float lowPercentage; // percentage of time at low coherance
    float mediumPercentage; // percentage of time at medium coherance
    float highPercentage; // percentage of time at high coherance
    float achievementScore; // achievement score
    // TODO: need to add vector of coherance data from recording class so we can generate the graph

    /*
    Based off of feature in specs:

    When the user ends a session a summary view will appear that includes the following
    information: challenge level, percentage of time in different coherence levels (low
    medium and high), average coherence, length of session, achievement score, entire
    HRV graph
     */

};

#endif // LOG_H
