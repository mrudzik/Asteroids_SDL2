
#include "Torpedo.hpp"
#include "Asteroid.hpp"


Torpedo::Torpedo(GameSDL_Window* window, PicTexture* newAvatar,
    int xPos, int yPos, float xVec, float yVec,
	float speed, float rotation, float angle) : 
        AbstractGameObject(window, newAvatar, xPos, yPos, xVec, yVec,
        speed, rotation, angle)
{
	// _maxSize = 5;
}

Torpedo::~Torpedo()
{
	// if (_target != NULL)
	// 	_target->lockObj.TorpedoDestroyed();
}

// void Torpedo::TargetDestroyed()
// {
// 	_target = NULL;
// }


bool Torpedo::AimTarget(Asteroid* target)
{
	if (target == NULL)
		return false; // Protection
	// std::shared_ptr<Asteroid> tempObj = _target.lock();

	CalculateAngle(target->GetPosX(), target->GetPosY());
	_xVec = cos(_angle * M_PI / 180.0f) * 2;
	_yVec = sin(_angle * M_PI / 180.0f) * 2;
	std::cout << "Vec x: " << _xVec << " y: " << _yVec
		<< "\nPos x: " << _xPos << " y: " << _yPos
		<< std::endl;
	if (isnan(_xVec) || isnan(_yVec))
	{// If having some troubles
		// (posX == _xPos || posY == _yPos
		target->lockObj.SetLock(false);
		return false;
	}
	return true;
}


void Torpedo::CalculateAngle(int targX, int targY)
{
	bool 	halfFlag = false;
	if (targY < _yPos)
		halfFlag = true;

	int vecx_A = _xPos - targX;
	int vecy_A = _yPos - targY;
	int vecx_B = 10;
	int vecy_B = 0;
	double 	angle_cos = (vecx_A * vecx_B + vecy_A * vecy_B) /
		(sqrt(vecx_A * vecx_A + vecy_A * vecy_A) * sqrt(vecx_B * vecx_B + vecy_B * vecy_B));

	_angle = 90.0 - acos(angle_cos) * (180.0 / M_PI);
	if (halfFlag)
		_angle = 90.0 + (90.0 - _angle);
	_angle += 90; // Reversing SpaceShip
}
