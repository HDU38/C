#include<stdlib.h>
#include "CommonData.h"

int main(void)
{
	/* ��ʾ�Թ� */
	for (int i = 0; i<MAZEROWNUM; i++)
	{
		for (int j = 0; j < MAZEROWNUM; j++)
		{
			printf("%c", maze[i][j]);
		}
		printf("\n");
	}
	/* ��ʼλ�� */
	SElemType start = { 1,1,1 };
	/* ����λ�� */
	SElemType end = { 16,16,1 };
	MazePath(start, end);
	system("pause");
	return TRUE;
}
