#include "Resource.h"

//全局变量的声明 
int value[4][4];//每个方格中的值 
int scr;//分数 

//函数的前置声明
void begin();
void print();
void mainloop();
void gameover();
bool check();
void my_exit();

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
//	color_test();

	while (1) {
		initgraph(640, TITAL + 640);
		setbkmode(0);
		setlinecolor(BLACK);
		setbkcolor(WHITE);

		begin();
		mainloop();
		gameover();

		settextstyle(30, 0, "新宋体");
		outtextxy(320 - 8 * 14, 420, "按下任意键退出");

		INT result = MessageBox(NULL, "再来一局？", "2048", MB_YESNO | MB_ICONINFORMATION | MB_SYSTEMMODAL);
		if (result == IDNO) {
			break;
		}

		closegraph();
	}
	return 0;
}

void begin()
{
	memset(value, -1, sizeof(value));
	scr = 0;
	int z1, z2;
	z1 = rand() % 16;
	z2 = rand() % 16;
	while (z1 == z2) z2 = rand() % 16;
	value[z1 / 4][z1 % 4] = 2;
	value[z2 / 4][z2 % 4] = 2;
	print();
}

void print() {
	cleardevice();
	line(0, 0, 640, 0);
	line(0, 0, 0, TITAL);
	line(640, 0, 640, TITAL);
	settextcolor(BLACK);
	settextstyle(30, 0, "华文琥珀");
	outtextxyf(320 - 5 * get_length(scr) - 80, 10, "你的得分：%d", scr);
	settextcolor(WHITE);
	settextstyle(50, 0, "华文琥珀");
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			if (~value[i][j]) {
				setfillcolor(get_color(value[i][j]));
				fillrectangle(j * 160, TITAL + i * 160, j * 160 + 160, TITAL + i * 160 + 160);
				outtextxyf(j * 160 + 80 - 15 * get_length(value[i][j]), TITAL + i * 160 + 60, "%d", value[i][j]);
			}
			else {
				setfillcolor(WHITE);
				fillrectangle(j * 160, TITAL + i * 160, j * 160 + 160, TITAL + i * 160 + 160);
			}
		}
}

void mainloop()
{
	while (1) {
		ExMessage msg;
		getkeymessage(&msg);
		if (msg.vkcode == VK_ESCAPE) my_exit();
		while (msg.vkcode < VK_LEFT && msg.vkcode > VK_DOWN)
			getkeymessage(&msg);
		bool fg = 0;
		switch (msg.vkcode) {
		case VK_UP:
			for (int j = 0; j < 4; j++) {
				for (int i = 0; i < 4; i++) {
					if (!~value[i][j]) for (int k = i + 1; k < 4; k++) if (~value[k][j]) { std::swap(value[i][j], value[k][j]); fg = 1; break; }
					if (~value[i][j]) for (int k = i + 1; k < 4; k++) if (~value[k][j])
					{
						if (value[i][j] == value[k][j]) { value[i][j] <<= 1; fg = 1; scr += value[i][j]; value[k][j] = -1; }
						break;
					}
				}
			}break;
		case VK_DOWN:
			for (int j = 0; j < 4; j++) {
				for (int i = 3; i >= 0; i--) {
					if (!~value[i][j]) for (int k = i - 1; k >= 0; k--) if (~value[k][j]) { std::swap(value[i][j], value[k][j]); fg = 1; break; }
					if (~value[i][j]) for (int k = i - 1; k >= 0; k--) if (~value[k][j])
					{
						if (value[i][j] == value[k][j]) { value[i][j] <<= 1; fg = 1; scr += value[i][j]; value[k][j] = -1; }
						break;
					}
				}
			}break;
		case VK_LEFT:
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (!~value[i][j]) for (int k = j + 1; k < 4; k++) if (~value[i][k]) { std::swap(value[i][j], value[i][k]); fg = 1; break; }
					if (~value[i][j]) for (int k = j + 1; k < 4; k++) if (~value[i][k])
					{
						if (value[i][j] == value[i][k]) { value[i][j] <<= 1; fg = 1; scr += value[i][j]; value[i][k] = -1; }
						break;
					}
				}
			}break;
		case VK_RIGHT:
			for (int i = 0; i < 4; i++) {
				for (int j = 3; j >= 0; j--) {
					if (!~value[i][j]) for (int k = j - 1; k >= 0; k--) if (~value[i][k]) { std::swap(value[i][j], value[i][k]); fg = 1; break; }
					if (~value[i][j]) for (int k = j - 1; k >= 0; k--) if (~value[i][k])
					{
						if (value[i][j] == value[i][k]) { value[i][j] <<= 1; fg = 1; scr += value[i][j]; value[i][k] = -1; }
						break;
					}
				}
			}break;
		default:break;
		}
		if (!fg) continue;
		int candidate[16];
		int cnt = 0;
		int maxn = 0;
		for (int i = 0; i < 16; i++)
			if (!~value[i / 4][i % 4])
				candidate[cnt++] = i;
			else
				maxn = max(maxn, value[i / 4][i % 4]);
		if (cnt) {
			int i = rand() % cnt;
			int z = candidate[i];
			int seed;
			int num[5] = { 2, 4, 8, 16, 32 };
			if (maxn <= 32) seed = 1;
			else if (maxn <= 128) seed = 2;
			else if (maxn <= 1024) seed = 3;
			else if (maxn <= 4096) seed = 4;
			else seed = 5;
			value[z / 4][z % 4] = num[rand() % seed];
		}
		print();
		if (check()) continue;
		else break;
	}
}

