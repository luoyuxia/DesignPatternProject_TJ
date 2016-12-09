#pragma once
#ifndef UNDOABLEEDITEVENT
#define UNDOABLEEDITEVENT
class UndoableEdit;
class UndoableEditEvent
{
public:
	UndoableEditEvent(UndoableEdit*edit);
	~UndoableEditEvent();
	UndoableEdit* getUndoableEdit();

private:
	UndoableEdit* undoableEdit;
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

