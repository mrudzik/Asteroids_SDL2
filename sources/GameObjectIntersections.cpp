
#include "GameObjectFactory.hpp"





void 	ClearObjectFromFlags(AbstractGameObject* tempObject)
{
	tempObject->AllIntersectCalculated = false;
	if (tempObject->Intersecting)
		tempObject->WasIntersecting = true;
	else
		tempObject->WasIntersecting = false;
	tempObject->Intersecting = false;
}

int 	AsteroidCollisionHandle(AbstractGameObject* tempObj, AbstractGameObject* tempTarget)
{
	if (tempObj->CheckIntersect(tempTarget) == 1)
	{
		tempObj->Intersecting = true;
		tempTarget->Intersecting = true;
		tempObj->BounceFrom(tempTarget);
		tempTarget->BounceFrom(tempObj);

		tempObj->AllIntersectCalculated = true;
		tempTarget->AllIntersectCalculated = true;
		return 1;
	}
	return 0;
}

void	GameObjectFactory::BigAsteroidSplit(Bullet* tempBullet, BigAsteroid* tempTarget)
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



	std::cout << "Checking Intersections" << std::endl;

	for (int i = (int)_bullets.size() - 1; i > -1; i--)
	{// Checking all Bullets
		Bullet* tempBullet = _bullets.at(i);
		for (int iTarg = (int)_smallAsteroids.size() - 1; iTarg > -1; iTarg--)
		{// Small Asteroids
			SmallAsteroid* tempTarget = _smallAsteroids.at(iTarg);
			if (tempBullet->CheckIntersect(tempTarget))
			{// Only Destroy both
				DestroyObject(ObjectsEnum::BulletType, i);
				DestroyObject(ObjectsEnum::SmallAsteroidType, iTarg);
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
				// Destroy Both
				DestroyObject(ObjectsEnum::BulletType, i);
				DestroyObject(ObjectsEnum::BigAsteroidType, iTarg);
				break;
			}
		}
	}


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

		// for (int iTarg = 0; iTarg < (int)_bigAsteroids.size(); iTarg++)
		// {// Big Asteroids
		// 	BigAsteroid* tempTarget = _bigAsteroids.at(iTarg);
		// 	if (tempTarget->AllIntersectCalculated == true)
		// 		continue;// If have calculated Intersection for this frame
		// 	if (AsteroidCollisionHandle(tempObj, tempTarget))
		// 		break;
		// }
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
	
	std::cout << "Intersection Check Over" << std::endl;

}