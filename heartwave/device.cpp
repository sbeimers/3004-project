#include "device.h"
#include "consts.h"

#include "QString"
#include "QDebug"
#include "QDateTime"

Device::Device(){
    // Singleton recording device that gets updated
    recording = Recording();

    // Initially set device state to home
    state = DeviceState::HOME;

    breathPace = 9;
    challengeLevel = 0;

    batteryLevel = 100;
    turnedOn = true;

    //amount of time in each indicator state
    lowIndicatorTime = 0;
    mediumIndicatorTime = 0;
    highIndicatorTime = 0;
}

Device::~Device() {
    for (Log* l: logs) {
        delete l;
    }
}

// State logic
DeviceState Device::getState(){ return state; }
void Device::changeState(DeviceState state){ this->state = state; }

// Sets up things for session
void Device::startSession(int option){
    //reset amount of time in each indicator state
    lowIndicatorTime = 0;
    mediumIndicatorTime = 0;
    highIndicatorTime = 0;

    // Reset recording data
    recording.reset();

    // Set plot points and coherence scores used for simulations
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

    // Set breath interval and challenge levels
    recording.setBreathInterval(breathPace);
    recording.setChallengeLevel(challengeLevel);
}

// Update current session info
void Device::update(){
    recording.update();
}

// Save info from current recording object to log object stored in device
void Device::saveRecording() {
    // Logs are identified by date and time
    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("dd.MM.yyyy hh:mm:ss");

    //calculates the percentage of time spent in each indicator state
    float lowPercentage = (float(lowIndicatorTime) / recording.getLengthOfSession()) * 100;
    float medPercentage = (float(mediumIndicatorTime) / recording.getLengthOfSession()) * 100;
    float highPercentage = (float(highIndicatorTime) / recording.getLengthOfSession()) * 100;

    // Create log and add to log vector, this persists as long as the device turns
    // on and off and only get erased when the program ends
    Log* newLog = new Log(formattedTime, recording.getChallengeLevel(), recording.getBreathInterval(), recording.getLengthOfSession(), recording.getAverageCoherence(), lowPercentage, medPercentage, highPercentage, recording.getCurrentAchievementScore(), recording.getAllPlotPoints());
    logs.push_back(newLog);
}

// Indicator level logic
int Device::getIndicator(){
    //indicator 0 = low (red)
    //indicator 1 = medium (blue)
    //indicator 2 = high (green)
    int indicatorNum = 0;
    float mediumRangeLow = 0;
    float mediumRangeHigh = 0;

    float coherence = recording.getCoherenceScore();

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

     // Checks ranges and updates amount of time spent in each indicator state
    if(coherence >= mediumRangeLow && coherence <= mediumRangeHigh){
        indicatorNum = 1;
        mediumIndicatorTime += 5;
    }
    else if(coherence < mediumRangeLow){
        indicatorNum = 0;
        lowIndicatorTime += 5;
    }
    else{
        indicatorNum = 2;
        highIndicatorTime += 5;
    }
    return indicatorNum;
}

// Device power and battery logic
void Device::toggleOnOff(){ turnedOn = !turnedOn; }
bool Device::getOnOffState(){ return turnedOn; }
int Device::getBatteryLevel(){ return batteryLevel; } // returns the battery level
void Device::resetBatteryLevel() { batteryLevel = 100; }// changes the battery level to 100
void Device::setBatteryLevel(int power) { batteryLevel = power; }

// Log history logic
vector<Log*> Device::getLogs() { return logs; }

int Device::getLogIndexByDate(QString d){
    for (int x = 0; x < logs.size(); x++){
        // Log dates are always unique, so we can compare them with it
        if (QString::compare(logs.at(x)->getDate(), QString::fromStdString(d.toStdString().substr(13))) == 0){
            return x;
        }
    }
    return 0;
}

void Device::deleteLog(int index) {
    logs.erase(logs.begin() + index);
}

// Restore device settings and data
void Device::restore() {
    lowIndicatorTime = 0;
    mediumIndicatorTime = 0;
    highIndicatorTime = 0;
    breathPace = 9;
    challengeLevel = 0;
    turnedOn = true;
    recording = Recording();
    logs.clear();
}



//setters
void Device::setBreathPace(int bp){ breathPace = bp; }
void Device::setChallengeLevel(int cl){ challengeLevel = cl; }

//getters

int Device::getBreathPace() { return breathPace; }
int Device::getChallengeLevel() { return challengeLevel; }
int Device::getRecordingLength(){ return recording.getLengthOfSession(); }
float Device::getRecordingCoherenceScore(){ return recording.getCoherenceScore(); }
float Device::getRecordingAchievementScore(){ return recording.getCurrentAchievementScore(); }
vector<float> Device::getRecordingDataPoints() { return recording.getCurrentDataPoints(); }





//change menu state




