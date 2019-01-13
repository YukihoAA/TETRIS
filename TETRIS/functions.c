#include "TETRIS.h"

BOOL CtrlHandler( DWORD fdwCtrlType )
{
	switch(fdwCtrlType)
	{
	case CTRL_C_EVENT:
	case CTRL_CLOSE_EVENT:
	case CTRL_LOGOFF_EVENT:
	case CTRL_SHUTDOWN_EVENT:
	case CTRL_BREAK_EVENT:
	default:
		UnInit();
		_exit(0);
		break;
	}
	return FALSE;
}

//초기화 함수
void init(void)
{
	hWnd=FindWindow(L"ConsoleWindowClass",NULL);
	ShowWindow(hWnd, SW_HIDE);

	hInst=GetModuleHandle(NULL);
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	_setmode(_fileno(stdout), _O_U16TEXT);

	SetConsoleCtrlHandler( ( PHANDLER_ROUTINE )CtrlHandler, TRUE );

	CoInitialize(NULL);

	GetDir();

	ToggleCursor(FALSE);

	srand((unsigned)time(NULL));

	GetDefColor();

	if (!FileExists("fmodex.dll")) {
		MessageBox(hWnd, L"fmodex.dll이 없습니다.", L"오류", MB_OK | MB_ICONERROR);
		FatalError(ERROR_FMOD_INIT);
	}

	if (FMOD_System_Create(&fmodSystem) != FMOD_OK) // FMOD system 생성 
		FatalError(ERROR_FMOD_INIT);
	
	if (FMOD_System_Init(fmodSystem, 32, FMOD_INIT_NORMAL, NULL) != FMOD_OK) {// FMOD system 초기화.
		FMOD_System_Release(fmodSystem);
		FatalError(ERROR_FMOD_INIT);
	}

	bSEFF=RegReadInt(HCU,KEY,"bSEFF",TRUE);
	bBGM=RegReadInt(HCU,KEY,"bBGM",TRUE);
	vMusic=0.7f;
	vGameSound=0.7f;

	if(bSEFF)
		InitGameSound();

	strcpy(MusicPath,"");
	Music_Type=RegReadInt(HCU,KEY,"Music",MUSIC_ANI);
	if(Music_Type < MUSIC_OFF || Music_Type > MUSIC_USER_DEFINE)
#ifndef NORMAL_TETRIS
		Music_Type=MUSIC_CATMARIO;
#else
		Music_Type=MUSIC_ANI;
#endif
	if(Music_Type == MUSIC_USER_DEFINE)
	{
		RegReadStr(HCU,KEY,"MusicPath","",MusicPath,1024);
		if(!strcmp(MusicPath,"") || !FileExists(MusicPath))
#ifndef NORMAL_TETRIS
			Music_Type=MUSIC_CATMARIO;
#else
			Music_Type=MUSIC_ANI;
#endif
	}

	Lbest=RegReadInt(HCU,KEY,"BestScore",0);

	SoundChk(Music_Type);
	
	bExitGame=FALSE;

	SetWinSize(50, 30);
	SetTitle(L"TETRIS");
	ShowWindow(hWnd, SW_SHOW);
}

//로드 종료 함수
void UnInit(void)
{
	bExitGame=TRUE;
	FMOD_Channel_Stop(cMusic);
	FMOD_Sound_Release(Music);
	FMOD_Channel_Stop(cBGM);
	StopGameSound();
	UnInitGameSound();
	FMOD_System_Release(fmodSystem);
	CoUninitialize();
	RegWriteInt(HCU,KEY,"Music",Music_Type);
	RegWriteInt(HCU,KEY,"bSEFF",bSEFF);
	RegWriteInt(HCU,KEY,"bBGM",bBGM);
	RegWriteInt(HCU,KEY,"BestScore",Lbest);

	if(Music_Type == MUSIC_USER_DEFINE)
		RegWriteStr(HCU,KEY,"MusicPath",MusicPath);
	cls();
}

