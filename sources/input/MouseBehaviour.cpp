
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
            if (_game->holdingLock)
            {
                _game->holdingLock = false;
				if (_game->player->selectedAbility == AbilityType::TorpedoAbil)
				{
					std::cout << "Torpedo" << std::endl;
					_game->LaunchTorpedo();
				}
				else if (_game->player->selectedAbility == AbilityType::AimshootAbil)
				{
					std::cout << "Shoot" << std::endl;
					_game->AbilityShoot(); 
				}
				else
				{
					std::cout << "Fail" << std::endl;
					_game->holdingLock = true; 
				}
			}
        }
    }
}