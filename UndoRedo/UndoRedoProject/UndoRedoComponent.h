#pragma once
#ifndef UNDOREDOCOMPONENT
#define UNDOREDOCOMPONENT
#define LIMIT 100
#include<string>
#include<vector>
#include"UndoableEditEvent.h"
#include"MyException.h"
using namespace std;


//抽象的UndoableEdit编辑操作，提供了几个纯虚函数，让子类实现
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


//继承自UndoableEdit类，实现了其全部的纯虚函数，自己定义的
//可以UndoRedo类只需继承该类就可以了
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

//由于是单个编辑操作，在向该当编辑操作中添加操作时将抛出异常
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


//复合编辑操作，由多个编辑操作组成
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

//对该复合编辑操作中的每一个操作，都进行Undo操作
inline void CompoundEdit::undo()
{
	vector<UndoableEdit*>::iterator iter = undoableEdits.begin();
	for (; iter != undoableEdits.end(); iter++)
	{
		(*iter)->undo();
	}
}

//对该复合编辑操作中的每一个操作，都进行Redo操作
inline void CompoundEdit::redo()
{
	vector<UndoableEdit*>::iterator iter = undoableEdits.begin();
	for (; iter != undoableEdits.end(); iter++)
	{
		(*iter)->redo();
	}
}

//添加单个编辑操作
inline void CompoundEdit::addEdit(UndoableEdit * undoableEdit)
{
	undoableEdits.push_back(undoableEdit);
}

//如果该复合操作其中有任何一个编辑操作可以Undo，则该复合操作都可以Undo
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

//如果该复合操作其中有任何一个编辑操作可以Redo，则该复合操作都可以Redo
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

//管理UndoRedo操作的类，继承CompoundEdit， UndoableEditListener以监听UndoableEditEvent
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
	int indexOfNextAdd = 0;//类似于指针，指向容器当前的位置
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

//从容器的当前指针指向的操作，到某一个编辑操作都进行Undo
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

//从容器当前指针指向的操作，到某一个编辑操作都进行Redo
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

	//从容器当前指针指向的元素到第一个可以被Undo的edit都Undo掉
	undoTo(edit);


}
inline void UndoManager::redo()
{
	//找到第一个可以被Redo的edit
	UndoableEdit* edit = editToBeRedone();
	//如果为空，表示不存在可以被Redo的edit
	if (edit == NULL)
		throw new CannotRedoException();
	//从容器当前指针指向的元素到第一个可以被Redo的edit都Redo掉
	redoTo(edit);

}

//在容器当前指针指向的位置添加一个编辑操作
inline void UndoManager::addEdit(UndoableEdit * undoableEdit)
{
	if (indexOfNextAdd >= limit)
		throw new UndoOverFlowException();

	//将容器当前指针指向位置的后面的元素全部擦除
	undoableEdits.erase(undoableEdits.begin() + indexOfNextAdd, undoableEdits.end());
	indexOfNextAdd++;
	undoableEdits.push_back(undoableEdit);
}

//如果能找到可以被Undo的操作，则表示可以Undo
inline bool UndoManager::canUndo()
{
	return editToBeUndone() != NULL;
}

//如果能找到可以被Redo的操作，则表示可以Redo
inline bool UndoManager::canRedo()
{
	return editToBeRedone() != NULL;
}

//从容器当前指针指向的操作，找到第一个能够被Undo的edit（操作）
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

//从容器当前指针指向的操作，找到第一个能够被Redo的edit（操作）
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

