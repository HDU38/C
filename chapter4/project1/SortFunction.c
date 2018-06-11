#include "SortFunction.h"

/* 交换元素 */
int swap(int *pa, int *pb)
{
	int temp;
	if (pa == NULL || pb == NULL)
	{
		printf("交换失败");
		return FALSE;
	}
	temp = *pa;
	*pa = *pb;
	*pb = temp;
	return TRUE;
}

/* 遍历数组,a为数组第一个元素的指针,length为数组长度 */
int traverse(int *pa, int length)
{
	int i;
	if (pa == NULL)
	{
		printf("数组指针传入失败");
		return FALSE;
	}
	for (i = 0; i < length; i++)
		printf("%d ", *(pa + i));
	return TRUE;
}

/* 
*  快速排序,a为数组第一个元素的指针，lo为最左
*  的元素的数组下标,hi为最右的元素的数组下标 
*/
int quicksort(int *pa, int lo, int hi)
{
	/*i 跟踪左边元素的位置，j跟踪右边元素的位置*/
	int i = lo;
	int j = hi + 1;
	int temp = 0;
	/*
	* 当切分元素恰好在最左或最右处时,lo会大于hi，当子列表只有一个元素时，lo=hi，
	*  这些情况都不应该执行排序
	*/
	if (pa == NULL)
	{
		printf("数组传入失败");
		return FALSE;
	}

	if (lo >= hi)
	{
		return TRUE;
	};

	/* 切分元素的值 */
	temp = *(pa + lo);

	while (TRUE)
	{
		/* 遍历左边的元素，如果恰好是一个递增序列，则不用排序，直接退出循环 */
		while (pa[++i] < temp)
			if (i == hi)
				break;

		/* 遍历右边的元素，如果恰好是一个递增序列，则不用排序，直接退出循环 */
		while (pa[--j] > temp)
			if (j == lo)
				break;

		/* 当i>=j 说明切分结束 */
		if (i >= j)
			break;

		/* 如果左边有大于切分元素的值或右边有小于切分元素的值，则交换 */
		swap(pa + i, pa + j);
	}

	/* 切分结束，temp归位 */
	swap(pa + lo, pa + j);

	/* 切分左边的数组 */
	quicksort(pa, lo, j - 1);

	/* 切分右边的数组 */
	quicksort(pa, j + 1, hi);

	return TRUE;

}
/* 检测是否排序成功,a为数组第一个元素的指针,length为数组长度 */
int assert(int *pa, int length)
{
	int i = 0;
	if (pa == NULL)
	{
		printf("数组传入失败");
		return FALSE;
	}
	while (*(pa + i) <= *(pa + i + 1) && i<length - 1)
	{
		i++;
	}
	/* i等于数组最后一个元素的下标说明排序成功 */
	if (i == length - 1)
	{
		printf("\nsorted successfully\n");
		printf("array length=%d\n", length);
		return TRUE;
	}
	/* 反之排序失败 */
	else
	{
		printf("\nsorted failed");
		printf("\n%d", i);
		printf("\n%d,%d,%d", *(pa + i - 1), *(pa + i), *(pa + i + 1));
		return FALSE;
	}
}