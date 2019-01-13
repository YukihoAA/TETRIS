#include "TETRIS.h"


enum MenuSelect {
	MENU_NONE,
	MENU_PLAY,
	MENU_HOWTO,
	MENU_SETTING,
	MENU_EXIT,
	MENU_REDRAW,
	MENU_MUSIC,
	MENU_SEFF,
	MENU_MENU,
	MENU_OFF,
	MENU_8BIT,
	MENU_ANI,
	MENU_CAT,
	MENU_CUSTOM,
	MENU_SEFF_ON,
	MENU_SEFF_OFF
};

void prtMenuForm(void) {
	wprintf(L"\n\
\t##################################\n\
\t#                                #\n\
\t#                                #\n\
\t#                                #\n\
\t##################################\n");
}

void SEFFSetting(void)
{
	BOOL bExit=FALSE;
	BOOL isPlaying=FALSE;
	enum MenuSelect MenuSel=MENU_NONE;
	cls();
	SetWinSize(50, 30);

	prtMenuForm();
	gotoxy(15, 3);
	wprintf(L"Sound Effect SETTING");
	
	while(_kbhit()) _getch();

	while(!bExit && !bExitGame)
	{
		//print Part
		switch(MenuSel)
		{
		case MENU_REDRAW:
			cls();
			SetWinSize(50, 30);

			prtMenuForm();
			gotoxy(15, 3);
			wprintf(L"Sound Effect SETTING");
		case MENU_NONE:
			gotoxy(13, 15);
			wprintf(L"┌--------------------┐\n");
			gotoxy(13, 16);
			wprintf(L"│         ON         │\n");
			gotoxy(13, 17);
			wprintf(L"└--------------------┘\n");
			gotoxy(13, 19);
			wprintf(L"┌--------------------┐\n");
			gotoxy(13, 20);
			wprintf(L"│         OFF        │\n");
			gotoxy(13, 21);
			wprintf(L"└--------------------┘\n");
			gotoxy(10, 16);
			_putwch(L'>');
			if(bSEFF)
				MenuSel=MENU_SEFF_ON;
			else
				MenuSel=MENU_SEFF_OFF;
			continue;
		case MENU_SEFF_ON:
			gotoxy(10, 20);
			_putwch(L' ');
			gotoxy(10, 16);
			_putwch(L'>');
			break;
		case MENU_SEFF_OFF:
			gotoxy(10, 16);
			_putwch(L' ');
			gotoxy(10, 20);
			_putwch(L'>');
			break;
		default:
			FatalError(ERROR_MENU_PRINT);
		}

		//input Part
		switch(_getch())
		{
		case 0:
			switch (_getch())
			{
			case 63:		//F5
				PlayGameSound(GAME_SEL);
				FMOD_Channel_IsPlaying(cBGM,&isPlaying);
				if(isPlaying)
					FMOD_Channel_Stop(cBGM);
				else
				{
					FMOD_System_PlaySound(fmodSystem, FMOD_CHANNEL_FREE, BGM, 0, &cBGM);
					FMOD_Channel_SetVolume(cBGM,vMusic);
				}
				FMOD_System_Update(fmodSystem);
				break;
			case 65:		//F7
				PlayGameSound(GAME_SEL);
				vMusic -= 0.1f;
				if (vMusic < 0.0f)
					vMusic = 0.0f;
				FMOD_Channel_SetVolume(cBGM, vMusic);
				FMOD_System_Update(fmodSystem);
				break;
			case 66:		//F8
				PlayGameSound(GAME_SEL);
				vMusic += 0.1f;
				if (vMusic > 1.0f)
					vMusic = 1.0f;
				FMOD_Channel_SetVolume(cBGM, vMusic);
				FMOD_System_Update(fmodSystem);
				break;
			case 67:		//F9
				PlayGameSound(GAME_SEL);
				if(bSEFF)
					bSEFF=FALSE;
				else
					bSEFF=TRUE;
				FMOD_System_Update(fmodSystem);
				break;
			case 68:		//F10
				PlayGameSound(GAME_SEL);
				vGameSound -= 0.1f;
				if (vGameSound < 0.0f)
					vGameSound = 0.0f;
				FMOD_System_Update(fmodSystem);
				break;
			}
			break;
		case FUNC_KEY:		//특수키
			switch(_getch())
			{
			case 133:		//F11
				PlayGameSound(GAME_SEL);
				vGameSound += 0.1f;
				if (vGameSound > 1.0f)
					vGameSound = 1.0f;
				FMOD_System_Update(fmodSystem);
				break;
			case ARROW_LEFT:	//←
			case ARROW_UP:		//↑
				MenuSel--;
				PlayGameSound(GAME_SEL);
				if(MenuSel<MENU_SEFF_ON) MenuSel=MENU_SEFF_OFF;
				break;

			case ARROW_RIGHT:	//→
			case ARROW_DOWN:	//↓
				MenuSel++;
				PlayGameSound(GAME_SEL);
				if(MenuSel>MENU_SEFF_OFF) MenuSel=MENU_SEFF_ON;
				break;
			}
			break;
		case ENTER_KEY:
			switch(MenuSel)
			{
			case MENU_SEFF_ON:
				PlayGameSound(GAME_SELECTED);
				bSEFF=TRUE;
				bExit=TRUE;
				break;
			case MENU_SEFF_OFF:
				PlayGameSound(GAME_SELECTED);
				bSEFF=FALSE;
				bExit=TRUE;
				break;
			default:
				FatalError(ERROR_SETTING_INPUT);
			}
			MenuSel=MENU_REDRAW;
			break;
		}
	}
}

