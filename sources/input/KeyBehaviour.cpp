
#include <InputControl.hpp>

void InputControl::KeyboardEventInput()
{
    if (_event.type == SDL_KEYDOWN)
    {// Start Button press
        if (_event.key.keysym.sym == SDLK_ESCAPE)
        {
            std::cout << "Closing by Escape" << std::endl;
            _game->QuitGame();
        }
    }
}

void InputControl::KeyboardScancodeInput()
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