#include "log.h"

// ctor for log... no setters since this should never be changed after.
Log::Log(string idate, int ichallengeLevel, int ibreathInterval, int ilengthOfSession, float iaverageCoherence, float ilowPercentage, float imediumPercentage, float ihighPercentage, float iachievementScore) {
    date = idate;
    challengeLevel = ichallengeLevel;
    breathInterval = ibreathInterval;
    lengthOfSession = ilengthOfSession;
    averageCoherence = iaverageCoherence;
    lowPercentage = ilowPercentage;
    mediumPercentage = imediumPercentage;
    highPercentage = ihighPercentage;
    achievementScore = iachievementScore;
}

// Getters
string Log::getDate() { return date; }
int Log::getChallengeLevel() { return challengeLevel; }
int Log::getBreathInterval() { return breathInterval; }
int Log::getLengthOfSession() { return lengthOfSession; }
float Log::getAverageCoherence() { return averageCoherence; }
float Log::getLowPercentage() { return lowPercentage; }
float Log::getMediumPercentage() { return mediumPercentage; }
float Log::getHighPercentage() { return highPercentage; }
float Log::getAchievementScore() { return achievementScore; }

