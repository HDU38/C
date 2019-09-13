#include "MazeDataStruct.h"

/* 标记已走的路 */
void MarkFoot(SElemType curpos)
{
	maze[curpos.x][curpos.y] = '#';
}

/* 标记不可到达出口的位置*/
void NotAccessible(SElemType curpos)
{
	maze[curpos.x][curpos.y] = '!';
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
	if (maze[curpos.x][curpos.y] == ' ')
		return TRUE;
	else
		return FALSE;
}

/* 寻找迷宫路径 */
Status MazePath(SElemType start, SElemType end)
{
	SElemType curpos;/* 跟踪位置 */
	LinkStack S = (LinkStack)malloc(sizeof(StackNode));/* 分配空间 */
	SElemType *ne = (SElemType*)malloc(sizeof(SElemType));/* 储存刚出栈的元素 */
	SElemType *e = NULL;/* 将要入栈的元素 */
	SElemType *temp = NULL;/* 临时结点 */

	InitStack(S);/* 创建一个空栈 */
	curpos = start;/* 初始化起点 */

	do
	{
		if (IsAccessible(curpos)==TRUE)/* 当前位置可通 */
		{
			MarkFoot(curpos);/* 留下足迹 */
			e = (SElemType*)malloc(sizeof(SElemType));/* 分配储存空间 */
			e->x = curpos.x;
			e->y = curpos.y;
			e->derection = 1;/* 方向初值为1，可顺时针变化，即从1到4递增 */
			Push(S, e);/* 入栈，加入路径 */
			if (curpos.x == end.x&&curpos.y == end.y)/* 判断是否到达出口 */
			{
				printf("\n路径为:\n");
				DisplayPath();
				return TRUE;
			}
			curpos.derection = 1;/* 先向东走 */
			NextPosition(&curpos);/* 更新位置 */
		}
		else/* 当前位置不可通 */
		{
			Pop(S, ne);/* 出栈 */
			while (ne->derection == 4 && !IsEmpty(S))
			{
				NotAccessible(*ne);/* 方向为北说明四个方向都不可到达出口，标记 */
				Pop(S, ne);
			}
			if (ne->derection < 4)
			{
				ne->derection++;/* 修改方向 */
				/*
				一定要重新创建一个结构指针来指向新的位置结构，而不能使用ne，因为
				ne只有一份存储空间，后面还涉及对ne的操作，ne只能用来暂时储存刚出栈
				的元素
				*/
				temp = (SElemType*)malloc(sizeof(SElemType));
				*temp = *ne;
				/*重新压入栈中*/
				Push(S, temp);
				/* 更新位置 */
				NextPosition(ne);
				curpos = *ne;
			}
		}
	} while (IsEmpty(S)==FALSE);
	return FALSE;
}

/* 显示路径 */
void DisplayPath(void)
{
	int i, j;
	for (i = 0; i < MAZEROWNUM; i++)
	{
		for (j = 0; j < MAZEROWNUM; j++)
		{
			if (maze[i][j] != '!')
			{
				printf("%c", maze[i][j]);
			}
			else
				printf(" ");

		}
		printf("\n");
	}
}