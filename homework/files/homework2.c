#include<stdio.h>

#define STUDENT_NUM  30
#define COURSE_NUM 4

int g_sumScore[STUDENT_NUM] = { 0 };
double g_averageScore[STUDENT_NUM] = { 0 };
int g_studentScore[STUDENT_NUM][COURSE_NUM] = { 0 };

void input()
{
	int i, j;
	for (i = 0; i < STUDENT_NUM; i++)
	{
		for (j = 0; j < COURSE_NUM; j++)
		{
			scanf("%d", &g_studentScore[i][j]);
		}
	}
}
void process()
{
	int i, j;
	for (i = 0; i < STUDENT_NUM; i++)
	{
		for (j = 0; j < COURSE_NUM; j++)
		{
			g_sumScore[i] += g_studentScore[i][j];
		}
		g_averageScore[i] = (double)g_sumScore[i] / (double)COURSE_NUM;
	}
}
void output()
{
	int i;
	printf("学号  科目一  科目二  科目三  科目四    总分    平均分\n");
	for (i = 0; i < STUDENT_NUM; i++)
	{
		if (i < 9)
		{
			printf("%d     %d       %d       %d       %d       %d       %0.2f \n",
				i + 1, g_studentScore[i][0], g_studentScore[i][1], g_studentScore[i][2], g_studentScore[i][3],
				g_sumScore[i], g_averageScore[i]);
		}
		else
		{
			printf("%d    %d       %d       %d       %d       %d       %0.2f \n",
				i + 1, g_studentScore[i][0], g_studentScore[i][1], g_studentScore[i][2], g_studentScore[i][3],
				g_sumScore[i], g_averageScore[i]);
		}
	}
}
int mainhomework2()
{
	input();
	process();
	output();
	getch();
	return 0;
}