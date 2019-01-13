#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__


typedef enum _BLOCK_TYPE{
	BLOCK_NONE, /* 초기상태 */

			/*  MAIN     LEFT     FLIP     RIGHT   */
	BLOCK_A,/*  □      □■■
				■■    ■■
				  ■    
			*/
	BLOCK_B,/*  □■    □■
				■■      ■■
				■
			*/
	BLOCK_C,/*  □      □■      □■  
				■■    ■■■    ■■    □■■
				■                  ■      ■
			*/
	BLOCK_D,/*  □      □  ■    □■    
				■      ■■■      ■    □■■
				■■                ■    ■ 
			*/
	BLOCK_E,/*  □■    □        □■    
				■      ■■■      ■    □■■
				■                ■■        ■
			*/
	BLOCK_F,/*  □■
				■■
			*/
	BLOCK_G,/*    
				□■■■
			*/
	BLOCK_BOMB/*♪*/

}BLOCK_TYPE;

typedef enum _BLOCK_STATE{
	BLOCK_FIXED,	//0 : 모양 설정 안됨
	BLOCK_MAIN,		//1 : 기본 형태
	BLOCK_RIGHT,	//2 : 우측 90도
	BLOCK_FLIP,		//3 : 180도 회전
	BLOCK_LEFT		//4 : 좌측 90도
}BLOCK_STATE;


typedef enum _BLOCK_MOVE{
	MOVE_NONE,		//0 : 현재위치
	MOVE_DOWN,		//1 : 아래로 진행
	MOVE_RIGHT,		//2 : 우측 진행
	MOVE_LEFT,		//3 : 좌측 진행
	MOVE_UP,		//4 : 위로 진행
	TURN_RIGHT,		//5 : 우로 90도 회전
	TURN_LEFT		//6 : 좌로 90도 회전
}BLOCK_MOVE;

typedef enum _BLOCK_COLOR{
	BLOCK_NULL,		//0 : 빈 공간
	BLOCK_BLACK,	//1 + 9 : 검은색 블럭
	BLOCK_BLUE,		//2 + 10 : 파랑색 블럭
	BLOCK_GREEN,	//3 + 11 : 초록색 블럭
	BLOCK_SKY_BLUE,	//4 + 12 : 하늘색 블럭
	BLOCK_RED,		//5 + 13 : 빨강색 블럭
	BLOCK_VIOLET,	//6 + 14 : 보라색 블럭
	BLOCK_YELLOW,	//7 + 15 : 노란색 블럭
	BLOCK_WHITE		//8 + 16 : 하얀색 블럭
}BLOCK_COLOR;

typedef struct _BLOCK{
	int x;
	int y;

	BLOCK_TYPE Type;
	BLOCK_COLOR Color;
	BLOCK_STATE State;

	int dropy;
}BLOCK;

typedef struct _SCOREDATA{
	int Level;
	int lines;
	unsigned int score;
	unsigned int best;
}SCOREDATA;


typedef enum _MUSIC_TYPE{
	MUSIC_OFF,
	MUSIC_8BIT,
	MUSIC_ANI,
	MUSIC_CATMARIO,
	MUSIC_USER_DEFINE
}MUSIC_TYPE;

typedef enum _GAME_SOUND{
	GAME_BOOM,
	GAME_GAMEOVER,
	GAME_LVUP,
	GAME_SEL,
	GAME_SELECTED,
	GAME_TICK,
	GAME_TURN,
	GAME_CLRLINE,
	GAME_COIN
}GAME_SOUND;


//윈도우 배경색 및 문자색 설정 함수
typedef enum _CON_COLOR
{

	CON_BLACK,/* 0 : 까망 */
	CON_DARK_BLUE,/* 1 : 어두운 파랑 */
	CON_DARK_GREEN,/* 2 : 어두운 초록 */ 
	CON_DARK_SKY_BLUE, /* 3 : 어두운 하늘 */
	CON_DARK_RED, /* 4 : 어두운 빨강 */
	CON_DARK_VIOLET, /* 5 : 어두운 보라 */
	CON_DARK_YELLOW, /* 6 : 어두운 노랑 */
	CON_GRAY, /* 7 : 회색 */
	CON_DARK_GRAY, /* 8 : 어두운 회색 */ 
	CON_BLUE, /* 9 : 파랑 */
	CON_GREEN, /* 10 : 초록 */ 
	CON_SKY_BLUE, /* 11 : 하늘 */
	CON_RED, /* 12 : 빨강 */ 
	CON_VIOLET, /* 13 : 보라 */
	CON_YELLOW, /* 14 : 노랑 */
	CON_WHITE, /* 15 : 하양 */
}CON_COLOR;

#endif