
#include "InputControl.hpp"

void    InputControl::MouseEventInput()
{
    // Mouse events
    if (_event.type == SDL_MOUSEBUTTONUP)
    {
        if (_event.button.button == SDL_BUTTON_LEFT)
        {
			_game->Shoot();
        }
        if (_event.button.button == SDL_BUTTON_RIGHT)
        {
            if (_holdingLock)
            {
                _game->LaunchTorpedo();
                _holdingLock = false;
            }
                // std::cout << "Torpedo!" << std::endl;
        }
    }
}