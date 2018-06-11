#include<stdio.h>
#include<stdlib.h>

int RemoveDuplicates(int *pScores, int nScores);

int main(void)
{
	/* 数组长度 */
	int nScores;
	int scores[] = { 65,72,75,79,82,82,84,84,84,86,90,94,95 };
	int i;

	/* 未删除前先遍历一次 */
	printf("scores为:");
	for (i = 0; i < sizeof(scores) / sizeof(scores)[0]; i++)
		printf("%d ", scores[i]);
	printf("\n长度nScores为%d\n", sizeof(scores) / sizeof(scores[0]));

	/* 删除重复元素之后 */
	nScores = RemoveDuplicates(scores, sizeof(scores) / sizeof(scores[0]));

	if (nScores != 0)
	{
		printf("scores为:");
		for (int i = 0; i < nScores; i++)
		{
			printf("%d ", scores[i]);
		}
		printf("\n有效长度nScores为%d\n", nScores);
	}
	else
	{
		printf("数组有效长度为0或函数调用失败");
	}
	system("pause");
}
int RemoveDuplicates(int *pScores, int nScores)
{
	int i;
	int count = 0;/* 记录有效长度 */
	if (pScores == NULL)
	{
		printf("指针传入失败");
		return 0;
	}
	for (i = 0; i<nScores; i++)//遍历所有元素
	{
		count++;
		if (*(pScores + i) == *(pScores+i+1))
		{
			int j;
			for (j = i; j < nScores - 1; j++)
			{
				*(pScores + j) = *(pScores + j + 1);/* 多余的元素后移*/
			}
			/* 给多余的元素赋值为0 */
			*(pScores + j)=0;
			/* 数组长度减小 */
			nScores--;
			/* 有效长度减小 */
			count--;
			/* 回退一格，这步很关键*/
			i--;
		}
	}
	/* 返回有效长度 */
	return count;
}