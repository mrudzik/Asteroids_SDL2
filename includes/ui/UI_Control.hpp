#ifndef UI_CONTROL_HPP
#define UI_CONTROL_HPP

#include "Reticle.hpp"
#include "Informer.hpp"
#include "FPS_Timer.hpp"

struct s_UIData
{
	int limBullets;
	int limAsteroids;

	int bullets;
	int asteroids;
	int collectables;

	int playerPosX;
	int playerPosY;
	int playerScore;
	int mousePosX;
	int mousePosY;

	bool showHelp;
	bool showCheatHelp;
	bool showPlayerStatus;
	bool showObjectsStatus;

	// bool isShielded;


	void HideAll()
	{
		showHelp = false;
		showCheatHelp = false;

		showPlayerStatus = false;
		showObjectsStatus = false;
	}
};

class UI_Control
{
private:
	GameSDL_Window* _window;

	Informer 	_informer;
	Reticle 	_mouseReticle;
	FPS_Timer	_fpsTimer;

	std::stringstream	_strBuilder;

public:
	UI_Control(GameSDL_Window* window);
	~UI_Control();

	void 	RenderAll(s_UIData data);
	// Cheats
	void	RenderPlayerStatus(int const mousePosX, int const mousePosY,
		int const playerPosX, int const playerPosY);
	void 	RenderObjectsStatus(int const curBullets, int const limBullets,
		int const curAsteroids, int const limAsteroids,
		int const curCollectables);
	
	// UI
	void 	RenderPlayerUI(int const score);


};




#endif