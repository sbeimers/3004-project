#include "device.h"

Device::Device()
{

    state = MenuState::HOME;

}

void Device::changeMenuState(MenuState state){
    this->state = state;
}

MenuState Device::getState(){
    return state;
}