bool check()
{
	for (int z = 0; z < 16; z++)
		if (!~value[z / 4][z % 4]) return 1;
	int fg[4][2] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++)
				if (i + fg[k][0] >= 0 && i + fg[k][0] < 4 && j + fg[k][1] >= 0 && j + fg[k][1] < 4 && value[i][j] == value[i + fg[k][0]][j + fg[k][1]])
					return 1;
	return 0;
}

void gameover()
{
	std::stringstream ss;
	points person[11];
	settextcolor(BLACK);
	settextstyle(100, 0, "华文琥珀");
	outtextxyf(320 - 240, 320 + TITAL / 2 - 40, "Game Over !");

	CHAR my_documents[MAX_PATH];
	HRESULT result = SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);
	if (result != S_OK) {
		ss.clear();
		ss << "Error: " << result << "\n";
		MessageBox(nullptr, ss.str().c_str(), "2048", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		return;
	}
	Sleep(1500);
	ss.clear();
	ss << my_documents << "\\Toby'sProgram";
	if (_access(ss.str().c_str(), 0) == -1)
		_mkdir(ss.str().c_str());
	ss << "\\2048";
	if (_access(ss.str().c_str(), 0) == -1)
		_mkdir(ss.str().c_str());
	ss << "\\rank.txt";
	std::fstream frank(ss.str().c_str(), std::ios::in);
	int cnt = 0;
	while (frank >> person[cnt].name >> person[cnt].score) { person[cnt].flag = 0; cnt++; }

	cleardevice();
	closegraph();
	initgraph(640, 480);
	setbkmode(0);
	setlinecolor(BLACK);
	setbkcolor(WHITE);
	settextcolor(BLACK);
	cleardevice();
	settextstyle(50, 0, "华文琥珀");
	outtextxyf(320 - 15 * get_length(scr) - 150, 10, "你的得分是：%d", scr);
	outtextxyf(320 - 190, 60, "请输入你的名字：");
	int len = 0;
	while (1) {
		char ch;
		ch = getmessage(EX_CHAR).ch;
		if (ch == '\r' || ch == '\n') break;
		if (ch == '\b' || ch == 127) {
			if (!len) continue;
			len--;
			person[cnt].name[len] = '\000';
		}
		else {
			person[cnt].name[len++] = ch;
			person[cnt].name[len] = '\000';
		}
		cleardevice();
		settextstyle(50, 0, "华文琥珀");
		outtextxyf(320 - 15 * get_length(scr) - 150, 10, "你的得分是：%d", scr);
		outtextxyf(320 - 190, 60, "请输入你的名字：");
		settextstyle(50, 0, "新宋体");
		outtextxyf(320 - len * 15, 120, "%s", person[cnt].name);
	}

	if (person[cnt].name[0] == '\000')
		for (int i = 0; i < 7; i++)
			person[cnt].name[i] = "未命名"[i];
	person[cnt].score = scr;
	person[cnt].flag = 1;
	cnt++;
	std::sort(person, person + cnt);

	cleardevice();
	settextstyle(50, 0, "新宋体");
	outtextxyf(320 - 60, 10, "排名");
	char rnk[12][5] = { "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th" };
	settextstyle(30, 0, "华文琥珀");
	for (int i = 0; i < cnt && i < 10; i++) {
		if (person[i].flag) settextcolor(RED);
		else settextcolor(BLACK);
		outtextxyf(320 - 7 * 36, 60 + i * 35, "%4s", rnk[i]);
		outtextxyf(320 - 7 * 24, 60 + i * 35, "%20s", person[i].name);
		outtextxyf(320 - 7 * (-20), 60 + i * 35, "%8d", person[i].score);
	}
	frank.close();
	frank.open(ss.str().c_str(), std::ios::out);
	for (int i = 0; i < cnt && i < 10; i++)
		frank << person[i].name << " " << person[i].score << std::endl;
}

void my_exit() {
	int result = MessageBox(NULL, "你真的要退出吗？\n（警告：你的进度将不会被保存）", "2048", MB_YESNO | MB_ICONWARNING | MB_SYSTEMMODAL);
	if (result == IDYES) exit(0);
}
