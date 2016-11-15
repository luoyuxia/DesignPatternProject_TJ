#pragma once
#ifndef _CLOCK
#define _CLOCK
#include<Windows.h>
#include<iostream>
using namespace std;
#define CLOCK_CENTER_X 450
#define CLOCK_CENTER_Y 200
#define CLOCK_RAD 100
#define PI 3.1415926
#define LEFTX 340
#define LEFTY 320
#define WIDTH 220
#define HIGTH 80


//时钟的抽象类
class Clock
{
public:
	Clock():_hour(-1),_min(-1),_sec(-1){
		_hWnd = GetConsoleWindow();
		_hdc = GetWindowDC(_hWnd);
		hopen1 = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		hbrush2 = (HBRUSH)GetStockObject(NULL_BRUSH);
		maskPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		SelectObject(_hdc, hopen1);
		SelectObject(_hdc, hbrush2);
	};
	~Clock() {};
	virtual void updateClock(int hour, int min, int sec)
	{
		drawBackGround();
		drawTime(hour, min, sec);
		_hour = hour;
		_min = min;
		_sec = sec;
	}
	virtual void drawBackGround() {};
	virtual void drawTime(int hour, int min, int sec) {};
	void setHideColor() { SelectObject(_hdc, maskPen); }
	void restoreColor(){ SelectObject(_hdc, hopen1); }
	void backToOrginal(){ MoveToEx(_hdc, CLOCK_CENTER_X, CLOCK_CENTER_Y, NULL); }
protected:
	int _hour;
	int _min;
	int _sec;
	HWND _hWnd;
	HDC _hdc;
	HPEN hopen1;
	HBRUSH hbrush2;
	HPEN maskPen;
};

//数字时钟
class DigitalClock:public Clock
{
public:
	DigitalClock() {};
	~DigitalClock() {};
	virtual void drawBackGround();
	virtual void drawTime(int hour, int min, int sec);

private:
	void parseNum(TCHAR* t_char, int num)
	{
		char buffer[3];
		sprintf_s(buffer, "%d", num);
		t_char[0] = '0';
		t_char[1] = buffer[0];
		if (num >= 10) {
			t_char[0] = buffer[0];
			t_char[1] = buffer[1];
		}
		t_char[2] = '\0';
	}

	
};
//绘制背景
void DigitalClock::drawBackGround()
{
	HPEN hopen2 = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
	SelectObject(_hdc, hopen2);
	Rectangle(_hdc, LEFTX, LEFTY, LEFTX + WIDTH, LEFTY + HIGTH);
	for (double i = LEFTX+WIDTH/3; i <LEFTX+WIDTH; i += WIDTH / 3)
	{
		int gap = 7;
		for (double j = LEFTY+HIGTH/2; j <= LEFTY + HIGTH / 2+gap; j += gap)
		{
			Ellipse(_hdc, i, j, i + 3, j + 3);
		}
	}
}

void DigitalClock::drawTime(int hour, int min, int sec)
{
	//更新小时
	SetTextColor(_hdc, RGB(255, 0, 0));
	TCHAR str[10];
	parseNum(str, hour);
	TextOut(_hdc, LEFTX + WIDTH / 6, LEFTY + HIGTH / 3 + 8, str, lstrlen(str));

	//更新分钟
	SetTextColor(_hdc, RGB(255, 0, 0));
	parseNum(str, min);
	TextOut(_hdc, LEFTX + (WIDTH / 2), LEFTY + HIGTH / 3 + 8, str, lstrlen(str));


	//更新秒
	SetTextColor(_hdc, RGB(255, 0, 0));
	parseNum(str, sec);
	TextOut(_hdc, LEFTX + 5 * (WIDTH / 6), LEFTY + HIGTH / 3 + 8, str, lstrlen(str));


}










//普通时钟，即带指针的时钟
class NormalClock:public Clock
{
public:
	NormalClock() {};
	~NormalClock() {};
	virtual void drawBackGround();
	virtual void drawTime(int hour, int min, int sec);
};
//绘制背景
void NormalClock::drawBackGround()
{
	HPEN hopen2 = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	SelectObject(_hdc, hopen2);
	Rectangle(_hdc, CLOCK_CENTER_X - CLOCK_RAD - 10, CLOCK_CENTER_Y - CLOCK_RAD - 10,
		CLOCK_CENTER_X + CLOCK_RAD + 10, CLOCK_CENTER_Y + CLOCK_RAD + 10);
	restoreColor();
	for (int i = 0, m = 0, h = 0; i < 12; i++, h++)
	{
		double x = CLOCK_RAD * sin((h * 60 + m) / 360.0 * PI) + CLOCK_CENTER_X;
		double y = CLOCK_CENTER_Y - CLOCK_RAD * cos((h * 60 + m) / 360.0 * PI);
		Ellipse(_hdc, x, y, x + 5, y + 5);
	}
	for (int i = 0, m = 0; i <= 59; i++, m++)
	{
		double x = CLOCK_RAD * sin((double)(m / 30.0) * PI) + CLOCK_CENTER_X;
		double y = CLOCK_CENTER_Y - CLOCK_RAD * cos(m / 30.0 * PI);
		Ellipse(_hdc, x, y, x + 3, y + 3);
	}

}



inline void NormalClock::drawTime(int hour, int min, int sec)
{
	//更新小时
	backToOrginal();
	double prexH = (CLOCK_RAD - 30) * sin((_hour * 60 + _min) / 360.0*PI) + CLOCK_CENTER_X;
	double preyH = CLOCK_CENTER_Y - (CLOCK_RAD - 30) * cos((_hour * 60 + _min) / 360.0*PI);
	setHideColor();
	LineTo(_hdc, prexH, preyH);

	backToOrginal();
	double xH = (CLOCK_RAD - 30) * sin((hour * 60 + min) / 360.0*PI) + CLOCK_CENTER_X;
	double yH = CLOCK_CENTER_Y - (CLOCK_RAD - 30) * cos((hour * 60 + min) / 360.0*PI);
	restoreColor();
	LineTo(_hdc, xH, yH);

	//更新分钟
	backToOrginal();
	double prexM = (CLOCK_RAD - 20) * sin(_min / 30.0*PI) + CLOCK_CENTER_X;
	double preyM = CLOCK_CENTER_Y - (CLOCK_RAD - 20) * cos((_min / 30.0*PI));
	setHideColor();
	LineTo(_hdc, prexM, preyM);

	backToOrginal();
	double xM = (CLOCK_RAD - 20) * sin(min / 30.0*PI) + CLOCK_CENTER_X;
	double yM = CLOCK_CENTER_Y - (CLOCK_RAD - 20) * cos((min / 30.0*PI));
	restoreColor();
	LineTo(_hdc, xM, yM);


	//更新秒

	backToOrginal();
	double prexS = (CLOCK_RAD - 10) * sin((_sec / 30.0*PI)) + CLOCK_CENTER_X;
	double preyS = CLOCK_CENTER_Y - (CLOCK_RAD - 10) * cos((_sec / 30.0*PI));
	setHideColor();
	LineTo(_hdc, prexS, preyS);

	backToOrginal();
	double xS = (CLOCK_RAD - 10) * sin((sec / 30.0*PI)) + CLOCK_CENTER_X;
	double yS = CLOCK_CENTER_Y - (CLOCK_RAD - 10) * cos((sec / 30.0*PI));
	restoreColor();
	LineTo(_hdc, xS, yS);
}
#endif // !_CLOCK
