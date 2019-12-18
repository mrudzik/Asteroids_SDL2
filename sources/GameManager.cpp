
#include "GameManager.hpp"
#include "InputControl.hpp"
#include "PicTexture.hpp"

GameManager::GameManager(s_ParsedData parsedData) :
_window("Asteroids", parsedData.winSize_x, parsedData.winSize_y, 100, 100)
{
    std::cout << "Starting Game Loop" << std::endl;
    _gameLoop = true;
    GameLoop();
}

GameManager::~GameManager()
{

}

void    GameManager::GameLoop()
{// Do Game stuff here

    InputControl inputController(this);

    PicTexture  testTexture;
    testTexture.LoadFromFile("resourses/background.png", _window);

    while(_gameLoop)
    {
        inputController.ManageInput();
        // GameLogic
        // Some calculations where something positioned etc.


        SDL_RenderClear(_window.GetRender());

        testTexture.RenderPic(_window, 100, 100, NULL, 90, NULL, SDL_FLIP_NONE);

        SDL_RenderPresent(_window.GetRender());
    }
}



// TODO Transfer this to another file
void    GameManager::QuitGame()
{
    _gameLoop = false;
    std::cout << "End of Game Loop" << std::endl;
}


