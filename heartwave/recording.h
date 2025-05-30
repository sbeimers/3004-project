/*
- Coherence value: one second of coherence data
- Coherence score/average: the average of the last 64 coherence values; recalculated and updated every 5 seconds
- Achievement Score: the sum of all coherence scores/averages; recalculated and updated every 5 seconds.
*/

#ifndef RECORDING_H
#define RECORDING_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Recording
{
public:
    Recording(int challengeLevel = 0, int breathInterval = 9);
    ~Recording();

    // Getters
    float getCoherenceScore();
    float getAverageCoherence();
    int getChallengeLevel();
    int getBreathInterval();
    int getLengthOfSession();
    float getCurrentAchievementScore();
    vector<float>* getAllPlotPoints();


    // Setters
    void setChallengeLevel(int); //sets the challenge level
    void setBreathInterval(int); //sets the breath interval
    void setLengthOfSession(int); //adds to the duration of the session when called
    void setDataPoints(vector<float>*);
    void setCoherenceValues(vector <float>*);

    // Update recording
    void update();
    vector<float> getFiveLastestPlotPoints();

    // Plot points logic
    void addToPlotPoints();

    // Coherence logic
    void addToCoherenceScores();

    // Achievement score logic
    void updateAchievementScore(); //adds up all of the scores in the coherenceScores vector to update the achievement score attribute

    // Reset recording
    void reset();

private:
    vector<float> coherenceScores; //holds all coherence scores (each is calculated from the last 64 seconds), updating every 5 seconds
    vector<float> plotPoints; // Holds all y values of HR graph
    vector<float>* dataPoints;
    vector<float>* coherenceDataValues;
    int challengeLevel;  // from 0-3 (ui will show level 1-4)
    int breathInterval; //holds breath interval from 0-29
    int lengthOfSession; //duration of the session
    float achievementScore;  //achievement score; sum of all coherence scores
};

#endif // RECORDING_H
