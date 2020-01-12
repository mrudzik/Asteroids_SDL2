
#include "InputControl.hpp"
#include "Informer.hpp"

void InputControl::KeyboardEventInput()
{
    if (_event.type == SDL_KEYDOWN)
    {// Start Button press
        if (_event.key.keysym.sym == SDLK_ESCAPE)
        {
            std::cout << "Closing by Escape" << std::endl;
            _game->QuitGame();
        }
		if (_event.key.keysym.sym == SDLK_F1)
			_game->ShowHelp(InfoEnum::HelpText);
		if (_event.key.keysym.sym == SDLK_F2)
			_game->ShowHelp(InfoEnum::CheatText);
		if (_event.key.keysym.sym == SDLK_KP_1)
			_game->DoCheat(1);
		if (_event.key.keysym.sym == SDLK_KP_2)
			_game->DoCheat(2);

		if (_event.key.keysym.sym == SDLK_KP_8)
			_game->DoCheat(8);
		if (_event.key.keysym.sym == SDLK_KP_9)
			_game->DoCheat(9);

		if (_event.key.keysym.sym == SDLK_1)
			_game->player->SetShieldActive(!_game->player->IsShielded());



      if ((_event.key.keysym.sym == SDLK_LSHIFT
	  	|| _event.key.keysym.sym == SDLK_RSHIFT)
        && !_game->holdingLock) // Lock Target
      {
        _game->LockObject(true);
        _game->holdingLock = true;
      }
       
    }
    if (_event.type == SDL_KEYUP)
    {
		if ((_event.key.keysym.sym == SDLK_LSHIFT
	  		|| _event.key.keysym.sym == SDLK_RSHIFT)
        	&& _game->holdingLock) // Unlock Target
      	{
			_game->LockObject(false);
			_game->holdingLock = false;
		}

		if (_event.key.keysym.sym == SDLK_2)
		{ //Select Torpedo
			_game->player->selectedAbility = AbilityType::TorpedoAbil;
		}
		if (_event.key.keysym.sym == SDLK_3)
		{ // Select AutoAiming
			_game->player->selectedAbility = AbilityType::AimshootAbil;
		}
    }

}











void InputControl::KeyboardScancodeInput()
{
	MovementScancodeInput();
}

void	InputControl::MovementScancodeInput()
{
	int inertia = 4;

    if (_keyState[SDL_SCANCODE_UP] || _keyState[SDL_SCANCODE_W])
    {
		_game->player->MoveY(inertia);
    }
    if (_keyState[SDL_SCANCODE_DOWN] || _keyState[SDL_SCANCODE_S])
    {
		_game->player->MoveY(-inertia);
    }
    if (_keyState[SDL_SCANCODE_LEFT] || _keyState[SDL_SCANCODE_A])
    {
		_game->player->MoveX(inertia);
    }
    if (_keyState[SDL_SCANCODE_RIGHT] || _keyState[SDL_SCANCODE_D])
    {
		_game->player->MoveX(-inertia);
    }
}