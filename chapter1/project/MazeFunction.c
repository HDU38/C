#include "MazeDataStruct.h"

/* ������ߵ�· */
void MarkFoot(SElemType curpos)
{
	maze[curpos.x][curpos.y] = '#';
}

/* ��ǲ��ɵ�����ڵ�λ��*/
void NotAccessible(SElemType curpos)
{
	maze[curpos.x][curpos.y] = '!';
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
	if (maze[curpos.x][curpos.y] == ' ')
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
			SElemType* e = (SElemType*)malloc(sizeof(SElemType));/* ���䴢��ռ� */
			e->x = curpos.x;
			e->y = curpos.y;
			e->derection = 1;/* �����ֵΪ1����˳ʱ��仯������1��4���� */
			Push(S, e);/* ��ջ������·�� */
			if (curpos.x == end.x&&curpos.y == end.y)/* �ж��Ƿ񵽴���� */
			{
				printf("\n·��Ϊ:\n");
				DisplayPath();
				return TRUE;
			}
			curpos.derection = 1;/* ������ */
			NextPosition(&curpos);/* ����λ�� */
		}
		else/* ��ǰλ�ò���ͨ */
		{
			Pop(S, ne);/* ��ջ */
			while (ne->derection == 4 && !IsEmpty(S))
			{
				NotAccessible(*ne);/* ����Ϊ��˵���ĸ����򶼲��ɵ�����ڣ���� */
				Pop(S, ne);
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
void DisplayPath(void)
{
	for (int i = 0; i < MAZEROWNUM; i++)
	{
		for (int j = 0; j < MAZEROWNUM; j++)
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