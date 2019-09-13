#include<stdio.h>

int main64()
{
	int cow[10000] = { 0 };
	int i, j = 0;
	int cow_sum = 1;/* 母牛头数 */
	cow[0] = 3;/* 大于等于3表示有生殖能力 */
	for (i = 0; i < 20; i++)
	{
	
		while (j < cow_sum && cow[j++] >= 3)
			cow_sum++;
		printf("第%d年有%d头母牛\n", i + 1, cow_sum);
		for (j = 0; j < cow_sum; j++) cow[j]++;/* 所有母牛加一岁 */
		j = 0;
	}
	getchar();
	return 0;
}

