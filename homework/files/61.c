#include <stdio.h>

#include <math.h>

int main61()

{

	int a[10] = { -2,5,9,1,-15,-20,10,-13,8,7 };

	int i, j;

	double sum = 0, average = 0;

	double deta_x = 1000, temp;

	for (i = 0; i < 10; i++)

	{

		sum += a[i];

	}

	average = (double)sum / 10.0;

	for (i = 0; i < 10; i++)

	{

		temp = abs((double)a[i] - average);

		if (temp < deta_x)

		{

			deta_x = temp;

			j = i;

		}

	}

	printf("平均值v是%f,与v相差最小的数组元素为a[%d]=%d", average, j, a[j]);

	getch();

	return 0;

}

