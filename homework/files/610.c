#include<stdio.h>
#define MAX 6
int g_status = 0;

int main610()
{
	int matrix[5][5] = { {5,3,2,4,0}, {2,3,5,0,4}, {0,4,8,4,5}, {9,3,5,10,4}, {3,4,4,4,3} };
	int n = sizeof(matrix[0]) / sizeof(matrix[0][0]);
	int value[MAX];
	int index_c[MAX] = { 0 };
	int i, j, k;
	for (i = 0; i < n; i++) 
	{
		value[i] = matrix[i][0];
		for (j = 1; j < n; j++) 
		{
			if (matrix[i][j] > value[i])
			{
				value[i] = matrix[i][j];/* ���ֵ*/
				index_c[i] = j;/* ���ֵ������ */
			}
		}
	}
	for (k = 0; k < n; k++) 
	{
		j = index_c[k];/* ��k�����ֵ������ */
		for (i = 0; i < n; i++) 
		{
			if (matrix[i][j] < value[k]) break;
		}
		if (i == n)
		{
			g_status = 1;
			printf("�ҵ�����A[%d][%d]=%d\n", k, j, value[k]);
		}
	}
	if(!g_status) printf("δ�ҵ�����\n");
	getchar();
	return 0;
}