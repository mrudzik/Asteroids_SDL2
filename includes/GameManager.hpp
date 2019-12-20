
#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "ParserControl.hpp"
#include "GameSDL_Window.hpp"
#include "GameObjectFactory.hpp"

class GameManager
{
private:
	GameSDL_Window _window;
	GameObjectFactory _objectFactory;
	bool _gameLoop;

public:

	Player*	player; // Allocated at Object Factory

	GameManager(s_ParsedData parsedData);
	~GameManager();

	void 	GameLoop();

	void 	Shoot();
	void 	QuitGame();
};

#endif
