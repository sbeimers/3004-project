#ifndef DEVICE_H
#define DEVICE_H

#include "recording.h"
#include "log.h"
#include "menustate.h"

class Device
{
public:
    Device();

    void changeMenuState(MenuState state);
    MenuState getState();

    void setBreathPace(int bp);
    void setChallengeLevel(int cl);

    int getBreathPace();
    int getChallengeLevel();

private:
    MenuState state;

    int breathPace;
    int challengeLevel;

    // need one recording
    // vector(?) of logs, gotta store a few of those
};

#endif // DEVICE_H
