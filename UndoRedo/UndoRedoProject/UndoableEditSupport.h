#pragma once
#ifndef UNDOABLEEDITSUPPORT
#define UNDOABLEEDITSUPPORT
#include"UndoableEditEvent.h"
#include"UndoRedoComponent.h"
class UndoableEditListener;

//UndoRedo�༭�����ĸ�����
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

//���һ��Undoable�ļ�����
inline void UndoRedoEditSupport::addUndoableEditListener(UndoableEditListener * editListener)
{
	undoableEditListeners.push_back(editListener);
}

//ɾ��һ��Undoable������
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

//��һ���༭������װ���¼������͸�������
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

