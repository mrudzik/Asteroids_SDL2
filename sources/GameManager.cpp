
#include "GameManager.hpp"
#include "InputControl.hpp"

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

    while(_gameLoop)
    {
        inputController.ManageInput();


    }
}




void    GameManager::QuitGame()
{
    _gameLoop = false;
    std::cout << "End of Game Loop" << std::endl;
}


