
#ifndef FPS_TIMER_HPP
#define FPS_TIMER_HPP

#include "GameSDL_Window.hpp"
#include <sstream>

class FPS_Timer
{// Light FPS Timer
// Counts real frames from real second

private:

	Uint32 timerStart;
	Uint32 timerCurrent;
	int _countedFrames = 0;
	int _avgFPS;
	
	std::stringstream 	_textFPS;


public:
	FPS_Timer(/* args */);
	~FPS_Timer();

	int 			CountFrames();
	std::string 	TextFrames();
};




#endif