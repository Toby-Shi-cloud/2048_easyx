#include "Resource.h"

COLORREF get_color(int number)
{
	switch (number) {
	case 0:    return C0;
	case 2:    return C2;
	case 4:    return C4;
	case 8:    return C8;
	case 16:   return C16;
	case 32:   return C32;
	case 64:   return C64;
	case 128:  return C128;
	case 256:  return C256;
	case 512:  return C512;
	case 1024: return C1024;
	case 2048: return C2048;
	default:   return C4096;
	}
}

void outtextxyf(int x, int y, LPCTSTR format, ...)
{
	va_list ap;
	va_start(ap, format);
	char str[200] = "";
	vsprintf_s(str, format, ap);
	va_end(ap);
	outtextxy(x, y, str);
}

void color_test()
{
	initgraph(640, 480);
	setbkmode(0);
	setlinecolor(BLACK);
	setbkcolor(WHITE);
	settextcolor(WHITE);
	settextstyle(50, 0, "华文琥珀");
	for (int i = 0; i < 12; i++) {
		setfillcolor(get_color(2 << i));
		fillrectangle(i % 4 * 160, i / 4 * 160, i % 4 * 160 + 160, i / 4 * 160 + 160);
		outtextxyf(i % 4 * 160 + 80 - 15 * get_length(2 << i), i / 4 * 160 + 60, "%d", 2 << i);
	}
	_getch();
	closegraph();
}

int get_length(int number)
{
	if (!number) return 1;
	int len = 0;
	while (number) {
		len++;
		number /= 10;
	}
	return len;
}
