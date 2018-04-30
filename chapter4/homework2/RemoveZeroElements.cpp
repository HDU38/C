#include<stdio.h>
#include<stdlib.h>

int RemoveZeroElements(int *pScores, int nScores);

int main(void)
{
	/* 数组长度 */
	int nScores;
	int scores[13] = { 65,0,95,0,0,79,82,0,84,94,86,90,0 };
	int i;

	/* 未删除前先遍历一次 */
	printf("scores为:");
	for (i = 0; i < sizeof(scores) / sizeof(scores)[0]; i++)
		printf("%d ", scores[i]);
	printf("\n长度nScores为%d\n", sizeof(scores) / sizeof(scores[0]));

	/* 删除0元素之后 */
	nScores = RemoveZeroElements(scores, sizeof(scores) / sizeof(scores[0]));
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
	return 0;
}

/* 移除数组中值为0的元素，并返回有效长度，scores为数组指针，nScores为数组原本长度 */
int RemoveZeroElements(int *pScores, int nScores)
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
		if (*(pScores + i) == 0)
		{
			int j;
			for (j = i; j < nScores-1; j++)
			{
				/* 0之后的元素前移 */
				*(pScores + j) = *(pScores + j + 1);
			}
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