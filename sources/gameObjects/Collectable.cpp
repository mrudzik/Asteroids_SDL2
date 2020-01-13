
#include "Collectable.hpp"

Collectable::Collectable(GameSDL_Window* window, PicTexture* newAvatar,
    int xPos, int yPos, float xVec, float yVec, float speed, float rotation,
    float angle) : 
        AbstractGameObject(window, newAvatar, xPos, yPos, xVec, yVec,
        speed, rotation, angle)
{
    _isShowable = true;
    _timeSpawn = SDL_GetTicks();
    _timeLive = _timeSpawn + 10000;
    _timeBlinkStart = _timeSpawn + 6000;
    _timeBlinkInterval = 150;
}

Collectable::~Collectable()
{
}




bool Collectable::DestroyTimer()
{
    Uint32 timeNow = SDL_GetTicks();
    _isShowable = true;

    if (_timeLive < timeNow)
        return true; // Life time is ended
    
    if (_timeBlinkStart < timeNow)
    {// Time for blinking
        if (((timeNow - _timeBlinkStart) / _timeBlinkInterval) % 2 == 0)
        {
            _isShowable = false;
        }
    }
    return false;
}


bool    Collectable::IsShowable()
{
    return _isShowable;
}