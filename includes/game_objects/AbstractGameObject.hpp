
#ifndef ABSTRACTGAMEOBJECT_HPP
#define ABSTRACTGAMEOBJECT_HPP

#include "PicTexture.hpp"

class AbstractGameObject
{

protected:
    // Current Position
    float   _xPos;
    float   _yPos;
    // Movement Vector
    float   _xVec;
    float   _yVec;
	// Acceleration vector
	float 	_xAcc;
	float	_yAcc;
    // Speed modificator
    float   _speed;

    // Rotation stuff
    float   _rotationSpeed;
    float   _angle;
    // Size Radius;
	float 	_maxSize;
    // float   _sizeRadius;
    
    // Texture with sprite Avatar
    PicTexture*     _Avatar;
    // Pointer to Window Controller
    GameSDL_Window* _window;

public:
	bool	AllIntersectCalculated; // For Optimization purposes
	
    AbstractGameObject(GameSDL_Window* window,
        PicTexture* newAvatar, int xPos, int yPos,
        float xVec, float yVec, float speed,
        float rotation, float angle);//, float size);
    ~AbstractGameObject();

	int GetPosX();
	int GetPosY();
	float GetVecX();
	float GetVecY();
	float GetSpeed();
	float GetAngle();
	float GetSize();
	


    void CalculateMovement(int mapWidth, int mapHeight);
    int 	CheckIntersect(AbstractGameObject* target);
	void 	StaticResolution(AbstractGameObject* target);
	void	DynamicResolution(AbstractGameObject* target);
	// void 	BounceFrom(AbstractGameObject* bounceFrom);

	void RestoreSize();

    void virtual RenderOnWindow(int xPlayer, int yPlayer);

    void StopMoving();
	void SetNewVec(float x, float y);
	void SetNewPos(int x, int y);


};







#endif
