#pragma once
#ifndef MYPOINT
#define MYPOINT
using namespace System::Drawing;

//自定义的点
class MyPoint
{
public :
	MyPoint(int x = 0, int y = 0) :_x(x), _y(y) {};
	~MyPoint()
	{

	}
	int getX()
	{
		return _x;
	}
	int getY()
	{
		return _y;
	}
private:
	int _x;
	int _y;
};


//自定义的线
class MyLine
{
public:
	MyLine(MyPoint* start = new MyPoint(0,0), MyPoint* end = new MyPoint(0,0)) :_start(start), _end(end) {};
	MyLine(Point startPoint=Point(0,0), Point endPoint= Point(0,0)) {
		_start = new MyPoint(startPoint.X, startPoint.Y);
		_end = new MyPoint(endPoint.X, endPoint.Y);
	}
	~MyLine() {};
	MyPoint* getStartPoint() { return _start; }
	MyPoint* getEndPoint() { return _end; }
private:
	MyPoint* _start;
	MyPoint* _end;
};
#endif // !MYPOINT
