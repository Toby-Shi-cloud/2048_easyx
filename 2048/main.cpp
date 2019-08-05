#include <cstdio>
#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <algorithm>
#include <cstring>
#include <direct.h>
#include <shlobj.h>
#include <fstream>
#include <sstream>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

//全局变量的声明 
int value[4][4];//每个方格中的值 
int scr;//分数 

//前置的函数声明 
void begin();
void print();
bool mainloop();
bool check();
void over();

//主函数(参数不起任何作用，但是我们需要它) 
int main(int argc, char** argv)
{
	srand(time(0));
	begin();
	while(mainloop());
	over();
	system("pause");
	return 0;
}

void print()
{
	system("cls");
	char _empty[50] = "          |          |          |          \n";
	printf("\t\tYour score: %d\n\n\n", scr);
	printf("%s", _empty);
	for(int i = 0; i < 4; i++){
		if(i){
			for(int i = 0; i < 43; i++) printf("-");
			printf("\n%s%s", _empty, _empty);
		}
		for(int j = 0; j < 4; j++){
			if(j) printf("|");
			if(value[i][j]) printf("  %-6d  ", value[i][j]);
			else for(int k = 0; k < 10; k++)printf(" ");
		}
		printf("\n%s%s", _empty, _empty);
	}
}

void begin()
{
	memset(value, 0, sizeof(value));
	scr = 0;
	int z1, z2;
	z1 = rand() % 16;
	z2 = rand() % 16;
	while(z1 == z2) z2 = rand() % 16;
	value[z1/4][z1%4] = 2;
	value[z2/4][z2%4] = 2;
	print();
}

bool mainloop()
{
	char ch;
	ch = getch();
	while(ch != -32) ch = getch();
	ch = getch();
	bool fg = 0;
	switch(ch){
		case UP:
			for(int j = 0; j < 4; j++){
				for(int i = 0; i < 4; i++){
					if(!value[i][j]) for(int k = i + 1; k < 4; k++) if(value[k][j]){std::swap(value[i][j], value[k][j]); fg = 1; break;}
					if(value[i][j]) for(int k = i + 1; k < 4; k++) if(value[k][j])
						if(value[i][j] == value[k][j]) {value[i][j] <<= 1; fg = 1; scr += value[i][j]; value[k][j] = 0;} else break;
				}
			}break;
		case DOWN:
			for(int j = 0; j < 4; j++){
				for(int i = 3; i >= 0; i--){
					if(!value[i][j]) for(int k = i - 1; k >= 0; k--) if(value[k][j]){std::swap(value[i][j], value[k][j]); fg = 1; break;}
					if(value[i][j]) for(int k = i - 1; k >= 0; k--) if(value[k][j])
						if(value[i][j] == value[k][j]) {value[i][j] <<= 1; fg = 1; scr += value[i][j]; value[k][j] = 0;} else break;
				}
			}break;
		case LEFT:
			for(int i = 0; i < 4; i++){
				for(int j = 0; j < 4; j++){
					if(!value[i][j]) for(int k = j + 1; k < 4; k++) if(value[i][k]){std::swap(value[i][j], value[i][k]); fg = 1; break;}
					if(value[i][j]) for(int k = j + 1; k < 4; k++) if(value[i][k])
						if(value[i][j] == value[i][k]) {value[i][j] <<= 1; fg = 1; scr += value[i][j]; value[i][k] = 0;} else break;
				}
			}break;
		case RIGHT:
			for(int i = 0; i < 4; i++){
				for(int j = 3; j >= 0; j--){
					if(!value[i][j]) for(int k = j - 1; k >= 0; k--) if(value[i][k]){std::swap(value[i][j], value[i][k]); fg = 1; break;}
					if(value[i][j]) for(int k = j - 1; k >= 0; k--) if(value[i][k])
						if(value[i][j] == value[i][k]) {value[i][j] <<= 1; fg = 1; scr += value[i][j]; value[i][k] = 0;} else break;
				}
			}break;
		default:break;
	}
	if(!fg) return 1;
	int candidate[16];
	int cnt = 0;
	int maxn = 0;
	for(int i = 0; i < 16; i++)
		if(!value[i/4][i%4])
			candidate[cnt++] = i;
		else
			maxn = std::max(maxn, value[i/4][i%4]);
	if(cnt){
		int i = rand() % cnt;
		int z = candidate[i];
		int seed;
		int num[5] = {2, 4, 8, 16, 32};
		if(maxn <= 32) seed = 1;
		else if(maxn <= 128) seed = 2;
		else if(maxn <= 1024) seed = 3;
		else if(maxn <= 4096) seed = 4;
		else seed = 5;
		value[z/4][z%4] = num[rand() % seed];
	} 
	print();
	return check();
}

bool check()
{
	for(int z = 0; z < 16; z++)
		if(!value[z/4][z%4]) return 1;
	int fg[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			for(int k = 0; k < 4; k++)
				if(i+fg[k][0]>=0 && i+fg[k][0]<4 && j+fg[k][1]>=0 &&  j+fg[k][1]<4 && value[i][j]==value[i+fg[k][0]][j+fg[k][1]])
					return 1;
	return 0;
}

struct points{
   	char name[100];
   	int score;
   	bool operator < (const points x) const {return score > x.score;}
}person[11];

void over()
{
	printf("GameOver!!!\n");
	Sleep(2000);
	system("cls");
	printf("GameOver!!!\n");
	printf("Your total score is %d!\n", scr);
	printf("Please input your name:\n\t");
	std::string name;
	std::cin >> name;
	CHAR my_documents[MAX_PATH];
    HRESULT result = SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);
	if (result != S_OK){
        std::cout << "Error: " << result << "\n";
        return;
	}
	std::stringstream ss;
	ss << my_documents << "\\Toby'sProgram";
    if (_access(ss.str().c_str(), 0) == -1)
    	_mkdir(ss.str().c_str());
    ss << "\\2048";
    if (_access(ss.str().c_str(), 0) == -1)
    	_mkdir(ss.str().c_str());
    ss << "\\rank.txt";
    std::fstream frank(ss.str().c_str(), std::ios::in);
	int cnt = 0;
	while(frank >> person[cnt].name >> person[cnt].score) cnt++;
	strcpy(person[cnt].name, name.c_str());
	person[cnt].score = scr;
	cnt++;
	std::sort(person, person + cnt);
	printf("Here is the ranking:\n");
	char rnk[12][5] = {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th"};
	for(int i = 0; i < cnt && i < 10; i++)
		printf("%4s %20s:   %6d\n", rnk[i], person[i].name, person[i].score);
	frank.close();
	frank.open(ss.str().c_str(), std::ios::out);
	for(int i = 0; i < cnt && i < 10; i++)
		frank << person[i].name << " " <<person[i].score << std::endl;
}

