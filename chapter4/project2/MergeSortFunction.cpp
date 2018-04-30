#include "MergeSort.h"
int TEMP[MAX_ARRAY_LENGTH];/* �������� */

/* 
������a��ֵ���Ƶ�����b��,paΪ�����һ��
Ԫ�ص�ָ��,pbΪ������ 
*/
int copyArray(int *pa, int length, int *pb)
{
	int i;
	if (pa == NULL || pb == NULL)
	{
		printf("����ָ�봫��ʧ��");
		return FALSE;
	}
	for (i = 0; i<length; i++)
	{
		*(pb + i) = *(pa + i);
	}
	return TRUE;
}

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

/* 
�鲢��������,paΪ�����һ��Ԫ�ص�ָ��,loΪ��
С�±�,hiΪ��������±꣬midΪ�м�Ԫ�ص��±�
*/
int mergeArray(int *pa, int lo, int mid, int hi)
{
	if (pa == NULL)
	{
		printf("����ָ�봫��ʧ��\n�鲢ʧ��!\n");
		return FALSE;
	}
	/* ���������(a[lo...mid])���ұ�����(a[mid+1]...hi)�鲢 */
	int i = lo;
	int j = mid + 1;
	int k;
	/* 
	��������,һ��Ҫ�ڸú����ڸ��ƣ���Ϊÿ
	�ι鲢��Ҫʹ��һ���µ����鸱����������
	ÿ�ι鲢����ͬһ��������������ⲿ����
	���ǹ鲢ʱ������������ֵ�ͻ�ı䣬��
	���������Ŀ�� 
	*/
	if (copyArray(pa, hi+1, TEMP) == FALSE)
	{
		printf("���鸴��ʧ��");
		return FALSE;
	}
	for (k = lo; k <= hi; k++)
	{
		/* ���ȫ���鲢��� */
		if (i>mid)
			*(pa + k) = TEMP[j++];
		/* �ұ�ȫ���鲢��� */
		else if (j>hi)
			*(pa + k) = TEMP[i++];
		/* �ұ�С����� */
		else if (*(TEMP + j)<*(TEMP + i))
			*(pa + k) = TEMP[j++];
		/* ���С���ұ� */
		else
			*(pa + k) = TEMP[i++];
	}
	return TRUE;
}

/* �鲢����,paΪ�����һ��Ԫ�ص�ָ��,loΪ��
С�±�,hiΪ��������±� */
int mergeSort(int *pa, int lo, int hi)
{
	if (hi <= lo)
		return TRUE;
	int mid = (lo+hi) / 2;/* �м��±� */
	mergeSort(pa, lo, mid);/* ������� */
	mergeSort(pa, mid + 1, hi);/* �����ұ� */
	mergeArray(pa, lo, mid, hi);/* �鲢�������� */
	return TRUE;
}

/* ��������,paΪ�����һ��Ԫ�ص�ָ��,lengthΪ���鳤�� */
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