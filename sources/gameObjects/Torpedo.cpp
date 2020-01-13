
#include "Torpedo.hpp"
#include "Asteroid.hpp"


Torpedo::Torpedo(GameSDL_Window* window, PicTexture* newAvatar,
    int xPos, int yPos, float xVec, float yVec,
	float speed, float rotation, float angle,
	int targetID) : 
        AbstractGameObject(window, newAvatar, xPos, yPos, xVec, yVec,
        speed, rotation, angle)
{
	_targetID = targetID;
}

Torpedo::~Torpedo()
{
}



int Torpedo::GetTargetID()
{
	return _targetID;
}




bool Torpedo::AimTarget(Asteroid* target, int mapWidth, int mapHeight)
{
	if (target == NULL)
		return false; // Protection

	int targX = target->GetPosX();
	int targY = target->GetPosY();

	CalcShortestPos(&targX, &targY, mapWidth, mapHeight);
	CalculateAngle(targX, targY);

	// My "Cold Siberia" formula
	float x_vec = fabs(_xPos - targX);
	float y_vec = fabs(_yPos - targY);
	float dist = sqrt((x_vec * x_vec) + (y_vec * y_vec));
	float len = _speed;
	_xVec = -1 * (_xPos - (_xPos + (targX - _xPos) * (len / dist)));
	_yVec = -1 * (_yPos - (_yPos + (targY - _yPos) * (len / dist)));


	if (isnan(_xVec) || isnan(_yVec))
	{// If having some troubles
		target->lockObj.SetLock(false);
		return false;
	}
	return true;
}


void Torpedo::CalcShortestPos(int* targX, int* targY, int mapWidth, int mapHeight)
{
	int xDistCur = fabs(*targX - _xPos);
	int yDistCur = fabs(*targY - _yPos);

	// Checking shortest X
	if (fabs(*targX + mapWidth -_xPos) < xDistCur)
		*targX += mapWidth;
	else if (fabs(*targX - mapWidth - _xPos) < xDistCur)
		*targX -= mapWidth;
	// Checking shortest Y
	if (fabs(*targY + mapHeight -_yPos) < yDistCur)
		*targY += mapHeight;
	else if (fabs(*targY - mapHeight - _yPos) < yDistCur)
		*targY -= mapHeight;
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
}
