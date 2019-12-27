
#include "AbstractGameObject.hpp"
#include <cmath>

AbstractGameObject::AbstractGameObject(GameSDL_Window* window,
    PicTexture* newAvatar, int xPos, int yPos, float xVec, float yVec,
    float speed, float rotation, float angle)   //, float size)
{
    _window = window;
    _Avatar = newAvatar;
    //.LoadFromFile(spritePath, *_window);
    _xPos = xPos;
    _yPos = yPos;
    _xVec = xVec;
    _yVec = yVec;
    _speed = speed;
    _rotationSpeed = rotation;
    _angle = angle;
    // _sizeRadius = _Avatar->GetWidth() / 2;
	_maxSize = _Avatar->GetWidth() / 2;//= _sizeRadius;

	AllIntersectCalculated = false;
	WasIntersecting = false;
	Intersecting = false;
    // _size = size;
}

AbstractGameObject::~AbstractGameObject()
{ }



int AbstractGameObject::GetPosX()
{
	return _xPos + _Avatar->GetWidth() / 2;
}

int AbstractGameObject::GetPosY()
{
	return _yPos + _Avatar->GetHeight() / 2;
}

float AbstractGameObject::GetVecX()
{
	return _xVec;
}

float AbstractGameObject::GetVecY()
{
	return _yVec;
}

float AbstractGameObject::GetSpeed()
{
	return _speed;
}

float AbstractGameObject::GetAngle()
{
	return _angle;
}

float AbstractGameObject::GetSize()
{
	return _maxSize;
}













void AbstractGameObject::CalculateMovement(int mapWidth, int mapHeight)
{
	// // Normalising vectors and adjusting speed
	// float vecLen = sqrt(_xVec * _xVec + _yVec * _yVec);
	// if (vecLen > 1)
	// { // if Object is moving
	// 	_xVec /= vecLen;
	// 	_yVec /= vecLen;
	// 	_speed += vecLen;
	// }

	if (fabs(_xVec * _xVec + _yVec * _yVec) < 0.1f)
	{// If Scalar speed is very low
		_xVec = 0;
		_yVec = 0;
	}

    // Calculate on Map Position
    _xPos += _xVec * _speed;
    _yPos += _yVec * _speed;
    // Calculate Rotation angle
    _angle += _rotationSpeed;

	// Map Wrapping
	if (_xPos >= mapWidth)
		_xPos -= mapWidth;
	if (_xPos < 0)
		_xPos += mapWidth;
	
	if (_yPos >= mapHeight)
		_yPos -= mapHeight;
	if (_yPos < 0)
		_yPos += mapHeight;

}


void AbstractGameObject::RenderOnWindow(int xPlayer, int yPlayer)
{
    int xDif = xPlayer - _xPos + _window->GetWidthHalf() - _Avatar->GetWidth();
    int yDif = yPlayer - _yPos + _window->GetHeightHalf() - _Avatar->GetHeight();

    // TODO Protection to not render something that you cannot see

    _Avatar->RenderPic(*_window, xDif, yDif, NULL, _angle, NULL, SDL_FLIP_NONE);
	// _Avatar->RenderPicResized(*_window,
	// 	xDif, yDif,
	// 	NULL, _angle, NULL, SDL_FLIP_NONE,
	// 	5, 5);
}

void AbstractGameObject::StopMoving()
{
    _xVec = 0;
    _yVec = 0;
    _rotationSpeed = 0;
}


void AbstractGameObject::SetNewVec(float x, float y)
{
	_xVec = x;
	_yVec = y;
}
void AbstractGameObject::SetNewPos(int x, int y)
{
	_xPos = x;
	_yPos = y;
}


int AbstractGameObject::CheckIntersect(AbstractGameObject* target)
{
    // Formula to check distance between two dots
    float horDist = pow(GetPosX() - target->GetPosX(), 2.0f);
    float verDist = pow(GetPosY() - target->GetPosY(), 2.0f);

	// if (WasIntersecting)
	// { // For handling stucks between 3 and more objects
	// 	_sizeRadius -= 0.1f;
	// 	if (_sizeRadius < 0)
	// 		_sizeRadius = 0;
	// }
	// else
	// {// This will restore size
	// 	_sizeRadius = _maxSize;
	// }

    if ((horDist + verDist) <= pow(_maxSize + target->GetSize(), 2.0f))
        return 1;
	return 0;
}


