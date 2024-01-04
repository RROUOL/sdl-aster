#pragma once
#include <stdio.h>

#ifndef aTimerFILE
#define aTimerFILE
#include <iostream>
#include <SDL.h>
class SZ_Timer
{
		// written by oszymanezyk@lincoln.ac.uk
		// part of games programming module
	private:
		int startTicks; // SDL time when the timer started 
	public:
		const int DELTA_TIME = 17;
		SZ_Timer();
		//SDL timer stuff
		void resetTicksTimer(); // resets timer to zero
		int getTicks(); // returns how much time has passed since timer has been reset
	};
#endif


