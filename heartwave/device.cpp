#include "device.h"
#include "consts.h"

#include "QString"
#include "QDebug"
#include "QDateTime"

Device::Device(){
    state = MenuState::HOME;
    breathPace = 9;
    challengeLevel = 0;

    batteryLevel = 100;// battery level
    turnedOn = false; // determins if the device is on or off

    recording = Recording();
}

Device::~Device() {
    for (Log* l: logs) {
        delete l;
    }
}

void Device::startSession(int option){
    recording.reset();
    if (option == 0) {
           recording.setDataPoints(&HIGH_COHERENCE_PLOT_POINTS);
    } // add elses for med and low

    recording.setBreathInterval(breathPace);
    recording.setChallengeLevel(challengeLevel);

}

void Device::saveRecording() {
    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("dd.MM.yyyy hh:mm:ss");

    qDebug() << "Saving Log with Date: " + formattedTime;

    Log* newLog = new Log(formattedTime, recording.getChallengeLevel(), recording.getBreathInterval(), recording.getLengthOfSession(), recording.getCoherenceAverage(), (float) 100.0, (float) 0.0, (float) 0.0, recording.getCurrentAchievementScore(), recording.getCurrentDataPoints());
    logs.push_back(newLog);
}

void Device::update(){
    recording.update();
}

//setters
void Device::setBreathPace(int bp){ breathPace = bp; }
void Device::setChallengeLevel(int cl){ challengeLevel = cl; }

//getters
MenuState Device::getState(){ return state; }
int Device::getBreathPace() { return breathPace; }
int Device::getChallengeLevel() { return challengeLevel; }
int Device::getRecordingLength(){ return recording.getLengthOfSession(); }
float Device::getRecordingCoherenceScore(){ return recording.getCoherenceAverage(); }
float Device::getRecordingAchievementScore(){ return recording.getCurrentAchievementScore(); }
vector<float>* Device::getRecordingDataPoints() { return recording.getCurrentDataPoints(); }

//power logic
void Device::turnOn(){ turnedOn = true; } //device turn on
void Device::turnOff(){ turnedOn = false; } // device turn off
int Device::getBatteryLevel(){ return batteryLevel; } // returns the battery level
void Device::resetBatteryLevel() { batteryLevel = 100; }// changes the battery level to 100
void Device::setBatteryLevel(int power) { batteryLevel = power; }


//change menu state
void Device::changeMenuState(MenuState state){ this->state = state; }
