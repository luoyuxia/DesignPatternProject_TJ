#pragma once
#ifndef MYEXCEPTION
#define MYEXCEPTION
#include <string>
#include<iostream>
using namespace std;
using namespace System::Windows::Forms;

//自定义的异常
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
}


//不能进行Undo的异常
class CannotUndoException :public MyException
{
public:
	CannotUndoException() :MyException("不能再撤销操作了 ") {};
	~CannotUndoException() {};

private:

};


//不能进行Redo的异常
class CannotRedoException :public MyException
{
public:
	CannotRedoException();
	~CannotRedoException();

private:

};

CannotRedoException::CannotRedoException() :MyException("不能再重做了")
{

}

CannotRedoException::~CannotRedoException()
{
}


//不能添加编辑操作的异常
class CannotAddEditException :public MyException
{
public:
	CannotAddEditException();
	~CannotAddEditException();

private:

};

CannotAddEditException::CannotAddEditException() :MyException("不能添加Edit")
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

UndoOverFlowException::UndoOverFlowException() :MyException("undo操作已经超过了容器的大小了！")
{

}

UndoOverFlowException::~UndoOverFlowException()
{
}
#endif // !MYEXCEPTION