void MusicSetting(void)
{
	BOOL bExit=FALSE;
	BOOL isPlaying=FALSE;
	enum MenuSelect MenuSel=MENU_NONE;
	cls();
	SetWinSize(50, 30);

	prtMenuForm();
	gotoxy(18, 3);
	wprintf(L"Music SETTING");
	
	while(_kbhit()) _getch();

	while(!bExit && !bExitGame)
	{
		//print Part
		switch(MenuSel)
		{
		case MENU_REDRAW:
			cls();
			SetWinSize(50, 30);

			prtMenuForm();
			gotoxy(18, 3);
			wprintf(L"Music SETTING");
		case MENU_NONE:
			gotoxy(13, 9);
			wprintf(L"┌--------------------┐\n");
			gotoxy(13, 10);
			wprintf(L"│      Music OFF     │\n");
			gotoxy(13, 11);
			wprintf(L"└--------------------┘\n");
			gotoxy(13, 13);
			wprintf(L"┌--------------------┐\n");
			gotoxy(13, 14);
			wprintf(L"│     8-Bit Music    │\n");
			gotoxy(13, 15);
			wprintf(L"└--------------------┘\n");
			gotoxy(13, 17);
			wprintf(L"┌--------------------┐\n");
			gotoxy(13, 18);
			wprintf(L"│   8-Bit Ani Song   │\n");
			gotoxy(13, 19);
			wprintf(L"└--------------------┘\n");
			gotoxy(13, 21);
			wprintf(L"┌--------------------┐\n");
			gotoxy(13, 22);
			wprintf(L"│   Cat Mario Song   │\n");
			gotoxy(13, 23);
			wprintf(L"└--------------------┘\n");
			gotoxy(13, 25);
			wprintf(L"┌--------------------┐\n");
			gotoxy(13, 26);
			wprintf(L"│   Cat Mario Song   │\n");
			gotoxy(13, 27);
			wprintf(L"└--------------------┘\n");
			gotoxy(13, 25);
			wprintf(L"┌--------------------┐\n");
			gotoxy(13, 26);
			wprintf(L"│    Custom Song     │\n");
			gotoxy(13, 27);
			wprintf(L"└--------------------┘\n");
			gotoxy(10, 10);
			wprintf(L">");
			switch(Music_Type)
			{
			case MUSIC_OFF:
				MenuSel=MENU_OFF;
				break;
			case MUSIC_8BIT:
				MenuSel=MENU_8BIT;
				break;
			case MUSIC_ANI:
				MenuSel=MENU_ANI;
				break;
			case MUSIC_CATMARIO:
				MenuSel=MENU_CAT;
				break;
			case MUSIC_USER_DEFINE:
				MenuSel=MENU_CUSTOM;
				break;
			}
			continue;
		case MENU_OFF:
			gotoxy(10, 26);
			_putwch(L' ');
			gotoxy(10, 14);
			_putwch(L' ');
			gotoxy(10, 10);
			_putwch(L'>');
			break;
		case MENU_8BIT:
			gotoxy(10, 10);
			_putwch(L' ');
			gotoxy(10, 18);
			_putwch(L' ');
			gotoxy(10, 14);
			_putwch(L'>');
			break;
		case MENU_ANI:
			_putwch(L'\b');
			_putwch(L' ');
			gotoxy(10, 18);
			_putwch(L'>');
			break;
		case MENU_CAT:
			_putwch(L'\b');
			_putwch(L' ');
			gotoxy(10, 22);
			_putwch(L'>');
			break;
		case MENU_CUSTOM:
			_putwch(L'\b');
			_putwch(L' ');
			gotoxy(10, 26);
			_putwch(L'>');
			break;
		default:
			FatalError(ERROR_MENU_PRINT);
		}

		//input Part
		switch(_getch())
		{
		case 0:
			switch (_getch())
			{
			case 63:		//F5
				PlayGameSound(GAME_SEL);
				FMOD_Channel_IsPlaying(cBGM,&isPlaying);
				if(isPlaying)
					FMOD_Channel_Stop(cBGM);
				else
				{
					FMOD_System_PlaySound(fmodSystem, FMOD_CHANNEL_FREE, BGM, 0, &cBGM);
					FMOD_Channel_SetVolume(cBGM,vMusic);
				}
				FMOD_System_Update(fmodSystem);
				break;
			case 65:		//F7
				PlayGameSound(GAME_SEL);
				vMusic -= 0.1f;
				if (vMusic < 0.0f)
					vMusic = 0.0f;
				FMOD_Channel_SetVolume(cBGM, vMusic);
				FMOD_System_Update(fmodSystem);
				break;
			case 66:		//F8
				PlayGameSound(GAME_SEL);
				vMusic += 0.1f;
				if (vMusic > 1.0f)
					vMusic = 1.0f;
				FMOD_Channel_SetVolume(cBGM, vMusic);
				FMOD_System_Update(fmodSystem);
				break;
			case 67:		//F9
				PlayGameSound(GAME_SEL);
				if(bSEFF)
					bSEFF=FALSE;
				else
					bSEFF=TRUE;
				FMOD_System_Update(fmodSystem);
				break;
			case 68:		//F10
				PlayGameSound(GAME_SEL);
				vGameSound -= 0.1f;
				if (vGameSound < 0.0f)
					vGameSound = 0.0f;
				FMOD_System_Update(fmodSystem);
				break;
			}
			break;
		case FUNC_KEY:		//특수키
			switch(_getch())
			{
			case 133:		//F11
				PlayGameSound(GAME_SEL);
				vGameSound += 0.1f;
				if (vGameSound > 1.0f)
					vGameSound = 1.0f;
				FMOD_System_Update(fmodSystem);
				break;
			case ARROW_LEFT:	//←
			case ARROW_UP:		//↑
				MenuSel--;
				PlayGameSound(GAME_SEL);
				if(MenuSel<MENU_OFF) MenuSel=MENU_CUSTOM;
				break;

			case ARROW_RIGHT:	//→
			case ARROW_DOWN:	//↓
				MenuSel++;
				PlayGameSound(GAME_SEL);
				if(MenuSel>MENU_CUSTOM) MenuSel=MENU_OFF;
				break;
			}
			break;
		case ENTER_KEY:
			switch(MenuSel)
			{
			case MENU_OFF:
				PlayGameSound(GAME_SELECTED);
				Music_Type=MUSIC_OFF;
				FMOD_Channel_IsPlaying(cBGM,&isPlaying);
				if(isPlaying)
					FMOD_Channel_Stop(cBGM);
				FMOD_System_Update(fmodSystem);
				bExit=TRUE;
				break;
			case MENU_8BIT:
				if(bBGM)
				{
					PlayGameSound(GAME_SELECTED);
					Music_Type=MUSIC_8BIT;
					bExit=TRUE;
				}
				else
				{
					MessageBoxA(hWnd,"사운드 파일이 없어서 선택할 수 없습니다.","오류",MB_OK);
				}
				break;
			case MENU_ANI:
				if(bBGM)
				{
					PlayGameSound(GAME_SELECTED);
					Music_Type=MUSIC_ANI;
					bExit=TRUE;
				}
				else
				{
					MessageBoxA(hWnd,"사운드 파일이 없어서 선택할 수 없습니다.","오류",MB_OK);
				}
				break;
			case MENU_CAT:
				if(bBGM)
				{
					PlayGameSound(GAME_SELECTED);
					Music_Type=MUSIC_CATMARIO;
					bExit=TRUE;
				}
				else
				{
					MessageBoxA(hWnd,"사운드 파일이 없어서 선택할 수 없습니다.","오류",MB_OK);
				}
				break;
			case MENU_CUSTOM:
				PlayGameSound(GAME_SELECTED);
				Music_Type=MUSIC_USER_DEFINE;
				BGMSel();
				bExit=TRUE;
				break;
			default:
				FatalError(ERROR_SETTING_INPUT);
			}
			MenuSel=MENU_REDRAW;
			break;
		}
	}
}

