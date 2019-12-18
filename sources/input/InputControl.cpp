#include "InputControl.hpp"

InputControl::InputControl(GameManager* gameManager)
{
    _game = gameManager;
    _keyState = SDL_GetKeyboardState(NULL);
}

InputControl::~InputControl()
{
}


void InputControl::ManageInput()
{
    while (SDL_PollEvent(&_event))
	{
		if (_event.type == SDL_QUIT)
		{
			std::cout << "Closing By Cross" << std::endl;
            _game->QuitGame();
		}
			// // Mouse events
			// if (event.button.button == SDL_BUTTON_LEFT)
			// {
			// 	i = 0;
			// 	while (i < bullet_count)
			// 	{
			// 		if (bullet[i].is_active == 0)
			// 		{
			// 			bullet[i].shoot(player);
			// 			break;
			// 		}
			// 		i++;
			// 	}
			// }
	}
}