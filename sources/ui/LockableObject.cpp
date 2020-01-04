
#include "LockableObject.hpp"

LockableObject::LockableObject(/* args */)
{
	_isLocked = false;
	_lockPic = NULL;
	_rotationSpeed = 1.0f;
}

LockableObject::~LockableObject()
{
}


bool LockableObject::IsLocked()
{
	return _isLocked;
}

void LockableObject::SetLock(bool state)
{
	_isLocked = state;
	_angle = 0;
}

void LockableObject::SetLockPic(PicTexture* newPic)
{
	_lockPic = newPic;
}


void LockableObject::ShowLock(GameSDL_Window* window,
	int posX, int posY, int plX, int plY)
{
	_angle += _rotationSpeed;
	_lockPic->RenderPic(*window,
		plX - posX + window->GetWidthHalf() - _lockPic->GetWidth() / 1.5f,
		plY - posY + window->GetHeightHalf() - _lockPic->GetHeight() / 1.5f,
		NULL, _angle, NULL, SDL_FLIP_NONE);
}