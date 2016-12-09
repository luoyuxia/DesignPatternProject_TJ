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
	UndoableEdit(string editName = "未命名的edit");
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
	CompoundEdit(string compoundEditName = "未命名的compoundEdit");
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

//清空所有操作
inline void UndoManager::discardAllEdits()
{
	vector<UndoableEdit*>::reverse_iterator riter = undoableEdits.rbegin();
	//undo 所有的edit
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
		//如果已经到了UndoTo的edit，退出循环
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
		//如果已经到了RedoTo的edit，退出循环
		if ((*iter) == edit)
			break;
		iter++;

	}
}
inline void UndoManager::undo()
{
	//找到第一个可以被Undo的元素
	UndoableEdit* edit = editToBeUndone();
	//如果为空，表示不存在可以被Uodo的edit
	if (edit == NULL)
		throw new CannotUndoException();

	//从最后一个元素到第一个可以被Undo的edit都Undo掉
	undoTo(edit);


}
inline void UndoManager::redo()
{
	//找到第一个可以被Redo的edit
	UndoableEdit* edit = editToBeRedone();
	//如果为空，表示不存在可以被Redo的edit
	if (edit == NULL)
		throw new CannotRedoException();
	redoTo(edit);

}
inline void UndoManager::addEdit(UndoableEdit * undoableEdit)
{
	if (indexOfNextAdd >= limit)
		throw new UndoOverFlowException();

	//将IndexOfNextAdd后面的元素全部擦除
	undoableEdits.erase(undoableEdits.begin() + indexOfNextAdd, undoableEdits.end());
	indexOfNextAdd++;
	/*	//如果edit应添加的位置索引大于或edit列表的大小，用push函数
	if (indexOfNextAdd >= undoableEdits.size())
	{
	undoableEdits.push_back(undoableEdit);
	indexOfNextAdd++;
	}
	//否则，直接通过索引添加，因为已经有这样的空间了
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
	//从容器的最后一个元素开始遍历
	if (indexOfNextAdd == 0)return NULL;
	vector<UndoableEdit*>::iterator iter = undoableEdits.begin() + indexOfNextAdd - 1;

	//从后往前历整个容器，找到第一个可以被Undo的edit
	for (; iter >= undoableEdits.begin(); iter--)
	{
		//如果该操作有意义且可以被Undo，将该操作返回
		if ((*iter)->canUndo() && (*iter)->isSignificant())
		{
			return *iter;
		}
	}
	return NULL;
}
inline UndoableEdit * UndoManager::editToBeRedone()
{
	//从容器的最后一个元素开始遍历
	vector<UndoableEdit*>::iterator iter = undoableEdits.begin() + indexOfNextAdd;

	//从后往前历整个容器，找到第一个可以被Undo的edit
	for (; iter != undoableEdits.end(); iter++)
	{
		//如果该操作有意义且可以被Redo，将该操作返回
		if ((*iter)->isSignificant() && (*iter)->canRedo())
		{
			return *iter;
		}
	}
	return NULL;
}
#endif // !UNDOREDOCOMPONENT

