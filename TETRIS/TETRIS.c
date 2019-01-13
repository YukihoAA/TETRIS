//헤더 파일 포함
#include "TETRIS.h"

//진입점 함수 정의
int main(int argc, char *argv[])
{
	init();
	StartUp();
	FMOD_System_PlaySound(fmodSystem, FMOD_CHANNEL_FREE, BGM, 0, &cBGM);
	FMOD_Channel_SetVolume(cBGM,vMusic);
	menu();
	UnInit();

	return 0;
}