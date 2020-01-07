
#ifndef LOCKABLE_OBJECT_HPP
#define LOCKABLE_OBJECT_HPP

#include "PicTexture.hpp"
#include "GameSDL_Window.hpp"

class LockableObject
{
private:
	bool _isLocked;
	float _angle;
	float _rotationSpeed;

	PicTexture* _lockPic;
	int 		_id;

public:

	LockableObject();
	~LockableObject();

	void SetLock(bool state);
	void SetLockData(PicTexture* newPic, int id);

	void ShowLock(GameSDL_Window* window, int posX, int posY, int plX, int plY);
	bool IsLocked();
	int	GetID();

};




#endif