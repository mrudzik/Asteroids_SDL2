
#include "GameObjectFactory.hpp"


void 	GameObjectFactory::RenderSpecific(int posX, int posY)
{// This will render objects relative to position
	
	for (int i = 0; i < (int)_collectables.size(); i++)
	{// Collectables
		if (_collectables.at(i)->IsShowable())
			_collectables.at(i)->RenderOnWindow(posX, posY);
	}
	for (int i = 0; i < (int)_bigAsteroids.size(); i++)
	{// Big Asteroids
		BigAsteroid* tempObj = _bigAsteroids.at(i);
		if (tempObj->IsLocked())
			tempObj->ShowLock(_window,
				tempObj->GetPosX(), tempObj->GetPosY(),
				posX, posY);
		tempObj->RenderOnWindow(posX, posY);
	}
	for (int i = 0; i < (int)_smallAsteroids.size(); i++)
	{// Small Asteroids
		SmallAsteroid* tempObj = _smallAsteroids.at(i);
		if (tempObj->IsLocked())
			tempObj->ShowLock(_window,
				tempObj->GetPosX(), tempObj->GetPosY(),
				posX, posY);
		tempObj->RenderOnWindow(posX, posY);
	}
	for (int i = 0; i < (int)_bullets.size(); i++)
	{// Bullets
		_bullets.at(i)->RenderOnWindow(posX, posY);
	}
	

	// // Rendering player precise at his position
	// player->RenderOnWindow(posX - 15, posY - 15);

}

void	GameObjectFactory::RenderBackground(int xDif, int yDif)
{// This will render backGrounds
	if (_zoneToRender[0])
		_background->RenderSpecific(xDif - _window->mapSizeX, yDif - _window->mapSizeY);
	if (_zoneToRender[1])
		_background->RenderSpecific(xDif, yDif - _window->mapSizeY);
	if (_zoneToRender[2])
		_background->RenderSpecific(xDif + _window->mapSizeX, yDif - _window->mapSizeY);
	if (_zoneToRender[3])
		_background->RenderSpecific(xDif - _window->mapSizeX, yDif);
	if (_zoneToRender[4])
		_background->RenderSpecific(xDif, yDif);
	if (_zoneToRender[5])
		_background->RenderSpecific(xDif + _window->mapSizeX, yDif);
	if (_zoneToRender[6])
		_background->RenderSpecific(xDif - _window->mapSizeX, yDif + _window->mapSizeY);
	if (_zoneToRender[7])
		_background->RenderSpecific(xDif, yDif + _window->mapSizeY);
	if (_zoneToRender[8])
		_background->RenderSpecific(xDif + _window->mapSizeX, yDif + _window->mapSizeY);
}

void 	GameObjectFactory::RenderObjects(int playerX, int playerY)
{// This will render objects
	if (_zoneToRender[0] == true)
		RenderSpecific(playerX - _window->mapSizeX, playerY - _window->mapSizeY);
	if (_zoneToRender[1] == true)
		RenderSpecific(playerX, playerY - _window->mapSizeY);
	if (_zoneToRender[2] == true)
		RenderSpecific(playerX + _window->mapSizeX, playerY - _window->mapSizeY);
	if (_zoneToRender[3] == true)
		RenderSpecific(playerX - _window->mapSizeX, playerY);
	if (_zoneToRender[4] == true)
		RenderSpecific(playerX, playerY);
	if (_zoneToRender[5] == true)
		RenderSpecific(playerX + _window->mapSizeX, playerY);
	if (_zoneToRender[6] == true)
		RenderSpecific(playerX - _window->mapSizeX, playerY + _window->mapSizeY);
	if (_zoneToRender[7] == true)
		RenderSpecific(playerX, playerY + _window->mapSizeY);
	if (_zoneToRender[8] == true)
		RenderSpecific(playerX + _window->mapSizeX, playerY + _window->mapSizeY);
}

void 	GameObjectFactory::CheckWarpZones(int playerX, int playerY)
{// Check if see warp zones								
	for (int i = 0; i < 9; i++)		// 	0 1 2	
	{// Clear result				// 	3 P 5
		_zoneToRender[i] = false;	// 	6 7 8
	}
	_zoneToRender[4] = true;// Always Current Player Zone

	if (playerY > (_window->mapSizeY - _window->GetHeightHalf()))
	{// Top Zones 0 1 2
		_zoneToRender[1] = true; // Zone near Top Map Border 		1
		if (playerX > (_window->mapSizeX - _window->GetWidthHalf()))
			_zoneToRender[0] = true; // Zone near Top Left Border	0
		if (playerX < _window->GetWidthHalf())
			_zoneToRender[2] = true; // Zone near Top Right Border	2
	}
	if (playerY < _window->GetHeightHalf())
	{// Down Zones 6 7 8
		_zoneToRender[7] = true; // Zone near Bottom Map Border 		7
		if (playerX > (_window->mapSizeX - _window->GetWidthHalf()))
			_zoneToRender[6] = true; // Zone near Down Left Border	6
		if (playerX < _window->GetWidthHalf())
			_zoneToRender[8] = true; // Zone near Down Right Border	8
	}
	// Middle side Zones
	if (playerX > (_window->mapSizeX - _window->GetWidthHalf()))
		_zoneToRender[3] = true; // Zone near Left Map Border 		3
	if (playerX < _window->GetWidthHalf())
		_zoneToRender[5] = true; // Zone near Right Map Border 		5
}


void	GameObjectFactory::RenderAll()
{
	// For Objects
	int playerX = player->GetPosX();
	int playerY = player->GetPosY();
	// For BackGround
	int xDif = playerX + _window->GetWidthHalf();
    int yDif = playerY + _window->GetHeightHalf();

	CheckWarpZones(playerX, playerY);

	// Render all stuff
	RenderBackground(xDif, yDif);
	RenderObjects(playerX, playerY);

	// Rendering player precise at his position
	player->RenderOnWindow(playerX - 15, playerY - 15);
}
