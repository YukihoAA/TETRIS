#include "TETRIS.h"

int PrevMap[MAP_Y][MAP_X];
extern int Lbest = 0;

//Map상 좌표 이동 함수
void gotoMapxy(int x,int y)
{
	COORD XY = {(SHORT)x*2+MAP_POS_X,(SHORT)y+MAP_POS_Y};
	SetConsoleCursorPosition(hOut,XY);
}

//NextBlock상 좌표 이동 함수
void gotoNextBlockxy(int x,int y)
{
	COORD XY = {(SHORT)x*2+NEXT_BLOCK_POS_X,(SHORT)y+NEXT_BLOCK_POS_Y};
	SetConsoleCursorPosition(hOut,XY);
}

//NNextBlock상 좌표 이동 함수
void gotoNNextBlockxy(int x,int y)
{
	COORD XY = {(SHORT)x*2+NNEXT_BLOCK_POS_X,(SHORT)y+NNEXT_BLOCK_POS_Y};
	SetConsoleCursorPosition(hOut,XY);
}


int AvobeBlock(int Map[MAP_Y][MAP_X], int x, int y)
{
	int i=0,num=0;
	for(i=y;i>=0;i--)
	{
		if(Map[i][x])
			num++;
	}
	return num;
}

void FlickLine(int Map[MAP_Y][MAP_X], int line, int FlickLength, int Time, int ClearCount)
{
	int i = 0;
	while (Time--)
	{
		gotoMapxy(0, line-ClearCount);

		for (i = 0; i < MAP_X; i++)
			_prtBlock(BLOCK_NULL);

		Sleep(FlickLength);
		
		gotoMapxy(0, line-ClearCount);

		for (i = 0; i < MAP_X; i++)
			_prtBlock(Map[line][i]);

		Sleep(FlickLength);
	}
}

BOOL isCollision(int Map[MAP_Y][MAP_X], BLOCK *CurrBlock, BLOCK_MOVE BlockMove)
{
	int X=CurrBlock->x, Y=CurrBlock->y;
	switch(BlockMove)
	{
	case MOVE_NONE:
		break;
	case MOVE_DOWN:
		Y++;
		break;
	case MOVE_RIGHT:
		X++;
		break;
	case MOVE_LEFT:
		X--;
		break;
	case MOVE_UP:
		Y--;
		break;
	default:
		FatalError(ERROR_IS_COLLISION);
	}
	if(X < 0 || Y < 0)
		return TRUE;
	
	switch(CurrBlock->Type)
	{
	case BLOCK_NONE:
		return FALSE;
	case BLOCK_A:
		switch(CurrBlock->State)
		{
		case BLOCK_MAIN:
		case BLOCK_FLIP:
			if(X + 1 > MAP_MAX_X || Y + 2 > MAP_MAX_Y)
				return TRUE;
			else if(Map[Y][X] || Map[Y+1][X] || Map[Y+1][X+1] || Map[Y+2][X+1])
				return TRUE;
			break;
		case BLOCK_LEFT:
		case BLOCK_RIGHT:
			if(X + 2 > MAP_MAX_X || Y + 1 > MAP_MAX_Y)
				return TRUE;
			else if(Map[Y][X+1] || Map[Y][X+2] || Map[Y+1][X] || Map[Y+1][X+1])
				return TRUE;
			break;
		default:
			FatalError(ERROR_IS_COLLISION);
		}
		break;
	case BLOCK_B:
		switch(CurrBlock->State)
		{
		case BLOCK_MAIN:
		case BLOCK_FLIP:
			if(X + 1 > MAP_MAX_X || Y + 2 > MAP_MAX_Y)
				return TRUE;
			else if(Map[Y][X+1] || Map[Y+1][X] || Map[Y+1][X+1] || Map[Y+2][X])
				return TRUE;
			break;
		case BLOCK_LEFT:
		case BLOCK_RIGHT:
			if(X + 2 > MAP_MAX_X || Y + 1 > MAP_MAX_Y)
				return TRUE;
			else if(Map[Y][X] || Map[Y][X+1] || Map[Y+1][X+1] || Map[Y+1][X+2])
				return TRUE;
			break;
		default:
			FatalError(ERROR_IS_COLLISION);
		}
		break;
	case BLOCK_C:
		switch(CurrBlock->State)
		{
		case BLOCK_MAIN:
			if(X + 1 > MAP_MAX_X || Y + 2 > MAP_MAX_Y)
				return TRUE;
			else if(Map[Y][X] || Map[Y+1][X] || Map[Y+1][X+1] || Map[Y+2][X])
				return TRUE;
			break;
		case BLOCK_LEFT:
			if(X + 2 > MAP_MAX_X || Y + 1 > MAP_MAX_Y)
				return TRUE;
			else if(Map[Y][X+1] || Map[Y+1][X] || Map[Y+1][X+1] || Map[Y+1][X+2])
				return TRUE;
			break;
		case BLOCK_RIGHT:
			if(X + 2 > MAP_MAX_X || Y + 1 > MAP_MAX_Y)
				return TRUE;
			else if(Map[Y][X] || Map[Y][X+1] || Map[Y][X+2] || Map[Y+1][X+1])
				return TRUE;
			break;
		case BLOCK_FLIP:
			if(X + 1 > MAP_MAX_X || Y + 2 > MAP_MAX_Y)
				return TRUE;
			else if(Map[Y][X+1] || Map[Y+1][X] || Map[Y+1][X+1] || Map[Y+2][X+1])
				return TRUE;
			break;
		default:
			FatalError(ERROR_IS_COLLISION);
		}
		break;
	case BLOCK_D:
		switch(CurrBlock->State)
		{
		case BLOCK_MAIN:
			if(X + 1 > MAP_MAX_X || Y + 2 > MAP_MAX_Y)
				return TRUE;
			else if(Map[Y][X] || Map[Y+1][X] || Map[Y+2][X] || Map[Y+2][X+1])
				return TRUE;
			break;
		case BLOCK_LEFT:
			if(X + 2 > MAP_MAX_X || Y + 1 > MAP_MAX_Y)
				return TRUE;
			else if(Map[Y][X+2] || Map[Y+1][X] || Map[Y+1][X+1] || Map[Y+1][X+2])
				return TRUE;
			break;
		case BLOCK_RIGHT:
			if(X + 2 > MAP_MAX_X || Y + 1 > MAP_MAX_Y)
				return TRUE;
			else if(Map[Y][X] || Map[Y][X+1] || Map[Y][X+2] || Map[Y+1][X])
				return TRUE;
			break;
		case BLOCK_FLIP:
			if(X + 1 > MAP_MAX_X || Y + 2 > MAP_MAX_Y)
				return TRUE;
			else if(Map[Y][X] || Map[Y][X+1] || Map[Y+1][X+1] || Map[Y+2][X+1])
				return TRUE;
			break;
		default:
			FatalError(ERROR_IS_COLLISION);
		}
		break;
	case BLOCK_E:
		switch(CurrBlock->State)
		{
		case BLOCK_MAIN:
			if(X + 1 > MAP_MAX_X || Y + 2 > MAP_MAX_Y)
				return TRUE;
			else if(Map[Y][X] || Map[Y][X+1] || Map[Y+1][X] || Map[Y+2][X])
				return TRUE;
			break;
		case BLOCK_LEFT:
			if(X + 2 > MAP_MAX_X || Y + 1 > MAP_MAX_Y)
				return TRUE;
			else if(Map[Y][X] || Map[Y+1][X] || Map[Y+1][X+1] || Map[Y+1][X+2])
				return TRUE;
			break;
		case BLOCK_RIGHT:
			if(X + 2 > MAP_MAX_X || Y + 1 > MAP_MAX_Y)
				return TRUE;
			else if(Map[Y][X] || Map[Y][X+1] || Map[Y][X+2] || Map[Y+1][X+2])
				return TRUE;
			break;
		case BLOCK_FLIP:
			if(X + 1 > MAP_MAX_X || Y + 2 > MAP_MAX_Y)
				return TRUE;
			else if(Map[Y][X+1] || Map[Y+1][X+1] || Map[Y+2][X] || Map[Y+2][X+1])
				return TRUE;
			break;
		default:
			FatalError(ERROR_IS_COLLISION);
		}
		break;
	case BLOCK_F:
		switch(CurrBlock->State)
		{
		case BLOCK_MAIN:
		case BLOCK_LEFT:
		case BLOCK_RIGHT:
		case BLOCK_FLIP:
			if(X + 1 > MAP_MAX_X || Y + 1 > MAP_MAX_Y)
				return TRUE;
			else if(Map[Y][X] || Map[Y][X+1] || Map[Y+1][X] || Map[Y+1][X+1])
				return TRUE;
			break;
		default:
			FatalError(ERROR_IS_COLLISION);
		}
		break;
	case BLOCK_G:
		switch(CurrBlock->State)
		{
		case BLOCK_MAIN:
		case BLOCK_FLIP:
			if(X + 3 > MAP_MAX_X || Y > MAP_MAX_Y)
				return TRUE;
			else if(Map[Y][X] || Map[Y][X+1] || Map[Y][X+2] || Map[Y][X+3])
				return TRUE;
			break;
		case BLOCK_LEFT:
		case BLOCK_RIGHT:
			if(X > MAP_MAX_X || Y + 3 > MAP_MAX_Y)
				return TRUE;
			else if(Map[Y][X] || Map[Y+1][X] || Map[Y+2][X] || Map[Y+3][X])
				return TRUE;
			break;
		default:
			FatalError(ERROR_IS_COLLISION);
		}
		break;
	case BLOCK_BOMB:
		switch(CurrBlock->State)
		{
		case BLOCK_MAIN:
		case BLOCK_LEFT:
		case BLOCK_RIGHT:
		case BLOCK_FLIP:
			if(X > MAP_MAX_X || Y > MAP_MAX_Y)
				return TRUE;
			else if(Map[Y][X])
				return TRUE;
			break;
		default:
			FatalError(ERROR_IS_COLLISION);
		}
		break;
	default:
		FatalError(ERROR_IS_COLLISION);
	}
	return FALSE;
}

