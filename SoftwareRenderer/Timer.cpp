/*
	Timer.cpp
	Author: Dean Marsinelli
*/

#include <Windows.h>

#include "Timer.h"

Timer::Timer()
{
	__int64 frequency;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	milli = 1.0f / (float)((double)frequency / 1000.0);
	Start();
}

void Timer::Stop()
{
	if (!stopped)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&currentCount);
		stopped = true;
	}
}

void Timer::Start()
{
	stopped = false;
	QueryPerformanceCounter((LARGE_INTEGER*)&startCount);
}

float Timer::Tick() const
{
	if (!stopped)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&currentCount);
		return (float)(currentCount - startCount) * milli;
	}
	else
	{
		return (float)(currentCount - startCount) * milli;
	}
}
