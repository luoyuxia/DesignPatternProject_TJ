#pragma once
#ifndef _OBSERVER
#define _OBSERVER
#include"Clock.h"
#include"MyTime.h"
#include"Observable.h"
class Observable;
class Observer
{
public:
	Observer() { }
	~Observer() { }
	virtual void update(Observable* o) {};
};



#endif // !_OBSERVER

