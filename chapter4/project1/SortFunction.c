#include<stdio.h>
#include "SortFunction.h"

/* ����Ԫ�� */
int swap(int *pa, int *pb)
{
	if (pa == NULL || pb == NULL)
	{
		printf("����ʧ��");
		return FALSE;
	}
	int temp;
	temp = *pa;
	*pa = *pb;
	*pb = temp;
	return TRUE;
}

/* ��������,aΪ�����һ��Ԫ�ص�ָ��,lengthΪ���鳤�� */
int traverse(int *pa, int length)
{
	if (pa == NULL)
	{
		printf("����ָ�봫��ʧ��");
		return FALSE;
	}
	int i;
	for (i = 0; i < length; i++)
		printf("%d ", *(pa + i));
	return TRUE;
}

/* 
��������,aΪ�����һ��Ԫ�ص�ָ�룬loΪ����
��Ԫ�ص������±�,hiΪ���ҵ�Ԫ�ص������±� 
*/
int quicksort(int *pa, int lo, int hi)
{
	/*
	���з�Ԫ��ǡ������������Ҵ�ʱ,lo�����hi�������б�ֻ��һ��Ԫ��ʱ��lo=hi��
	��Щ�������Ӧ��ִ������
	*/
	if (pa == NULL)
	{
		printf("���鴫��ʧ��");
		return FALSE;
	}

	if (lo >= hi)
	{
		return TRUE;
	};

	/*i �������Ԫ�ص�λ�ã�j�����ұ�Ԫ�ص�λ��*/
	int i = lo;
	int j = hi + 1;


	/* �з�Ԫ�ص�ֵ */
	int temp = *(pa + lo);

	while (TRUE)
	{
		/* ������ߵ�Ԫ�أ����ǡ����һ���������У���������ֱ���˳�ѭ�� */
		while (pa[++i] < temp)
			if (i == hi)
				break;

		/* �����ұߵ�Ԫ�أ����ǡ����һ���������У���������ֱ���˳�ѭ�� */
		while (pa[--j] > temp)
			if (j == lo)
				break;

		/* ��i>=j ˵���зֽ��� */
		if (i >= j)
			break;

		/* �������д����з�Ԫ�ص�ֵ���ұ���С���з�Ԫ�ص�ֵ���򽻻� */
		swap(pa + i, pa + j);
	}

	/* �зֽ�����temp��λ */

	swap(pa + lo, pa + j);

	/* �з���ߵ����� */

	quicksort(pa, lo, j - 1);

	/* �з��ұߵ����� */

	quicksort(pa, j + 1, hi);

	return TRUE;

}

/* ����Ƿ�����ɹ�,aΪ�����һ��Ԫ�ص�ָ��,lengthΪ���鳤�� */
int assert(int *pa, int length)
{
	int i = 0;
	if (pa == NULL)
	{
		printf("���鴫��ʧ��");
		return FALSE;
	}
	while (*(pa + i) <= *(pa + i + 1) && i<length - 1)
	{
		i++;
	}
	/* i�����������һ��Ԫ�ص��±�˵������ɹ� */
	if (i == length - 1)
	{
		printf("\nsorted successfully\n");
		printf("array length=%d\n", length);
		return TRUE;
	}
	/* ��֮����ʧ�� */
	else
	{
		printf("\nsorted failed");
		printf("\n%d", i);
		printf("\n%d,%d,%d", *(pa + i - 1), *(pa + i), *(pa + i + 1));
		return FALSE;
	}
}