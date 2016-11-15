#pragma once
#ifndef _TIMECLOCKSHOW
#define _TIMECLOCKSHOW
#include "Timer.h"
#include"TimeObserver.h"
class TimeClockShow
{
public:
	TimeClockShow();
	~TimeClockShow();
	void startRun();
private:
	Timer* timer;
};

TimeClockShow::TimeClockShow()
{
	timer = new Timer();
}

TimeClockShow::~TimeClockShow()
{
	delete timer;
}

void TimeClockShow::startRun()
{
	timer->addObserver(TimeObserver::createDigitalClockObserver());
	timer->addObserver(TimeObserver::createNormalClockObserver());
	while (true)
	{
		timer->resetCurrentTime();
		timer->setChanged();
		timer->notifyObservers();
		Sleep(1000);
	}
	
}
#endif
// _TIMECLOCKSHOW