BOOL isCleared(int Map[MAP_Y][MAP_X], SCOREDATA *ScoreData)
{
	BOOL ClearLine=TRUE;
	int i=0,j=0,k=0,l=0;
	int ClearCount=0;
	int key[4]={1,5,7,24};
	for(i=MAP_Y-1;i>=0;i--)
	{
		ClearLine=TRUE;
		for(j=0;j<MAP_X;j++)
		{
			if(!Map[i][j])
				ClearLine=FALSE;
		}

		if(!ClearLine)
			continue;
		ScoreData->score+=200+ScoreData->Level*20+ClearCount*50;

		if(ScoreData->score > ScoreData->best)
			ScoreData->best=ScoreData->score;

		ScoreData->lines++;
		
		FlickLine(Map,i,150,2,ClearCount);
		PlayGameSound(GAME_CLRLINE);

		for(k=i;k>0;k--)
		{
			for(l=0;l<MAP_X;l++)
			{
				Map[k][l]=Map[k-1][l];
			}
		}
		for(l=0;l<MAP_X;l++)
		{
			Map[k][l]=0;
		}

		
		if(ScoreData->lines%5==0)
		{
			ScoreData->Level++;
			PlayGameSound(GAME_LVUP);
		}
		prtScore(*ScoreData);

		Sleep(500);

		ClearCount++;
		i++;
	}
	return ClearCount;
}

void TurnBlock(int Map[MAP_Y][MAP_X], BLOCK *CurrBlock, BLOCK_MOVE BlockMove)
{
	BLOCK TempBlock=*CurrBlock;

	if(!(TempBlock.Type && TempBlock.State))
		return ;

	switch(BlockMove)
	{
	case TURN_RIGHT:
		TempBlock.State>BLOCK_FLIP?TempBlock.State=BLOCK_MAIN:TempBlock.State++;
		if(!isCollision(Map,&TempBlock,MOVE_NONE))
			CurrBlock->State=TempBlock.State;
		else if(!isCollision(Map,&TempBlock,MOVE_LEFT) && TempBlock.Type != BLOCK_G)
		{
			CurrBlock->State=TempBlock.State;
			CurrBlock->x--;
		}
		else if(TempBlock.Type == BLOCK_G)
		{
			if((TempBlock.State == BLOCK_RIGHT || TempBlock.State == BLOCK_LEFT))
			{
				if (++TempBlock.x<MAP_X && !isCollision(Map, &TempBlock, MOVE_NONE))
				{
					CurrBlock->State = TempBlock.State;
					CurrBlock->x++;
					break;
				}
				else if (++TempBlock.x<MAP_X && !isCollision(Map, &TempBlock, MOVE_NONE))
				{
					CurrBlock->State = TempBlock.State;
					CurrBlock->x+=2;
					break;
				}
				if (++TempBlock.x<MAP_X && !isCollision(Map, &TempBlock, MOVE_NONE))
				{
					CurrBlock->State = TempBlock.State;
					CurrBlock->x+=3;
					break;
				}
			}
			else if(TempBlock.State == BLOCK_MAIN || TempBlock.State == BLOCK_FLIP)
			{
				if(--TempBlock.x>0 && !isCollision(Map, &TempBlock, MOVE_NONE))
				{
					CurrBlock->State=TempBlock.State;
					CurrBlock->x--;
				}
				else if(--TempBlock.x>0 && !isCollision(Map,&TempBlock,MOVE_NONE))
				{
					CurrBlock->State=TempBlock.State;
					CurrBlock->x-=2;
				}
				else if(--TempBlock.x>0 && !isCollision(Map,&TempBlock,MOVE_NONE))
				{
					CurrBlock->State=TempBlock.State;
					CurrBlock->x-=3;
				}
			}
		}
		break;
	case TURN_LEFT:
		TempBlock.State<BLOCK_RIGHT?TempBlock.State=BLOCK_LEFT:TempBlock.State--;
		if(!isCollision(Map,&TempBlock,MOVE_NONE))
			CurrBlock->State=TempBlock.State;
		else if(!isCollision(Map,&TempBlock,MOVE_LEFT) && TempBlock.Type != BLOCK_G)
		{
			CurrBlock->State=TempBlock.State;
			CurrBlock->x--;
		}
		else if(TempBlock.Type == BLOCK_G)
		{
			if((TempBlock.State == BLOCK_RIGHT || TempBlock.State == BLOCK_LEFT))
			{
				if (++TempBlock.x<MAP_X && !isCollision(Map, &TempBlock, MOVE_NONE))
				{
					CurrBlock->State = TempBlock.State;
					CurrBlock->x++;
					break;
				}
				else if (++TempBlock.x<MAP_X && !isCollision(Map, &TempBlock, MOVE_NONE))
				{
					CurrBlock->State = TempBlock.State;
					CurrBlock->x+=2;
					break;
				}
				if (++TempBlock.x<MAP_X && !isCollision(Map, &TempBlock, MOVE_NONE))
				{
					CurrBlock->State = TempBlock.State;
					CurrBlock->x+=3;
					break;
				}
			}
			else if(TempBlock.State == BLOCK_MAIN || TempBlock.State == BLOCK_FLIP)
			{
				if(--TempBlock.x>0 && !isCollision(Map, &TempBlock, MOVE_NONE))
				{
					CurrBlock->State=TempBlock.State;
					CurrBlock->x--;
				}
				else if(--TempBlock.x>0 && !isCollision(Map,&TempBlock,MOVE_NONE))
				{
					CurrBlock->State=TempBlock.State;
					CurrBlock->x-=2;
				}
				else if(--TempBlock.x>0 && !isCollision(Map,&TempBlock,MOVE_NONE))
				{
					CurrBlock->State=TempBlock.State;
					CurrBlock->x-=3;
				}
			}
		}
		break;
	default:
		FatalError(ERROR_TURN_BLOCK);
		break;
	}
}

void FallBlock(int Map[MAP_Y][MAP_X], BLOCK *CurrBlock)
{
	BLOCK TempBlock=*CurrBlock;
	for ( ; TempBlock.y<MAP_Y ; TempBlock.y++)
	{
		if(isCollision(Map,&TempBlock,MOVE_DOWN))
		{
			CurrBlock->y=TempBlock.y;
			prtCurrBlock(CurrBlock);
			Sleep(100);
			break;
		}
		else if(!(TempBlock.y % 5))
		{
			prtCurrBlock(&TempBlock);
			Sleep(30);
		}
	}
}

void GetDropPos(int Map[MAP_Y][MAP_X], BLOCK *CurrBlock)
{
	BLOCK TempBlock=*CurrBlock;
	for ( ; TempBlock.y<MAP_Y ; TempBlock.y++)
	{
		if(isCollision(Map,&TempBlock,MOVE_DOWN))
		{
			CurrBlock->dropy=TempBlock.y;
			break;
		}
	}
}

void NewBlock(BLOCK *Block)
{
	Block->x=NEW_BLOCK_X;
	Block->y=NEW_BLOCK_Y;
	Block->State=BLOCK_MAIN;
#ifndef NORMAL_TETRIS
	Block->Type=rand()%(rand()%5<3?BLOCK_BOMB:BLOCK_G) + 1;
#else
	Block->Type=rand()%(rand()%3?BLOCK_BOMB:BLOCK_G) + 1;
#endif
	Block->Color=Block->Type +1;
}


void CreateNewBlock(BLOCK *CurrBlock, BLOCK *NextBlock, BLOCK *NNextBlock)
{
#ifndef NORMAL_TETRIS
	if(rand()%10)
	{
		*CurrBlock=*NextBlock;
		*NextBlock=*NNextBlock;
		NewBlock(NNextBlock);
	}
	else
	{
		NewBlock(CurrBlock);
		*NextBlock=*NNextBlock;
		NewBlock(NNextBlock);
	}
	if(rand()%10==0 && CurrBlock->Type == BLOCK_BOMB)
		NewBlock(CurrBlock);

#else
	BLOCK PrevBlock=*CurrBlock;
	*CurrBlock=*NextBlock;
	*NextBlock=*NNextBlock;
	NewBlock(NNextBlock);
	//4개 연속으로 같은블록이 나오는걸 방지하는 코드
	do
	{
		NewBlock(NNextBlock);
	}
	while (PrevBlock.Type == CurrBlock->Type && CurrBlock->Type == NextBlock->Type && CurrBlock->Type == NNextBlock->Type);


#endif
}

void prtxy(int x, int y, BLOCK_COLOR color)
{
	gotoxy(x,y);
	_prtBlock(color);
}

void prtMapxy(int x, int y, BLOCK_COLOR color)
{
	gotoMapxy(x,y);
	_prtBlock(color);
}


void _prtBlock(BLOCK_COLOR color)
{
	if(color)
	{
		SetColor(color+7,color-1);		//BLOCK_COLOR를 CON_COLOR로 변경
		_putwch(L'■');
		SetDefColor();
	}
	else
	{
		SetDefColor();
		_putwch(L' ');
		_putwch(L' ');
	}
}

void _prtDrpBlock(BLOCK_COLOR color)
{
	if(color)
	{
		SetColor(color-1,color-1);		//BLOCK_COLOR를 CON_COLOR로 변경
		_putwch(L'■');
		SetDefColor();
	}
	else
	{
		SetDefColor();
		_putwch(L' ');
		_putwch(L' ');
	}
}

void _prtBomb(void)
{
	SetDefColor();
	_putwch(L'♪');
}

void _prtDrpBomb(void)
{
	SetColor(CON_GRAY,CON_BLACK);
	_putwch(L'♪');
}



