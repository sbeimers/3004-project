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

private:
    MenuState state;

    // need one recording
    // vector(?) of logs, gotta store a few of those
};

#endif // DEVICE_H
