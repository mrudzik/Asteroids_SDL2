
#include "GameObjectFactory.hpp"





void 	ClearObjectFromFlags(AbstractGameObject* tempObject)
{
	tempObject->AllIntersectCalculated = false;
}

int 	AsteroidCollisionHandle(AbstractGameObject* tempObj, AbstractGameObject* tempTarget)
{
	if (tempObj->CheckIntersect(tempTarget) == 1)
	{
		tempObj->StaticResolution(tempTarget);
		tempObj->DynamicResolution(tempTarget);

		tempObj->AllIntersectCalculated = true;
		tempTarget->AllIntersectCalculated = true;
		return 1;
	}
	return 0;
}


void 	GameObjectFactory::CreateResource(int posX, int posY)
{
	ObjectsEnum tempType;

	int random = rand() % 100;
	if (random < _abilityProb * 100) // by default 0.3 to 30%
	{
		random = rand() % 3;
		if (random == 1)
			tempType = ObjectsEnum::TorpedoAmmoType;
		else
			tempType = ObjectsEnum::ShieldBatteryType;
	}
	else
	{
		random = rand() % 4;
		if (random == 1)
			tempType = ObjectsEnum::CrystalGreenType;
		if (random == 2)
			tempType = ObjectsEnum::CrystalBlueType;
		if (random == 3)
			tempType = ObjectsEnum::CrystalPurpleType;
		else
			tempType = ObjectsEnum::CrystalWhiteType;
	}
	
	
	CreateObject(tempType, posX, posY,
		0, 0, 0, 1.0f, rand() % 360);
}



void	GameObjectFactory::BigAsteroidSplit(AbstractGameObject* tempBullet, BigAsteroid* tempTarget)
{
	int random = rand() % 2;
	float xVec = tempBullet->GetVecX();
	float yVec = tempBullet->GetVecY();

	int x1_Pos = tempTarget->GetPosX();
	int x2_Pos = tempTarget->GetPosX();
	int y1_Pos = tempTarget->GetPosY();
	int y2_Pos = tempTarget->GetPosY();

	if (tempBullet->GetPosX() > tempTarget->GetPosX())
	{// 1 or 2 Hour Side
		if (tempBullet->GetPosY() > tempTarget->GetPosY())
		{// Side 1 (0:01 to 3:00)
			x1_Pos += tempTarget->GetSize();
			y2_Pos += tempTarget->GetSize();
		}
		else
		{// Side 2 (3:01 to 6:00)
			x1_Pos += tempTarget->GetSize();
			y2_Pos -= tempTarget->GetSize();
		}
	}
	else
	{// 3 or 4 Hour Side
		if (tempBullet->GetPosY() > tempTarget->GetPosY())
		{// Side 4 (9:01 to 0:00)
			x1_Pos -= tempTarget->GetSize();
			y2_Pos += tempTarget->GetSize();
		}
		else
		{// Side 3 (6:01 to 9:00)
			x1_Pos -= tempTarget->GetSize();
			y2_Pos -= tempTarget->GetSize();
		}
	}

	switch (random)
	{
	case 0:
		xVec *= -1;
		break;
	case 1:
		yVec *= -1;
		break;
	default:
		break;
	}
	CreateObject(SmallAsteroidType, x1_Pos, y1_Pos,
		xVec, yVec, 1.2, -1, rand() % 360);
	CreateObject(SmallAsteroidType, x2_Pos, y2_Pos,
		-xVec, -yVec, tempTarget->GetSpeed(), 1, rand() % 360);
}


void 	GameObjectFactory::BulletIntersections()
{
	for (int i = (int)_bullets.size() - 1; i > -1; i--)
	{// Checking all Bullets
		Bullet* tempBullet = _bullets.at(i);
		for (int iTarg = (int)_smallAsteroids.size() - 1; iTarg > -1; iTarg--)
		{// Small Asteroids
			SmallAsteroid* tempTarget = _smallAsteroids.at(iTarg);
			if (tempBullet->CheckIntersect(tempTarget))
			{
				// Create Resource here
				CreateResource(tempTarget->GetPosX(), tempTarget->GetPosY());
				// Destroy both
				DestroyObject(ObjectsEnum::BulletType, i);
				DestroyObject(ObjectsEnum::SmallAsteroidType, iTarg);
				tempBullet = NULL;
				break;
			}
		}
		if (tempBullet == NULL)
			continue;// In case if Bullet Already Deleted
		for (int iTarg = (int)_bigAsteroids.size() - 1; iTarg > -1; iTarg--)
		{// Small Asteroids
			BigAsteroid* tempTarget = _bigAsteroids.at(iTarg);
			if (tempBullet->CheckIntersect(tempTarget))
			{// Create two small Asteroids
				BigAsteroidSplit(tempBullet, tempTarget);
				// Create Resource here
				CreateResource(tempTarget->GetPosX(), tempTarget->GetPosY());
				// Destroy Both
				DestroyObject(ObjectsEnum::BulletType, i);
				DestroyObject(ObjectsEnum::BigAsteroidType, iTarg);
				tempBullet = NULL;
				break;
			}
		}
	}
}