void _prtNBlock(BLOCK *PrevBlock, BLOCK *NextBlock)
{
	//이전 좌표 제거
	switch (PrevBlock->Type)
	{
	case BLOCK_A:
		gotoNextBlockxy(1, 0);
		_prtBlock(BLOCK_NULL);
		gotoNextBlockxy(1, 1);
		_prtBlock(BLOCK_NULL);
		_prtBlock(BLOCK_NULL);
		gotoNextBlockxy(2, 2);
		_prtBlock(BLOCK_NULL);
		break;
	case BLOCK_B:
		gotoNextBlockxy(2, 0);
		_prtBlock(BLOCK_NULL);
		gotoNextBlockxy(1, 1);
		_prtBlock(BLOCK_NULL);
		_prtBlock(BLOCK_NULL);
		gotoNextBlockxy(1, 2);
		_prtBlock(BLOCK_NULL);
		break;
	case BLOCK_C:
		gotoNextBlockxy(1, 0);
		_prtBlock(BLOCK_NULL);
		gotoNextBlockxy(1, 1);
		_prtBlock(BLOCK_NULL);
		_prtBlock(BLOCK_NULL);
		gotoNextBlockxy(1, 2);
		_prtBlock(BLOCK_NULL);
		break;
	case BLOCK_D:
		gotoNextBlockxy(1, 0);
		_prtBlock(BLOCK_NULL);
		gotoNextBlockxy(1, 1);
		_prtBlock(BLOCK_NULL);
		gotoNextBlockxy(1, 2);
		_prtBlock(BLOCK_NULL);
		_prtBlock(BLOCK_NULL);
		break;
	case BLOCK_E:
		gotoNextBlockxy(1, 0);
		_prtBlock(BLOCK_NULL);
		_prtBlock(BLOCK_NULL);
		gotoNextBlockxy(1, 1);
		_prtBlock(BLOCK_NULL);
		gotoNextBlockxy(1, 2);
		_prtBlock(BLOCK_NULL);
		break;
	case BLOCK_F:
		gotoNextBlockxy(1, 1);
		_prtBlock(BLOCK_NULL);
		_prtBlock(BLOCK_NULL);
		gotoNextBlockxy(1, 2);
		_prtBlock(BLOCK_NULL);
		_prtBlock(BLOCK_NULL);
		break;
	case BLOCK_G:
		gotoNextBlockxy(0, 1);
		_prtBlock(BLOCK_NULL);
		_prtBlock(BLOCK_NULL);
		_prtBlock(BLOCK_NULL);
		_prtBlock(BLOCK_NULL);
		break;
	case BLOCK_BOMB:
		gotoNextBlockxy(0, 1);
		_putwch(L' ');
		_prtBlock(BLOCK_NULL);
		_prtBlock(BLOCK_NULL);
		break;
	}

	//새로운 블럭 출력
	switch (NextBlock->Type)
	{
	case BLOCK_A:
		gotoNextBlockxy(1, 0);
		_prtBlock(NextBlock->Color);
		gotoNextBlockxy(1, 1);
		_prtBlock(NextBlock->Color);
		_prtBlock(NextBlock->Color);
		gotoNextBlockxy(2, 2);
		_prtBlock(NextBlock->Color);
		break;
	case BLOCK_B:
		gotoNextBlockxy(2, 0);
		_prtBlock(NextBlock->Color);
		gotoNextBlockxy(1, 1);
		_prtBlock(NextBlock->Color);
		_prtBlock(NextBlock->Color);
		gotoNextBlockxy(1, 2);
		_prtBlock(NextBlock->Color);
		break;
	case BLOCK_C:
		gotoNextBlockxy(1, 0);
		_prtBlock(NextBlock->Color);
		gotoNextBlockxy(1, 1);
		_prtBlock(NextBlock->Color);
		_prtBlock(NextBlock->Color);
		gotoNextBlockxy(1, 2);
		_prtBlock(NextBlock->Color);
		break;
	case BLOCK_D:
		gotoNextBlockxy(1, 0);
		_prtBlock(NextBlock->Color);
		gotoNextBlockxy(1, 1);
		_prtBlock(NextBlock->Color);
		gotoNextBlockxy(1, 2);
		_prtBlock(NextBlock->Color);
		_prtBlock(NextBlock->Color);
		break;
	case BLOCK_E:
		gotoNextBlockxy(1, 0);
		_prtBlock(NextBlock->Color);
		_prtBlock(NextBlock->Color);
		gotoNextBlockxy(1, 1);
		_prtBlock(NextBlock->Color);
		gotoNextBlockxy(1, 2);
		_prtBlock(NextBlock->Color);
		break;
	case BLOCK_F:
		gotoNextBlockxy(1, 1);
		_prtBlock(NextBlock->Color);
		_prtBlock(NextBlock->Color);
		gotoNextBlockxy(1, 2);
		_prtBlock(NextBlock->Color);
		_prtBlock(NextBlock->Color);
		break;
	case BLOCK_G:
		gotoNextBlockxy(0, 1);
		_prtBlock(NextBlock->Color);
		_prtBlock(NextBlock->Color);
		_prtBlock(NextBlock->Color);
		_prtBlock(NextBlock->Color);
		break;
	case BLOCK_BOMB:
		gotoNextBlockxy(1, 1);
		_putwch(L' ');
		_prtBomb();
		break;
	}
}

void _prtNNBlock(BLOCK *PrevBlock, BLOCK *NextBlock)
{
	//이전 좌표 제거
	switch (PrevBlock->Type)
	{
	case BLOCK_A:
		gotoNNextBlockxy(1, 0);
		_prtBlock(BLOCK_NULL);
		gotoNNextBlockxy(1, 1);
		_prtBlock(BLOCK_NULL);
		_prtBlock(BLOCK_NULL);
		gotoNNextBlockxy(2, 2);
		_prtBlock(BLOCK_NULL);
		break;
	case BLOCK_B:
		gotoNNextBlockxy(2, 0);
		_prtBlock(BLOCK_NULL);
		gotoNNextBlockxy(1, 1);
		_prtBlock(BLOCK_NULL);
		_prtBlock(BLOCK_NULL);
		gotoNNextBlockxy(1, 2);
		_prtBlock(BLOCK_NULL);
		break;
	case BLOCK_C:
		gotoNNextBlockxy(1, 0);
		_prtBlock(BLOCK_NULL);
		gotoNNextBlockxy(1, 1);
		_prtBlock(BLOCK_NULL);
		_prtBlock(BLOCK_NULL);
		gotoNNextBlockxy(1, 2);
		_prtBlock(BLOCK_NULL);
		break;
	case BLOCK_D:
		gotoNNextBlockxy(1, 0);
		_prtBlock(BLOCK_NULL);
		gotoNNextBlockxy(1, 1);
		_prtBlock(BLOCK_NULL);
		gotoNNextBlockxy(1, 2);
		_prtBlock(BLOCK_NULL);
		_prtBlock(BLOCK_NULL);
		break;
	case BLOCK_E:
		gotoNNextBlockxy(1, 0);
		_prtBlock(BLOCK_NULL);
		_prtBlock(BLOCK_NULL);
		gotoNNextBlockxy(1, 1);
		_prtBlock(BLOCK_NULL);
		gotoNNextBlockxy(1, 2);
		_prtBlock(BLOCK_NULL);
		break;
	case BLOCK_F:
		gotoNNextBlockxy(1, 1);
		_prtBlock(BLOCK_NULL);
		_prtBlock(BLOCK_NULL);
		gotoNNextBlockxy(1, 2);
		_prtBlock(BLOCK_NULL);
		_prtBlock(BLOCK_NULL);
		break;
	case BLOCK_G:
		gotoNNextBlockxy(0, 1);
		_prtBlock(BLOCK_NULL);
		_prtBlock(BLOCK_NULL);
		_prtBlock(BLOCK_NULL);
		_prtBlock(BLOCK_NULL);
		break;
	case BLOCK_BOMB:
		gotoNNextBlockxy(1, 1);
		_putwch(L' ');
		_prtBlock(BLOCK_NULL);
		break;
	}

	//새로운 블럭 출력
	switch (NextBlock->Type)
	{
	case BLOCK_A:
		gotoNNextBlockxy(1, 0);
		_prtBlock(NextBlock->Color);
		gotoNNextBlockxy(1, 1);
		_prtBlock(NextBlock->Color);
		_prtBlock(NextBlock->Color);
		gotoNNextBlockxy(2, 2);
		_prtBlock(NextBlock->Color);
		break;
	case BLOCK_B:
		gotoNNextBlockxy(2, 0);
		_prtBlock(NextBlock->Color);
		gotoNNextBlockxy(1, 1);
		_prtBlock(NextBlock->Color);
		_prtBlock(NextBlock->Color);
		gotoNNextBlockxy(1, 2);
		_prtBlock(NextBlock->Color);
		break;
	case BLOCK_C:
		gotoNNextBlockxy(1, 0);
		_prtBlock(NextBlock->Color);
		gotoNNextBlockxy(1, 1);
		_prtBlock(NextBlock->Color);
		_prtBlock(NextBlock->Color);
		gotoNNextBlockxy(1, 2);
		_prtBlock(NextBlock->Color);
		break;
	case BLOCK_D:
		gotoNNextBlockxy(1, 0);
		_prtBlock(NextBlock->Color);
		gotoNNextBlockxy(1, 1);
		_prtBlock(NextBlock->Color);
		gotoNNextBlockxy(1, 2);
		_prtBlock(NextBlock->Color);
		_prtBlock(NextBlock->Color);
		break;
	case BLOCK_E:
		gotoNNextBlockxy(1, 0);
		_prtBlock(NextBlock->Color);
		_prtBlock(NextBlock->Color);
		gotoNNextBlockxy(1, 1);
		_prtBlock(NextBlock->Color);
		gotoNNextBlockxy(1, 2);
		_prtBlock(NextBlock->Color);
		break;
	case BLOCK_F:
		gotoNNextBlockxy(1, 1);
		_prtBlock(NextBlock->Color);
		_prtBlock(NextBlock->Color);
		gotoNNextBlockxy(1, 2);
		_prtBlock(NextBlock->Color);
		_prtBlock(NextBlock->Color);
		break;
	case BLOCK_G:
		gotoNNextBlockxy(0, 1);
		_prtBlock(NextBlock->Color);
		_prtBlock(NextBlock->Color);
		_prtBlock(NextBlock->Color);
		_prtBlock(NextBlock->Color);
		break;
	case BLOCK_BOMB:
		gotoNNextBlockxy(1, 1);
		_putwch(L' ');
		_prtBomb();
		break;
	}
}

