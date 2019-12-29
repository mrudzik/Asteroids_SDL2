
#include "FPS_Timer.hpp"

FPS_Timer::FPS_Timer(/* args */)
{
	timerStart = SDL_GetTicks();
}

FPS_Timer::~FPS_Timer()
{
}


int 	FPS_Timer::CountFrames()
{
	// This will count Frame
	_countedFrames++;	
	// Timer for every second
	timerCurrent = SDL_GetTicks();
	if (timerCurrent > timerStart + 1000.0f)
	{// This will be true every second
		timerStart = timerCurrent;

		_avgFPS = _countedFrames;
		_countedFrames = 0;
	}

	return _avgFPS;
}

std::string 	FPS_Timer::TextFrames()
{
	_textFPS.str("");
	_textFPS << "FPS: " << CountFrames();
	return _textFPS.str();
}

