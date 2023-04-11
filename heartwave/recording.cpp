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
float Recording::getCoherenceAverage(){ return 0; }//coherenceScores.back(); }
int Recording::getChallengeLevel(){ return challengeLevel; }
int Recording::getBreathInterval(){ return breathInterval; }
int Recording::getLengthOfSession(){ return lengthOfSession; }
float Recording::getCurrentAchievementScore(){ return achievementScore; }

//setters
void Recording::setChallengeLevel(int challengeLevel){ this->challengeLevel = challengeLevel; }
void Recording::setBreathInterval(int breathInterval){ this->breathInterval = breathInterval;}
void Recording::setLengthOfSession(int duration){ this->lengthOfSession = duration; }
void Recording::setDataPoints(vector<float>* dataPoints) { this->dataPoints = dataPoints; }

//this function adds a new coherence value to the queueOfCoherenceValues.
//a coherence value is indicative of 1 second passing
bool Recording::addCoherenceValue(float coherence){
    //checks if queue is over 64 values, then erases the oldest value
    if(queueOfCoherenceValues.size() >= 64){
        queueOfCoherenceValues.erase(queueOfCoherenceValues.begin());
    }

    //adds the new value to the queue
    queueOfCoherenceValues.push_back(coherence);
    return true;
}

//this function calculates the coherence average (AKA score), which is the average of the last 64 seconds of coherence values, and returns the value.
float Recording::calculateCoherenceAverage(){
    float sum = 0;
    for(float c: queueOfCoherenceValues){
        sum += c;
    }
    float average = sum / queueOfCoherenceValues.size();
    return average;
}

//this function appends the coherence average/score to coherenceScores.
void Recording::addToCoherenceScores(float score){
    coherenceScores.push_back(score);
}

//this function updates the achievement score by looking at the last recorded coherence average and adding it to the preestablished achievement score.
//achievement score is the sum of all of the coherence scores/averages
void Recording::updateAchievementScore(){
       achievementScore += coherenceScores.back();
    //currentAchievementScore is public, no need to return it
}

void Recording::reset(){
    queueOfCoherenceValues.clear();
    coherenceScores.clear();
    plotPoints.clear();
    idealPlotDiff.clear();
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
}

int Recording::generateCoherenceValue(){
    //TODO: create a function that will be called every 5 seconds when display needs to update. The function should be called 5 times and generate a coherence value to append to the queueOfCoherenceValue, mimicking 5 seconds passing.
    return 1;
}

vector<float> Recording::getCurrentDataPoints() {
    //reads and returns the next 5 plot points
    vector<float> points;
    for(int i = 0; i < 5; i++){
     points.push_back(plotPoints.at(plotPoints.size()-1-i));
    }
    return points;
}

void Recording::addToPlotPoints(){
    //adds the next 5 plot points to the class vector
    for (int x = lengthOfSession - 5; x < lengthOfSession; x++){
        plotPoints.push_back(dataPoints->at(x));
    }
}

vector<float>* Recording::getAllPlotPoints(){
    //returns all plot points used for the session
    return &plotPoints;
}






