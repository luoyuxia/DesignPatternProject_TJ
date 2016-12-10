#pragma once
#ifndef UNDOABLEEDITSUPPORT
#define UNDOABLEEDITSUPPORT
#include"UndoableEditEvent.h"
#include"UndoRedoComponent.h"
class UndoableEditListener;

//UndoRedo编辑操作的辅助类
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

//添加一个Undoable的监听者
inline void UndoRedoEditSupport::addUndoableEditListener(UndoableEditListener * editListener)
{
	undoableEditListeners.push_back(editListener);
}

//删除一个Undoable监听者
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

//将一个编辑操作包装成事件，发送给监听者
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