void Setting(void)
{
	BOOL bExit=FALSE;
	BOOL isPlaying=FALSE;
	enum MenuSelect MenuSel=MENU_NONE;
	cls();
	SetWinSize(50, 30);

	prtMenuForm();
	gotoxy(21, 3);
	wprintf(L"SETTING");
	while(_kbhit()) _getch();

	while(!bExit && !bExitGame)
	{
		//print Part
		switch(MenuSel)
		{
		case MENU_REDRAW:
			cls();
			SetWinSize(50, 30);

			prtMenuForm();
			gotoxy(21, 3);
			wprintf(L"SETTING");
		case MENU_NONE:
			gotoxy(13, 11);
			wprintf(L"┌--------------------┐\n");
			gotoxy(13, 12);
			wprintf(L"│        Music       │\n");
			gotoxy(13, 13);
			wprintf(L"└--------------------┘\n");
			gotoxy(13, 15);
			wprintf(L"┌--------------------┐\n");
			gotoxy(13, 16);
			wprintf(L"│    Sound Effect    │\n");
			gotoxy(13, 17);
			wprintf(L"└--------------------┘\n");
			gotoxy(13, 23);
			wprintf(L"┌--------------------┐\n");
			gotoxy(13, 24);
			wprintf(L"│    Back to Menu    │\n");
			gotoxy(13, 25);
			wprintf(L"└--------------------┘\n");
			gotoxy(10, 12);
			_putwch(L'>');
			MenuSel=MENU_MUSIC;
			break;
		case MENU_MUSIC:
			_putwch(L'\b');
			_putwch(L' ');
			gotoxy(10, 12);
			_putwch(L'>');
			break;
		case MENU_SEFF:
			_putwch(L'\b');
			_putwch(L' ');
			gotoxy(10, 16);
			_putwch(L'>');
			break;
		case MENU_MENU:
			_putwch(L'\b');
			_putwch(L' ');
			gotoxy(10, 24);
			_putwch(L'>');
			break;
		default:
			FatalError(ERROR_MENU_PRINT);
		}

		//input Part
		switch(_getch())
		{
		case 0:
			switch (_getch())
			{
			case 63:		//F5
				PlayGameSound(GAME_SEL);
				FMOD_Channel_IsPlaying(cBGM,&isPlaying);
				if(isPlaying)
					FMOD_Channel_Stop(cBGM);
				else
				{
					FMOD_System_PlaySound(fmodSystem, FMOD_CHANNEL_FREE, BGM, 0, &cBGM);
					FMOD_Channel_SetVolume(cBGM,vMusic);
				}
				FMOD_System_Update(fmodSystem);
				break;
			case 65:		//F7
				PlayGameSound(GAME_SEL);
				vMusic -= 0.1f;
				if (vMusic < 0.0f)
					vMusic = 0.0f;
				FMOD_Channel_SetVolume(cBGM, vMusic);
				FMOD_System_Update(fmodSystem);
				break;
			case 66:		//F8
				PlayGameSound(GAME_SEL);
				vMusic += 0.1f;
				if (vMusic > 1.0f)
					vMusic = 1.0f;
				FMOD_Channel_SetVolume(cBGM, vMusic);
				FMOD_System_Update(fmodSystem);
				break;
			case 67:		//F9
				PlayGameSound(GAME_SEL);
				if(bSEFF)
					bSEFF=FALSE;
				else
					bSEFF=TRUE;
				FMOD_System_Update(fmodSystem);
				break;
			case 68:		//F10
				PlayGameSound(GAME_SEL);
				vGameSound -= 0.1f;
				if (vGameSound < 0.0f)
					vGameSound = 0.0f;
				FMOD_System_Update(fmodSystem);
				break;
			}
			break;
		case FUNC_KEY:		//특수키
			switch(_getch())
			{
			case 133:		//F11
				PlayGameSound(GAME_SEL);
				vGameSound += 0.1f;
				if (vGameSound > 1.0f)
					vGameSound = 1.0f;
				FMOD_System_Update(fmodSystem);
				break;
			case ARROW_LEFT:	//←
			case ARROW_UP:		//↑
				MenuSel--;
				PlayGameSound(GAME_SEL);
				if(MenuSel<MENU_MUSIC) MenuSel=MENU_MENU;
				break;

			case ARROW_RIGHT:	//→
			case ARROW_DOWN:	//↓
				MenuSel++;
				PlayGameSound(GAME_SEL);
				if(MenuSel>MENU_MENU) MenuSel=MENU_MUSIC;
				break;
			}
			break;
		case ENTER_KEY:
			switch(MenuSel)
			{
			case MENU_MUSIC:
				PlayGameSound(GAME_SELECTED);
				MusicSetting();
				break;
			case MENU_SEFF:
				PlayGameSound(GAME_SELECTED);
				SEFFSetting();
				break;
			case MENU_MENU:
				PlayGameSound(GAME_SELECTED);
				bExit=TRUE;
				break;
			default:
				FatalError(ERROR_SETTING_INPUT);
			}
			MenuSel=MENU_REDRAW;
			break;
		}
	}
}

