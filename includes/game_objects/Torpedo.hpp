
#ifndef TORPEDO_HPP
#define TORPEDO_HPP

#include <memory>
#include "AbstractGameObject.hpp"

class Asteroid;

class Torpedo final : public AbstractGameObject
{
private:
	int _targetID;

public:
	Torpedo(GameSDL_Window* window, PicTexture* newAvatar,
    	int xPos, int yPos, float xVec, float yVec,
		float speed, float rotation, float angle,
		int targetID);
	~Torpedo();

	int GetTargetID();
	bool AimTarget(Asteroid* target);
	// void TargetDestroyed();
	void CalculateAngle(int targX, int targY);
};





#endif