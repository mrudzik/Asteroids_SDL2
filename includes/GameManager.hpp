
#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "ParserControl.hpp"
#include "GameSDL_Window.hpp"
#include "GameObjectFactory.hpp"

#include "UI_Control.hpp"

class GameManager
{
private:
	GameSDL_Window 		_window;
	GameObjectFactory 	_objectFactory;
	UI_Control			_uiController;
	s_UIData			_uiData;

	bool 	_gameLoop;

	const int _limitAsteroid;
	const int _limitAmmo;

public:
	bool    holdingLock = false;

	Player*	player; // Allocated at Object Factory

	GameManager(s_ParsedData parsedData);
	~GameManager();

	void 	GameLoop();

	// Projectiles
	
	void 	LockObject(bool state);
	void 	LaunchTorpedo();
	void 	AbilityShoot();

	void 	AimShoot(AbstractGameObject* target);
	void 	Shoot();


	void 	QuitGame();
	void	RefreshUIData();
	void 	ShowHelp(InfoEnum textType);
	void 	DoCheat(int cheatNum);
	void 	CalcCheats();
};

#endif
