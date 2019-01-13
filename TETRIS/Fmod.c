#include "TETRIS.h"


FMOD_SOUND* FmodCreateStreamFromFile(const char* filename, int Loop)
{
	FMOD_RESULT result;
	FMOD_SOUND *sound;
	
	if(Loop)
	{
	result = FMOD_System_CreateStream(fmodSystem, filename,
		FMOD_SOFTWARE | FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound);
	}
	else
	result = FMOD_System_CreateStream(fmodSystem, filename,
		FMOD_SOFTWARE | FMOD_LOOP_OFF | FMOD_2D, 0, &sound);
	if (result != FMOD_OK)
		return NULL;
	
	return sound;
}

FMOD_SOUND* FmodCreateStreamFromResource(HMODULE hModule, LPCTSTR name, LPCTSTR type, int Loop)
{
	HRSRC hRsrc;
	DWORD size;
	HGLOBAL hGlobal;
	FMOD_RESULT result;
	FMOD_SOUND *sound;
	FMOD_CREATESOUNDEXINFO info = {0,};

	void *ptr;
	
	hRsrc = FindResource(hModule, name, type);
	if (NULL == hRsrc)
		return NULL;
		
	size = SizeofResource(hModule, hRsrc);
	if (0 == size)
		return NULL;
	
	hGlobal = LoadResource(hModule, hRsrc);
	if (NULL == hGlobal)
		return NULL;
	
	ptr = LockResource(hGlobal);
	if (NULL == ptr)
		return NULL;
	
	info.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
	info.length = size;
	if(Loop)
		result = FMOD_System_CreateStream(fmodSystem, (char*)ptr,
			FMOD_OPENMEMORY | FMOD_SOFTWARE | FMOD_LOOP_NORMAL | FMOD_2D,
			&info, &sound);
	else
		result = FMOD_System_CreateStream(fmodSystem, (char*)ptr,
			FMOD_OPENMEMORY | FMOD_SOFTWARE | FMOD_LOOP_OFF | FMOD_2D,
			&info, &sound);
	if (result != FMOD_OK)
		return NULL;
	
	return sound;
}

void InitGameSound(void)
{
	Boom		=	FmodCreateStreamFromResource(hInst, MAKEINTRESOURCE(SOUND_BOOM), TEXT("Sound"), FALSE);
	GameOver	=	FmodCreateStreamFromResource(hInst, MAKEINTRESOURCE(SOUND_GAMEOVER), TEXT("Sound"), FALSE);
	LvUp		=	FmodCreateStreamFromResource(hInst, MAKEINTRESOURCE(SOUND_LVUP), TEXT("Sound"), FALSE);
	Sel			=	FmodCreateStreamFromResource(hInst, MAKEINTRESOURCE(SOUND_SEL), TEXT("Sound"), FALSE);
	Selected	=	FmodCreateStreamFromResource(hInst, MAKEINTRESOURCE(SOUND_SELECTED), TEXT("Sound"), FALSE);
	Tick		=	FmodCreateStreamFromResource(hInst, MAKEINTRESOURCE(SOUND_TICK), TEXT("Sound"), FALSE);
	Turn		=	FmodCreateStreamFromResource(hInst, MAKEINTRESOURCE(SOUND_TURN), TEXT("Sound"), FALSE);
	ClrLine		=	FmodCreateStreamFromResource(hInst, MAKEINTRESOURCE(SOUND_CLRLINE), TEXT("Sound"), FALSE);
	BGM			=	FmodCreateStreamFromResource(hInst, MAKEINTRESOURCE(SOUND_BGM), TEXT("Sound"), TRUE);
	Coin		=	FmodCreateStreamFromResource(hInst, MAKEINTRESOURCE(SOUND_COIN), TEXT("Sound"), FALSE);
	FMOD_System_Update(fmodSystem);
}

void UnInitGameSound(void)
{
	FMOD_Sound_Release(Boom);
	FMOD_Sound_Release(GameOver);
	FMOD_Sound_Release(LvUp);
	FMOD_Sound_Release(Sel);
	FMOD_Sound_Release(Selected);
	FMOD_Sound_Release(Tick);
	FMOD_Sound_Release(Turn);
	FMOD_Sound_Release(ClrLine);
	FMOD_Sound_Release(Coin);
	FMOD_Sound_Release(BGM);
	FMOD_System_Update(fmodSystem);
}

void StopGameSound(void)
{
	BOOL isPlaying=FALSE;
	if(!bSEFF)
		return;
	FMOD_Channel_IsPlaying(cBoom,&isPlaying);
	if(isPlaying)
		FMOD_Channel_Stop(cBoom);

	FMOD_Channel_IsPlaying(cGameOver, &isPlaying);
	if (isPlaying)
		FMOD_Channel_Stop(cGameOver);

	FMOD_Channel_IsPlaying(cLvUp, &isPlaying);
	if (isPlaying)
		FMOD_Channel_Stop(cLvUp);

	FMOD_Channel_IsPlaying(cSel, &isPlaying);
	if (isPlaying)
		FMOD_Channel_Stop(cSel);

	FMOD_Channel_IsPlaying(cSelected, &isPlaying);
	if (isPlaying)
		FMOD_Channel_Stop(cSelected);

	FMOD_Channel_IsPlaying(cTick, &isPlaying);
	if (isPlaying)
		FMOD_Channel_Stop(cTick);

	FMOD_Channel_IsPlaying(cTurn, &isPlaying);
	if (isPlaying)
		FMOD_Channel_Stop(cTurn);

	FMOD_Channel_IsPlaying(cClrLine, &isPlaying);
	if (isPlaying)
		FMOD_Channel_Stop(cClrLine);
	
	FMOD_Channel_IsPlaying(cCoin, &isPlaying);
	if (isPlaying)
		FMOD_Channel_Stop(cCoin);
	FMOD_System_Update(fmodSystem);
}

