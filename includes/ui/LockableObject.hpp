
#ifndef LOCKABLE_OBJECT_HPP
#define LOCKABLE_OBJECT_HPP

#include "PicTexture.hpp"
#include "GameSDL_Window.hpp"
// #include "AbstractObject.hpp"

class LockableObject
{
private:
	bool _isLocked;
	float _angle;
	float _rotationSpeed;

	PicTexture* _lockPic;
	// AbstractObject* _gameObj;

public:
	LockableObject(/* args */);
	~LockableObject();

	void SetLock(bool state);
	void SetLockPic(PicTexture* newPic);

	void ShowLock(GameSDL_Window* window, int posX, int posY, int plX, int plY);

	bool IsLocked();
};




#endif