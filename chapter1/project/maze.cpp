#include<stdlib.h>
#include "CommonData.h"

int main(void)
{
	/* 显示迷宫 */
	for (int i = 0; i<MAZEROWNUM; i++)
	{
		for (int j = 0; j < MAZEROWNUM; j++)
		{
			printf("%c", maze[i][j]);
		}
		printf("\n");
	}
	/* 起始位置 */
	SElemType start = { 1,1,1 };
	/* 出口位置 */
	SElemType end = { 16,16,1 };
	MazePath(start, end);
	system("pause");
	return TRUE;
}
