#pragma once
#ifndef _TIMEOBSERVER
#define _TIMEOBSERVER
#include"Observer.h"
#include"Clock.h"
#include"Timer.h"
class TimeObserver:public Observer
{
public:
	TimeObserver(Clock* c) :Observer() { _clock = c; }
	~TimeObserver(){};
	virtual void update(Observable* o)
	{
		Timer* timer = (Timer*)o;
		_clock->updateClock(timer->getHour(), timer->getMin(), timer->getSec());
	}
	static Observer* createNormalClockObserver()
	{
		return new TimeObserver(new NormalClock());
	}
	static Observer* createDigitalClockObserver()
	{
		return new TimeObserver(new DigitalClock());
	}
private:
	Clock* _clock;

};


#endif // !_TIMEOBSERVER