void prtDropBlock(BLOCK *CurrBlock)
{
	static BLOCK PrevBlock = { 0, };

	if (CurrBlock->dropy > CurrBlock->y + 3 || PrevBlock.dropy != CurrBlock->dropy /*PrevBlock.State != CurrBlock->State || PrevBlock.dropy != CurrBlock->dropy || PrevBlock.Type != CurrBlock->Type || PrevBlock.Color != CurrBlock->Color */)
	{
		//이전 좌표 제거
		switch (PrevBlock.Type)
		{
		case BLOCK_NONE:
			break;
		case BLOCK_A:
			switch (PrevBlock.State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
			case BLOCK_FLIP:
				gotoMapxy(PrevBlock.x, PrevBlock.dropy);
				_prtDrpBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.dropy + 1);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x + 1, PrevBlock.dropy + 2);
				_prtDrpBlock(BLOCK_NULL);
				break;
			case BLOCK_RIGHT:
			case BLOCK_LEFT:
				gotoMapxy(PrevBlock.x + 1, PrevBlock.dropy);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.dropy + 1);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				break;
			}
			break;
		case BLOCK_B:
			switch (PrevBlock.State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
			case BLOCK_FLIP:
				gotoMapxy(PrevBlock.x + 1, PrevBlock.dropy);
				_prtDrpBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.dropy + 1);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.dropy + 2);
				_prtDrpBlock(BLOCK_NULL);
				break;
			case BLOCK_RIGHT:
			case BLOCK_LEFT:
				gotoMapxy(PrevBlock.x, PrevBlock.dropy);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x + 1, PrevBlock.dropy + 1);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				break;
			}
			break;
		case BLOCK_C:
			switch (PrevBlock.State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
				gotoMapxy(PrevBlock.x, PrevBlock.dropy);
				_prtDrpBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.dropy + 1);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.dropy + 2);
				_prtDrpBlock(BLOCK_NULL);
				break;
			case BLOCK_RIGHT:
				gotoMapxy(PrevBlock.x, PrevBlock.dropy);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x + 1, PrevBlock.dropy + 1);
				_prtDrpBlock(BLOCK_NULL);
				break;
			case BLOCK_LEFT:
				gotoMapxy(PrevBlock.x + 1, PrevBlock.dropy);
				_prtDrpBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.dropy + 1);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				break;
			case BLOCK_FLIP:
				gotoMapxy(PrevBlock.x + 1, PrevBlock.dropy);
				_prtDrpBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.dropy + 1);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x + 1, PrevBlock.dropy + 2);
				_prtDrpBlock(BLOCK_NULL);
				break;
			}
			break;
		case BLOCK_D:
			switch (PrevBlock.State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
				gotoMapxy(PrevBlock.x, PrevBlock.dropy);
				_prtDrpBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.dropy + 1);
				_prtDrpBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.dropy + 2);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				break;
			case BLOCK_RIGHT:
				gotoMapxy(PrevBlock.x, PrevBlock.dropy);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.dropy + 1);
				_prtDrpBlock(BLOCK_NULL);
				break;
			case BLOCK_LEFT:
				gotoMapxy(PrevBlock.x + 2, PrevBlock.dropy);
				_prtDrpBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.dropy + 1);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				break;
			case BLOCK_FLIP:
				gotoMapxy(PrevBlock.x, PrevBlock.dropy);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x + 1, PrevBlock.dropy + 1);
				_prtDrpBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x + 1, PrevBlock.dropy + 2);
				_prtDrpBlock(BLOCK_NULL);
				break;
			}
			break;
		case BLOCK_E:
			switch (PrevBlock.State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
				gotoMapxy(PrevBlock.x, PrevBlock.dropy);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.dropy + 1);
				_prtDrpBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.dropy + 2);
				_prtDrpBlock(BLOCK_NULL);
				break;
			case BLOCK_RIGHT:
				gotoMapxy(PrevBlock.x, PrevBlock.dropy);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x + 2, PrevBlock.dropy + 1);
				_prtDrpBlock(BLOCK_NULL);
				break;
			case BLOCK_LEFT:
				gotoMapxy(PrevBlock.x, PrevBlock.dropy);
				_prtDrpBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.dropy + 1);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				break;
			case BLOCK_FLIP:
				gotoMapxy(PrevBlock.x + 1, PrevBlock.dropy);
				_prtDrpBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x + 1, PrevBlock.dropy + 1);
				_prtDrpBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.dropy + 2);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				break;
			}
			break;
		case BLOCK_F:
			switch (PrevBlock.State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
			case BLOCK_RIGHT:
			case BLOCK_LEFT:
			case BLOCK_FLIP:
				gotoMapxy(PrevBlock.x, PrevBlock.dropy);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.dropy + 1);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				break;
			}
			break;
		case BLOCK_G:
			switch (PrevBlock.State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
			case BLOCK_FLIP:
				gotoMapxy(PrevBlock.x, PrevBlock.dropy);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				_prtDrpBlock(BLOCK_NULL);
				break;
			case BLOCK_RIGHT:
			case BLOCK_LEFT:
				gotoMapxy(PrevBlock.x, PrevBlock.dropy);
				_prtDrpBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.dropy + 1);
				_prtDrpBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.dropy + 2);
				_prtDrpBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.dropy + 3);
				_prtDrpBlock(BLOCK_NULL);
				break;
			}
			break;
		case BLOCK_BOMB:
			switch (PrevBlock.State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
			case BLOCK_RIGHT:
			case BLOCK_LEFT:
			case BLOCK_FLIP:
				gotoMapxy(PrevBlock.x, PrevBlock.dropy);
				_prtDrpBlock(BLOCK_NULL);
				break;
			}
			break;
		default:
			FatalError(ERROR_BLOCK_PRT);
		}

		//새로운 블럭 출력
		if(CurrBlock->dropy > CurrBlock->y + 4)
		switch (CurrBlock->Type)
		{
		case BLOCK_NONE:
			break;
		case BLOCK_A:
			switch (CurrBlock->State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
			case BLOCK_FLIP:
				gotoMapxy(CurrBlock->x, CurrBlock->dropy);
				_prtDrpBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->dropy + 1);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x + 1, CurrBlock->dropy + 2);
				_prtDrpBlock(CurrBlock->Color);
				break;
			case BLOCK_RIGHT:
			case BLOCK_LEFT:
				gotoMapxy(CurrBlock->x + 1, CurrBlock->dropy);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->dropy + 1);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				break;
			}
			break;
		case BLOCK_B:
			switch (CurrBlock->State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
			case BLOCK_FLIP:
				gotoMapxy(CurrBlock->x + 1, CurrBlock->dropy);
				_prtDrpBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->dropy + 1);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->dropy + 2);
				_prtDrpBlock(CurrBlock->Color);
				break;
			case BLOCK_RIGHT:
			case BLOCK_LEFT:
				gotoMapxy(CurrBlock->x, CurrBlock->dropy);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x + 1, CurrBlock->dropy + 1);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				break;
			}
			break;
		case BLOCK_C:
			switch (CurrBlock->State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
				gotoMapxy(CurrBlock->x, CurrBlock->dropy);
				_prtDrpBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->dropy + 1);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->dropy + 2);
				_prtDrpBlock(CurrBlock->Color);
				break;
			case BLOCK_RIGHT:
				gotoMapxy(CurrBlock->x, CurrBlock->dropy);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x + 1, CurrBlock->dropy + 1);
				_prtDrpBlock(CurrBlock->Color);
				break;
			case BLOCK_LEFT:
				gotoMapxy(CurrBlock->x + 1, CurrBlock->dropy);
				_prtDrpBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->dropy + 1);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				break;
			case BLOCK_FLIP:
				gotoMapxy(CurrBlock->x + 1, CurrBlock->dropy);
				_prtDrpBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->dropy + 1);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x + 1, CurrBlock->dropy + 2);
				_prtDrpBlock(CurrBlock->Color);
				break;
			}
			break;
		case BLOCK_D:
			switch (CurrBlock->State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
				gotoMapxy(CurrBlock->x, CurrBlock->dropy);
				_prtDrpBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->dropy + 1);
				_prtDrpBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->dropy + 2);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				break;
			case BLOCK_RIGHT:
				gotoMapxy(CurrBlock->x, CurrBlock->dropy);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->dropy + 1);
				_prtDrpBlock(CurrBlock->Color);
				break;
			case BLOCK_LEFT:
				gotoMapxy(CurrBlock->x + 2, CurrBlock->dropy);
				_prtDrpBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->dropy + 1);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				break;
			case BLOCK_FLIP:
				gotoMapxy(CurrBlock->x, CurrBlock->dropy);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x + 1, CurrBlock->dropy + 1);
				_prtDrpBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x + 1, CurrBlock->dropy + 2);
				_prtDrpBlock(CurrBlock->Color);
				break;
			}
			break;
		case BLOCK_E:
			switch (CurrBlock->State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
				gotoMapxy(CurrBlock->x, CurrBlock->dropy);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->dropy + 1);
				_prtDrpBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->dropy + 2);
				_prtDrpBlock(CurrBlock->Color);
				break;
			case BLOCK_RIGHT:
				gotoMapxy(CurrBlock->x, CurrBlock->dropy);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x + 2, CurrBlock->dropy + 1);
				_prtDrpBlock(CurrBlock->Color);
				break;
			case BLOCK_LEFT:
				gotoMapxy(CurrBlock->x, CurrBlock->dropy);
				_prtDrpBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->dropy + 1);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				break;
			case BLOCK_FLIP:
				gotoMapxy(CurrBlock->x + 1, CurrBlock->dropy);
				_prtDrpBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x + 1, CurrBlock->dropy + 1);
				_prtDrpBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->dropy + 2);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				break;
			}
			break;
		case BLOCK_F:
			switch (CurrBlock->State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
			case BLOCK_RIGHT:
			case BLOCK_LEFT:
			case BLOCK_FLIP:
				gotoMapxy(CurrBlock->x, CurrBlock->dropy);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->dropy + 1);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				break;
			}
			break;
		case BLOCK_G:
			switch (CurrBlock->State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
			case BLOCK_FLIP:
				gotoMapxy(CurrBlock->x, CurrBlock->dropy);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				_prtDrpBlock(CurrBlock->Color);
				break;
			case BLOCK_RIGHT:
			case BLOCK_LEFT:
				gotoMapxy(CurrBlock->x, CurrBlock->dropy);
				_prtDrpBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->dropy + 1);
				_prtDrpBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->dropy + 2);
				_prtDrpBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->dropy + 3);
				_prtDrpBlock(CurrBlock->Color);
				break;
			}
			break;
		case BLOCK_BOMB:
			switch (CurrBlock->State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
			case BLOCK_RIGHT:
			case BLOCK_LEFT:
			case BLOCK_FLIP:
				gotoMapxy(CurrBlock->x, CurrBlock->dropy);
				_prtDrpBomb();
				break;
			}
			break;
		default:
			FatalError(ERROR_BLOCK_PRT);
		}

		PrevBlock.x = CurrBlock->x;
		PrevBlock.dropy = CurrBlock->dropy;
		PrevBlock.Type = CurrBlock->Type;
		PrevBlock.Color = CurrBlock->Color;
		PrevBlock.State = CurrBlock->State;
	}
	else
		return;
}

