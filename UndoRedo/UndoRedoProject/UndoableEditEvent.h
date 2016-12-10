#pragma once
#ifndef UNDOABLEEDITEVENT
#define UNDOABLEEDITEVENT

class UndoableEdit;

//Undoable编辑操作触发的事件，当发生编辑操作时，将其包装成一个事件，传给事件接收者
class UndoableEditEvent
{
public:
	UndoableEditEvent(UndoableEdit*edit);
	~UndoableEditEvent();
	UndoableEdit* getUndoableEdit();

private:
	UndoableEdit* undoableEdit;//编辑操作
};

UndoableEditEvent::UndoableEditEvent(UndoableEdit* edit)
{
	this->undoableEdit = edit;
}

UndoableEditEvent::~UndoableEditEvent()
{
}

inline UndoableEdit* UndoableEditEvent::getUndoableEdit()
{
	return undoableEdit;
}

//编辑操作触发的事件的监听者,只有一个undoableEditHappended抽象函数，由子类决定如何对传过来的
//事件进行处理
class UndoableEditListener
{
public:
	UndoableEditListener();
	~UndoableEditListener();
	virtual void undoableEditHappended(UndoableEditEvent* editEvent) = 0;
private:

};

UndoableEditListener::UndoableEditListener()
{
}

UndoableEditListener::~UndoableEditListener()
{
}
#endif // !UNDOABLEEDITEVENT

