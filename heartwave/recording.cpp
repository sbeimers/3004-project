#include "recording.h"

Recording::Recording(int challengeLevel, int breathInterval){
    this->challengeLevel = challengeLevel;
    this->breathInterval = breathInterval;
    lengthOfSession = 0;
    achievementScore = 0;
}

Recording::~Recording(){
    //deconstructor
}

//getters
float Recording::getCoherenceScore(){ return coherenceScores.back(); }
int Recording::getChallengeLevel(){ return challengeLevel; }
int Recording::getBreathInterval(){ return breathInterval; }
int Recording::getLengthOfSession(){ return lengthOfSession; }
float Recording::getCurrentAchievementScore(){ return achievementScore; }
vector<float>* Recording::getAllPlotPoints(){ return &plotPoints; }     //returns all plot points used for the session

//setters
void Recording::setChallengeLevel(int challengeLevel){ this->challengeLevel = challengeLevel; }
void Recording::setBreathInterval(int breathInterval){ this->breathInterval = breathInterval;}
void Recording::setLengthOfSession(int duration){ this->lengthOfSession = duration; }
void Recording::setDataPoints(vector<float>* dataPoints) { this->dataPoints = dataPoints; }
void Recording::setCoherenceValues(vector<float> * coherenceDataValues) {this->coherenceDataValues = coherenceDataValues; }

void Recording::reset(){
    coherenceScores.clear();
    plotPoints.clear();
    lengthOfSession = 0;
    achievementScore = 0;
}

//this function updates all the necessary values to prepare for the UI display
//it is called and indicates 5 seconds passing
//this function does not return anything, instead it updates values so the Device class can use getters for them.
/*device will call the following functions to update the UI
  1. getAchievementScore()
  2. getCoherenceAverage(0
  3 .getLengthOfSession()
The device may tentatively call checkIndicator() to understand what colour the indicator needs to be */
void Recording::update(){
    setLengthOfSession(lengthOfSession + 5); //updates the duration to reflect the 5 seconds that have passed
    addToPlotPoints(); //adds the next 5 plot points
    addToCoherenceScores();
    updateAchievementScore();
}

//reads and returns the next 5 plot points
vector<float> Recording::getCurrentDataPoints() {
    vector<float> points;
    for(int i = 0; i < 5; i++){
     points.push_back(plotPoints.at(plotPoints.size()-5+i));
    }
    return points;
}

//adds the next 5 plot points to the class vector
void Recording::addToPlotPoints(){
    for (int x = lengthOfSession - 5; x < lengthOfSession; x++){
        plotPoints.push_back(dataPoints->at(x));
    }
}

//this function appends the newest coherence average/score to coherenceScores.
void Recording::addToCoherenceScores(){
    coherenceScores.push_back(coherenceDataValues->at(coherenceScores.size()));
}

//returns the average coherence based off of all coherence scores during the session
//sum of coherence scores, AKA achievement score, divided by the amount of coherence scores
float Recording::getAverageCoherence(){
    float average =  achievementScore / float(coherenceScores.size());
    return average;
}

//this function updates the achievement score by looking at the last recorded coherence average and adding it to the preestablished achievement score.
//achievement score is the sum of all of the coherence scores/averages
void Recording::updateAchievementScore(){
       achievementScore += coherenceScores.back();
}










