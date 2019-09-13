#include<stdlib.h>
#include "MazeDataStruct.h"

int main(void)
{
	int i, j;
	/* 起始位置 */
	SElemType start = { 1,1,1 };
	/* 出口位置 */
	SElemType end = { 16,16,1 };
	/* 显示迷宫 */
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
