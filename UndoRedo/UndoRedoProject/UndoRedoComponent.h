#pragma once
#ifndef UNDOREDOCOMPONENT
#define UNDOREDOCOMPONENT
#define LIMIT 100
#include<string>
#include<vector>
#include"UndoableEditEvent.h"
#include"MyException.h"
using namespace std;

public class UndoableEdit
{
public:
	UndoableEdit(string editName = "δ������edit");
	~UndoableEdit();
	virtual void undo() = 0;
	virtual void redo() = 0;
	virtual void addEdit(UndoableEdit* undoableEdit) = 0;
	virtual bool isSignificant() = 0;
	virtual bool canUndo() = 0;
	virtual bool canRedo() = 0;
	string getPresentationName();
	string getUndoPresentationName();
	string getRedoPresentationName();
private:

protected:

	string presentationName;

};
UndoableEdit::UndoableEdit(string editName)
{
	presentationName = editName;
}

UndoableEdit::~UndoableEdit()
{
}
string UndoableEdit::getPresentationName()
{
	return presentationName;
}

string UndoableEdit::getUndoPresentationName()
{
	return "un_" + presentationName;
}

string UndoableEdit::getRedoPresentationName()
{
	return "re_" + presentationName;
}


public class AbstractUndoableEdit :public UndoableEdit
{
public:
	AbstractUndoableEdit();
	AbstractUndoableEdit(string editName);
	~AbstractUndoableEdit();
	virtual void undo();
	virtual void redo();
	virtual void addEdit(UndoableEdit* undoableEdit);
	virtual bool isSignificant();
	virtual bool canUndo();
	virtual bool canRedo();
private:
	bool hasBeenDone = true;
	bool alive = true;

};

AbstractUndoableEdit::AbstractUndoableEdit() :UndoableEdit()
{
}

inline AbstractUndoableEdit::AbstractUndoableEdit(string editName) : UndoableEdit(editName)
{
}

AbstractUndoableEdit::~AbstractUndoableEdit()
{
}

inline void AbstractUndoableEdit::undo()
{
	hasBeenDone = false;
}

inline void AbstractUndoableEdit::redo()
{
	hasBeenDone = true;
}

inline void AbstractUndoableEdit::addEdit(UndoableEdit * undoableEdit)
{
	throw new CannotAddEditException();
}

inline bool AbstractUndoableEdit::isSignificant()
{
	return true;
}

inline bool AbstractUndoableEdit::canUndo()
{
	return hasBeenDone == true;
}

inline bool AbstractUndoableEdit::canRedo()
{
	return hasBeenDone == false;
}

class CompoundEdit :public AbstractUndoableEdit
{
public:
	CompoundEdit(string compoundEditName = "δ������compoundEdit");
	~CompoundEdit();
	virtual void undo();
	virtual void redo();
	virtual void addEdit(UndoableEdit* undoableEdit);
	virtual bool canUndo();
	virtual bool canRedo();
private:

protected:
	vector<UndoableEdit*> undoableEdits;
};

CompoundEdit::CompoundEdit(string compoundEditName) :AbstractUndoableEdit(compoundEditName)
{
}

CompoundEdit::~CompoundEdit()
{
}
inline void CompoundEdit::undo()
{
	vector<UndoableEdit*>::iterator iter = undoableEdits.begin();
	for (; iter != undoableEdits.end(); iter++)
	{
		(*iter)->undo();
	}
}
inline void CompoundEdit::redo()
{
	vector<UndoableEdit*>::iterator iter = undoableEdits.begin();
	for (; iter != undoableEdits.end(); iter++)
	{
		(*iter)->redo();
	}
}
inline void CompoundEdit::addEdit(UndoableEdit * undoableEdit)
{
	undoableEdits.push_back(undoableEdit);
}

inline bool CompoundEdit::canUndo()
{
	vector<UndoableEdit*>::iterator iter = undoableEdits.begin();
	for (; iter != undoableEdits.end(); iter++)
	{
		if ((*iter)->canUndo())
			return true;
	}
	return false;
}

inline bool CompoundEdit::canRedo()
{
	vector<UndoableEdit*>::iterator iter = undoableEdits.begin();
	for (; iter != undoableEdits.end(); iter++)
	{
		if ((*iter)->canRedo())
			return true;
	}
	return false;
}


class UndoableEditListener;
class UndoableEditEvent;
class UndoManager :public CompoundEdit, public UndoableEditListener
{
public:
	UndoManager();
	~UndoManager();
	int getLimit() { return limit; }
	void setLimit(int l) { this->limit = l; }
	void discardAllEdits();

