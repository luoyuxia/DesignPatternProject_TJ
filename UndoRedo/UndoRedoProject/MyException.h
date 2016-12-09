#pragma once
#ifndef MYEXCEPTION
#define MYEXCEPTION
#include <string>
#include<iostream>
using namespace std;
using namespace System::Windows::Forms;
class MyException
{
public:
	MyException(string error);
	~MyException();
	string printException();
private:
	string errorMessage;
};

MyException::MyException(string error = "error")
{
	errorMessage = error;
}

MyException::~MyException()
{

}
string MyException::printException()
{
	return errorMessage;
	//	cout << errorMessage;
}

class CannotUndoException :public MyException
{
public:
	CannotUndoException() :MyException("�����ٳ��������� ") {};
	~CannotUndoException() {};

private:

};

class CannotRedoException :public MyException
{
public:
	CannotRedoException();
	~CannotRedoException();

private:

};

CannotRedoException::CannotRedoException() :MyException("������������")
{

}

CannotRedoException::~CannotRedoException()
{
}

class CannotAddEditException :public MyException
{
public:
	CannotAddEditException();
	~CannotAddEditException();

private:

};

CannotAddEditException::CannotAddEditException() :MyException("�������Edit")
{
}

CannotAddEditException::~CannotAddEditException()
{
}
class UndoOverFlowException :MyException
{
public:
	UndoOverFlowException();
	~UndoOverFlowException();

private:

};

UndoOverFlowException::UndoOverFlowException() :MyException("undo�����Ѿ������������Ĵ�С�ˣ�")
{

}

UndoOverFlowException::~UndoOverFlowException()
{
}
#endif // !MYEXCEPTION