void prtCurrBlock(BLOCK *CurrBlock)
{
	static BLOCK PrevBlock = { 0, };

	if (PrevBlock.State != CurrBlock->State || PrevBlock.x != CurrBlock->x || PrevBlock.y != CurrBlock->y || PrevBlock.Type != CurrBlock->Type || PrevBlock.Color != CurrBlock->Color )
	{
		//이전 좌표 제거
		switch (PrevBlock.Type)
		{
		case BLOCK_NONE:
			break;
		case BLOCK_A:
			switch (PrevBlock.State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
			case BLOCK_FLIP:
				gotoMapxy(PrevBlock.x, PrevBlock.y);
				_prtBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.y + 1);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x + 1, PrevBlock.y + 2);
				_prtBlock(BLOCK_NULL);
				break;
			case BLOCK_RIGHT:
			case BLOCK_LEFT:
				gotoMapxy(PrevBlock.x + 1, PrevBlock.y);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.y + 1);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				break;
			}
			break;
		case BLOCK_B:
			switch (PrevBlock.State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
			case BLOCK_FLIP:
				gotoMapxy(PrevBlock.x + 1, PrevBlock.y);
				_prtBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.y + 1);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.y + 2);
				_prtBlock(BLOCK_NULL);
				break;
			case BLOCK_RIGHT:
			case BLOCK_LEFT:
				gotoMapxy(PrevBlock.x, PrevBlock.y);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x + 1, PrevBlock.y + 1);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				break;
			}
			break;
		case BLOCK_C:
			switch (PrevBlock.State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
				gotoMapxy(PrevBlock.x, PrevBlock.y);
				_prtBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.y + 1);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.y + 2);
				_prtBlock(BLOCK_NULL);
				break;
			case BLOCK_RIGHT:
				gotoMapxy(PrevBlock.x, PrevBlock.y);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x + 1, PrevBlock.y + 1);
				_prtBlock(BLOCK_NULL);
				break;
			case BLOCK_LEFT:
				gotoMapxy(PrevBlock.x + 1, PrevBlock.y);
				_prtBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.y + 1);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				break;
			case BLOCK_FLIP:
				gotoMapxy(PrevBlock.x + 1, PrevBlock.y);
				_prtBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.y + 1);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x + 1, PrevBlock.y + 2);
				_prtBlock(BLOCK_NULL);
				break;
			}
			break;
		case BLOCK_D:
			switch (PrevBlock.State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
				gotoMapxy(PrevBlock.x, PrevBlock.y);
				_prtBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.y + 1);
				_prtBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.y + 2);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				break;
			case BLOCK_RIGHT:
				gotoMapxy(PrevBlock.x, PrevBlock.y);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.y + 1);
				_prtBlock(BLOCK_NULL);
				break;
			case BLOCK_LEFT:
				gotoMapxy(PrevBlock.x + 2, PrevBlock.y);
				_prtBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.y + 1);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				break;
			case BLOCK_FLIP:
				gotoMapxy(PrevBlock.x, PrevBlock.y);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x + 1, PrevBlock.y + 1);
				_prtBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x + 1, PrevBlock.y + 2);
				_prtBlock(BLOCK_NULL);
				break;
			}
			break;
		case BLOCK_E:
			switch (PrevBlock.State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
				gotoMapxy(PrevBlock.x, PrevBlock.y);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.y + 1);
				_prtBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.y + 2);
				_prtBlock(BLOCK_NULL);
				break;
			case BLOCK_RIGHT:
				gotoMapxy(PrevBlock.x, PrevBlock.y);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x + 2, PrevBlock.y + 1);
				_prtBlock(BLOCK_NULL);
				break;
			case BLOCK_LEFT:
				gotoMapxy(PrevBlock.x, PrevBlock.y);
				_prtBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.y + 1);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				break;
			case BLOCK_FLIP:
				gotoMapxy(PrevBlock.x + 1, PrevBlock.y);
				_prtBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x + 1, PrevBlock.y + 1);
				_prtBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.y + 2);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				break;
			}
			break;
		case BLOCK_F:
			switch (PrevBlock.State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
			case BLOCK_RIGHT:
			case BLOCK_LEFT:
			case BLOCK_FLIP:
				gotoMapxy(PrevBlock.x, PrevBlock.y);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.y + 1);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				break;
			}
			break;
		case BLOCK_G:
			switch (PrevBlock.State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
			case BLOCK_FLIP:
				gotoMapxy(PrevBlock.x, PrevBlock.y);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				_prtBlock(BLOCK_NULL);
				break;
			case BLOCK_RIGHT:
			case BLOCK_LEFT:
				gotoMapxy(PrevBlock.x, PrevBlock.y);
				_prtBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.y + 1);
				_prtBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.y + 2);
				_prtBlock(BLOCK_NULL);
				gotoMapxy(PrevBlock.x, PrevBlock.y + 3);
				_prtBlock(BLOCK_NULL);
				break;
			}
			break;
		case BLOCK_BOMB:
			switch (PrevBlock.State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
			case BLOCK_RIGHT:
			case BLOCK_LEFT:
			case BLOCK_FLIP:
				gotoMapxy(PrevBlock.x, PrevBlock.y);
				_prtBlock(BLOCK_NULL);
				break;
			}
			break;
		default:
			FatalError(ERROR_BLOCK_PRT);
		}

		prtDropBlock(CurrBlock);

		//새로운 블럭 출력
		switch (CurrBlock->Type)
		{
		case BLOCK_NONE:
			break;
		case BLOCK_A:
			switch (CurrBlock->State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
			case BLOCK_FLIP:
				gotoMapxy(CurrBlock->x, CurrBlock->y);
				_prtBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->y + 1);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x + 1, CurrBlock->y + 2);
				_prtBlock(CurrBlock->Color);
				break;
			case BLOCK_RIGHT:
			case BLOCK_LEFT:
				gotoMapxy(CurrBlock->x + 1, CurrBlock->y);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->y + 1);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				break;
			}
			break;
		case BLOCK_B:
			switch (CurrBlock->State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
			case BLOCK_FLIP:
				gotoMapxy(CurrBlock->x + 1, CurrBlock->y);
				_prtBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->y + 1);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->y + 2);
				_prtBlock(CurrBlock->Color);
				break;
			case BLOCK_RIGHT:
			case BLOCK_LEFT:
				gotoMapxy(CurrBlock->x, CurrBlock->y);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x + 1, CurrBlock->y + 1);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				break;
			}
			break;
		case BLOCK_C:
			switch (CurrBlock->State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
				gotoMapxy(CurrBlock->x, CurrBlock->y);
				_prtBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->y + 1);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->y + 2);
				_prtBlock(CurrBlock->Color);
				break;
			case BLOCK_RIGHT:
				gotoMapxy(CurrBlock->x, CurrBlock->y);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x + 1, CurrBlock->y + 1);
				_prtBlock(CurrBlock->Color);
				break;
			case BLOCK_LEFT:
				gotoMapxy(CurrBlock->x + 1, CurrBlock->y);
				_prtBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->y + 1);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				break;
			case BLOCK_FLIP:
				gotoMapxy(CurrBlock->x + 1, CurrBlock->y);
				_prtBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->y + 1);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x + 1, CurrBlock->y + 2);
				_prtBlock(CurrBlock->Color);
				break;
			}
			break;
		case BLOCK_D:
			switch (CurrBlock->State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
				gotoMapxy(CurrBlock->x, CurrBlock->y);
				_prtBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->y + 1);
				_prtBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->y + 2);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				break;
			case BLOCK_RIGHT:
				gotoMapxy(CurrBlock->x, CurrBlock->y);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->y + 1);
				_prtBlock(CurrBlock->Color);
				break;
			case BLOCK_LEFT:
				gotoMapxy(CurrBlock->x + 2, CurrBlock->y);
				_prtBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->y + 1);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				break;
			case BLOCK_FLIP:
				gotoMapxy(CurrBlock->x, CurrBlock->y);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x + 1, CurrBlock->y + 1);
				_prtBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x + 1, CurrBlock->y + 2);
				_prtBlock(CurrBlock->Color);
				break;
			}
			break;
		case BLOCK_E:
			switch (CurrBlock->State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
				gotoMapxy(CurrBlock->x, CurrBlock->y);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->y + 1);
				_prtBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->y + 2);
				_prtBlock(CurrBlock->Color);
				break;
			case BLOCK_RIGHT:
				gotoMapxy(CurrBlock->x, CurrBlock->y);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x + 2, CurrBlock->y + 1);
				_prtBlock(CurrBlock->Color);
				break;
			case BLOCK_LEFT:
				gotoMapxy(CurrBlock->x, CurrBlock->y);
				_prtBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->y + 1);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				break;
			case BLOCK_FLIP:
				gotoMapxy(CurrBlock->x + 1, CurrBlock->y);
				_prtBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x + 1, CurrBlock->y + 1);
				_prtBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->y + 2);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				break;
			}
			break;
		case BLOCK_F:
			switch (CurrBlock->State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
			case BLOCK_RIGHT:
			case BLOCK_LEFT:
			case BLOCK_FLIP:
				gotoMapxy(CurrBlock->x, CurrBlock->y);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->y + 1);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				break;
			}
			break;
		case BLOCK_G:
			switch (CurrBlock->State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
			case BLOCK_FLIP:
				gotoMapxy(CurrBlock->x, CurrBlock->y);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				_prtBlock(CurrBlock->Color);
				break;
			case BLOCK_RIGHT:
			case BLOCK_LEFT:
				gotoMapxy(CurrBlock->x, CurrBlock->y);
				_prtBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->y + 1);
				_prtBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->y + 2);
				_prtBlock(CurrBlock->Color);
				gotoMapxy(CurrBlock->x, CurrBlock->y + 3);
				_prtBlock(CurrBlock->Color);
				break;
			}
			break;
		case BLOCK_BOMB:
			switch (CurrBlock->State)
			{
			case BLOCK_FIXED:
				break;
			case BLOCK_MAIN:
			case BLOCK_RIGHT:
			case BLOCK_LEFT:
			case BLOCK_FLIP:
				gotoMapxy(CurrBlock->x, CurrBlock->y);
				_prtBomb();
				break;
			}
			break;
		default:
			FatalError(ERROR_BLOCK_PRT);
		}

		PrevBlock.x = CurrBlock->x;
		PrevBlock.y = CurrBlock->y;
		PrevBlock.Type = CurrBlock->Type;
		PrevBlock.Color = CurrBlock->Color;
		PrevBlock.State = CurrBlock->State;
	}
	else
		return;
}

void prtNextBlocks(BLOCK *NextBlock, BLOCK *NNextBlock)
{
	static BLOCK PrevNextBlock={0,},PrevNNextBlock={0,};
	
	if(PrevNextBlock.Type != NextBlock->Type || PrevNextBlock.Color != NextBlock->Color)
	{
		_prtNBlock(&PrevNextBlock,NextBlock);
		PrevNextBlock.Type = NextBlock->Type;
		PrevNextBlock.Color = NextBlock->Color;
	}
	if(PrevNNextBlock.Type != NNextBlock->Type || PrevNNextBlock.Color != NNextBlock->Color)
	{
		_prtNNBlock(&PrevNNextBlock,NNextBlock);
		PrevNNextBlock.Type = NNextBlock->Type;
		PrevNNextBlock.Color = NNextBlock->Color;
	}
}

