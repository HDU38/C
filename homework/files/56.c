#include<stdio.h>

#include<stdlib.h>



int day_sum[12] = { 0,31,28,31,30,31,30,31,31,30,31,30 };

int getDay(int year, int month, int day)

{

	int result = day, i;

	for (i = 0; i<month; i++)

	{

		result += day_sum[i];

	}

	/* 是闰年且月份大于二，加一天 */

	if (month > 2 && (year % 4 == 0 && year % 100 != 0 || year % 400 == 0))

	{

		result++;

	}

	return result;

}

int main56()

{

	int year, month, day;

	while (1)

	{

		scanf("%d %d %d", &year, &month, &day);

		printf("%d\n", getDay(year, month, day));

	}

	return 0;

}

