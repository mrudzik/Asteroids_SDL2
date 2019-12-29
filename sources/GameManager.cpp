
#include "GameManager.hpp"
#include "InputControl.hpp"
#include "BackGroundControl.hpp"
#include "GameObjectFactory.hpp"
#include "SpawnControl.hpp"

#include "FPS_Timer.hpp"


GameManager::GameManager(s_ParsedData parsedData) :
_window("Asteroids", parsedData.winSize_x, parsedData.winSize_y, 300, 100,
	parsedData.mapSize_x, parsedData.mapSize_y),
_objectFactory(&_window, parsedData.brownianMotion),
_informer(&_window),
_limitAsteroid(parsedData.asteroidNum), _limitAmmo(parsedData.ammoNum),
_abilityProbability(parsedData.abilityProbability)
{
	srand(0); // Seeding Random

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
	SpawnControl spawnController(&_objectFactory, _limitAsteroid);
	Reticle mouseReticle(&_window, 100, 1);
	FPS_Timer fpsTimer;

	(void)_abilityProbability; // To silence warning

	_objectFactory.RestartBehaviour();
	player->RestartBehaviour();

	while(_gameLoop)
	{
		// Game Logic
		if (spawnController.NeedToSpawnAsteroid())
			spawnController.SpawnRandomAsteroid();
		inputController.ManageInput();
		// Some calculations where something positioned etc.
		_objectFactory.CalculateMovementAll();
		_objectFactory.CalculateIntersectionsAll();
		
		// Rendering Logic
		SDL_RenderClear(_window.GetRender());
		// Render Objects and Background
		_objectFactory.RenderAll();
		mouseReticle.Render(_objectFactory.mousePosX, _objectFactory.mousePosY);
		// Render Text
		// _window.DrawText("Hello there", 100, 100, _window.GetColor(ColorEnum::White));
		_informer.RenderText(InfoEnum::MakersSign);


		_window.DrawText(fpsTimer.TextFrames().c_str(),
		50, 50, _window.GetColor(ColorEnum::White));

		SDL_RenderPresent(_window.GetRender());
	}

}



void 	GameManager::Shoot()
{
	_objectFactory.BulletReload(_limitAmmo);
	float angle = player->GetAngle() + 90;
	_objectFactory.CreateObject(ObjectsEnum::BulletType,
	player->GetPosX(), player->GetPosY(),
	cos(angle * M_PI / 180.0f) * 2, sin(angle * M_PI / 180.0f) * 2,
	5, 0, angle - 90);
}

// TODO Transfer this to another file
void    GameManager::QuitGame()
{
	_gameLoop = false;
	std::cout << "End of Game Loop" << std::endl;
}


