#include<stdio.h>

#define row 2
#define col 4

void cal__(double(*a))
{
	int i, j;
	double max;
	double tmp1,tmp2;
	double max_sign;
	for (i = 0; i < row; i++)
	{
		tmp1 = *(a + i*col);
		max = tmp1 > 0 ? tmp1 : -tmp1;
		max_sign = tmp1;
		for (j = 1; j < col; j++)
		{
			tmp2 = *(a + i * col + j);
			if ((tmp2 > 0 ? tmp2 : -tmp2) > max)
			{
				max = tmp2 > 0 ? tmp2 : -tmp2;
				max_sign = tmp2;
			}
		}
		for (j = 0; j < col; j++)
		{
			*(a + i * col + j) = *(a + i * col + j) / max_sign;
		}
	}
}

int main810()
{
	double a[row][col] = {
		{1.3,-1.6,1.4,-1.5},
		{4.3,-3.6,2.4,-5.5}
	};
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			printf("%0.2f ", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	cal__(a);
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			printf("%0.2f ", a[i][j]);
		}
		printf("\n");
	}
	getchar();
	return 0;
}