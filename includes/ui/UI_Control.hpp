#ifndef UI_CONTROL_HPP
#define UI_CONTROL_HPP

#include "Reticle.hpp"
#include "Informer.hpp"
#include "FPS_Timer.hpp"
#include "Player.hpp"

struct s_UIData
{
	int limBullets;
	int limAsteroids;

	int bullets;
	int asteroids;
	int collectables;
	int torpedos;

	int playerPosX;
	int playerPosY;
	int playerScore;
	int mousePosX;
	int mousePosY;
	int mousePosX_world;
	int mousePosY_world;

	bool showHelp = false;
	bool showCheatHelp = false;
	bool showPlayerStatus = false;
	bool showObjectsStatus = false;
	bool infShield = false;
	bool infTorpedo = false;

	bool isShielded;
	int shieldCapacity;
	int shieldEnergy;

	bool isLocking;
	int torpedoCapacity;
	int torpedoCount;

	AbilityType currentAbility;

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
	void	RenderPlayerStatus(
		int const screenX, int const screenY,
		int const mousePosX, int const mousePosY,
		int const mousePosX_world, int const mousePosY_world,
		int const playerPosX, int const playerPosY);
	void 	RenderObjectsStatus(int const screenX, int const screenY,
		int const curBullets, int const limBullets,
		int const curAsteroids, int const limAsteroids,
		int const curCollectables,
		int const curTorpedos);
	void 	RenderCurrentCheats(
		int const screenX, int const screenY,
		bool const infShield, bool const infTorpedo,
		bool const showObjects, bool const showPlayerInfo);
	
	// UI
	void 	RenderPlayerUI(
		int const screenX, int const screenY,
		int const score);
	void 	RenderShieldUI(
		int const screenX, int const screenY,
		int const shieldCap, int const shieldEn,
		bool const isShielded);
	void 	RenderTorpedoUI(
		int const screenX, int const screenY,
		int const torpCap, int const torpCount, bool const isLocking);
	void 	RenderAutoShootUI(
		int const screenX, int const screenY,
		bool const isLocking);

};




#endif