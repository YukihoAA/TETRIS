#ifndef __CONSOLE_H__
#define __CONSOLE_H__

extern int DefBgColor,DefColor;			//기본 글자색, 배경색

COORD GetCurPos(void);					//현재 커서 위치
void ToggleCursor(BOOL isVisible);		//커서 보이거나 숨기는 함수

void gotoxy(int x,int y);				//좌표 이동 함수
void gotowxy(int x,int y);				//좌표를 x축 방향으로 두 칸씩 이동하는 함수


void SetWinSize(int cols, int lines);	//윈도우 크기 설정 함수
void SetTitle(LPCWSTR lpConsoleTitle);	//윈도우 제목 설정 함수

int GetColor(void);						//글자색 얻기
int GetBgColor(void);					//배경색 얻기
void GetDefColor(void);					//기본 글자색, 배경색 저장
void SetDefColor(void);					//기본 글자색, 배경색으로 복원
void SetColor(int Color, int BgColor);	//글자색, 배경색 변경




#endif