#include<stdlib.h>
#include "MazeDataStruct.h"

int main(void)
{
	int i, j;
	/* ��ʼλ�� */
	SElemType start = { 1,1,1 };
	/* ����λ�� */
	SElemType end = { 16,16,1 };
	/* ��ʾ�Թ� */
	for (i = 0; i<MAZEROWNUM; i++)
	{
		for (j = 0; j < MAZEROWNUM; j++)
		{
			printf("%c", maze[i][j]);
		}
		printf("\n");
	}
	MazePath(start, end);
	system("pause");
	return TRUE;
}
