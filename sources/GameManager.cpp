
#include "GameManager.hpp"
#include "InputControl.hpp"
#include "BackGroundControl.hpp"
#include "GameObjectFactory.hpp"
#include "SpawnControl.hpp"



GameManager::GameManager(s_ParsedData parsedData) :
_window("Asteroids", parsedData.winSize_x, parsedData.winSize_y, 300, 5,
	parsedData.mapSize_x, parsedData.mapSize_y),
_objectFactory(&_window, parsedData.brownianMotion, parsedData.abilityProbability),
_uiController(&_window),
_limitAsteroid(parsedData.asteroidNum), _limitAmmo(parsedData.ammoNum)
{
	srand(0); // Seeding Random
	// Seting UI Data
	_uiData.limAsteroids = parsedData.asteroidNum;
	_uiData.limBullets = parsedData.ammoNum;
	_uiData.HideAll();
	// Setuping player
	player = _objectFactory.player;
	// Starting Game Loop
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
		
		
		// Refreshing UI Data
		RefreshUIData();
		// Rendering Logic
		SDL_RenderClear(_window.GetRender());

		// Render Objects and Background
		_objectFactory.RenderAll();
		// Rendering UI
		_uiController.RenderAll(_uiData);

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

void 	GameManager::LockTorpedo(bool state)
{
	if (!state)
	{
		if (player->lockedObject == NULL)
			return; // Protection
		player->lockedObject->lockObj.SetLock(false);
		return;
	}

	int worldPosX = _objectFactory.mouseWorldPosX;
	int worldPosY = _objectFactory.mouseWorldPosY;

	player->lockedObject = NULL;
	player->lockedObject = _objectFactory.GetClosestAsteroid(worldPosX, worldPosY);
	if (player->lockedObject == NULL)
		return; // Protection

	player->lockedObject->lockObj.SetLock(true);
}

void 	GameManager::LaunchTorpedo()
{
	if (player->lockedObject == NULL)
		return; // Protection
	if (player->GetTorpedoCount() <= 0)
	{
		player->lockedObject->lockObj.SetLock(false);
		return;
	}
	player->RechargeTorpedo(-1);
	_objectFactory.CreateObject(ObjectsEnum::TorpedoType,
		player->GetPosX(), player->GetPosY(), 0, 0, 2.0f, 0, 0);

	// LockTorpedo(false);
	// std::cout << "Lock Unlock" << std::endl;
	// _lockedAsteroid->SetLock(false);

	
}








// TODO Transfer this to another file
void    GameManager::QuitGame()
{
	_gameLoop = false;
	std::cout << "End of Game Loop" << std::endl;
}

void 	GameManager::ShowHelp(InfoEnum textType)
{
	if (textType == InfoEnum::HelpText)
	{
		if (!_uiData.showHelp)
			_uiData.HideAll();
		_uiData.showHelp = !_uiData.showHelp;
	}
	if (textType == InfoEnum::CheatText)
	{
		if (!_uiData.showCheatHelp)
			_uiData.HideAll();
		_uiData.showCheatHelp = !_uiData.showCheatHelp;
	}
}

void 	GameManager::ShowCheat(int cheatNum)
{
	if (cheatNum == 1)
		_uiData.showPlayerStatus = !_uiData.showPlayerStatus;
	if (cheatNum == 2)
		_uiData.showObjectsStatus = !_uiData.showObjectsStatus;
	
}

void 	GameManager::RefreshUIData()
{
	// Player Score
	_uiData.playerScore = player->GetScore();
	// Player Position
	_uiData.playerPosX = player->GetPosX();
	_uiData.playerPosY = player->GetPosY();
	// Mouse Position
	_uiData.mousePosX = _objectFactory.mousePosX;
	_uiData.mousePosY = _objectFactory.mousePosY;
	// Mouse World Position
	_uiData.mousePosX_world = _objectFactory.mouseWorldPosX;
	_uiData.mousePosY_world = _objectFactory.mouseWorldPosY;
	// Object Counters
	_uiData.bullets = _objectFactory.GetBulletCount();
	_uiData.asteroids = _objectFactory.GetAsteroidCount();
	_uiData.collectables = _objectFactory.GetCollectableCount();
	_uiData.torpedos = _objectFactory.GetTorpedoCount();
	// Shield Stuff
	_uiData.shieldCapacity = player->GetShieldCap();
	_uiData.shieldEnergy = player->GetShieldEn();
	_uiData.isShielded = player->IsShielded();
	// Torpedo Stuff
	_uiData.torpedoCapacity = player->GetTorpedoCap();
	_uiData.torpedoCount = player->GetTorpedoCount();
	_uiData.isLockingTorpedo = holdingLock;

}


