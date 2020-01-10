
#ifndef ABSTRACTGAMEOBJECT_HPP
#define ABSTRACTGAMEOBJECT_HPP

#include "PicTexture.hpp"

enum ObjectsEnum
{
	BigAsteroidType,
	SmallAsteroidType,
	BulletType,
	PlayerType,
	CrystalWhiteType,
	CrystalGreenType,
	CrystalBlueType,
	CrystalPurpleType,
	TorpedoType,
	ShieldBatteryType,
	TorpedoAmmoType,
};


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
	float 	_maxSize;
 
	// This shifts for optimization purposes
	// Used on Rendering
	int _xShift;
	int _yShift;
    
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

	void RestoreSize();

    void virtual RenderOnWindow(int xPlayer, int yPlayer);

    void StopMoving();
	void SetNewVec(float x, float y);
	void SetNewPos(int x, int y);


};







#endif