	virtual void undo();
	virtual void redo();
	virtual void addEdit(UndoableEdit* undoableEdit);
	virtual void undoableEditHappended(UndoableEditEvent* editEvent) { addEdit(editEvent->getUndoableEdit()); };
	virtual bool canUndo();
	virtual bool canRedo();
private:
	int limit = LIMIT;
	int indexOfNextAdd = 0;
protected:
	UndoableEdit* editToBeUndone();
	UndoableEdit* editToBeRedone();
	void undoTo(UndoableEdit* edit);
	void redoTo(UndoableEdit* edit);
};

UndoManager::UndoManager()
{
}

UndoManager::~UndoManager()
{
}

//������в���
inline void UndoManager::discardAllEdits()
{
	vector<UndoableEdit*>::reverse_iterator riter = undoableEdits.rbegin();
	//undo ���е�edit
	for (; riter != undoableEdits.rend(); riter++)
	{
		(*riter)->undo();
	}
	indexOfNextAdd = 0;
	undoableEdits.clear();
}
inline void UndoManager::undoTo(UndoableEdit * edit)
{
	vector<UndoableEdit*>::iterator iter = undoableEdits.begin() + indexOfNextAdd - 1;
	while (true)
	{
		(*iter)->undo();
		indexOfNextAdd--;
		//����Ѿ�����UndoTo��edit���˳�ѭ��
		if ((*iter) == edit)
			break;
		iter++;
	}

}
inline void UndoManager::redoTo(UndoableEdit * edit)
{
	vector<UndoableEdit*>::iterator iter = undoableEdits.begin() + indexOfNextAdd;
	while (true)
	{
		(*iter)->redo();
		indexOfNextAdd++;
		//����Ѿ�����RedoTo��edit���˳�ѭ��
		if ((*iter) == edit)
			break;
		iter++;

	}
}
inline void UndoManager::undo()
{
	//�ҵ���һ�����Ա�Undo��Ԫ��
	UndoableEdit* edit = editToBeUndone();
	//���Ϊ�գ���ʾ�����ڿ��Ա�Uodo��edit
	if (edit == NULL)
		throw new CannotUndoException();

	//�����һ��Ԫ�ص���һ�����Ա�Undo��edit��Undo��
	undoTo(edit);


}
inline void UndoManager::redo()
{
	//�ҵ���һ�����Ա�Redo��edit
	UndoableEdit* edit = editToBeRedone();
	//���Ϊ�գ���ʾ�����ڿ��Ա�Redo��edit
	if (edit == NULL)
		throw new CannotRedoException();
	redoTo(edit);

}
inline void UndoManager::addEdit(UndoableEdit * undoableEdit)
{
	if (indexOfNextAdd >= limit)
		throw new UndoOverFlowException();

	//��IndexOfNextAdd�����Ԫ��ȫ������
	undoableEdits.erase(undoableEdits.begin() + indexOfNextAdd, undoableEdits.end());
	indexOfNextAdd++;
	/*	//���editӦ���ӵ�λ���������ڻ�edit�б��Ĵ�С����push����
	if (indexOfNextAdd >= undoableEdits.size())
	{
	undoableEdits.push_back(undoableEdit);
	indexOfNextAdd++;
	}
	//����ֱ��ͨ���������ӣ���Ϊ�Ѿ��������Ŀռ���
	else
	{
	undoableEdits[indexOfNextAdd++] = undoableEdit;
	}*/
	undoableEdits.push_back(undoableEdit);
}
inline bool UndoManager::canUndo()
{
	return editToBeUndone() != NULL;
}
inline bool UndoManager::canRedo()
{
	return editToBeRedone() != NULL;
}
inline UndoableEdit * UndoManager::editToBeUndone()
{
	//�����������һ��Ԫ�ؿ�ʼ����
	if (indexOfNextAdd == 0)return NULL;
	vector<UndoableEdit*>::iterator iter = undoableEdits.begin() + indexOfNextAdd - 1;

	//�Ӻ���ǰ�������������ҵ���һ�����Ա�Undo��edit
	for (; iter >= undoableEdits.begin(); iter--)
	{
		//����ò����������ҿ��Ա�Undo�����ò�������
		if ((*iter)->canUndo() && (*iter)->isSignificant())
		{
			return *iter;
		}
	}
	return NULL;
}
inline UndoableEdit * UndoManager::editToBeRedone()
{
	//�����������һ��Ԫ�ؿ�ʼ����
	vector<UndoableEdit*>::iterator iter = undoableEdits.begin() + indexOfNextAdd;

	//�Ӻ���ǰ�������������ҵ���һ�����Ա�Undo��edit
	for (; iter != undoableEdits.end(); iter++)
	{
		//����ò����������ҿ��Ա�Redo�����ò�������
		if ((*iter)->isSignificant() && (*iter)->canRedo())
		{
			return *iter;
		}
	}
	return NULL;
}
#endif // !UNDOREDOCOMPONENT
