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
    turnedOn = true; // determins if the device is on or off

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
           recording.setCoherenceValues(&HIGH_COHERENCE_SCORES);
    }
    else if(option == 1){
        recording.setDataPoints(&MED_COHERENCE_PLOT_POINTS);
        recording.setCoherenceValues(&MED_COHERENCE_SCORES);
    }
    else{
        recording.setDataPoints(&LOW_COHERENCE_PLOT_POINTS);
        recording.setCoherenceValues(&LOW_COHERENCE_SCORES);
    }
    recording.setBreathInterval(breathPace);
    recording.setChallengeLevel(challengeLevel);
}

void Device::saveRecording() {
    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("dd.MM.yyyy hh:mm:ss");

    qDebug() << "Saving Log with Date: " + formattedTime;

    Log* newLog = new Log(formattedTime, recording.getChallengeLevel(), recording.getBreathInterval(), recording.getLengthOfSession(), recording.getCoherenceAverage(), (float) 100.0, (float) 0.0, (float) 0.0, recording.getCurrentAchievementScore(), recording.getAllPlotPoints());
    logs.push_back(newLog);
}

void Device::deleteLog(int index) {
    logs.erase(logs.begin() + index);
}

void Device::restore() {
    breathPace = 9;
    challengeLevel = 0;
    turnedOn = true;
    recording = Recording();
    logs.clear();
}

int Device::getLogIndexByDate(QString d){
    for (int x = 0; x < logs.size(); x++){
        if (QString::compare(logs.at(x)->getDate(), QString::fromStdString(d.toStdString().substr(13))) == 0){
            return x;
        }
    }
    return 0;
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
vector<float> Device::getRecordingDataPoints() { return recording.getCurrentDataPoints(); }
vector<Log*> Device::getLogs() { return logs; }

//power logic
void Device::toggleOnOff(){ turnedOn = !turnedOn; }
bool Device::getOnOffState(){ return turnedOn; }
int Device::getBatteryLevel(){ return batteryLevel; } // returns the battery level
void Device::resetBatteryLevel() { batteryLevel = 100; }// changes the battery level to 100
void Device::setBatteryLevel(int power) { batteryLevel = power; }


//change menu state
void Device::changeMenuState(MenuState state){ this->state = state; }


//indicator logic
//TODO: add challenge level logic
int Device::getIndicator(){
    //indicator 0 = low (red)
    //indicator 1 = medium (blue)
    //indicator 2 = high (green)
    int indicatorNum = 0;

    //float coherence = recording.getCoherenceAverage(); //actual function call, coherence not set
    float coherence = 1; //placeholder value for testing

     float mediumRangeLow = 0;
     float mediumRangeHigh = 0;
    if(challengeLevel == 0){
        mediumRangeLow = 0.5;
        mediumRangeHigh = 0.9;
    }
    else if(challengeLevel == 1){
        mediumRangeLow = 0.6;
        mediumRangeHigh = 2.1;
    }
    else if(challengeLevel ==2){
        mediumRangeLow = 1.8;
        mediumRangeHigh = 4.0;
    }
    else{
        mediumRangeLow = 4.0;
        mediumRangeHigh = 6.0;
    }

    if(coherence >= mediumRangeLow && coherence <= mediumRangeHigh){
        indicatorNum = 1;
    }
    else if(coherence < mediumRangeLow){
        indicatorNum = 0;
    }
    else{
        indicatorNum = 2;
    }
    return indicatorNum;
}
