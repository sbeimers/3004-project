#ifndef DEVICE_H
#define DEVICE_H

#include "recording.h"
#include "log.h"
#include "menustate.h"

class Device
{
public:
    Device();

    //getters
    int getBreathPace();
    int getChallengeLevel();


    //settters
    void setBreathPace(int bp);
    void setChallengeLevel(int cl);

    //device power and battery logic
    void turnOn(); // turn device off
    void turnOff(); // turn device off
    int getBatteryLevel(); // returns battery level
    void resetBatteryLevel();// resets battery level
    void setBatteryLevel(int);

    //menu logic
    void changeMenuState(MenuState state);
    MenuState getState();




private:
    MenuState state;

    int breathPace;
    int challengeLevel;

    int batteryLevel;
    bool turnedOn;


    // need one recording
    // vector(?) of logs, gotta store a few of those
};

#endif // DEVICE_H
