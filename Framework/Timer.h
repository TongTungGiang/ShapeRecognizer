//------------------------------------------------------------------------------------------
//
//  Timer.h
//
//  Created by CNTA.C++ Team in 2014
//
#ifndef TIMER_H
#define TIMER_H

#include <SDL\SDL.h>

namespace Framework
{

	class Timer
	{
	private:
		static Timer* singleton;
		Timer() {};

	public:
		static Timer* instance()
		{
			if (!singleton)
			{
				singleton = new Timer();
			}
			return singleton;
		}

		unsigned int fwt_getTime();
		void fwt_destroy();
	};

}

#endif