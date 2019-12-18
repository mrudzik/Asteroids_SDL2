
#include "InputControl.hpp"

void    InputControl::MouseEventInput()
{
    // Mouse events
    if (_event.type == SDL_MOUSEBUTTONUP)
    {
        if (_event.button.button == SDL_BUTTON_LEFT)
        {
            std::cout << "Peu" << std::endl;
        }
    }
}