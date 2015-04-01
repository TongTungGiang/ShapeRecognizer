//------------------------------------------------------------------------------------------
//
//  Timer.cpp
//
//  Created by CNTA.C++ Team in 2014
//
#include "Timer.h"

namespace Framework
{

	Timer* Timer::singleton = NULL;

	unsigned int Timer::fwt_getTime()
	{
		return SDL_GetTicks();
	}

	void Timer::fwt_destroy()
	{
		delete singleton;
	}

}