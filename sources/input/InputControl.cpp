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
		{// Pressed red cross on window
			std::cout << "Closing by Cross" << std::endl;
            _game->QuitGame();
		}
        KeyboardEventInput();
        MouseEventInput();
    }
    KeyboardScancodeInput();
}