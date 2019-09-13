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

/* 初始化迷宫 */
char MAZE[DIGITROW][4 * DIGITCOL] = { 0 };

/* 标记已走的路 */
void MarkFoot(SElemType curpos)
{
	MAZE[curpos.x][curpos.y] = '#';
}

/* 标记不可到达出口的位置*/
void NotAccessible(SElemType curpos)
{
	MAZE[curpos.x][curpos.y] = '!';
}

/* 更新位置 */
void NextPosition(SElemType *curpos)
{
	switch (curpos->derection)
	{
		/* 向东走 */
	case 1:
		(curpos->y)++;
		break;
		/* 向南走 */
	case 2:
		(curpos->x)++;
		break;
		/* 向西走 */
	case 3:
		(curpos->y)--;
		break;
		/* 向北走 */
	case 4:
		(curpos->x)--;
		break;
	}
}

/* 判断当前位置是否可通 */
Status IsAccessible(SElemType curpos)
{
	if (MAZE[curpos.x][curpos.y] == ' ')
		return TRUE;
	else
		return FALSE;
}

/* 寻找迷宫路径 */
Status MazePath(SElemType start, SElemType end)
{
	LinkStack S;
	S = (LinkStack)malloc(sizeof(StackNode));/* 分配空间 */
	InitStack(S);/* 创建一个空栈 */
	SElemType curpos;/* 跟踪位置 */
	curpos = start;/* 初始化起点 */
	SElemType *ne = (SElemType*)malloc(sizeof(SElemType));/* 储存刚出栈的元素 */
	do
	{
		if (IsAccessible(curpos))/* 当前位置可通 */
		{
			MarkFoot(curpos);/* 留下足迹 */
			DisplayPath(curpos);
			SElemType* e = (SElemType*)malloc(sizeof(SElemType));/* 分配储存空间 */
			e->x = curpos.x;
			e->y = curpos.y;
			e->derection = 1;/* 方向初值为1，可顺时针变化，即从1到4递增 */
			Push(S, e);/* 入栈，加入路径 */
			if (curpos.x == end.x&&curpos.y == end.y)/* 判断是否到达出口 */
			{
				return TRUE;
			}
			curpos.derection = 1;/* 先向东走 */
			NextPosition(&curpos);/* 更新位置 */
		}
		else/* 当前位置不可通 */
		{
			Pop(S, ne);/* 出栈 */
			DisplayPath(*ne);
			while (ne->derection == 4 && !IsEmpty(S))
			{
				NotAccessible(*ne);/* 方向为北说明四个方向都不可到达出口，标记 */
				Pop(S, ne);
				DisplayPath(*ne);
			}
			if (ne->derection < 4)
			{
				ne->derection++;/* 修改方向 */
								/*
								一定要重新创建一个结构指针来指向新的位置结构，而不能使用ne，因为
								ne只有一份存储空间，后面还涉及对ne的操作，ne只能用来暂时储存刚出栈
								的元素
								*/
				SElemType *temp = (SElemType*)malloc(sizeof(SElemType));
				*temp = *ne;
				/*重新压入栈中*/
				Push(S, temp);
				/* 更新位置 */
				NextPosition(ne);
				curpos = *ne;
			}
		}
	} while (!IsEmpty(S));
	return FALSE;
}

/* 显示路径 */
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

/* 画出迷宫 */
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

/* 产生一个迷宫所对应的二维数组 */
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

/* 设置填充色 */
void SetMazeColor() 
{
	srand((unsigned)time(NULL) + rand());/* 制作种子 */
	blockFillColor.r = 0 + (rand() % (255 + 0 - 1)) - 1;/* 产生随机位置 */
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

/* 复制一个二维数组 */
void ArrayCopy(char (*a)[DIGITCOL], char (*b)[DIGITCOL])
{
	for (int i = 0; i < DIGITROW; i++)
		for (int j = 0; j < DIGITCOL; j++)
			b[i][j] = a[i][j];
}

/* 根据天数创建数字数组 */
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

/* 根据月数创建数字数组 */
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

/* 开始寻找路径 */
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
	/* 起始位置 */
	SElemType start = { 1,2,1 };
	/* 出口位置 */
	SElemType end = { 13,14,1 };
	MazePath(start, end);
	//rectangle(LEFTMARGIN,WINDOWSHEIGHT-TOPMARGIN, WINDOWSWIDTH - RIGHTMARGIN, BOTTOMTMARGIN);
}