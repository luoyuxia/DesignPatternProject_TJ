#pragma once
#ifndef UNDOABLEEDITEVENT
#define UNDOABLEEDITEVENT

class UndoableEdit;

//Undoable�༭�����������¼����������༭����ʱ�������װ��һ���¼��������¼�������
class UndoableEditEvent
{
public:
	UndoableEditEvent(UndoableEdit*edit);
	~UndoableEditEvent();
	UndoableEdit* getUndoableEdit();

private:
	UndoableEdit* undoableEdit;//�༭����
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

//�༭�����������¼��ļ�����,ֻ��һ��undoableEditHappended�������������������ζԴ�������
//�¼����д���
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

