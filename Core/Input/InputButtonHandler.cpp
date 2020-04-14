#include "InputButtonHandler.h"
#include <iostream>

namespace DonkeyKong
{
    std::unordered_map<ButtonName, bool> InputButtonHandler::buttonPressed;

    InputButtonHandler::InputButtonHandler()
    {
        buttonPressed[ButtonName::Move_Left] = false;
        buttonPressed[ButtonName::Move_Right] = false;
        buttonPressed[ButtonName::Jump] = false;
        buttonPressed[ButtonName::Climb_Up] = false;
        buttonPressed[ButtonName::Climb_Down] = false;
    }

    const bool InputButtonHandler::IsButtonPressed(const ButtonName buttonName) 
    {
        return buttonPressed[buttonName];
    }   
}