void reprtMap(int Map[MAP_Y][MAP_X])
{
	gotoMapxy(3, 10);
	wprintf(L"           ");
	int i=0,j=0;
	for (i=0;i<MAP_Y;i++)
	{
		for (j=0;j<MAP_X;j++)
		{
			PrevMap[i][j] = BLOCK_NULL;
		}
	}
	prtMap(Map);
	gotoxy(4, 25);
	wprintf(L"                            ");
	gotoxy(4, 26);
	wprintf(L"                          ");
}

void prtMap(int Map[MAP_Y][MAP_X])
{
	int i=0,j=0;
	for (i=0;i<MAP_Y;i++)
	{
		for (j=0;j<MAP_X;j++)
		{
			if(PrevMap[i][j] != Map[i][j])
			{
				PrevMap[i][j] = Map[i][j];
				prtMapxy(j,i,Map[i][j]);
			}
		}
	}
}

void updMap(int Map[MAP_Y][MAP_X])
{
	int i=0,j=0;
	for (i=0;i<MAP_Y;i++)
	{
		for (j=0;j<MAP_X;j++)
		{
			if(PrevMap[i][j] != Map[i][j])
			{
				PrevMap[i][j] = Map[i][j];
			}
		}
	}
}

void prtFinMap(int Map[MAP_Y][MAP_X])
{
	int i=0,j=0;
	for (i=0;i<MAP_Y;i++)
	{
		for (j=0;j<MAP_X;j++)
		{
			if(Map[i][j])
				prtMapxy(j,i,BLOCK_BLACK);
		}
	}
	gotoMapxy(4, 10);
	wprintf(L"GameOver");
	gotoxy(4, 26);
	wprintf(L"Press Enter to Continue...");
}

void prtPusMap(int Map[MAP_Y][MAP_X], BLOCK *CurrBlock)
{
	BLOCK TmpBlock=*CurrBlock;
	int i=0,j=0;
	for (i=0;i<MAP_Y;i++)
	{
		for (j=0;j<MAP_X;j++)
		{
			if(Map[i][j])
				prtMapxy(j,i,BLOCK_BLACK);
		}
	}
	TmpBlock.Color=BLOCK_BLACK;
	prtCurrBlock(&TmpBlock);
	gotoMapxy(3, 10);
	wprintf(L"Game Paused");
	gotoxy(4, 25);
	wprintf(L"Press ESC to Back to Menu...");
	gotoxy(4, 26);
	wprintf(L"Press Enter to Continue...");
}

void prtScore(SCOREDATA ScoreData)
{
	int key[4]={1,5,7,24};
	//Level
	gotoxy(LEVEL_POS_X, LEVEL_POS_Y);
	wprintf(L"%d", ScoreData.Level);

	//LINE
	gotoxy(LINE_POS_X, LINE_POS_Y);
	wprintf(L"%d", ScoreData.lines);

	//SCORE
	gotoxy(SCORE_POS_X, SCORE_POS_Y);
	wprintf(L"%d", ScoreData.score);

	//BEST
	gotoxy(BEST_POS_X, BEST_POS_Y);
	wprintf(L"%d", ScoreData.best);
}

void prtgameform(void)
{
	wprintf(L"\n [F5] Music Skip [F6] Album [F7/F8] Volume Down/Up [F9] S/E\n\n\
    ┌-------------------------┐       ┌-------------┐\n\
    │                         │       │             │\n\
    │                         │       │             │\n\
    │                         │       │             │\n\
    │                         │       │             │\n\
    │                         │       │             │\n\
    │                         │       └-------------┘\n\
    │                         │\n\
    │                         │         ┌---------┐\n\
    │                         │         │         │\n\
    │                         │         │         │\n\
    │                         │         │         │\n\
    │                         │         └---------┘\n\
    │                         │\n\
    │                         │\n\
    │                         │\n\
    │                         │    Level : \n\
    │                         │    Lines : \n\
    │                         │\n\
    │                         │    Score : \n\
    │                         │    Local Best : \n\
    └-------------------------┘\n");
	
}


