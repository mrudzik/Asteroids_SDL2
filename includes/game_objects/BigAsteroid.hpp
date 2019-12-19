
#ifndef BIGASTEROID_HPP
#define BIGASTEROID_HPP

#include "AbstractGameObject.hpp"

class BigAsteroid : AbstractGameObject
{

private:

    /* data */
public:

    BigAsteroid(GameSDL_Window* window,
        std::string spritePath, int xPos, int yPos,
        float xVec, float yVec, float speed,
        float rotation, float angle, float size);
    ~BigAsteroid();

};





#endif