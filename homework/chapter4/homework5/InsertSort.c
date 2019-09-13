#include<stdio.h>
#include<stdlib.h>

#define MAXLENGTH 1000

void insertSort(int *, int);
void swap(int *, int *);

int main()
{
	int a[] = { 1,2,3,8,9,10,4,3,8,98,23,4,5,6,2,3,4,5,6,7 };
	int k;
	/* 未排序前遍历一遍数组 */
	for (k = 0; k<sizeof(a)/sizeof(a[0]); k++)
		printf("%d ", *(a + k));
	printf("\n");
	insertSort(a,sizeof(a)/sizeof(a[0]));
	system("pause");
	return 0;
}

/* 插入排序,a为数组第一个元素的指针,length为数组长度 */
void insertSort(int *a, int length)
{
	int i, k;
	if (a == NULL)
	{
		printf("数组指针传入失败");
		return;
	}

	/* 从第二个元素遍历到最后一个元素 */
	for (i = 1; i<length; i++)
	{
		int j;
		/* 
		从第i个元素遍历到第二个元素，如果后面
		的元素大于前面的元素则交换，因为i前面
		的元素已经有序，因此只需交换后面比前
		面大的元素 
		*/
		for (j = i; j>0 && (a[j]<a[j - 1]); j--)
			swap(a + j, a + j - 1);
	}
	/* 排序完毕，遍历一遍数组 */
	for (k = 0; k<length; k++)
		printf("%d ", a[k]);
	printf("\n");
}

/*交换数值 */
void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}