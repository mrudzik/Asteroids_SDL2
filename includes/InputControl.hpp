# ifndef INPUTCONTROL_HPP
# define INPUTCONTROL_HPP

# include <iostream>
# include <SDL2/SDL.h>
# include "GameManager.hpp"

class InputControl
{
private:
    /* data */
    SDL_Event       _event;
    const Uint8*    _keyState;

    GameManager*    _game;

public:
    InputControl(GameManager* gameManager);
    ~InputControl();

    void ManageInput();
    
    void KeyboardEventInput();
    void KeyboardScancodeInput();
    
    void MouseEventInput();
    void MouseScancodeInput();
};





#endif