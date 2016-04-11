/*
	Timer.h
	Author: Dean Marsinelli

	A basic timer to keep track of delta time
	between frames.
*/

#pragma once

class Timer
{
public:
	Timer();
	void Start();
	void Stop();
	float Tick() const;
private:
	float milli;
	bool stopped;
	__int64 currentCount;
	__int64 startCount;
};