//도움말 함수
void HowToDo(void)
{
	cls();

	wprintf(L"\t     <HOW TO PLAY TETRIS>\n\
1. Game Contorl\n\n\
 → : Move Right\n\
 ← : Move Left\n\
 ↓ : Move Down\n\
 ↑ : Turn CW 90˚\n\n\
 z : Turn CCW 90˚\n\
 x : Turn CW 90˚\n\n\
 \n\
2. Music Control\n\n\
 F5 : Next Music (in Game)\n\
      ON / OFF Music (in Menu)\n\
 F6 : Select Different Type of Music\n\
      (8BIT, ANI, CATMARIO, Custom, OFF)\n\
 F7 : Music Volume Down\n\
 F8 : Music Volume Up\n\
 F9 : Sound Effect ON/OFF\n\
 F10 : Sound Effect Volume Down\n\
 F11 : Sound Effect Volume Up\n\n\n\n\n\n Press Enter to Continue...");
	while (_kbhit()) _getch();
	getchar();
	cls();
	wprintf(L"3. Play Rule\n\n\
 Rotate and Move Blocks to Make Lines.\n\
 You'll Get More Points If You Distroy\n\
 Multiple Lines.\n\
 Every time you destroy 5 lines,\n\
 Level will be going up.\n\
 Block Drop Speed is Being Faster\n\
 Depends on Level\n");
	wprintf(L"\n\n\n\n\n\n\n\n\t    Thank you for Playing.\n\n\n\
    Made By Yuki (https://github.com/YukihoAA)\n\n\n\n\n\n\n\n Press Enter to Continue...");
	while (_kbhit()) _getch();
	getchar();
}

