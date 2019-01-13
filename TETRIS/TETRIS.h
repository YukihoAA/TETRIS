#ifndef __TETRIS_H__
#define __TETRIS_H__

#define _CRT_SECURE_NO_WARNINGS

//테트리스 버전 정의
#define NORMAL_TETRIS

//표준 라이브러리 포함
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include <WinInet.h>
#include <math.h>
#include <fmod.h>
#include <io.h>
#include <fcntl.h>
#include <CommCtrl.h>					//Progress Bar

#pragma comment(lib,"DelayImp.lib")		//dll 로딩
#pragma comment(lib, "fmodex_vc.lib")	//FMOD 사운드 라이브러리

#include "resource.h"

#include "Typedef.h"
#include "Define.h"
#include "Console.h"

//매니페스트 - 리소스에 테마 적용
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

//레지스트리 함수
UINT RegReadInt(HKEY hKey, LPCSTR lpKey, LPCSTR lpValue, INT nDefault);
BOOL RegReadStr(HKEY hKey, LPCSTR lpKey, LPCSTR lpValue, LPCSTR lpDefault, LPSTR lpRet, DWORD nSize);
BOOL RegWriteInt(HKEY hKey, LPCSTR lpKey, LPCSTR lpValue, UINT nData);
BOOL RegWriteStr(HKEY hKey, LPCSTR lpKey, LPCSTR lpValue, LPCSTR lpData);

extern int Lbest;

void init(void);
void UnInit(void);
void menu(void);
void GetDir(void);
void PlayGame(void);
void LoadMusic(void);
char confirmYN(void);
void prtd(WCHAR *str, int delay);
void prtCurrBlock(BLOCK *CurrBlock);
void prtMap(int Map[MAP_Y][MAP_X]);
void FatalError(int ErrorCode);
void InitGameSound(void);
void UnInitGameSound(void);
void StopGameSound(void);
void BGMSel(void);
void SoundChk(MUSIC_TYPE Type);
void prtScore(SCOREDATA ScoreData);
void HowToDo(void);
void StartUp(void);
BOOL cls(void);

void _prtBomb(void);
void _prtBlock(BLOCK_COLOR color);
void PlayGameSound(GAME_SOUND Sound_Type);

HWND hOut;
HWND hWnd;
HINSTANCE hInst;
BOOL FileExists(const char* FileName);

char MusicPath[1024];

BOOL bSEFF;

FMOD_SYSTEM *fmodSystem;

FMOD_SOUND *Boom;
FMOD_CHANNEL *cBoom;
FMOD_SOUND *GameOver;
FMOD_CHANNEL *cGameOver;
FMOD_SOUND *LvUp;
FMOD_CHANNEL *cLvUp;
FMOD_SOUND *Sel;
FMOD_CHANNEL *cSel;
FMOD_SOUND *Selected;
FMOD_CHANNEL *cSelected;
FMOD_SOUND *Tick;
FMOD_CHANNEL *cTick;
FMOD_SOUND *Turn;
FMOD_CHANNEL *cTurn;
FMOD_SOUND *ClrLine;
FMOD_CHANNEL *cClrLine;
FMOD_SOUND *Coin;
FMOD_CHANNEL *cCoin;

float vGameSound;

FMOD_SOUND *BGM;
FMOD_CHANNEL *cBGM;

BOOL bBGM;

FMOD_SOUND *Music;
FMOD_CHANNEL *cMusic;

float vMusic;

MUSIC_TYPE Music_Type;

BOOL bExitGame;


#endif