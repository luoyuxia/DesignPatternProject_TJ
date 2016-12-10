#pragma once
#ifndef _ENTRY
#define _ENTRY
#include<string>
#include<iostream>
#include"EntryException.h"
#define MAXSIZE 64
#define ROOT "root"
using namespace std;
class Entry
{
public:
	Entry();
	~Entry();
	virtual string getName();
	virtual int getSize();
	virtual void add(Entry* entry);
	virtual void deleteEntry(Entry* entry);
	virtual string getType();
	virtual bool isDir() {return false;}
	void print();
	string tostring();
	virtual void printList(string prefix);
private:

};

Entry::Entry()
{
}

Entry::~Entry()
{

}
void Entry::print()
{
	printList("\n");
	cout << "\n";
}
inline string Entry::tostring()
{
	char num[MAXSIZE];
	sprintf_s(num, "%d", getSize());
	return string(getName()+"("+num+")" + " " + getType());
}
void Entry::printList(string prefix)
{

}
inline int Entry::getSize()
{
	return 0;
}
inline void Entry::add(Entry* entry)
{
	throw EnTryException("����!�޷�����ļ�!\n");
}
inline void Entry::deleteEntry(Entry * entry)
{
	throw EnTryException("����!�޷�ɾ���ļ�!\n");
}
inline string Entry::getType()
{
	return string();
}
inline string Entry::getName()
{
	return "";
}

#endif // !_ENTRY

