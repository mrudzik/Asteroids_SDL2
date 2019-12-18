
#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "ParserControl.hpp"
#include "GameSDL_Window.hpp"

class GameManager
{
private:
	GameSDL_Window _window;
	
	bool _gameLoop;

public:
	GameManager(s_ParsedData parsedData);
	~GameManager();

	void 	GameLoop();


	void 	QuitGame();
};

#endif
