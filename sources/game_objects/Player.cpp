#include "Player.hpp"

Player::Player(GameSDL_Window* window, PicTexture* newAvatar,
    int xPos, int yPos, float xVec, float yVec,
	float speed, float rotation, float angle,
	PicTexture* newShieldPic) : 
        AbstractGameObject(window, newAvatar, xPos, yPos, xVec, yVec,
        speed, rotation, angle)
{
	_slowingSpeed = 0.1f;
	_speed = 1;
	_screenPosX = window->GetWidthHalf() - newAvatar->GetWidth() / 4;
	_screenPosY = window->GetHeightHalf() - newAvatar->GetHeight() / 4;
	_score = 0;

	// Shield stuff
	_shieldPic = newShieldPic;
	_isShielded = false;
	_shieldAngle = 0;
}

Player::~Player()
{
}

int Player::GetScore()
{
	return _score;
}
bool Player::IsShielded()
{
	return _isShielded;
}

void Player::RestartBehaviour()
{
	_xPos = 0;
	_yPos = 0;
	_xVec = 0;
	_yVec = 0;
	_speed = 1;
	_score = 0;

	_shieldAngle = 0;
}

void Player::MoveX(float xVec)
{
	_xVec = xVec;
}
void Player::MoveY(float yVec)
{
	_yVec = yVec;
}

void	SlowVector(float& vect, float slowingSpeed)
{
	if (vect != 0)
	{// If moving on this axis
		if (vect < 0)
		{// Moving Negative
			vect += slowingSpeed;
			if (vect >= 0)
				vect = 0;// Finaly stops
		}
		else
		{// Moving Positive
			vect -= slowingSpeed;
			if (vect <= 0)
				vect = 0;// Finaly stops
		}
	}
}

void Player::InertiaDampeners()
{
	SlowVector(_xVec, _slowingSpeed);
	SlowVector(_yVec, _slowingSpeed);
}


void Player::CalculateAngle(int mouseScreenPosX, int mouseScreenPosY)
{
	bool 	halfFlag = false;
	if (mouseScreenPosY < _screenPosY)
		halfFlag = true;

	int vecx_A = _screenPosX - mouseScreenPosX;
	int vecy_A = _screenPosY - mouseScreenPosY;
	int vecx_B = 10;
	int vecy_B = 0;
	double 	angle_cos = (vecx_A * vecx_B + vecy_A * vecy_B) /
		(sqrt(vecx_A * vecx_A + vecy_A * vecy_A) * sqrt(vecx_B * vecx_B + vecy_B * vecy_B));

	_angle = 90.0 - acos(angle_cos) * (180.0 / M_PI);
	if (halfFlag)
		_angle = 90.0 + (90.0 - _angle);
	_angle += 180; // Reversing SpaceShip

	// std::cout << "Angle : " << _angle << std::endl;
	return;
}

void Player::RenderOnWindow(int xPlayer, int yPlayer)
{
	int xDif = xPlayer - _xPos + _window->GetWidthHalf();
    int yDif = yPlayer - _yPos + _window->GetHeightHalf();

    // TODO Protection to not render something that you cannot see

	if (_isShielded)
	{
		_shieldAngle += _rotationSpeed;
		_shieldPic->RenderPic(*_window,
		xDif - _shieldPic->GetWidth() / 1.5, yDif - _shieldPic->GetHeight() / 1.5,
		NULL, _shieldAngle, NULL, SDL_FLIP_NONE);
	}
    _Avatar->RenderPic(*_window,
		xDif - _Avatar->GetWidth(), yDif - _Avatar->GetHeight(),
		NULL, _angle, NULL, SDL_FLIP_NONE);
}



void Player::RetrieveCollectable(ObjectsEnum type)
{
	if (type == ObjectsEnum::CrystalWhiteType)
		_score += 10;
	if (type == ObjectsEnum::CrystalGreenType)
		_score += 15;
	if (type == ObjectsEnum::CrystalBlueType)
		_score += 25;
	if (type == ObjectsEnum::CrystalPurpleType)
		_score += 40;
}

void Player::SetShieldActive(bool state)
{
	_isShielded = state;
}