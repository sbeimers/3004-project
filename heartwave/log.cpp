#include "iostream"
#include "log.h"

using namespace std;

// ctor for log... no setters since this should never be changed after.
Log::Log(QString& idate, int ichallengeLevel, int ibreathInterval, int ilengthOfSession, float iaverageCoherence, float ilowPercentage, float imediumPercentage, float ihighPercentage, float iachievementScore, vector<float> *iplotPoints
         ) : plotPoints(*iplotPoints) { // plot points will take the entire graph, so fix when TAs say what to do.
    date = idate;
    challengeLevel = ichallengeLevel;
    breathInterval = ibreathInterval;
    lengthOfSession = ilengthOfSession;
    averageCoherence = iaverageCoherence;

    lowPercentage = ((int)(ilowPercentage*10))/10.0;
    mediumPercentage = ((int)(imediumPercentage*10))/10.0;
    highPercentage = ((int)(ihighPercentage*10))/10.0;
    achievementScore = iachievementScore;
}

// Getters
QString Log::getDate() { return date; }
int Log::getChallengeLevel() { return challengeLevel; }
int Log::getBreathInterval() { return breathInterval; }
int Log::getLengthOfSession() { return lengthOfSession; }
float Log::getAverageCoherence() { return averageCoherence; }
float Log::getLowPercentage() { return lowPercentage; }
float Log::getMediumPercentage() { return mediumPercentage; }
float Log::getHighPercentage() { return highPercentage; }
float Log::getAchievementScore() { return achievementScore; }
vector<float> Log::getPlotPoints() { return plotPoints; }

