#include "MazeDataStruct.h"
 

int originX = LEFTMARGIN;
int originY = BOTTOMTMARGIN;
int dY = 30;
int dX = dY;
int count = 0;
mazeColor circleFillColor = { 0,0,0 };
mazeColor blockFillColor = { 0,0,0 };

char MonthFirstPosition[DIGITROW][DIGITCOL] = { 0 };
char DayFirstPosition[DIGITROW][DIGITCOL] = { 0 };
char DaySecondPosition[DIGITROW][DIGITCOL] = { 0 };
char MonthSecondPosition[DIGITROW][DIGITCOL] = { 0 };

/* ��ʼ���Թ� */
char MAZE[DIGITROW][4 * DIGITCOL] = { 0 };

/* ������ߵ�· */
void MarkFoot(SElemType curpos)
{
	MAZE[curpos.x][curpos.y] = '#';
}

/* ��ǲ��ɵ�����ڵ�λ��*/
void NotAccessible(SElemType curpos)
{
	MAZE[curpos.x][curpos.y] = '!';
}

/* ����λ�� */
void NextPosition(SElemType *curpos)
{
	switch (curpos->derection)
	{
		/* ���� */
	case 1:
		(curpos->y)++;
		break;
		/* ������ */
	case 2:
		(curpos->x)++;
		break;
		/* ������ */
	case 3:
		(curpos->y)--;
		break;
		/* ���� */
	case 4:
		(curpos->x)--;
		break;
	}
}

/* �жϵ�ǰλ���Ƿ��ͨ */
Status IsAccessible(SElemType curpos)
{
	if (MAZE[curpos.x][curpos.y] == ' ')
		return TRUE;
	else
		return FALSE;
}

/* Ѱ���Թ�·�� */
Status MazePath(SElemType start, SElemType end)
{
	LinkStack S;
	S = (LinkStack)malloc(sizeof(StackNode));/* ����ռ� */
	InitStack(S);/* ����һ����ջ */
	SElemType curpos;/* ����λ�� */
	curpos = start;/* ��ʼ����� */
	SElemType *ne = (SElemType*)malloc(sizeof(SElemType));/* ����ճ�ջ��Ԫ�� */
	do
	{
		if (IsAccessible(curpos))/* ��ǰλ�ÿ�ͨ */
		{
			MarkFoot(curpos);/* �����㼣 */
			DisplayPath(curpos);
			SElemType* e = (SElemType*)malloc(sizeof(SElemType));/* ���䴢��ռ� */
			e->x = curpos.x;
			e->y = curpos.y;
			e->derection = 1;/* �����ֵΪ1����˳ʱ��仯������1��4���� */
			Push(S, e);/* ��ջ������·�� */
			if (curpos.x == end.x&&curpos.y == end.y)/* �ж��Ƿ񵽴���� */
			{
				return TRUE;
			}
			curpos.derection = 1;/* ������ */
			NextPosition(&curpos);/* ����λ�� */
		}
		else/* ��ǰλ�ò���ͨ */
		{
			Pop(S, ne);/* ��ջ */
			DisplayPath(*ne);
			while (ne->derection == 4 && !IsEmpty(S))
			{
				NotAccessible(*ne);/* ����Ϊ��˵���ĸ����򶼲��ɵ�����ڣ���� */
				Pop(S, ne);
				DisplayPath(*ne);
			}
			if (ne->derection < 4)
			{
				ne->derection++;/* �޸ķ��� */
								/*
								һ��Ҫ���´���һ���ṹָ����ָ���µ�λ�ýṹ��������ʹ��ne����Ϊ
								neֻ��һ�ݴ洢�ռ䣬���滹�漰��ne�Ĳ�����neֻ��������ʱ����ճ�ջ
								��Ԫ��
								*/
				SElemType *temp = (SElemType*)malloc(sizeof(SElemType));
				*temp = *ne;
				/*����ѹ��ջ��*/
				Push(S, temp);
				/* ����λ�� */
				NextPosition(ne);
				curpos = *ne;
			}
		}
	} while (!IsEmpty(S));
	return FALSE;
}

/* ��ʾ·�� */
void DisplayPath(SElemType curpos)
{
	if(count%10==0) SetMazeColor();
	BeginBatchDraw();
	cleardevice();
	setfillcolor(RGB(blockFillColor.r,blockFillColor.g,blockFillColor.b));
	DrawMaze();
	setfillcolor(RGB(circleFillColor.r, circleFillColor.g, circleFillColor.b));
	solidcircle(originX + curpos.y * dX + dX / 2, originY + curpos.x * dY + dY / 2, dX / 2);
	Sleep(40);
	FlushBatchDraw();
	count++;
}

