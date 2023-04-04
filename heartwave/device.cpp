#include "device.h"

Device::Device(){
    state = MenuState::HOME;
    breathPace = 9;
    challengeLevel = 0;

    batteryLevel = 100;// battery level
    turnedOn = false; // determins if the device is on or off

    recording = Recording();
}

void Device::startSession(vector<float>* dataPoints){
    recording.reset();
    recording.setDataPoints(dataPoints);
    recording.setBreathInterval(breathPace);
    recording.setChallengeLevel(challengeLevel);
}

void Device::update(){
    recording.update();
}

vector<float>* Device::getCurrentRecordingDataPoints(){
    return recording.getCurrentDataPoints();
}

int Device::getRecordingLength(){
    return recording.getLengthOfSession();
}

float Device::getRecordingCoherenceScore(){
    return recording.getCoherenceAverage();
}

float Device::getRecordingAchievementScore(){
    return recording.getCurrentAchievementScore();
}

void Device::changeMenuState(MenuState state){
    this->state = state;
}

void Device::setBreathPace(int bp){
    breathPace = bp;
}

//setters
void Device::setBreathPace(int bp){ breathPace = bp; }
void Device::setChallengeLevel(int cl){ challengeLevel = cl; }

//getters
MenuState Device::getState(){ return state; }
int Device::getBreathPace() { return breathPace; }
int Device::getChallengeLevel() { return challengeLevel; }

//power logic
void Device::turnOn(){ turnedOn = true; } //device turn on
void Device::turnOff(){ turnedOn = false; } // device turn off
int Device::getBatteryLevel(){ return batteryLevel; } // returns the battery level
void Device::resetBatteryLevel() { batteryLevel = 100; }// changes the battery level to 100
void Device::setBatteryLevel(int power) { batteryLevel = power; }


//change menu state
void Device::changeMenuState(MenuState state){ this->state = state; }
