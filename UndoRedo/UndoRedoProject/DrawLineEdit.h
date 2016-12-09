#pragma once
#ifndef DRAWLINEEDIT
#define DRAWLINEEDIT
#include"UndoRedoComponent.h"
#include"MyPoint.h"
#include<vector>
using namespace std;
public class DrawLineEdit:public AbstractUndoableEdit
{
	public:
	DrawLineEdit(vector<MyLine*>*l,MyLine* newLine):AbstractUndoableEdit("»­Ïß")
	{
		lines = l;
		addedLine = newLine;
		lines->push_back(newLine);
	}
/*	DrawLineEdit(vector<pair<Point,Point>*>*l, pair<Point,Point>line) :AbstractUndoableEdit("»­Ïß")
	{
			//	lines = l;
			//	addedLine = newLine;
			//	lines->push_back(newLine);
		lines = l;
	//	addedLine = line;
	//	lines->push_back(line);
	};*/
	~DrawLineEdit() {};
	virtual void undo();
	virtual void redo();
	private:
		vector<MyLine*>*lines;
	//	vector<pair<Point, Point>*>*lines;
		MyLine* addedLine;
	//	pair<Point, Point>* addedLine;
		
};
void DrawLineEdit::undo()
{
	AbstractUndoableEdit::undo();
	vector<MyLine*>::iterator iter = lines->begin();
	for (; iter != lines->end(); iter++)
	{
		if ((*iter) == addedLine)
		{
			lines->erase(iter, iter + 1);
			return;
		}
	}
	throw CannotUndoException();
}

void DrawLineEdit::redo()
{
	AbstractUndoableEdit::redo();
	lines->push_back(addedLine);
}
#endif // !DRAWLINEEDIT
