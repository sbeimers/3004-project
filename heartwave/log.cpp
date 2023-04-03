#include "log.h"

// ctor for log... no setters since this should never be changed after.
Log::Log(string idate, int ichallengeLevel, int ibreathInterval, int ilengthOfSession, float iaverageCoherance, float ilowPercentage, float imediumPercentage, float ihighPercentage, float iachievementScore) {
    date = idate;
    challengeLevel = ichallengeLevel;
    breathInterval = ibreathInterval;
    lengthOfSession = ilengthOfSession;
    averageCoherance = iaverageCoherance;
    lowPercentage = ilowPercentage;
    mediumPercentage = imediumPercentage;
    highPercentage = ihighPercentage;
    achievementScore = iachievementScore;
}

// Getters
Log::getDate() { return date; }
Log::getChallengeLevel() { return challengeLevel; }
Log::getBreathInterval() { return breathInterval; }
Log::getLengthOfSession() { return lengthOfSession; }
Log::getAverageCoherance() { return averageCoherance; }
Log::getLowPercentage() { return lowPercentage; }
Log::getMediumPercentage() { return mediumPercentage; }
Log::getHighPercentage() { return highPercentage; }
Log::getAchievementScore() { return achievementScore; }