void 	GameObjectFactory::TorpedoIntersections()
{
	for (int i = (int)_torpedos.size() - 1; i > -1; i--)
	{// Checking all Bullets
		Torpedo* tempObj = _torpedos.at(i);
		for (int iTarg = (int)_smallAsteroids.size() - 1; iTarg > -1; iTarg--)
		{// Small Asteroids
			SmallAsteroid* tempTarget = _smallAsteroids.at(iTarg);
			if (tempObj->CheckIntersect(tempTarget))
			{
				// Create Resource here
				CreateResource(tempTarget->GetPosX(), tempTarget->GetPosY());
				// Destroy both
				DestroyObject(ObjectsEnum::TorpedoType, i);
				DestroyObject(ObjectsEnum::SmallAsteroidType, iTarg);
				tempObj = NULL;
				break;
			}
		}
		if (tempObj == NULL)
			continue;// In case if Bullet Already Deleted
		for (int iTarg = (int)_bigAsteroids.size() - 1; iTarg > -1; iTarg--)
		{// Small Asteroids
			BigAsteroid* tempTarget = _bigAsteroids.at(iTarg);
			if (tempObj->CheckIntersect(tempTarget))
			{// Create two small Asteroids
				BigAsteroidSplit(tempObj, tempTarget);
				// Create Resource here
				CreateResource(tempTarget->GetPosX(), tempTarget->GetPosY());
				// Destroy Both
				DestroyObject(ObjectsEnum::TorpedoType, i);
				DestroyObject(ObjectsEnum::BigAsteroidType, iTarg);
				tempObj = NULL;
				break;
			}
		}
	}
}

void 	GameObjectFactory::AsteroidsIntersections()
{
	// Checking intersections with all Asteroids
	for (int i = 0; i < (int)_bigAsteroids.size(); i++)
	{// Big Asteroids
		BigAsteroid* tempObj = _bigAsteroids.at(i);

		for (int iTarg = 0; iTarg < (int)_bigAsteroids.size(); iTarg++)
		{// Big Asteroids
			if (iTarg == i)
				continue;// If same Asteroid
			BigAsteroid* tempTarget = _bigAsteroids.at(iTarg);
			if (tempTarget->AllIntersectCalculated == true)
				continue;// If have calculated Intersection for this frame
			if (AsteroidCollisionHandle(tempObj, tempTarget))
				break;
		}
		if (tempObj->AllIntersectCalculated)
			continue; // If already bounced from someone
		for (int iTarg = 0; iTarg < (int)_smallAsteroids.size(); iTarg++)
		{// Small Asteroids
			SmallAsteroid* tempTarget = _smallAsteroids.at(iTarg);
			if (tempTarget->AllIntersectCalculated == true)
				continue;// If have calculated Intersection for this frame
			if (AsteroidCollisionHandle(tempObj, tempTarget))
				break;
		}
		tempObj->AllIntersectCalculated = true; // No need to check this Object
	}

	for (int i = 0; i < (int)_smallAsteroids.size(); i++)
	{// Small Asteroids
		SmallAsteroid* tempObj = _smallAsteroids.at(i);
		
		for (int iTarg = 0; iTarg < (int)_smallAsteroids.size(); iTarg++)
		{// Small Asteroids
			if (iTarg == i)
				continue;// If same Asteroid
			SmallAsteroid* tempTarget = _smallAsteroids.at(iTarg);
			if (tempTarget->AllIntersectCalculated == true)
				continue;// If have calculated Intersection for this frame
			if (AsteroidCollisionHandle(tempObj, tempTarget))
				break;
		}
		tempObj->AllIntersectCalculated = true; // No need to check this Object
	}
}

bool 	GameObjectFactory::PlayerIntersections()
{

	// Checking Intersections with all collectables
	for (int i = (int)_collectables.size() - 1; i > -1; i--)
	{
		Collectable* tempTarget = _collectables.at(i);
		if (player->CheckIntersect(tempTarget))
		{// If Picked object Logic
			player->RetrieveCollectable(tempTarget->type);
			DestroyObject(tempTarget->type, i);
		}
	}

	if (player->IsShielded())
		return false; // Shield protection from lethal damage

	// Checking intersections with all Asteroids
	for (int iTarg = 0; iTarg < (int)_bigAsteroids.size(); iTarg++)
	{// Big Asteroids
		BigAsteroid* tempTarget = _bigAsteroids.at(iTarg);
		if (player->CheckIntersect(tempTarget))
			return true; // Ship Crashed
	}
	
	for (int iTarg = 0; iTarg < (int)_smallAsteroids.size(); iTarg++)
	{// Small Asteroids
		SmallAsteroid* tempTarget = _smallAsteroids.at(iTarg);
		if (player->CheckIntersect(tempTarget))
			return true; // Ship Crashed
	}

	

	return false; // Ship Alive
}

void 	GameObjectFactory::CalculateIntersectionsAll()
{
	// Clear all Objects from calculated flag

	for (int i = 0; i < (int)_bigAsteroids.size(); i++)
	{// Asteroids
		ClearObjectFromFlags(_bigAsteroids.at(i));
	}
	for (int i = 0; i < (int)_smallAsteroids.size(); i++)
	{// Small Asteroids
		ClearObjectFromFlags(_smallAsteroids.at(i));
	}

	// std::cout << "Checking Intersections" << std::endl;
	
	BulletIntersections();
	TorpedoIntersections();
	if (brownianMotion) // Asteroid bouncing can be turned on/off
		AsteroidsIntersections();

	if (PlayerIntersections())
	{
		std::cout << "Spaceship Crashed" << std::endl;
		RestartBehaviour(RestartScenarioEnum::Death);
		player->RestartBehaviour();
	}
	// std::cout << "Intersection Check Over" << std::endl;

}