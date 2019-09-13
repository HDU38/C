#include<stdio.h>
#include<stdlib.h>

int main52()
{
	int num, i, sum = 0;
	printf("请输入一个小于9位数的数\n");
	while (1)
	{
		scanf("%d", &num);
		for (i = 1; i < 10; i++)
		{
			sum += num % 10;
			num = num / 10;
			if (!num)
			{
				printf("%d\n", sum);
				break;
			}
		}
		sum = 0;
	}
	return 0;
}
