#include "MergeSort.h"
int TEMP[MAX_ARRAY_LENGTH];/* 复制数组 */

/* 
将数组a的值复制到数组b中,pa为数组第一个
元素的指针,pb为空数组 
*/
int copyArray(int *pa, int length, int *pb)
{
	int i;
	if (pa == NULL || pb == NULL)
	{
		printf("数组指针传入失败");
		return FALSE;
	}
	for (i = 0; i<length; i++)
	{
		*(pb + i) = *(pa + i);
	}
	return TRUE;
}

/* 交换元素 */
int swap(int *pa, int *pb)
{
	if (pa == NULL || pb == NULL)
	{
		printf("交换失败");
		return FALSE;
	}
	int temp;
	temp = *pa;
	*pa = *pb;
	*pb = temp;
	return TRUE;
}

/* 
归并两个数组,pa为数组第一个元素的指针,lo为最
小下标,hi为数组最大下标，mid为中间元素的下标
*/
int mergeArray(int *pa, int lo, int mid, int hi)
{
	if (pa == NULL)
	{
		printf("数组指针传入失败\n归并失败!\n");
		return FALSE;
	}
	/* 将左边数组(a[lo...mid])和右边数组(a[mid+1]...hi)归并 */
	int i = lo;
	int j = mid + 1;
	int k;
	/* 
	复制数组,一定要在该函数内复制，因为每
	次归并都要使用一个新的数组副本，而不是
	每次归并都用同一个副本，如果在外部复制
	，那归并时待排序的数组的值就会改变，达
	不到排序的目的 
	*/
	if (copyArray(pa, hi+1, TEMP) == FALSE)
	{
		printf("数组复制失败");
		return FALSE;
	}
	for (k = lo; k <= hi; k++)
	{
		/* 左边全部归并完毕 */
		if (i>mid)
			*(pa + k) = TEMP[j++];
		/* 右边全部归并完毕 */
		else if (j>hi)
			*(pa + k) = TEMP[i++];
		/* 右边小于左边 */
		else if (*(TEMP + j)<*(TEMP + i))
			*(pa + k) = TEMP[j++];
		/* 左边小于右边 */
		else
			*(pa + k) = TEMP[i++];
	}
	return TRUE;
}

/* 归并排序,pa为数组第一个元素的指针,lo为最
小下标,hi为数组最大下标 */
int mergeSort(int *pa, int lo, int hi)
{
	if (hi <= lo)
		return TRUE;
	int mid = (lo+hi) / 2;/* 中间下标 */
	mergeSort(pa, lo, mid);/* 排序左边 */
	mergeSort(pa, mid + 1, hi);/* 排序右边 */
	mergeArray(pa, lo, mid, hi);/* 归并左右两边 */
	return TRUE;
}

/* 遍历数组,pa为数组第一个元素的指针,length为数组长度 */
int traverse(int *pa, int length)
{
	if (pa == NULL)
	{
		printf("数组指针传入失败");
		return FALSE;
	}
	int i;
	for (i = 0; i < length; i++)
		printf("%d ", *(pa + i));
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