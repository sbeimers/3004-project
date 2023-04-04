#ifndef RECORDING_H
#define RECORDING_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Recording
{
public:
    Recording();
    ~Recording();

    //getters
    float getCoheranceAverage();
    int getChallengeLevel();
    int getBreathInterval();
    int getLengthOfSession();
    int getCurrentAchievementScore();

    //setters
    void setChallengeLevel(int); //sets the challenge level
    void setBreathInterval(int); //sets the breath interval
    void setLengthOfSession(int); //adds to the duration of the session when called

    //coherance logic
    bool addCoheranceValue(int); //adds a new coherance value to the queue
    int calculateCoheranceAverage(); //calculates coherance average over 64 seconds to come up with the coherance score, adds it to the coheranceScores vectors

    //challenge level logic
    void checkIndicator(); //calculates the colour of the indicator dependant on the challenge level and coherance score

    //achievement score logic
    int calculateAchievementScore(); //adds up all of the scores in the coheranceScores vector to get an achievement score


private:
    vector<float> queueOfCoheranceValues; //holds 64 values only, updated every second
    vector<float> coheranceScores; //holds all coherance scores (each is calculated from the last 64 seconds), updating every 5 seconds
    int challengeLevel;  // from 0-3 (ui will show level 1-4)
    int breathInterval; //holds breath interval from 0-29
    int lengthOfSession; //duration of the session
    int currentAchievementScore;  //achievement score; sum of all coherance scores

};

#endif // RECORDING_H
