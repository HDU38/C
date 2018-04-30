#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "shuffle.h"

int main(void)
{
	int a[MAX] = { 0 };
	/* 创建一个从1到52排列的数组 */
	int i;
	for (i = 0; i < 52; i++)
	{
		a[i] = i + 1;
	}
	/* 遍历一遍数组*/
	traverse(a, sizeof(a) / sizeof(a[0]));
	printf("\n");
	/* 打乱数组 */
	selectShuffle(a, 0, sizeof(a) / sizeof(a[0]));
	traverse(a, sizeof(a) / sizeof(a[0]));
	system("pause");
	return 0;
}

void selectShuffle(int *a, int lo, int hi)
{
	int i;
	int pos;
	for (i = 0; i < hi; i++)
	{
		int min = i;
		int j;
		for (j = i + 1; j < hi; j++)
			if (a[j] < a[min])
				min = j;/* 寻找最小值 */
		srand((unsigned)time(NULL) + rand());/* 制作种子 */
		pos = MIN + (rand() % (MAX + MIN - 1))-1;/* 产生随机位置 */
		swap(a + pos, a + min);/* 交换位置 */
	}
}

/* 交换数值 */
void swap(int *pa, int *pb)
{
	int temp;
	temp = *pa;
	*pa = *pb;
	*pb = temp;
}

/* 遍历数组 */
void traverse(int *parray, int length)
{
	int i;
	for (i = 0; i < length; i++)
		printf("%d ", *(parray + i));
	printf("\n");
}