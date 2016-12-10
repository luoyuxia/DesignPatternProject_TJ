#pragma once
#ifndef _FILE
#define _FILE
#include"Entry.h"

class File :public Entry
{
public:
	File(string name , int size=0);
	
	File();
	~File();
	virtual string getName();
	virtual int getSize();
	virtual string getType();
	virtual void printList(string prefix);
	virtual Entry* clone() { return new File(_name, _size); }
private:
	string _name;
	int _size;
};

File::File(string name, int  size) :_name(name),_size(size)
{
}
File::File()
{
	File("null", 0);
}

File::~File()
{
} 
string File::getName()
{
	return _name;
}

int File::getSize()
{
	return _size;
}

inline string File::getType()
{
	return string("@нд╪Ч@");
}

void File::printList(string prefx)
{
	cout << prefx + "/" +tostring()+"\n";
}
#endif // !_FILE
