#include "SDL_InputButton.h"

namespace DonkeyKong
{
    SDL_InputButton::SDL_InputButton() : InputButtonHandler(), keysPressed{}
    {
        sdl_keycodeMapping[SDL_SCANCODE_LEFT] = ButtonName::Move_Left;
        sdl_keycodeMapping[SDL_SCANCODE_RIGHT] = ButtonName::Move_Right;
        sdl_keycodeMapping[SDL_SCANCODE_SPACE] = ButtonName::Jump;
        sdl_keycodeMapping[SDL_SCANCODE_UP] = ButtonName::Climb_Up;
        sdl_keycodeMapping[SDL_SCANCODE_DOWN] = ButtonName::Climb_Down;
    }
    
    void SDL_InputButton::UpdateStatus() 
    {
        SDL_Event event;

        while(SDL_PollEvent(&event)) 
        {
            keysPressed = SDL_GetKeyboardState(NULL);      
            for(auto keycode_buttonName : sdl_keycodeMapping)
            {
                buttonPressed[keycode_buttonName.second] = static_cast<bool>(keysPressed[keycode_buttonName.first]);
            }
        }      
    }
}