void menu(void)
{
	BOOL bExit=FALSE;
	BOOL isPlaying=FALSE;
	enum MenuSelect MenuSel=MENU_NONE;
	cls();
	SetWinSize(50, 30);

	prtMenuForm();
	gotoxy(22, 3);
	prtd(L"TETRIS", 200);
	while(_kbhit()) _getch();

	while(!bExit && !bExitGame)
	{
		//print Part
		switch(MenuSel)
		{
		case MENU_REDRAW:
			cls();
			SetWinSize(50, 30);

			prtMenuForm();
			gotoxy(22, 3);
			wprintf(L"TETRIS");
		case MENU_NONE:
			gotoxy(13, 11);
			wprintf(L"┌--------------------┐");
			gotoxy(13, 12);
			wprintf(L"│        Play        │");
			gotoxy(13, 13);
			wprintf(L"└--------------------┘");
			gotoxy(13, 15);
			wprintf(L"┌--------------------┐");
			gotoxy(13, 16);
			wprintf(L"│     How To Play    │");
			gotoxy(13, 17);
			wprintf(L"└--------------------┘");
			gotoxy(13, 19);
			wprintf(L"┌--------------------┐");
			gotoxy(13, 20);
			wprintf(L"│       Setting      │");
			gotoxy(13, 21);
			wprintf(L"└--------------------┘");
			gotoxy(13, 23);
			wprintf(L"┌--------------------┐");
			gotoxy(13, 24);
			wprintf(L"│        Exit        │");
			gotoxy(13, 25);
			wprintf(L"└--------------------┘");
			gotoxy(10, 12);
			_putwch(L'>');
			MenuSel=MENU_PLAY;
			break;
		case MENU_PLAY:
			_putwch(L'\b');
			_putwch(L' ');
			gotoxy(10, 12);
			_putwch(L'>');
			break;
		case MENU_HOWTO:
			_putwch(L'\b');
			_putwch(L' ');
			gotoxy(10, 16);
			_putwch(L'>');
			break;
		case MENU_SETTING:
			_putwch(L'\b');
			_putwch(L' ');
			gotoxy(10, 20);
			_putwch(L'>');
			break;
		case MENU_EXIT:
			_putwch(L'\b');
			_putwch(L' ');
			gotoxy(10, 24);
			_putwch(L'>');
			break;
		default:
			FatalError(ERROR_MENU_PRINT);
		}

		//input Part
		switch(_getch())
		{
		case 0:
			switch (_getch())
			{
			case 63:		//F5
				PlayGameSound(GAME_SEL);
				FMOD_Channel_IsPlaying(cBGM,&isPlaying);
				if(isPlaying)
					FMOD_Channel_Stop(cBGM);
				else
				{
					FMOD_System_PlaySound(fmodSystem, FMOD_CHANNEL_FREE, BGM, 0, &cBGM);
					FMOD_Channel_SetVolume(cBGM,vMusic);
				}
				FMOD_System_Update(fmodSystem);
				break;
			case 65:		//F7
				PlayGameSound(GAME_SEL);
				vMusic -= 0.1f;
				if (vMusic < 0.0f)
					vMusic = 0.0f;
				FMOD_Channel_SetVolume(cBGM, vMusic);
				FMOD_System_Update(fmodSystem);
				break;
			case 66:		//F8
				PlayGameSound(GAME_SEL);
				vMusic += 0.1f;
				if (vMusic > 1.0f)
					vMusic = 1.0f;
				FMOD_Channel_SetVolume(cBGM, vMusic);
				FMOD_System_Update(fmodSystem);
				break;
			case 67:		//F9
				PlayGameSound(GAME_SEL);
				if(bSEFF)
					bSEFF=FALSE;
				else
					bSEFF=TRUE;
				FMOD_System_Update(fmodSystem);
				break;
			case 68:		//F10
				PlayGameSound(GAME_SEL);
				vGameSound -= 0.1f;
				if (vGameSound < 0.0f)
					vGameSound = 0.0f;
				FMOD_System_Update(fmodSystem);
				break;
			}
			break;
		case FUNC_KEY:		//특수키
			switch(_getch())
			{
			case 133:		//F11
				PlayGameSound(GAME_SEL);
				vGameSound += 0.1f;
				if (vGameSound > 1.0f)
					vGameSound = 1.0f;
				FMOD_System_Update(fmodSystem);
				break;
			case ARROW_LEFT:	//←
			case ARROW_UP:		//↑
				MenuSel--;
				PlayGameSound(GAME_SEL);
				if(MenuSel<MENU_PLAY) MenuSel=MENU_EXIT;
				break;

			case ARROW_RIGHT:	//→
			case ARROW_DOWN:	//↓
				MenuSel++;
				PlayGameSound(GAME_SEL);
				if(MenuSel>MENU_EXIT) MenuSel=MENU_PLAY;
				break;
			}
			break;
		case '1':
			MenuSel=MENU_PLAY;
			PlayGameSound(GAME_SELECTED);
			FMOD_Channel_Stop(cBGM);
			PlayGame();
			FMOD_System_PlaySound(fmodSystem, FMOD_CHANNEL_FREE, BGM, 0, &cBGM);
			FMOD_Channel_SetVolume(cBGM,vMusic);
			break;
		case '2':
			MenuSel=MENU_HOWTO;
			PlayGameSound(GAME_SELECTED);
			HowToDo();
			break;
		case '3':
			MenuSel=MENU_SETTING;
			PlayGameSound(GAME_SELECTED);
			Setting();
			break;
		case '4':
			MenuSel=MENU_EXIT;
			PlayGameSound(GAME_SELECTED);
			bExit=TRUE;
			break;
		case ENTER_KEY:
			switch(MenuSel)
			{
			case MENU_PLAY:
				PlayGameSound(GAME_SELECTED);
				FMOD_Channel_Stop(cBGM);
				PlayGame();
				FMOD_System_PlaySound(fmodSystem, FMOD_CHANNEL_FREE, BGM, 0, &cBGM);
				FMOD_Channel_SetVolume(cBGM,vMusic);
				break;
			case MENU_HOWTO:
				PlayGameSound(GAME_SELECTED);
				HowToDo();
				break;
			case MENU_SETTING:
				PlayGameSound(GAME_SELECTED);
				Setting();
				break;
			case MENU_EXIT:
				PlayGameSound(GAME_SELECTED);
				bExit=TRUE;
				break;
			default:
				FatalError(ERROR_MENU_INPUT);
			}
			MenuSel=MENU_REDRAW;
			break;
		}
	}
}