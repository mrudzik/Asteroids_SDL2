
#include "LockableObject.hpp"

LockableObject::LockableObject()
{
	_isLocked = false;
	_lockPic = NULL;
	_rotationSpeed = 1.0f;
	_id = -1;
}

LockableObject::~LockableObject()
{
}

bool LockableObject::IsLocked()
{
	return _isLocked;
}

int LockableObject::GetID()
{
	return _id;
}

void LockableObject::SetLock(bool state)
{
	_isLocked = state;
	_angle = 0;
}

void LockableObject::SetLockData(PicTexture* newPic, int id)
{
	_lockPic = newPic;
	_id = id;
}


void LockableObject::ShowLock(GameSDL_Window* window,
	int posX, int posY, int plX, int plY)
{
	_angle += _rotationSpeed;
	_lockPic->RenderPic(*window,
		plX - posX + window->GetWidthHalf() - _lockPic->GetWidth() / 1.7f,
		plY - posY + window->GetHeightHalf() - _lockPic->GetHeight() / 1.7f,
		NULL, _angle, NULL, SDL_FLIP_NONE);
}