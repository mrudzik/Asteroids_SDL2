
#include "GameObjectFactory.hpp"

void 	GameObjectFactory::CalculateIntersectionsAll()
{
	// Clear all Objects from calculated flag

	for (int i = 0; i < (int)_bigAsteroids.size(); i++)
	{// Asteroids
		BigAsteroid* tempObject = _bigAsteroids.at(i);

		tempObject->AllIntersectCalculated = false;
		if (tempObject->Intersecting)
			tempObject->WasIntersecting = true;
		else
			tempObject->WasIntersecting = false;
		tempObject->Intersecting = false;
	}
	for (int i = 0; i < (int)_smallAsteroids.size(); i++)
	{// Small Asteroids
		SmallAsteroid* tempObject = _smallAsteroids.at(i);

		tempObject->AllIntersectCalculated = false;
		if (tempObject->Intersecting)
			tempObject->WasIntersecting = true;
		else
			tempObject->WasIntersecting = false;
		tempObject->Intersecting = false;
	}
	// for (int i = 0; i < (int)_bullets.size(); i++)
	// {
	// 	_bullets.at(i)->AllIntersectCalculated = false;
	// }



	std::cout << "Checking Intersections" << std::endl;

	// Checking intersections with all
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
			if (tempObj->CheckIntersect(tempTarget) == 1)
			{
				tempObj->Intersecting = true;
				tempTarget->Intersecting = true;
				tempObj->BounceRand();
				tempTarget->BounceRand();
				break;
			}
		}
		for (int iTarg = 0; iTarg < (int)_smallAsteroids.size(); iTarg++)
		{// Small Asteroids
			SmallAsteroid* tempTarget = _smallAsteroids.at(iTarg);
			if (tempTarget->AllIntersectCalculated == true)
				continue;// If have calculated Intersection for this frame
			if (tempObj->CheckIntersect(tempTarget) == 1)
			{
				tempObj->Intersecting = true;
				tempTarget->Intersecting = true;
				tempObj->BounceRand();
				tempTarget->BounceRand();
				break;
			}
		}
		// for (int i = 0; i < (int)_bullets.size(); i++)
		// {
		// 	_bullets.at(i)->IntersectCalculated = false;
		// }
		tempObj->AllIntersectCalculated = true; // No need to check this Object
	}




	for (int i = 0; i < (int)_smallAsteroids.size(); i++)
	{// Small Asteroids
		SmallAsteroid* tempObj = _smallAsteroids.at(i);

		for (int iTarg = 0; iTarg < (int)_bigAsteroids.size(); iTarg++)
		{// Big Asteroids
			BigAsteroid* tempTarget = _bigAsteroids.at(iTarg);
			if (tempTarget->AllIntersectCalculated == true)
				continue;// If have calculated Intersection for this frame
			if (tempObj->CheckIntersect(tempTarget) == 1)
			{
				tempObj->Intersecting = true;
				tempTarget->Intersecting = true;
				tempObj->BounceRand();
				tempTarget->BounceRand();
				break;
			}
		}
		for (int iTarg = 0; iTarg < (int)_smallAsteroids.size(); iTarg++)
		{// Small Asteroids
			if (iTarg == i)
				continue;// If same Asteroid
			SmallAsteroid* tempTarget = _smallAsteroids.at(iTarg);
			if (tempTarget->AllIntersectCalculated == true)
				continue;// If have calculated Intersection for this frame
			if (tempObj->CheckIntersect(tempTarget) == 1)
			{
				tempObj->Intersecting = true;
				tempTarget->Intersecting = true;
				tempObj->BounceRand();
				tempTarget->BounceRand();
				break;
			}
		}
		// for (int i = 0; i < (int)_bullets.size(); i++)
		// {
		// 	_bullets.at(i)->IntersectCalculated = false;
		// }
		tempObj->AllIntersectCalculated = true; // No need to check this Object
	}
	// for (int i = 0; i < (int)_bullets.size(); i++)
	// {
	// 	_bullets.at(i)->IntersectCalculated = false;
	// }

	std::cout << "Intersection Check Over" << std::endl;

}