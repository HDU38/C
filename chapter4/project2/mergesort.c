#include "MergeSort.h"

int TO_BE_SORTED_ARRAY[MAX_ARRAY_LENGTH];/* 待排序的数组 */
FILE   *stream;
int main()
{
	int i;
	double start, end, tcost;

	/* 打开文件 */
	FILE *fpRead = fopen("array.txt", "r");
	/* 打开失败 */
	if (fpRead == NULL)
	{
		return FALSE;
	}
	/* 创建一个数组 */
	for (i = 0; i<MAX_ARRAY_LENGTH; i++)
	{
		fscanf(fpRead, "%d ", &TO_BE_SORTED_ARRAY[i]);
	}
	start = clock();/* 开始时间 */
	printf("--------排序中---------\n");
	if (mergeSort(TO_BE_SORTED_ARRAY, 0, sizeof(TO_BE_SORTED_ARRAY) / sizeof(TO_BE_SORTED_ARRAY[0])-1) == 0)
	{
		return FALSE;
	}
	end = clock();/* 结束时间 */
	tcost = (double)(end - start) / CLOCKS_PER_SEC;/* 耗时 */
	printf("\n排序耗时：%lf\n", tcost);
	printf("即将遍历数组，输入任意字符继续\n");
	getchar();
	traverse(TO_BE_SORTED_ARRAY, sizeof(TO_BE_SORTED_ARRAY) / sizeof(TO_BE_SORTED_ARRAY[0]));
	assert(TO_BE_SORTED_ARRAY, sizeof(TO_BE_SORTED_ARRAY) / sizeof(TO_BE_SORTED_ARRAY[0]));
	system("pause");
	return TRUE;
}