void PlayGameSound(GAME_SOUND Sound_Type)
{
	BOOL isPlaying=FALSE;
	if(!bSEFF)
		return;
	switch(Sound_Type)
	{
	case GAME_BOOM:
		FMOD_Channel_IsPlaying(cBoom,&isPlaying);
		if(isPlaying)
			FMOD_Channel_Stop(cBoom);
		FMOD_System_PlaySound(fmodSystem, FMOD_CHANNEL_FREE, Boom, 0, &cBoom);
		FMOD_Channel_SetVolume(cBoom,vGameSound);
		break;
	case GAME_GAMEOVER:
		FMOD_Channel_IsPlaying(cGameOver,&isPlaying);
		if(isPlaying)
			FMOD_Channel_Stop(cGameOver);
		FMOD_System_PlaySound(fmodSystem, FMOD_CHANNEL_FREE, GameOver, 0, &cGameOver);
		FMOD_Channel_SetVolume(cGameOver,vGameSound);
		break;
	case GAME_LVUP:
		FMOD_Channel_IsPlaying(cLvUp,&isPlaying);
		if(isPlaying)
			FMOD_Channel_Stop(cLvUp);
		FMOD_System_PlaySound(fmodSystem, FMOD_CHANNEL_FREE, LvUp, 0, &cLvUp);
		FMOD_Channel_SetVolume(cLvUp,vGameSound);
		break;
	case GAME_SEL:
		FMOD_Channel_IsPlaying(cSel,&isPlaying);
		if(isPlaying)
			FMOD_Channel_Stop(cSel);
		FMOD_System_PlaySound(fmodSystem, FMOD_CHANNEL_FREE, Sel, 0, &cSel);
		FMOD_Channel_SetVolume(cSel,vGameSound);
		break;
	case GAME_SELECTED:
		FMOD_Channel_IsPlaying(cSelected,&isPlaying);
		if(isPlaying)
			FMOD_Channel_Stop(cSelected);
		FMOD_System_PlaySound(fmodSystem, FMOD_CHANNEL_FREE, Selected, 0, &cSelected);
		FMOD_Channel_SetVolume(cSelected,vGameSound);
		break;
	case GAME_TICK:
		FMOD_Channel_IsPlaying(cTick,&isPlaying);
		if(isPlaying)
			FMOD_Channel_Stop(cTick);
		FMOD_System_PlaySound(fmodSystem, FMOD_CHANNEL_FREE, Tick, 0, &cTick);
		FMOD_Channel_SetVolume(cTick,vGameSound);
		break;
	case GAME_TURN:
		FMOD_Channel_IsPlaying(cTurn,&isPlaying);
		if(isPlaying)
			FMOD_Channel_Stop(cTurn);
		FMOD_System_PlaySound(fmodSystem, FMOD_CHANNEL_FREE, Turn, 0, &cTurn);
		FMOD_Channel_SetVolume(cTurn,vGameSound);
		break;
	case GAME_CLRLINE:
		FMOD_Channel_IsPlaying(cClrLine,&isPlaying);
		if(isPlaying)
			FMOD_Channel_Stop(cClrLine);
		FMOD_System_PlaySound(fmodSystem, FMOD_CHANNEL_FREE, ClrLine, 0, &cClrLine);
		FMOD_Channel_SetVolume(cClrLine,vGameSound);
		break;
	case GAME_COIN:
		FMOD_Channel_IsPlaying(cCoin,&isPlaying);
		if(isPlaying)
			FMOD_Channel_Stop(cCoin);
		FMOD_System_PlaySound(fmodSystem, FMOD_CHANNEL_FREE, Coin, 0, &cCoin);
		FMOD_Channel_SetVolume(cCoin,vGameSound);
		break;
	default:
		FatalError(ERROR_PLAY_GAME_SOUND);
	}
	FMOD_System_Update(fmodSystem);
}

void LoadMusic(void)
{
	int i=0,num=0;
	char str[30]="";
	SoundChk(Music_Type);
	switch(Music_Type)
	{
	case MUSIC_OFF:
		Music=NULL;
		break;
	case MUSIC_8BIT:
		num=rand()%NUM_8BIT+1;
		sprintf(str, "MP3\\BGM\\8BIT\\%d.mp3", num);
		Music=FmodCreateStreamFromFile(str,FALSE);
		break;
	case MUSIC_ANI:
		num=rand()%NUM_ANI+1;
		sprintf(str, "MP3\\BGM\\ANI\\%d.mp3", num);
		Music=FmodCreateStreamFromFile(str,FALSE);
		break;
	case MUSIC_CATMARIO:
		num=rand()%NUM_CAT+1;
		sprintf(str, "MP3\\BGM\\CAT\\%d.mp3", num);
		Music=FmodCreateStreamFromFile(str,TRUE);
		FMOD_Sound_SetLoopCount(Music,5);
		break;
	case MUSIC_USER_DEFINE:
		Music = FmodCreateStreamFromFile(MusicPath,TRUE);
		break;
	}
	
	if(NULL==Music && Music_Type)
	{
		FatalError(ERROR_FMOD_LOAD);
	}
	
	FMOD_System_PlaySound(fmodSystem, FMOD_CHANNEL_FREE, Music, 0, &cMusic);
	FMOD_System_Update(fmodSystem);
}
