#include<stdio.h>

int judge(int num)

{

	int j, sum = 0;

	for (j = 2; j < num; j++)

	{

		if (num % j == 0) sum += j; /* jÊÇÒò×Ó */

	}

	return sum + 1 == num ? 1 : 0;



}

int main()
{
	int num;
	while (1)
	{
		scanf("%d", &num);

		printf("%d\n", judge(num));
	}

	return 0;

}

