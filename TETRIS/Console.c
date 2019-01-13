#include "TETRIS.h"

//기본 글자색, 배경색
extern int DefBgColor=0,DefColor=0;

//현재 커서 위치
COORD GetCurPos(void)
{
    CONSOLE_SCREEN_BUFFER_INFO buffInfo;
    GetConsoleScreenBufferInfo(hOut,&buffInfo);
    return buffInfo.dwCursorPosition;
}

//커서 보이거나 숨기는 함수
void ToggleCursor(BOOL isVisible)
{
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible=isVisible;
	ConsoleCursor.dwSize=1;
	SetConsoleCursorInfo(hOut,&ConsoleCursor);
}


//좌표 이동 함수
void gotoxy(int x,int y)
{
	COORD XY = {(SHORT)x,(SHORT)y};
	SetConsoleCursorPosition(hOut,XY);
}

//좌표를 x축 방향으로 두 칸씩 이동하는 함수
void gotowxy(int x,int y)
{
	COORD XY = {(SHORT)x*2,(SHORT)y*2};
	SetConsoleCursorPosition(hOut,XY);
}


//윈도우 크기 설정 함수
void SetWinSize(int cols, int lines)
{
	char str[35];
	sprintf(str,"mode con cols=%d lines=%d",cols,lines);
	system(str);
}

//윈도우 제목 설정 함수
void SetTitle(LPCWSTR lpConsoleTitle)
{
	SetConsoleTitle(lpConsoleTitle);
}


//글자색 얻기
int GetColor(void)
{
    int color;
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hOut, &info);
    color = info.wAttributes & 0xf;
    return color;
}

//배경색 얻기
int GetBgColor(void)
{
    int color;
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hOut, &info);
    color = (info.wAttributes & 0xf0) >> 4;
    return color;
}

//기본 글자색, 배경색 저장
void GetDefColor(void) {
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hOut, &info);
    DefBgColor = (info.wAttributes & 0xf0) >> 4;
    DefColor = info.wAttributes & 0xf;
}

//기본 글자색, 배경색으로 복원
void SetDefColor(void) {
    SetConsoleTextAttribute(hOut, (DefBgColor << 4) | DefColor);
}

//글자색, 배경색 변경
void SetColor(int Color, int BgColor) {
    Color &= 0xf;
    BgColor &= 0xf;
    SetConsoleTextAttribute(hOut, (BgColor << 4) | Color);
}