void AppendMap(int Map[MAP_Y][MAP_X], BLOCK *CurrBlock)
{
	int i=0;
	int m1=0, m2=0, m3=0;
	BOOL Changed=FALSE;
	switch (CurrBlock->Type)
	{
	case BLOCK_NONE:
		break;
	case BLOCK_A:
		switch (CurrBlock->State)
		{
		case BLOCK_FIXED:
			break;
		case BLOCK_MAIN:
		case BLOCK_FLIP:
			Map[CurrBlock->y][CurrBlock->x] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x + 1] = CurrBlock->Color;
			Map[CurrBlock->y + 2][CurrBlock->x + 1] = CurrBlock->Color;
			break;
		case BLOCK_RIGHT:
		case BLOCK_LEFT:
			Map[CurrBlock->y][CurrBlock->x + 1] = CurrBlock->Color;
			Map[CurrBlock->y][CurrBlock->x + 2] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x + 1] = CurrBlock->Color;
			break;
		}
		break;
	case BLOCK_B:
		switch (CurrBlock->State)
		{
		case BLOCK_FIXED:
			break;
		case BLOCK_MAIN:
		case BLOCK_FLIP:
			Map[CurrBlock->y][CurrBlock->x + 1] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x + 1] = CurrBlock->Color;
			Map[CurrBlock->y + 2][CurrBlock->x] = CurrBlock->Color;
			break;
		case BLOCK_RIGHT:
		case BLOCK_LEFT:
			Map[CurrBlock->y][CurrBlock->x] = CurrBlock->Color;
			Map[CurrBlock->y][CurrBlock->x + 1] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x + 1] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x + 2] = CurrBlock->Color;
			break;
		}
		break;
	case BLOCK_C:
		switch (CurrBlock->State)
		{
		case BLOCK_FIXED:
			break;
		case BLOCK_MAIN:
			Map[CurrBlock->y][CurrBlock->x] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x + 1] = CurrBlock->Color;
			Map[CurrBlock->y + 2][CurrBlock->x] = CurrBlock->Color;
			break;
		case BLOCK_RIGHT:
			Map[CurrBlock->y][CurrBlock->x] = CurrBlock->Color;
			Map[CurrBlock->y][CurrBlock->x + 1] = CurrBlock->Color;
			Map[CurrBlock->y][CurrBlock->x + 2] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x + 1] = CurrBlock->Color;
			break;
		case BLOCK_LEFT:
			Map[CurrBlock->y][CurrBlock->x + 1] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x + 1] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x + 2] = CurrBlock->Color;
			break;
		case BLOCK_FLIP:
			Map[CurrBlock->y][CurrBlock->x + 1] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x + 1] = CurrBlock->Color;
			Map[CurrBlock->y + 2][CurrBlock->x + 1] = CurrBlock->Color;
			break;
		}
		break;
	case BLOCK_D:
		switch (CurrBlock->State)
		{
		case BLOCK_FIXED:
			break;
		case BLOCK_MAIN:
			Map[CurrBlock->y][CurrBlock->x] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x] = CurrBlock->Color;
			Map[CurrBlock->y + 2][CurrBlock->x] = CurrBlock->Color;
			Map[CurrBlock->y + 2][CurrBlock->x + 1] = CurrBlock->Color;
			break;
		case BLOCK_RIGHT:
			Map[CurrBlock->y][CurrBlock->x] = CurrBlock->Color;
			Map[CurrBlock->y][CurrBlock->x + 1] = CurrBlock->Color;
			Map[CurrBlock->y][CurrBlock->x + 2] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x] = CurrBlock->Color;
			break;
		case BLOCK_LEFT:
			Map[CurrBlock->y][CurrBlock->x + 2] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x + 1] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x + 2] = CurrBlock->Color;
			break;
		case BLOCK_FLIP:
			Map[CurrBlock->y][CurrBlock->x] = CurrBlock->Color;
			Map[CurrBlock->y][CurrBlock->x + 1] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x + 1] = CurrBlock->Color;
			Map[CurrBlock->y + 2][CurrBlock->x + 1] = CurrBlock->Color;
			break;
		}
		break;
	case BLOCK_E:
		switch (CurrBlock->State)
		{
		case BLOCK_FIXED:
			break;
		case BLOCK_MAIN:
			Map[CurrBlock->y][CurrBlock->x] = CurrBlock->Color;
			Map[CurrBlock->y][CurrBlock->x + 1] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x] = CurrBlock->Color;
			Map[CurrBlock->y + 2][CurrBlock->x] = CurrBlock->Color;
			break;
		case BLOCK_RIGHT:
			Map[CurrBlock->y][CurrBlock->x] = CurrBlock->Color;
			Map[CurrBlock->y][CurrBlock->x + 1] = CurrBlock->Color;
			Map[CurrBlock->y][CurrBlock->x + 2] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x + 2] = CurrBlock->Color;
			break;
		case BLOCK_LEFT:
			Map[CurrBlock->y][CurrBlock->x] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x + 1] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x + 2] = CurrBlock->Color;
			break;
		case BLOCK_FLIP:
			Map[CurrBlock->y][CurrBlock->x + 1] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x + 1] = CurrBlock->Color;
			Map[CurrBlock->y + 2][CurrBlock->x] = CurrBlock->Color;
			Map[CurrBlock->y + 2][CurrBlock->x + 1] = CurrBlock->Color;
			break;
		}
		break;
	case BLOCK_F:
		switch (CurrBlock->State)
		{
		case BLOCK_FIXED:
			break;
		case BLOCK_MAIN:
		case BLOCK_RIGHT:
		case BLOCK_LEFT:
		case BLOCK_FLIP:
			Map[CurrBlock->y][CurrBlock->x] = CurrBlock->Color;
			Map[CurrBlock->y][CurrBlock->x + 1] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x + 1] = CurrBlock->Color;
			break;
		}
		break;
	case BLOCK_G:
		switch (CurrBlock->State)
		{
		case BLOCK_FIXED:
			break;
		case BLOCK_MAIN:
		case BLOCK_FLIP:
			Map[CurrBlock->y][CurrBlock->x] = CurrBlock->Color;
			Map[CurrBlock->y][CurrBlock->x + 1] = CurrBlock->Color;
			Map[CurrBlock->y][CurrBlock->x + 2] = CurrBlock->Color;
			Map[CurrBlock->y][CurrBlock->x + 3] = CurrBlock->Color;
			break;
		case BLOCK_RIGHT:
		case BLOCK_LEFT:
			Map[CurrBlock->y][CurrBlock->x] = CurrBlock->Color;
			Map[CurrBlock->y + 1][CurrBlock->x] = CurrBlock->Color;
			Map[CurrBlock->y + 2][CurrBlock->x] = CurrBlock->Color;
			Map[CurrBlock->y + 3][CurrBlock->x] = CurrBlock->Color;
			break;
		}
		break;
	case BLOCK_BOMB:
		switch (CurrBlock->State)
		{
		case BLOCK_FIXED:
			break;
		case BLOCK_MAIN:
		case BLOCK_RIGHT:
		case BLOCK_LEFT:
		case BLOCK_FLIP:
			PlayGameSound(GAME_BOOM);
			CurrBlock->Color=BLOCK_NULL;
			prtCurrBlock(CurrBlock);
			Map[CurrBlock->y][CurrBlock->x] = BLOCK_NULL;
			if (CurrBlock->x)
			{
				Map[CurrBlock->y][CurrBlock->x - 1] = BLOCK_NULL;
				if (CurrBlock->y)
					Map[CurrBlock->y - 1][CurrBlock->x - 1] = BLOCK_NULL;
				if (CurrBlock->y < MAP_MAX_Y)
					Map[CurrBlock->y + 1][CurrBlock->x - 1] = BLOCK_NULL;
			}
			if (CurrBlock->y)
				Map[CurrBlock->y - 1][CurrBlock->x] = BLOCK_NULL;
			if (CurrBlock->y < MAP_MAX_Y)
				Map[CurrBlock->y + 1][CurrBlock->x] = BLOCK_NULL;
			if (CurrBlock->x < MAP_MAX_X)
			{
				Map[CurrBlock->y][CurrBlock->x + 1] = BLOCK_NULL;
				if (CurrBlock->y)
					Map[CurrBlock->y - 1][CurrBlock->x + 1] = BLOCK_NULL;
				if (CurrBlock->y < MAP_MAX_Y)
					Map[CurrBlock->y + 1][CurrBlock->x + 1] = BLOCK_NULL;
			}


			gotoMapxy(CurrBlock->x,CurrBlock->y);
			_putwch(L'※');
			if (CurrBlock->x)
			{
				gotoMapxy(CurrBlock->x - 1,CurrBlock->y);
				_prtBlock(BLOCK_BLACK);
				if (CurrBlock->y)
				{
					gotoMapxy(CurrBlock->x - 1,CurrBlock->y - 1);
					_prtBlock(BLOCK_BLACK);
				}
				if (CurrBlock->y < MAP_MAX_Y)
				{
					gotoMapxy(CurrBlock->x - 1,CurrBlock->y + 1);
					_prtBlock(BLOCK_BLACK);
				}
			}
			if (CurrBlock->y)
			{
				gotoMapxy(CurrBlock->x,CurrBlock->y - 1);
				_prtBlock(BLOCK_BLACK);
			}
			if (CurrBlock->y < MAP_MAX_Y)
			{
				gotoMapxy(CurrBlock->x,CurrBlock->y + 1);
				_prtBlock(BLOCK_BLACK);
			}
			if (CurrBlock->x < MAP_MAX_X)
			{
				gotoMapxy(CurrBlock->x + 1,CurrBlock->y);
				_prtBlock(BLOCK_BLACK);
				if (CurrBlock->y)
				{
					gotoMapxy(CurrBlock->x + 1,CurrBlock->y - 1);
					_prtBlock(BLOCK_BLACK);
				}
				if (CurrBlock->y < MAP_MAX_Y)
				{
					gotoMapxy(CurrBlock->x + 1,CurrBlock->y + 1);
					_prtBlock(BLOCK_BLACK);
				}
			}

			Sleep(200);

			gotoMapxy(CurrBlock->x,CurrBlock->y);
			_putwch(L'※');
			if (CurrBlock->x)
			{
				gotoMapxy(CurrBlock->x - 1,CurrBlock->y);
				_prtBlock(BLOCK_NULL);
				if (CurrBlock->y)
				{
					gotoMapxy(CurrBlock->x - 1,CurrBlock->y - 1);
					_prtBlock(BLOCK_NULL);
				}
				if (CurrBlock->y < MAP_MAX_Y)
				{
					gotoMapxy(CurrBlock->x - 1,CurrBlock->y + 1);
					_prtBlock(BLOCK_NULL);
				}
			}
			if (CurrBlock->y)
			{
				gotoMapxy(CurrBlock->x,CurrBlock->y - 1);
				_prtBlock(BLOCK_NULL);
			}
			if (CurrBlock->y < MAP_MAX_Y)
			{
				gotoMapxy(CurrBlock->x,CurrBlock->y + 1);
				_prtBlock(BLOCK_NULL);
			}
			if (CurrBlock->x < MAP_MAX_X)
			{
				gotoMapxy(CurrBlock->x + 1,CurrBlock->y);
				_prtBlock(BLOCK_NULL);
				if (CurrBlock->y)
				{
					gotoMapxy(CurrBlock->x + 1,CurrBlock->y - 1);
					_prtBlock(BLOCK_NULL);
				}
				if (CurrBlock->y < MAP_MAX_Y)
				{
					gotoMapxy(CurrBlock->x + 1,CurrBlock->y + 1);
					_prtBlock(BLOCK_NULL);
				}
			}

			Sleep(200);
			gotoMapxy(CurrBlock->x, CurrBlock->y);
			_prtBlock(BLOCK_NULL);
			updMap(Map);

			//폭파된 블럭 위에 있던 블럭들은 모두 아래로 떨어진다.
			//if (CurrBlock->y > 1 && Map[CurrBlock->y - 2][CurrBlock->x - 1])
			//	m1 = TRUE;
			//if (CurrBlock->y > 1 && Map[CurrBlock->y - 2][CurrBlock->x])
			//	m2 = TRUE;
			//if (CurrBlock->y > 1 && Map[CurrBlock->y - 2][CurrBlock->x + 1])
			//	m3 = TRUE;

			for (i = CurrBlock->y + 1; CurrBlock->x > 0 && i < MAP_MAX_Y; i++)
			{
				if(i == CurrBlock->y + 1 && !AvobeBlock(Map, CurrBlock->x - 1,CurrBlock->y + 1))
					break;
				else if(!Map[i + 1][CurrBlock->x - 1])
					m1++;
				else
					break;
			}
			for (i = CurrBlock->y + 1; i < MAP_MAX_Y; i++)
			{
				if(i == CurrBlock->y + 1 && !AvobeBlock(Map, CurrBlock->x,CurrBlock->y + 1))
					break;
				else if(!Map[i + 1][CurrBlock->x])
					m2++;
				else
					break;
			}
			for (i = CurrBlock->y + 1; CurrBlock->x < MAP_MAX_X && i < MAP_MAX_Y; i++)
			{
				if(i == CurrBlock->y + 1 && !AvobeBlock(Map, CurrBlock->x + 1,CurrBlock->y + 1))
					break;
				else if(!Map[i + 1][CurrBlock->x + 1])
					m3++;
				else
					break;
			}

			do
			{
				Changed = FALSE;
				for (i = CurrBlock->y < MAP_MAX_Y ? CurrBlock->y + 1 : CurrBlock->y; i>0; i--)
				{
					if (CurrBlock->x > 0 && !Map[i][CurrBlock->x - 1] && Map[i - 1][CurrBlock->x - 1])
					{
						Map[i][CurrBlock->x - 1] = Map[i - 1][CurrBlock->x - 1];
						Map[i - 1][CurrBlock->x - 1] = BLOCK_NULL;
						Changed = TRUE;
					}

					if (!Map[i][CurrBlock->x] && Map[i - 1][CurrBlock->x])
					{
						Map[i][CurrBlock->x] = Map[i - 1][CurrBlock->x];
						Map[i - 1][CurrBlock->x] = BLOCK_NULL;
						Changed = TRUE;
					}

					if (CurrBlock->x < MAP_MAX_X && !Map[i][CurrBlock->x + 1] && Map[i - 1][CurrBlock->x + 1])
					{
						Map[i][CurrBlock->x + 1] = Map[i - 1][CurrBlock->x + 1];
						Map[i - 1][CurrBlock->x + 1] = BLOCK_NULL;
						Changed = TRUE;
					}
				}

				for (i = CurrBlock->y + 1; i < MAP_MAX_Y; i++)
				{
					if (m1 && Map[i][CurrBlock->x - 1] && !Map[i + 1][CurrBlock->x - 1])
					{
						Map[i + 1][CurrBlock->x - 1] = Map[i][CurrBlock->x - 1];
						Map[i][CurrBlock->x - 1] = BLOCK_NULL;
						Changed = TRUE;
						m1--;
						if (!m1)
							for (i = CurrBlock->y + 1; CurrBlock->x > 0 && i < MAP_MAX_Y; i++)
							{
							if (!Map[i + 1][CurrBlock->x - 1])
								m1++;
							else
								break;
							}
					}
					if (m2 && Map[i][CurrBlock->x] && !Map[i + 1][CurrBlock->x])
					{
						Map[i + 1][CurrBlock->x] = Map[i][CurrBlock->x];
						Map[i][CurrBlock->x] = BLOCK_NULL;
						Changed = TRUE;
						m2--;
						if (!m2)
							for (i = CurrBlock->y + 1; i < MAP_MAX_Y; i++)
							{
							if (!Map[i + 1][CurrBlock->x])
								m2++;
							else
								break;
							}
					}
					if (m3 && Map[i][CurrBlock->x + 1] && !Map[i + 1][CurrBlock->x + 1])
					{

						Map[i + 1][CurrBlock->x + 1] = Map[i][CurrBlock->x + 1];
						Map[i][CurrBlock->x + 1] = BLOCK_NULL;
						Changed = TRUE;
						m3--;
						if (!m3)
						{
							for (i = CurrBlock->y + 1; CurrBlock->x < MAP_MAX_X && i < MAP_MAX_Y; i++)
							{
								if (!Map[i + 1][CurrBlock->x + 1])
									m3++;
								else
									break;
							}
						}
					}
				}
				prtMap(Map);
				Sleep(200);
			//	getchar();
			} while (Changed);


			PrevMap[CurrBlock->y][CurrBlock->x] = BLOCK_NULL;

			break;
		}
		break;
	default:
		FatalError(ERROR_APPEND_MAP);
	}
}


double DropTime(int Level)
{
	switch(Level/5)
	{
	case 0:
		return (double)550-50*Level;
	case 1:
		return (double)300-30*(Level%5);
	case 2:
		return (double)150-10*(Level%5);
	default:
		return (double)100;
	}
}


