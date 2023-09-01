#pragma once
#include <io.h>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <direct.h>
#include <ShlObj.h>
#include <algorithm>
#include <graphics.h>

//这个头文件用来定义一些程序所需的宏和常量

#define C0    RGB(128, 128, 128);
#define C2    RGB(170, 255, 0)
#define C4    RGB(190, 220, 30)
#define C8    RGB(200, 180, 50)
#define C16   RGB(200, 150, 80)
#define C32   RGB(200, 120, 100)
#define C64   RGB(200, 100, 120)
#define C128  RGB(200, 70, 100)
#define C256  RGB(200, 40, 80)
#define C512  RGB(200, 10, 60)
#define C1024 RGB(200, 0, 40)
#define C2048 RGB(225, 0, 20)
#define C4096 RGB(255, 0, 0)

COLORREF get_color(int number);

void outtextxyf(int x, int y, LPCTSTR format, ...);

void color_test(void);

int get_length(int number);

void getkeymessage(ExMessage* msg);

#define TITAL 50

struct points {
	char name[100];
	int score;
	bool flag;
	bool operator < (const points x) const { return score > x.score; }
};