/* �����Թ� */
void DrawMaze()
{
	int row = sizeof(MAZE) / sizeof(MAZE[0]);
	int col = sizeof(MAZE[row]) / sizeof(MAZE[row][0]);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (MAZE[i][j] == 'x') {
				solidrectangle(originX + j * dX,
					originY + i * dY,
					originX + (j + 1) * dX,
					originY + (i + 1)*dY);
			}
			else {
			}
		}
	}
}

/* ����һ���Թ�����Ӧ�Ķ�ά���� */
void MazeGenerator(int month,int day)
{
	if (month > 12 || month < 1) exit(0);
	if (day > 31 || day < 1) exit(0);
	SwitchMonth(month);
	SwitchDay(day);
	int row = sizeof(MAZE) / sizeof(MAZE[0]);
	int col = sizeof(MAZE[row]) / sizeof(MAZE[row][0]);
	if (month < 10) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (j < DIGITCOL) MAZE[i][j] = MonthFirstPosition[i][j];
				else if (j >= DIGITCOL && j < 2 * DIGITCOL) MAZE[i][j] = DayFirstPosition[i][j - DIGITCOL];
				else if(j >= 2 * DIGITCOL&&j < 3 * DIGITCOL)MAZE[i][j] = DaySecondPosition[i][j - 2 * DIGITCOL];
				else;
			}
		}
		MAZE[6][7] = MAZE[6][8] = MAZE[6][15] = MAZE[6][16] = ' ';
	}
	else {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (j < DIGITCOL) MAZE[i][j] = MonthFirstPosition[i][j];
				else if (j >= DIGITCOL && j < 2 * DIGITCOL) MAZE[i][j] = MonthSecondPosition[i][j - DIGITCOL];
				else if (j >= 2 * DIGITCOL&&j < 3 * DIGITCOL) MAZE[i][j] = DayFirstPosition[i][j - 2 * DIGITCOL];
				else MAZE[i][j] = DaySecondPosition[i][j - 3 * DIGITCOL];

			}
		}
		MAZE[6][7] = MAZE[6][8] = MAZE[6][15] = MAZE[6][16] = MAZE[6][23] = MAZE[6][24] = ' ';
	}
}

/* �������ɫ */
void SetMazeColor() 
{
	srand((unsigned)time(NULL) + rand());/* �������� */
	blockFillColor.r = 0 + (rand() % (255 + 0 - 1)) - 1;/* �������λ�� */
	srand((unsigned)time(NULL) + rand());
	blockFillColor.g = 0 + (rand() % (255 + 0 - 1)) - 1;
	srand((unsigned)time(NULL) + rand());
	blockFillColor.b = 0 + (rand() % (255 + 0 - 1)) - 1;
	srand((unsigned)time(NULL) + rand());
	circleFillColor.r = 0 + (rand() % (255 + 0 - 1)) - 1;
	srand((unsigned)time(NULL) + rand());
	circleFillColor.g = 0 + (rand() % (255 + 0 - 1)) - 1;
	srand((unsigned)time(NULL) + rand());
	circleFillColor.b = 0 + (rand() % (255 + 0 - 1)) - 1;
}

/* ����һ����ά���� */
void ArrayCopy(char (*a)[DIGITCOL], char (*b)[DIGITCOL])
{
	for (int i = 0; i < DIGITROW; i++)
		for (int j = 0; j < DIGITCOL; j++)
			b[i][j] = a[i][j];
}

