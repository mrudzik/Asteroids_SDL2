
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

void 	GameManager::CalcCheats()
{
	if (_uiData.infShield)
		player->RechargeShield(10);
	if (_uiData.infTorpedo)
		player->RechargeTorpedo(1);
}



void 	GameManager::AimShoot(AbstractGameObject* target)
{
	// Basic Values
	// Chaser Location
	float chaseX = player->GetPosX();
	float chaseY = player->GetPosY();
	// Runner Location
	float runX = target->GetPosX();
	float runY = target->GetPosY();
	// Runner current speed and direction (dist per frame)
	float runVelX = target->GetVecX() * target->GetSpeed();
	float runVelY = target->GetVecY() * target->GetSpeed();
	// Vector from Runner to Chaser
	float vecRunChaseX = runX - chaseX;
	float vecRunChaseY = runY - chaseY;
	// Results
	float resPosX;
	float resPosY;
	float resVecX;
	float resVecY;

	float chaseSpeed = 5;

	float s = vecRunChaseX * runVelY - vecRunChaseY * runVelX;
	float d = (-2 * vecRunChaseX * s) * (-2 * vecRunChaseX * s)
		- 4 * (vecRunChaseX * vecRunChaseX + vecRunChaseY * vecRunChaseY)
		* (s * s - (vecRunChaseY * vecRunChaseY) * (chaseSpeed * chaseSpeed));
	if(!(d < 0))
	{
		float a1 = 		(2*vecRunChaseX*s + sqrtf(d))
				/ //--------------------------------------------
					(2*((vecRunChaseX*vecRunChaseX) + vecRunChaseY*vecRunChaseY));
		float a2 = 		(2*vecRunChaseX*s - sqrtf(d))
				/ //--------------------------------------------
					(2*((vecRunChaseX*vecRunChaseX) + vecRunChaseY*vecRunChaseY));
		float t1 = vecRunChaseY / (a1 - runVelY);
		float t2 = vecRunChaseY / (a2 - runVelY);
		float t = t1;
		if(t < 0 || (t > t2 && t2 > 0))
			t = t2;

		resPosX = runX + runVelX * t;
		resPosY = runY + runVelY * t;
		resVecX = resPosX - chaseX;
		resVecY = resPosY - chaseY;
		float len = sqrt(resVecX * resVecX + resVecY * resVecY);
		resVecX /= len;
		resVecY /= len;

		_objectFactory.BulletReload(_limitAmmo);
		_objectFactory.CreateObject(ObjectsEnum::BulletType,
			player->GetPosX(), player->GetPosY(),
			resVecX, resVecY,
			chaseSpeed, -1, 0);

		return;
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



void 	GameManager::LockObject(bool state)
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



void 	GameManager::AbilityShoot()
{
	if (player->lockedObject == NULL)
		return; // Protection
	AimShoot(player->lockedObject);
	// player->lockedObject->lockObj.SetLock(false);

	LockObject(false);
	// LockObject(true);

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
	
	// LockObject(true);
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


