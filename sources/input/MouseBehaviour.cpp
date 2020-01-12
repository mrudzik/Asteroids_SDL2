
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
					_game->LaunchTorpedo();
				}
				else if (_game->player->selectedAbility == AbilityType::AimshootAbil)
				{
					_game->AbilityShoot(); 
				}
				else
				{
					std::cout << "Failed to use Special Ability" << std::endl;
					_game->holdingLock = true; 
				}
			}
        }
    }
}