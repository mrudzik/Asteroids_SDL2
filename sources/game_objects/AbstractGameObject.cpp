
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

    if ((horDist + verDist) <= pow(_sizeRadius + target->_sizeRadius, 2.0f))
        return 1;
    return 0;
}

void AbstractGameObject::RenderOnWindow(int xPlayer, int yPlayer)
{
    int xDif = xPlayer + _xPos + _window->GetWidthHalf();// + _sizeRadius;
    int yDif = yPlayer + _yPos + _window->GetHeightHalf();// - _sizeRadius;

    // TODO Protection to not render something that you cannot see

    _Avatar->RenderPic(*_window, xDif, yDif, NULL, _angle, NULL, SDL_FLIP_NONE);
}

void AbstractGameObject::StopMoving()
{
    _xVec = 0;
    _yVec = 0;
    _rotationSpeed = 0;
}


