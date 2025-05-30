#include "recording.h"

Recording::Recording(int challengeLevel, int breathInterval){
    this->challengeLevel = challengeLevel;
    this->breathInterval = breathInterval;
    lengthOfSession = 0;
    achievementScore = 0;
}

Recording::~Recording(){}

// Getters
float Recording::getCoherenceScore(){ return coherenceScores.back(); }
int Recording::getChallengeLevel(){ return challengeLevel; }
int Recording::getBreathInterval(){ return breathInterval; }
int Recording::getLengthOfSession(){ return lengthOfSession; }
float Recording::getCurrentAchievementScore(){ return achievementScore; }
vector<float>* Recording::getAllPlotPoints(){ return &plotPoints; }     // Returns all plot points used for the session

// Setters
void Recording::setChallengeLevel(int challengeLevel){ this->challengeLevel = challengeLevel; }
void Recording::setBreathInterval(int breathInterval){ this->breathInterval = breathInterval;}
void Recording::setLengthOfSession(int duration){ this->lengthOfSession = duration; }
void Recording::setDataPoints(vector<float>* dataPoints) { this->dataPoints = dataPoints; }
void Recording::setCoherenceValues(vector<float> * coherenceDataValues) {this->coherenceDataValues = coherenceDataValues; }

// Updates all the necessary values to prepare for the UI display
// Called every 5 seconds
/* Device will call the following functions to update the UI
  1. getAchievementScore()
  2. getCoherenceAverage()
  3 .getLengthOfSession() */
void Recording::update(){
    setLengthOfSession(lengthOfSession + 5); //updates the duration to reflect the 5 seconds that have passed
    addToPlotPoints(); //adds the next 5 plot points
    addToCoherenceScores();
    updateAchievementScore();
}

// Returns 5 latest data plot points
vector<float> Recording::getFiveLastestPlotPoints() {
    vector<float> points;
    for(int i = 0; i < 5; i++){
     points.push_back(plotPoints.at(plotPoints.size()-5+i));
    }
    return points;
}

// Adds the next 5 plot points to the class vector
void Recording::addToPlotPoints(){
    for (int x = lengthOfSession - 5; x < lengthOfSession; x++){
        plotPoints.push_back(dataPoints->at(x % dataPoints->size()));
    }
}

//this function appends the newest coherence average/score to coherenceScores.
void Recording::addToCoherenceScores(){
    coherenceScores.push_back(coherenceDataValues->at(coherenceScores.size() % coherenceDataValues->size()));
}

//returns the average coherence based off of all coherence scores during the session
//sum of coherence scores, AKA achievement score, divided by the amount of coherence scores
float Recording::getAverageCoherence(){
    if(coherenceScores.size() == 0){
        return 0;
    }
    float average =  achievementScore / float(coherenceScores.size());
    return average;
}

//this function updates the achievement score by looking at the last recorded coherence average and adding it to the preestablished achievement score.
//achievement score is the sum of all of the coherence scores/averages
void Recording::updateAchievementScore(){
       achievementScore += coherenceScores.back();
}

// Reset recording data
void Recording::reset(){
    coherenceScores.clear();
    plotPoints.clear();
    lengthOfSession = 0;
    achievementScore = 0;
}
