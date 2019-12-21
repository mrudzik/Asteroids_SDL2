
#include "GameManager.hpp"
#include "InputControl.hpp"
#include "GameObjectFactory.hpp"


GameManager::GameManager(s_ParsedData parsedData) :
_window("Asteroids", parsedData.winSize_x, parsedData.winSize_y, 100, 100),
_objectFactory(&_window)
{
	srand(0);
	player = _objectFactory.player;
	std::cout << "Starting Game Loop" << std::endl;
	_gameLoop = true;
	GameLoop();
}

GameManager::~GameManager()
{
	player = NULL;
}

void    GameManager::GameLoop()
{// Do Game stuff here

	InputControl inputController(this);

	_objectFactory.CreateObject(ObjectsEnum::BigAsteroidType, 300, 200, -1, -1, 1, 0.5f, 0);
	_objectFactory.CreateObject(ObjectsEnum::BigAsteroidType, -110, 200, 1, -1, 1, -0.2f, 30);
	// _objectFactory.CreateObject(ObjectsEnum::BigAsteroidType, -200, 200, 0, 0, 0, -0.2f, 30);
	_objectFactory.CreateObject(ObjectsEnum::SmallAsteroidType, 300, -200, -1, 1, 1, -0.2f, 30);
	_objectFactory.CreateObject(ObjectsEnum::BulletType, -300, -200, 1, 1, 1, -0.2f, 30);

	while(_gameLoop)
	{
		inputController.ManageInput();
		// GameLogic
		// Some calculations where something positioned etc.

		// // All GameObjects Calculate Movement
		// // All GameObjects Calculate Intersections
		_objectFactory.CalculateMovementAll();
		_objectFactory.CalculateIntersectionsAll();
		
		SDL_RenderClear(_window.GetRender());
		// Render BackGround
		// Render Objects
		_objectFactory.RenderAll();
		SDL_RenderPresent(_window.GetRender());
	}

}



void 	GameManager::Shoot()
{
	float angle = player->GetAngle() - 90;
	_objectFactory.CreateObject(ObjectsEnum::BulletType,
	-player->GetPosX(), -player->GetPosY(),
	cos(angle * M_PI / 180.0f), sin(angle * M_PI / 180.0f),
	5, 0, angle + 90);
}

// TODO Transfer this to another file
void    GameManager::QuitGame()
{
	_gameLoop = false;
	std::cout << "End of Game Loop" << std::endl;
}