//BGM 설정 함수
void BGMSel(void)
{
	char lpstrMsg[1024]="";
	OPENFILENAMEA OFN;
	memset(&OFN,0,sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = hWnd;
	OFN.lpstrFilter="MPEG Audio파일(*.mp3)\0*.mp3\0Wave파일(*.wav)\0*.wav\0Windows Media Audio파일(*.wma)	<WMAFile>\0*.wma\0Ogg파일(*.ogg)	<OggFile>\0*.ogg\0Apple파일(*.aiff)\0*.aiff\0Apple-C파일(*.aifc)\0*.aifc\0FLAC Lossless Codec파일(*.flac)	<FLACFile>\0*.flac\0";
	OFN.lpstrFile = MusicPath;
	OFN.nMaxFile=1024;
	GetOpenFileNameA(&OFN);
	if(!strcmp(MusicPath,""))
	{
		MessageBox(hWnd,L"배경음을 선택하지 않으셨습니다.\n배경음 없음으로 설정됩니다.",L"오류",MB_OK | MB_ICONWARNING);\
		Music_Type=MUSIC_OFF;
		GetDir();
		return ;
	}
	sprintf(lpstrMsg,"배경음이 %s 로 설정되었습니다.",MusicPath);
	MessageBoxA(hWnd,lpstrMsg,"TETRIS",MB_OK | MB_ICONINFORMATION);
	GetDir();
}

//사운드 파일 체크 함수
void SoundChk(MUSIC_TYPE Type)
{
	int i=0;
	char str[30] = "";
	switch (Type)
	{
	case MUSIC_8BIT:
		for (i = 0; i < NUM_8BIT; i++)
		{
			sprintf(str, "MP3\\BGM\\8BIT\\%d.mp3", i + 1);
			if (!FileExists(str))
				FatalError(ERROR_NO_MUSIC_8BIT);
		}
		break;
	case MUSIC_ANI:
		for (i = 0; i < NUM_ANI; i++)
		{
			sprintf(str, "MP3\\BGM\\ANI\\%d.mp3", i + 1);
			if (!FileExists(str))
				FatalError(ERROR_NO_MUSIC_ANI);
		}
		break;
	case MUSIC_CATMARIO:
		for (i = 0; i < NUM_CAT; i++)
		{
			sprintf(str, "MP3\\BGM\\CAT\\%d.mp3", i + 1);
			if (!FileExists(str))
				FatalError(ERROR_NO_MUSIC_CAT);
		}
	}
}

//현 디렉터리 추출 함수
void GetDir(void)
{
	int i=0;
	char CurrDir[MAX_PATH]={0,};
	GetModuleFileNameA(hInst, CurrDir,sizeof(CurrDir));
	for(i=strlen(CurrDir)-1;i>0;i--)
	{
		if(CurrDir[i]=='\\')
		{
			CurrDir[i]='\0';
			break;
		}
	}
	SetCurrentDirectoryA(CurrDir);
}

//Y,N입력 확인 함수
char confirmYN(void)
{
	char ch;
	for(;;)
	{
		ch=(char)_getch();
		switch(ch)
		{
		case 'y': case 'Y': return 'Y';
		case 'n': case 'N': return 'N';
		default:
				wprintf(L"y,n을 입력해주세요");
		}
	}
}

//파일 존제여부 판단 함수
BOOL FileExists(const char* FileName)
{
	FILE *fp=fopen(FileName,"r");
	if(!fp)
		return FALSE;
	else
		fclose(fp);
	return TRUE;
}

void FatalError(int ErrorCode)
{
	char lpstrMsg[200]="";
	cls();
	switch(ErrorCode)
	{
	case ERROR_FMOD_INIT:
		sprintf(lpstrMsg,"Error Code: %d\nFMOD 사운드 라이브러리 초기화 중 오류가 발생했습니다.\n\n다시 실행해주세요",ErrorCode);
		MessageBoxA(hWnd,lpstrMsg,"",MB_OK|MB_ICONWARNING);
		break;
	case ERROR_NO_MUSIC_8BIT:
	case ERROR_NO_MUSIC_ANI:
	case ERROR_NO_MUSIC_CAT:
		sprintf(lpstrMsg,"Error Code: %d\n사운드 파일을 불러오는 중 오류가 발생했습니다.\n\n사운드 파일이 올바른 위치에 있는지 확인후 다시 실행해주세요",ErrorCode);
		MessageBoxA(hWnd,lpstrMsg,"",MB_OK|MB_ICONWARNING);
		break;
	default:
		sprintf(lpstrMsg,"Error Code: %d",ErrorCode);
		MessageBoxA(hWnd,lpstrMsg,"",MB_OK|MB_ICONWARNING);
	}
	_exit(0);
}

void prtd(WCHAR *str, int delay)
{
	size_t i=0;
	for(i=0;i<wcslen(str);i++)
	{
		_putwch(str[i]);
		Sleep(delay);
	}
}

void StartUp(void)
{
	Sleep(1000);
	PlayGameSound(GAME_COIN);
	gotoxy(19,14);
	SetColor(CON_DARK_GRAY,CON_BLACK);
	wprintf(L" 제작: 유키");
	Sleep(50);
	gotoxy(19,14);
	SetColor(CON_WHITE,CON_BLACK);
	wprintf(L" 제작: 유키");
	Sleep(2000);
	gotoxy(19,14);
	SetColor(CON_GRAY,CON_BLACK);
	wprintf(L" 제작: 유키");
	Sleep(200);
	gotoxy(19,14);
	SetColor(CON_DARK_GRAY,CON_BLACK);
	wprintf(L" 제작: 유키");
	Sleep(200);
	gotoxy(19,14);
	SetColor(CON_BLACK,CON_BLACK);
	wprintf(L" 제작: 유키");
	Sleep(500);
	SetDefColor();
}

BOOL cls(void)
{
	COORD coordScreen = { 0, 0 };    /* here's where we'll home the
										cursor */
	BOOL bSuccess;
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
	DWORD dwConSize;                 /* number of character cells in
										the current buffer */

										/* get the number of character cells in the current buffer */

	bSuccess = GetConsoleScreenBufferInfo(hOut, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	/* fill the entire screen with blanks */

	bSuccess = FillConsoleOutputCharacter(hOut, (TCHAR) ' ',
		dwConSize, coordScreen, &cCharsWritten);

	/* get the current text attribute */

	bSuccess = GetConsoleScreenBufferInfo(hOut, &csbi);

	/* now set the buffer's attributes accordingly */

	bSuccess = FillConsoleOutputAttribute(hOut, csbi.wAttributes,
		dwConSize, coordScreen, &cCharsWritten);

	/* put the cursor at (0, 0) */

	bSuccess = SetConsoleCursorPosition(hOut, coordScreen);
	return bSuccess;
}