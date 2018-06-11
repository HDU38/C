#include<stdio.h>
#include<stdlib.h>

void split(int n, int k);
void output(int *pArray);
int arrayLength(int *pArray);

int result[100] = { 0 };/* 储存划分后得到的整数 */
int num = 0;/* 待划分的数 */

int main()
{
	int k;
	printf("请输入要划分的整数（小于等于100）:");
	scanf("%d", &num);
	result[0] = num;
	for (k = 2; k <= num; k++)
		split(num, k);
	system("pause");
	return 0;
}

/* 将整数n划分为k个整数的和 */
void split(int n, int k)
{
	int i;
	if (k == 1)
		output(result);/* 输出结果 */
	for (i = 1; 2 * i <= n; i++)
	{
		if (i < result[arrayLength(result) - 2])/* 保持划分数的递增性 */
			continue;
		result[arrayLength(result) - 1] = i;/* 先将最后一个数划分为两个数 */
		result[arrayLength(result)] = n - i;
		split(n - i, k - 1);/* 分解倒数第一个数 */
		result[arrayLength(result) - 2] = n;/* 恢复为数组之前的状态 */
		result[arrayLength(result) - 1] = 0;/* 准备下一轮划分 */
	}

}

/* 输出划分结果 */
void output(int *pArray)
{
	int i = 0;
	printf("%d=",num);
	while (pArray[i] != 0)
	{
		printf("%d", pArray[i++]);
		if(pArray[i] != 0)/* 不是最后一个数就在输出的整数后输出加号 */
			printf("+");
	}
	printf("\n");
}

/* 输出数组长度 */
int arrayLength(int *pArray)
{
	int length = 0;
	while (pArray[length] != 0)
		length++;
	return length;
}

