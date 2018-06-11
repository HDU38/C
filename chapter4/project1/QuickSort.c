#include "sortfunction.h"


int a[MAX_ARRAY_LENGTH] = { 0 };

FILE   *stream;

int main()
{
	/* 打开文件 */
	FILE *fpRead = fopen("array.txt", "r");
	/* 打开失败 */
	if (fpRead == NULL)
	{
		return FALSE;
	}

	/* 创建一个长度为一百万的数组 */
	for (int i = 0; i<1000000; i++)
	{
		fscanf(fpRead, "%d ", &a[i]);
	}

	double start, end, tcost;

	start = clock();/* 开始时间 */
	if (quicksort(a, 0, sizeof(a) / sizeof(a[0])) == 0)
	{
		return FALSE;
	}
	end = clock();/* 结束时间 */
	tcost = (double)(end - start) / CLOCKS_PER_SEC;/* 耗时 */

	printf("\n排序耗时：%lf\n", tcost);
	printf("即将遍历数组，输入任意字符继续\n");
	getchar();
	traverse(a, sizeof(a) / sizeof(a[0]));
	assert(a, sizeof(a) / sizeof(a[0]));
	system("pause");
	return TRUE;
}
