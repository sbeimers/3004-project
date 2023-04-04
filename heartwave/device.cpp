#include "device.h"

Device::Device(){

    state = MenuState::HOME;
    breathPace = 9;
    challengeLevel = 0;
}

void Device::changeMenuState(MenuState state){
    this->state = state;
}

void Device::setBreathPace(int bp){
    breathPace = bp;
}

void Device::setChallengeLevel(int cl){
    challengeLevel = cl;
}

MenuState Device::getState(){
    return state;
}

int Device::getBreathPace() { return breathPace; }

int Device::getChallengeLevel() { return challengeLevel; }


