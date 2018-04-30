#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "shuffle.h"

int main(void)
{
	int a[MAX] = { 0 };
	/* ����һ����1��52���е����� */
	int i;
	for (i = 0; i < 52; i++)
	{
		a[i] = i + 1;
	}
	/* ����һ������*/
	traverse(a, sizeof(a) / sizeof(a[0]));
	printf("\n");
	/* �������� */
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
				min = j;/* Ѱ����Сֵ */
		srand((unsigned)time(NULL) + rand());/* �������� */
		pos = MIN + (rand() % (MAX + MIN - 1))-1;/* �������λ�� */
		swap(a + pos, a + min);/* ����λ�� */
	}
}

/* ������ֵ */
void swap(int *pa, int *pb)
{
	int temp;
	temp = *pa;
	*pa = *pb;
	*pb = temp;
}

/* �������� */
void traverse(int *parray, int length)
{
	int i;
	for (i = 0; i < length; i++)
		printf("%d ", *(parray + i));
	printf("\n");
}