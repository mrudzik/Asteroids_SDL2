
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
    if (_keyState[SDL_SCANCODE_UP] || _keyState[SDL_SCANCODE_W])
    {
        std::cout << "Move Up" << std::endl;
    }
    if (_keyState[SDL_SCANCODE_DOWN] || _keyState[SDL_SCANCODE_S])
    {
        std::cout << "Move Down" << std::endl;
    }
    if (_keyState[SDL_SCANCODE_LEFT] || _keyState[SDL_SCANCODE_A])
    {
        std::cout << "Move Left" << std::endl;
    }
    if (_keyState[SDL_SCANCODE_RIGHT] || _keyState[SDL_SCANCODE_D])
    {
        std::cout << "Move Right" << std::endl;
    }
}