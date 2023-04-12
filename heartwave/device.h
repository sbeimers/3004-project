#ifndef DEVICE_H
#define DEVICE_H

#include "recording.h"
#include "log.h"
#include "devicestate.h"

class Device
{
public:
    Device();
    ~Device();

    // State logic
    void changeState(DeviceState state);
    DeviceState getState();

    // Session logic
    void startSession(int option);
    void update();
    void saveRecording();
    int getIndicator();

    // Device power and battery logic
    void toggleOnOff();
    bool getOnOffState();
    int getBatteryLevel();
    void resetBatteryLevel();
    void setBatteryLevel(int);

    // Log history logic
    vector<Log*> getLogs();
    int getLogIndexByDate(QString);
    void deleteLog(int index);

    // Restore device settings and data
    void restore();

    //getters
    int getBreathPace();
    int getChallengeLevel();
    int getRecordingLength();
    float getRecordingCoherenceScore();
    float getRecordingAchievementScore();
    vector<float> getRecordingDataPoints();

    //settters
    void setBreathPace(int bp);
    void setChallengeLevel(int cl);

private:
    vector<Log*> logs;
    Recording recording;

    DeviceState state;

    int breathPace;
    int challengeLevel;

    int batteryLevel;
    bool turnedOn;

    int lowIndicatorTime;
    int mediumIndicatorTime;
    int highIndicatorTime;
};

#endif // DEVICE_H
