#pragma once
#ifndef _ENTRYEXCEPTION
#define _ENTRYEXCEPTION
#include<string>
#include<iostream>
using namespace std;
class EnTryException
{
public:
	EnTryException(char * s) :_message(s) {};
	EnTryException(string s) :_message(s) {};
	EnTryException() :_message("Entry Exception!") {}
	~EnTryException() {};
	void printException(ostream &os = cout) { os << _message<<"\n"; }

private:
	string _message;
};


#endif // !_ENTRYEXCEPTION

