
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
    _sizeRadius = _Avatar->GetWidth() / 2.5f;
	_maxSize = _sizeRadius;

	AllIntersectCalculated = false;
	WasIntersecting = false;
	Intersecting = false;
    // _size = size;
}

AbstractGameObject::~AbstractGameObject()
{ }


void AbstractGameObject::CalculateMovement()
{
    // Calculate on Map Position
    _xPos += _xVec * _speed;
    _yPos += _yVec * _speed;
    // Calculate Rotation angle
    _angle += _rotationSpeed;

}

int AbstractGameObject::CheckIntersect(AbstractGameObject* target)
{
    // TODO Protection from multiple checks of intersection
    // Something like flags

    // Formula to check distance between two dots
    float horDist = pow(_xPos - target->_xPos, 2.0f);
    float verDist = pow(_yPos - target->_yPos, 2.0f);

	if (WasIntersecting)
	{ // For handling stucks between 3 and more objects
		_sizeRadius -= 0.1f;
		if (_sizeRadius < 0)
			_sizeRadius = 0;
	}
	else
	{// This will restore size
		_sizeRadius = _maxSize;
	}

    if ((horDist + verDist) <= pow(_sizeRadius + target->_sizeRadius, 2.0f))
        return 1;
	return 0;
}

void AbstractGameObject::RenderOnWindow(int xPlayer, int yPlayer)
{
    int xDif = xPlayer + _xPos + _window->GetWidthHalf();
    int yDif = yPlayer + _yPos + _window->GetHeightHalf();

    // TODO Protection to not render something that you cannot see

    _Avatar->RenderPic(*_window, xDif, yDif, NULL, _angle, NULL, SDL_FLIP_NONE);
}

void AbstractGameObject::StopMoving()
{
    _xVec = 0;
    _yVec = 0;
    _rotationSpeed = 0;
}

void 	AbstractGameObject::BounceRand()
{
	int random = rand() % 4;
	float randDir = random / 10;

	if (random == 0)
	{
		_rotationSpeed += 0.1f;
	}
	else if (random == 1)
	{
		_rotationSpeed += -0.1f;
	}
	else if (random == 2)
	{
		_rotationSpeed += -0.3f;
		_xVec -= randDir;
		_yVec += randDir;
	}
	else
	{
		_rotationSpeed += 0.2f;
		_xVec += randDir;
		_yVec -= randDir;
	}
	
	_rotationSpeed *= -1;
	_xVec *= -1;
	_yVec *= -1;
}


