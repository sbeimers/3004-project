#ifndef DEVICE_H
#define DEVICE_H

#include "recording.h"
#include "log.h"
#include "menustate.h"

class Device
{
public:
    Device();
    ~Device();

    //getters
    int getBreathPace();
    int getChallengeLevel();
    void startSession();
    void update(int variability);
    void startSession(int option);
    void update();

    //settters
    void setBreathPace(int bp);
    void setChallengeLevel(int cl);

    //device power and battery logic
    void toggleOnOff();
    bool getOnOffState();
    int getBatteryLevel(); // returns battery level
    void resetBatteryLevel();// resets battery level
    void setBatteryLevel(int);

    //menu logic
    void changeMenuState(MenuState state);
    MenuState getState();

    int getRecordingLength();
    float getRecordingCoherenceScore();
    float getRecordingAchievementScore();

    vector<float>* getRecordingDataPoints();

    // recording save
    void saveRecording();

    void deleteLog(int index);
    void restore();

private:
    vector<Log*> logs;
    Recording recording;

    MenuState state;

    int breathPace;
    int challengeLevel;

    int batteryLevel;
    bool turnedOn;


    // need one recording
    // vector(?) of logs, gotta store a few of those
};

#endif // DEVICE_H
