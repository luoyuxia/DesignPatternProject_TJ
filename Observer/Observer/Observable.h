#pragma once
#ifndef _OBSERVABLE
#define _OBSERVABLE
#include<vector>
#include"Observer.h"
class Observer;
using namespace std;
class Observable
{
public:
	Observable();
	~Observable();
	void addObserver(Observer* observer)
	{
		for (int i = 0; i < obs.size(); i++)
		{
			if (obs[i] == observer)
				return;
		}
		obs.push_back(observer);
	};
	void deleteObserver(Observer* observer)
	{
		Observer* del = NULL;
		vector<Observer*>::iterator iter = obs.begin();
		for (; iter != obs.end(); iter++)
		{
			if (*iter == observer)
			{
				del = *iter;
				break;
			}
		}
		obs.erase(iter, iter + 1);
		if(del!=NULL) delete del;
	}
	void notifyObservers()
	{
		if (_changed == false)return;
		vector<Observer*>::iterator iter = obs.begin();
		for (; iter != obs.end(); iter++)
		{
			(*iter)->update(this);
		}
		clearChanged();
	}
/*	void notifyObservers()
	{
		notifyObservers(NULL);
	}*/

	void setChanged() { _changed = true; }
	void clearChanged() { _changed = false; }
private:
	vector<Observer*> obs;
	bool _changed;
};

Observable::Observable()
{
}

Observable::~Observable()
{

}
#endif // !_OBSERVABLE

