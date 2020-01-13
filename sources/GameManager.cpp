
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

	_objectFactory.RestartBehaviour(RestartScenarioEnum::Start);
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
		// Calculate cheats
		CalcCheats();

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
	_uiData.isLocking = holdingLock;
	// Current Ability
	_uiData.currentAbility = player->selectedAbility;
}








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


void 	GameManager::CalcCheats()
{
	if (_uiData.infShield)
		player->RechargeShield(10);
	if (_uiData.infTorpedo)
		player->RechargeTorpedo(1);
}

void 	GameManager::DoCheat(int cheatNum)
{
	if (cheatNum == 1)
		_uiData.showPlayerStatus = !_uiData.showPlayerStatus;
	if (cheatNum == 2)
		_uiData.showObjectsStatus = !_uiData.showObjectsStatus;
	
	if (cheatNum == 8)
		_uiData.infTorpedo = !_uiData.infTorpedo;
	if (cheatNum == 9)
		_uiData.infShield = !_uiData.infShield;
	
	
}




