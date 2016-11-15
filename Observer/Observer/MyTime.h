#pragma once
#ifndef _MYTIME
#define _MYTIME
class MyTime
{
public:
	MyTime() {};
	~MyTime() {};
	MyTime(int hour, int min, int sec) :_hour(hour), _min(min), _sec(sec) {}
	int getHour() { return _hour; }
	int getMin() { return _min; }
	int getSec() { return _sec; }
private:
	int _hour;
	int _min;
	int _sec;
};

#endif // !_MYTIME