/* �������������������� */
void SwitchDay(int day)
{
	if (day < 10) {
		ArrayCopy(ZERO, DayFirstPosition);
		switch (day) {
		case 1:
			ArrayCopy(ONE, DaySecondPosition);
			break;
		case 2:
			ArrayCopy(TWO, DaySecondPosition);
			break;
		case 3:
			ArrayCopy(THREE, DaySecondPosition);
			break;
		case 4:
			ArrayCopy(FOUR, DaySecondPosition);
			break;
		case 5:
			ArrayCopy(FIVE, DaySecondPosition);
			break;
		case 6:
			ArrayCopy(SIX, DaySecondPosition);
			break;
		case 7:
			ArrayCopy(SEVEN, DaySecondPosition);
			break;
		case 8:
			ArrayCopy(EIGHT, DaySecondPosition);
			break;
		case 9:
			ArrayCopy(NINE, DaySecondPosition);
			break;
		}
	}
	else if (day >= 10 && day < 20) {
		ArrayCopy(ONE, DayFirstPosition);
		switch (day - 10) {
		case 0:
			ArrayCopy(ZERO, DaySecondPosition);
		case 1:
			ArrayCopy(ONE, DaySecondPosition);
			break;
		case 2:
			ArrayCopy(TWO, DaySecondPosition);
			break;
		case 3:
			ArrayCopy(THREE, DaySecondPosition);
			break;
		case 4:
			ArrayCopy(FOUR, DaySecondPosition);
			break;
		case 5:
			ArrayCopy(FIVE, DaySecondPosition);
			break;
		case 6:
			ArrayCopy(SIX, DaySecondPosition);
			break;
		case 7:
			ArrayCopy(SEVEN, DaySecondPosition);
			break;
		case 8:
			ArrayCopy(EIGHT, DaySecondPosition);
			break;
		case 9:
			ArrayCopy(NINE, DaySecondPosition);
			break;
		}
	}
	else if (day >= 20 && day < 30) {
		ArrayCopy(TWO, DayFirstPosition);
		switch (day - 20) {
		case 0:
			ArrayCopy(ZERO, DaySecondPosition);
		case 1:
			ArrayCopy(ONE, DaySecondPosition);
			break;
		case 2:
			ArrayCopy(TWO, DaySecondPosition);
			break;
		case 3:
			ArrayCopy(THREE, DaySecondPosition);
			break;
		case 4:
			ArrayCopy(FOUR, DaySecondPosition);
			break;
		case 5:
			ArrayCopy(FIVE, DaySecondPosition);
			break;
		case 6:
			ArrayCopy(SIX, DaySecondPosition);
			break;
		case 7:
			ArrayCopy(SEVEN, DaySecondPosition);
			break;
		case 8:
			ArrayCopy(EIGHT, DaySecondPosition);
			break;
		case 9:
			ArrayCopy(NINE, DaySecondPosition);
			break;
		}
	}
	else if (day == 30 || day == 31) {
		ArrayCopy(THREE, DayFirstPosition);
		switch (day - 30) {
		case 0:
			ArrayCopy(ZERO, DaySecondPosition);
			break;
		case 1:
			ArrayCopy(ONE, DaySecondPosition);
			break;
		}
	}
	else;
}

/* �������������������� */
void SwitchMonth(int month)
{
	if (0 < month && month< 10) {
		switch (month) {
		case 1:
			ArrayCopy(ONE, MonthFirstPosition);
			break;
		case 2:
			ArrayCopy(TWO, MonthFirstPosition);
			break;
		case 3:
			ArrayCopy(THREE, MonthFirstPosition);
			break;
		case 4:
			ArrayCopy(FOUR, MonthFirstPosition);
			break;
		case 5:
			ArrayCopy(FIVE, MonthFirstPosition);
			break;
		case 6:
			ArrayCopy(SIX, MonthFirstPosition);
			break;
		case 7:
			ArrayCopy(SEVEN, MonthFirstPosition);
			break;
		case 8:
			ArrayCopy(EIGHT, MonthFirstPosition);
			break;
		case 9:
			ArrayCopy(NINE, MonthFirstPosition);
			break;
		}
	}
	if (month >= 10 && month <= 12)
	{
		ArrayCopy(ONE, MonthFirstPosition);
		switch (month % 10) {
		case 0:
			ArrayCopy(ZERO, MonthSecondPosition);
		case 1:
			ArrayCopy(ONE, MonthSecondPosition);
			break;
		case 2:
			ArrayCopy(TWO, MonthSecondPosition);
			break;
		}
	}
}

/* ��ʼѰ��·�� */
void Start(int month, int day)
{
	MazeGenerator(month, day);
	initgraph(WINDOWSWIDTH, WINDOWSHEIGHT);
	setbkcolor(WHITE);
	setlinecolor(BLACK);
	setfillcolor(RGB(255, 182, 193));
	cleardevice();
	Sleep(1000);
	DrawMaze();
	/* ��ʼλ�� */
	SElemType start = { 1,2,1 };
	/* ����λ�� */
	SElemType end = { 13,14,1 };
	MazePath(start, end);
	//rectangle(LEFTMARGIN,WINDOWSHEIGHT-TOPMARGIN, WINDOWSWIDTH - RIGHTMARGIN, BOTTOMTMARGIN);
}