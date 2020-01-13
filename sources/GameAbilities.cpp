
#include "GameManager.hpp"




void 	GameManager::LockObject(bool state)
{
	if (!state)
	{
		Asteroid* tempObject = _objectFactory.GetAsteroidByID(player->lockedID);
		if (tempObject == NULL)
			return; // Protection
		player->lockedID = -1;
		tempObject->lockObj.SetLock(false);
		return;
	}

	int worldPosX = _objectFactory.mouseWorldPosX;
	int worldPosY = _objectFactory.mouseWorldPosY;

	player->lockedID = -1;
	Asteroid* tempObject = _objectFactory.GetClosestAsteroid(worldPosX, worldPosY);
	if (tempObject == NULL)
		return; // Protection
	player->lockedID = tempObject->lockObj.GetID();
	tempObject->lockObj.SetLock(true);
}



void 	GameManager::AbilityShoot()
{
	Asteroid* tempObject = _objectFactory.GetAsteroidByID(player->lockedID);
	if (tempObject == NULL)
		return; // Protection
	AimShoot(tempObject);
	LockObject(false);
}

void 	GameManager::LaunchTorpedo()
{
	Asteroid* tempObject = _objectFactory.GetAsteroidByID(player->lockedID);
	if (tempObject == NULL)
		return; // Protection
	if (player->GetTorpedoCount() <= 0)
	{
		tempObject->lockObj.SetLock(false);
		return;
	}
	player->RechargeTorpedo(-1);
	_objectFactory.CreateObject(ObjectsEnum::TorpedoType,
		player->GetPosX(), player->GetPosY(), 0, 0, 2.0f, 0, 0);
	player->lockedID = -1;	
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

