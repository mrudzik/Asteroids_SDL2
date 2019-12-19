
#ifndef ABSTRACTGAMEOBJECT_HPP
#define ABSTRACTGAMEOBJECT_HPP

#include "PicTexture.hpp"
#include <cmath>

class AbstractGameObject
{

protected:
    // Current Position
    float   _xPos;
    float   _yPos;
    // Movement Vector
    float   _xVec;
    float   _yVec;
    // Speed modificator
    float   _speed;
    // Rotation stuff
    float   _rotationSpeed;
    float   _angle;

    // Size Radius;
    float   _sizeRadius;
    // Texture with sprite Avatar
    PicTexture  _Avatar;
    // Pointer to Window Controller
    GameSDL_Window*     _window;

public:
    AbstractGameObject(GameSDL_Window* window,
        std::string spritePath, int xPos, int yPos,
        float xVec, float yVec, float speed,
        float rotation, float angle);//, float size);
    ~AbstractGameObject();

    void CalculateMovement();
    int CheckIntersect(AbstractGameObject* target);

    void RenderOnWindow(int xPlayer, int yPlayer);

    void StopMoving();

};







#endif