void testGame(int Map[MAP_Y][MAP_X], BLOCK *CurrBlock, BLOCK *NextBlock, BLOCK *NNextBlock, SCOREDATA *ScoreData)
{
	/*Only For Test*/
	int testMap[MAP_Y][MAP_X]={{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0,0,1,2,3,4,5,6,7,8,}};
	int testMap2[MAP_Y][MAP_X]={{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0,0,1,1,2,2,5,5,5,},{0,0,1,1,2,2,5,0,0},};
	int testMap3[MAP_Y][MAP_X]={{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0,0,1,1,2,2,5,5,5,},{0,0,1,1,2,2,5,0,0},};
	BLOCK testBlock={0,0,BLOCK_A,BLOCK_WHITE,BLOCK_MAIN};
	BLOCK testBlock2={2,4,BLOCK_C,BLOCK_BLUE,BLOCK_LEFT};
	BLOCK testBlock3={5,7,BLOCK_F,BLOCK_VIOLET,BLOCK_FLIP};
	BLOCK testBlock4={0,10,BLOCK_BOMB,BLOCK_YELLOW,BLOCK_RIGHT};

	/*Only For Test End*/
	prtMap(testMap);
	prtScore(*ScoreData);
	ScoreData->Level=3;
	prtCurrBlock(&testBlock4);
	prtNextBlocks(&testBlock3,&testBlock2);
	prtScore(*ScoreData);
	_getch();


	prtMap(testMap);
	prtCurrBlock(&testBlock3);
	prtNextBlocks(&testBlock2,&testBlock4);
	ScoreData->Level = 100;
	prtScore(*ScoreData);


	_getch();

	
	prtMap(testMap);
	prtCurrBlock(&testBlock2);
	prtNextBlocks(&testBlock4,&testBlock);
	ScoreData->score = 122300;
	ScoreData->best = 2222200;
	ScoreData->Level = 10000;
	prtScore(*ScoreData);
}


void PlayGame(void)
{
	BOOL EndGame=FALSE;
	BOOL isPaused=FALSE;
	BOOL bCleared=FALSE;
	int *Channel=NULL;
	int Map[MAP_Y][MAP_X]={0,};
	clock_t tPrev=0,tNow=0;

	BLOCK CurrBlock={0,};
	BLOCK NextBlock={0,};
	BLOCK NNextBlock={0,};
	
	int key[4]={1,5,7,24};
	SCOREDATA ScoreData={1,};

	//Init values
	ScoreData.best=Lbest;
	prtMap(Map);
	prtCurrBlock(&CurrBlock);
	prtNextBlocks(&NextBlock,&NNextBlock);

	//Init Block Data
	NewBlock(&CurrBlock);
	NewBlock(&NextBlock);
	NewBlock(&NNextBlock);

	//Load Game Screen
	SetWinSize(62,28);
	prtgameform();
	prtScore(ScoreData);
	prtMap(Map);
	GetDropPos(Map,&CurrBlock);
	prtDropBlock(&CurrBlock);
	prtCurrBlock(&CurrBlock);
	prtNextBlocks(&NextBlock,&NNextBlock);
	tPrev=clock();
	tNow=clock();

	//Load Game Music
	InitGameSound();
	LoadMusic();

	//testGame(Map, &CurrBlock, &NextBlock, &NNextBlock, &ScoreData);

	while(!EndGame && !bExitGame)
	{
		if(_kbhit())
		{
		//input Part
		switch(_getch())
		{
		case 0:
			switch(_getch())
			{
			case 63:		//F5
				PlayGameSound(GAME_SEL);
				FMOD_Channel_Stop(cMusic);
				FMOD_System_Update(fmodSystem);
				break;
			case 64:		//F6
				PlayGameSound(GAME_SEL);
				FMOD_Channel_Stop(cMusic);
				FMOD_Sound_Release(Music);
				Music_Type++;
				if(!bBGM)
				{
					if(strcmp(MusicPath,"") && Music_Type>MUSIC_OFF)
						Music_Type=MUSIC_USER_DEFINE;
					else if(!strcmp(MusicPath,"") && Music_Type>MUSIC_OFF);
						Music_Type=MUSIC_OFF;
				}
				if(!strcmp(MusicPath,"") && Music_Type>MUSIC_CATMARIO || Music_Type>MUSIC_USER_DEFINE)
					Music_Type=MUSIC_OFF;
				FMOD_System_Update(fmodSystem);
				LoadMusic();
				break;
			case 65:		//F7
				PlayGameSound(GAME_SEL);
				vMusic-=0.1f;
				if(vMusic<0.0f)
					vMusic=0.0f;
				FMOD_Channel_SetVolume(cMusic,vMusic);
				FMOD_System_Update(fmodSystem);
				break;
			case 66:		//F8
				PlayGameSound(GAME_SEL);
				vMusic+=0.1f;
				if(vMusic>1.0f)
					vMusic=1.0f;
				FMOD_Channel_SetVolume(cMusic,vMusic);
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
				PlayGameSound(GAME_TICK);
				if(!isCollision(Map,&CurrBlock,MOVE_LEFT))
				{
					CurrBlock.x--;
					GetDropPos(Map,&CurrBlock);
					prtDropBlock(&CurrBlock);
				}
				break;
			case ARROW_UP:		//↑
				/*
				if(!isCollision(Map,&CurrBlock,MOVE_UP))
					CurrBlock.y--;*/
				PlayGameSound(GAME_TURN);
				TurnBlock(Map,&CurrBlock,TURN_RIGHT);
				GetDropPos(Map,&CurrBlock);
				prtDropBlock(&CurrBlock);
				break;

			case ARROW_RIGHT:	//→
				PlayGameSound(GAME_TICK);
				if(!isCollision(Map,&CurrBlock,MOVE_RIGHT))
				{
					CurrBlock.x++;
					GetDropPos(Map,&CurrBlock);
					prtDropBlock(&CurrBlock);
				}
				break;
			case ARROW_DOWN:	//↓
				PlayGameSound(GAME_TICK);
				if(!isCollision(Map,&CurrBlock,MOVE_DOWN))
					CurrBlock.y++;
				else
				{
					AppendMap(Map,&CurrBlock);
					prtCurrBlock(&CurrBlock);
					bCleared=isCleared(Map,&ScoreData);
					CreateNewBlock(&CurrBlock, &NextBlock, &NNextBlock);
					GetDropPos(Map,&CurrBlock);
					prtDropBlock(&CurrBlock);
					if(isCollision(Map,&CurrBlock,MOVE_NONE))
					{
						AppendMap(Map,&CurrBlock);
						EndGame=TRUE;
					}
					tPrev=clock();
				}
				break;
			}
			break;
		case 'z':			//좌로 90도 회전
		case 'Z':
			PlayGameSound(GAME_TURN);
			TurnBlock(Map,&CurrBlock,TURN_LEFT);
			GetDropPos(Map,&CurrBlock);
			prtDropBlock(&CurrBlock);
			break;
		case 'x':			//우로 90도 회전
		case 'X':
			PlayGameSound(GAME_TURN);
			TurnBlock(Map,&CurrBlock,TURN_RIGHT);
			GetDropPos(Map,&CurrBlock);
			prtDropBlock(&CurrBlock);
			break;
		case ' ':			//아래로 바로 떨어짐
			PlayGameSound(GAME_TURN);
			FallBlock(Map,&CurrBlock);
			AppendMap(Map,&CurrBlock);
			prtCurrBlock(&CurrBlock);
			Sleep(200);
		/*case ENTER_KEY:			//새로운 블럭*/
			bCleared=isCleared(Map,&ScoreData);
			CreateNewBlock(&CurrBlock, &NextBlock, &NNextBlock);
			GetDropPos(Map,&CurrBlock);
			prtDropBlock(&CurrBlock);
			if(isCollision(Map,&CurrBlock,MOVE_NONE))
			{
				AppendMap(Map,&CurrBlock);
				EndGame=TRUE;
			}
			tPrev=clock();
			break;
		case 'p':
		case 'P':
		case ESC_KEY:
			FMOD_Channel_SetPaused(cMusic,TRUE);
			prtPusMap(Map,&CurrBlock);
			tNow=clock();
			tNow=(clock_t)difftime(tPrev,tNow);
			
			if(_getch()==ESC_KEY)
				EndGame=TRUE;

			tPrev=clock();
			tNow=tPrev+tNow;
			reprtMap(Map);
			FMOD_Channel_SetPaused(cMusic,FALSE);
			break;
		}
		if(EndGame)
		{
			FMOD_Channel_Stop(cMusic);
			FMOD_Sound_Release(Music);
			FMOD_System_Update(fmodSystem);
			PlayGameSound(GAME_GAMEOVER);
			prtFinMap(Map);
			break;
		}
		else
		{
			GetDropPos(Map,&CurrBlock);
			prtDropBlock(&CurrBlock);
			prtCurrBlock(&CurrBlock);
			prtNextBlocks(&NextBlock,&NNextBlock);
			prtMap(Map);
			if(bCleared)
			{
				GetDropPos(Map,&CurrBlock);
				prtDropBlock(&CurrBlock);
				bCleared=FALSE;
			}
			prtScore(ScoreData);
			while(_kbhit()) _getch();
		}
		}
		else
		{
			Sleep(20);
			tNow=clock();
			
			FMOD_Channel_IsPlaying(cMusic,&isPaused);
			if(!isPaused)
				LoadMusic();
			if(difftime(tNow,tPrev) > DropTime(ScoreData.Level))
			{
				PlayGameSound(GAME_TICK);
				if(!isCollision(Map,&CurrBlock,MOVE_DOWN))
					CurrBlock.y++;
				else
				{
					AppendMap(Map,&CurrBlock);
					prtCurrBlock(&CurrBlock);
					isCleared(Map,&ScoreData);
					CreateNewBlock(&CurrBlock, &NextBlock, &NNextBlock);
					GetDropPos(Map,&CurrBlock);
					prtDropBlock(&CurrBlock);
					if(isCollision(Map,&CurrBlock,MOVE_NONE))
					{
						AppendMap(Map,&CurrBlock);
						EndGame=TRUE;
					}
					tPrev=clock();
				}
				if(EndGame)
				{
					FMOD_Channel_Stop(cMusic);
					FMOD_Sound_Release(Music);
					FMOD_System_Update(fmodSystem);
					PlayGameSound(GAME_GAMEOVER);
					prtFinMap(Map);
					break;
				}
				else
				{
					GetDropPos(Map,&CurrBlock);
					prtDropBlock(&CurrBlock);
					prtCurrBlock(&CurrBlock);
					prtNextBlocks(&NextBlock,&NNextBlock);
					prtMap(Map);
					if(bCleared)
					{
						GetDropPos(Map,&CurrBlock);
						prtDropBlock(&CurrBlock);
						bCleared=FALSE;
					}
					prtScore(ScoreData);
					tPrev=clock();
				}
			}
		}
	}
	Lbest=ScoreData.best;
	fflush(stdin);
	while(_getch() !='\r');
	StopGameSound();
}