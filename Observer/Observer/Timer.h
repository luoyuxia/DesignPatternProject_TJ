#ifndef _TIMER
#define _TIMER
#include<ctime>
#include"Observable.h"
class Timer :public Observable
{
public:
	Timer();
	~Timer();
	void resetCurrentTime();
	int getHour() { return _time->getHour(); }
	int getMin() {return _time->getMin(); }
	int getSec() { return _time->getSec(); };
private:
	MyTime* _time = NULL;
};

Timer::Timer()
{
	resetCurrentTime();
}

Timer::~Timer()
{
	delete _time;
}
void Timer::resetCurrentTime()
{
	time_t now;
	time(&now);
	tm* t_m = new tm();
	localtime_s(t_m, &now);
	if (_time != NULL) delete _time;
	_time = new MyTime(t_m->tm_hour, t_m->tm_min, t_m->tm_sec);
}


#endif // !_TIMER
