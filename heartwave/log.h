#ifndef LOG_H
#define LOG_H

#include <vector>
#include <string>
#include <iostream>
#include "QString"

using namespace std;

class Log
{
public:
    Log(QString& date, int challengeLevel, int breathInterval, int lengthOfSession, float averageCoherence, float lowPercentage, float mediumPercentage, float highPercentage, float achievementScore, vector<float> *plotPoints);
    QString getDate();
    int getChallengeLevel();
    int getBreathInterval();
    int getLengthOfSession();
    float getAverageCoherence();
    float getLowPercentage();
    float getMediumPercentage();
    float getHighPercentage();
    float getAchievementScore();
    vector<float> getPlotPoints();


private:
    QString date; // in format mm/dd/yyyy eg. 03/21/2023
    int challengeLevel; // from 0-3 (ui will show level 1-4)
    int breathInterval; // breathinterval
    int lengthOfSession; // total length of session in seconds
    float averageCoherence; // calculated average coherence
    float lowPercentage; // percentage of time at low coherence
    float mediumPercentage; // percentage of time at medium coherence
    float highPercentage; // percentage of time at high coherence
    float achievementScore; // achievement score
    vector<float> plotPoints; //holds plot points needed to generate the graph in log summary.

    /*
    Based off of feature in specs:

    When the user ends a session a summary view will appear that includes the following
    information: challenge level, percentage of time in different coherence levels (low
    medium and high), average coherence, length of session, achievement score, entire
    HRV graph
     */

};

#endif // LOG_H