void 	AbstractGameObject::StaticResolution(AbstractGameObject* target)
{// Not letting objects to overlapp each other
	
	// Distance between object centers
	float dist = sqrt((_xPos - target->GetPosX()) * (_xPos - target->GetPosX())
					+ (_yPos - target->GetPosY()) * (_yPos - target->GetPosY()));
	// ( obj1 (<-here->) obj2 )
	// How much this objects are overlapping divided by 2
	float overlapDistHalf = 0.5f * (dist - _maxSize - target->GetSize());

	// Displace current ball
	SetNewPos(_xPos - (overlapDistHalf * (_xPos - target->GetPosX()) / dist) - 10,
		_yPos - (overlapDistHalf * (_yPos - target->GetPosY()) / dist) - 10);
	// Displace target ball
	target->SetNewPos(target->GetPosX() + (overlapDistHalf * (_xPos - target->GetPosX()) / dist) + 10,
		target->GetPosY() + (overlapDistHalf * (_yPos - target->GetPosY()) / dist) + 10);
	
}


void 	AbstractGameObject::DynamicResolution(AbstractGameObject* target)
{
	// Distance between object centers
	float dist = sqrt(pow(target->GetPosX() - _xPos, 2)
					+ pow(target->GetPosY() - _yPos, 2));
	// Normal
	float nX = (target->GetPosX() - _xPos) / dist;
	float nY = (target->GetPosY() - _yPos) / dist;
	// Tangent
	float tgX = -nY;
	float tgY = nX;
	// Dot Product
	float dpTan1 = _xVec * tgX + _yVec * tgY;
	float dpTan2 = target->GetVecX() * tgX + target->GetVecY() * tgY;


	SetNewVec(tgX * dpTan1, tgY * dpTan1);
	target->SetNewVec(tgX * dpTan2, tgY * dpTan2);
}

// void 	AbstractGameObject::BounceFrom(AbstractGameObject* bounceFrom)
// {
// 	// Moving 
// 		// float angle = atan2(bounceFrom->GetPosY() -_yPos, bounceFrom->GetPosX() - _xPos);
// 		// float moveDist = _maxSize + bounceFrom->GetSize() -
// 		// 	sqrt(pow(bounceFrom->GetPosX() - _xPos, 2) + pow(bounceFrom->GetPosY() - _yPos, 2));

// 		// _xPos = cos(angle) * moveDist;
// 		// _yPos = cos(angle) * moveDist;

// 	// Bouncing Vector
// 	// Tangent Vector
// 	float tangX = bounceFrom->GetPosY() - _yPos;
// 	float tangY = -(bounceFrom->GetPosX() - _xPos);
// 	// Normalizing Vector
// 	float vectorLen = sqrt(pow(tangX, 2) + pow(tangY, 2));
// 	tangX = tangX / vectorLen;
// 	tangY = tangY / vectorLen;
// 	// Relative Velocity
// 	float relatX = _xVec - bounceFrom->GetVecX();
// 	float relatY = _yVec - bounceFrom->GetVecY();
// 	// Dot Product of Tangent and RelativeVel vectors
// 	// Gives Length of Velocity Component parallel to the tangent
// 	float length = tangX * relatX + tangY * relatY;
// 	// Get the vector component parallel to the tangent
// 	float tangVelX = tangX * length;
// 	float tangVelY = tangY * length;
// 	// Velocity perpendicular to tangent
// 	float velPerpX = relatX - tangVelX;
// 	float velPerpY = relatY - tangVelY;

// 	SetNewVec(_xVec - velPerpX, _yVec - velPerpY);
// 	bounceFrom->SetNewVec(bounceFrom->GetVecX() + velPerpX,
// 		bounceFrom->GetVecY() + velPerpY);
// }


