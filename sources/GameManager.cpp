
#include "GameManager.hpp"
#include "InputControl.hpp"
#include "PicTexture.hpp"
#include "AbstractGameObject.hpp"

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

    AbstractGameObject testObject(&_window, "resourses/big_asteroid.png", 100, 200,
    -1, -1, 1, 0.5f, 0);

    AbstractGameObject testObject2(&_window, "resourses/big_asteroid.png", -200, 200,
    1, -1, 1, 0.5f, 0);

    while(_gameLoop)
    {
        inputController.ManageInput();
        // GameLogic
        // Some calculations where something positioned etc.

        testObject.CalculateMovement();
        testObject2.CalculateMovement();

        if (testObject.CheckIntersect(&testObject2))
        {
            testObject.StopMoving();
            testObject2.StopMoving();
            std::cout << "Intersecting" << std::endl;
        }

        SDL_RenderClear(_window.GetRender());


        testTexture.RenderPic(_window, 100, 100, NULL, 90, NULL, SDL_FLIP_NONE);
        
        testObject2.RenderOnWindow(0, 0);
        testObject.RenderOnWindow(0, 0);



        SDL_RenderPresent(_window.GetRender());
    }
}



// TODO Transfer this to another file
void    GameManager::QuitGame()
{
    _gameLoop = false;
    std::cout << "End of Game Loop" << std::endl;
}


