#pragma once
#ifndef UNDOABLEEDITSUPPORT
#define UNDOABLEEDITSUPPORT
#include"UndoableEditEvent.h"
#include"UndoRedoComponent.h"
class UndoableEditListener;
public class UndoRedoEditSupport
{
public:
	UndoRedoEditSupport();
	~UndoRedoEditSupport();
	void addUndoableEditListener(UndoableEditListener* editListener);
	void removeUndoableEditListener(UndoableEditListener* editListener);
	void postEdit(UndoableEdit* edit);
	vector<UndoableEditListener*>& getUndoableEditListener() { return undoableEditListeners; }
private:
	vector<UndoableEditListener*>undoableEditListeners;
};

UndoRedoEditSupport::UndoRedoEditSupport()
{
}

UndoRedoEditSupport::~UndoRedoEditSupport()
{
}
inline void UndoRedoEditSupport::addUndoableEditListener(UndoableEditListener * editListener)
{
	undoableEditListeners.push_back(editListener);
}
inline void UndoRedoEditSupport::removeUndoableEditListener(UndoableEditListener * editListener)
{
	vector<UndoableEditListener*>::iterator iter = undoableEditListeners.begin();
	for (; iter != undoableEditListeners.end(); iter++)
	{
		if ((*iter) == editListener)
		{
			undoableEditListeners.erase(iter, iter + 1);
		}
	}
}
inline void UndoRedoEditSupport::postEdit(UndoableEdit* edit)
{
	UndoableEditEvent* editEvent = new UndoableEditEvent(edit);
	vector<UndoableEditListener*>::iterator iter = undoableEditListeners.begin();
	for (; iter != undoableEditListeners.end(); iter++)
	{
		(*iter)->undoableEditHappended(editEvent);
	}
}
#endif // !UNDOABLEEDITSUPPORT

