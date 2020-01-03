#ifndef COLLECTABLE_HPP
#define COLLECTABLE_HPP

#include "AbstractGameObject.hpp"

class Collectable final: public AbstractGameObject
{
private:
    Uint32 	_timeSpawn;
    Uint32 	_timeLive;
	Uint32 	_timeBlinkStart;
	Uint32	_timeBlinkInterval;

    bool	_isShowable;
public:
	ObjectsEnum	type;

    Collectable(GameSDL_Window* window, PicTexture* newAvatar,
        int xPos, int yPos, float xVec, float yVec, float speed,
        float rotation, float angle);
    ~Collectable();

    bool DestroyTimer();

	bool IsShowable();
};




#endif