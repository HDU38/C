#include<stdio.h>
#include<stdlib.h>

#define MAXLENGTH 1000

void insertSort(int *, int);
void swap(int *, int *);

int main()
{
	int a[] = { 1,2,3,8,9,10,4,3,8,98,23,4,5,6,2,3,4,5,6,7 };
	int k;
	/* δ����ǰ����һ������ */
	for (k = 0; k<sizeof(a)/sizeof(a[0]); k++)
		printf("%d ", *(a + k));
	printf("\n");
	insertSort(a,sizeof(a)/sizeof(a[0]));
	system("pause");
	return 0;
}

/* ��������,aΪ�����һ��Ԫ�ص�ָ��,lengthΪ���鳤�� */
void insertSort(int *a, int length)
{
	int i, k;
	if (a == NULL)
	{
		printf("����ָ�봫��ʧ��");
		return;
	}

	/* �ӵڶ���Ԫ�ر��������һ��Ԫ�� */
	for (i = 1; i<length; i++)
	{
		int j;
		/* 
		�ӵ�i��Ԫ�ر������ڶ���Ԫ�أ��������
		��Ԫ�ش���ǰ���Ԫ���򽻻�����Ϊiǰ��
		��Ԫ���Ѿ��������ֻ�轻�������ǰ
		����Ԫ�� 
		*/
		for (j = i; j>0 && (a[j]<a[j - 1]); j--)
			swap(a + j, a + j - 1);
	}
	/* ������ϣ�����һ������ */
	for (k = 0; k<length; k++)
		printf("%d ", a[k]);
	printf("\n");
}

/*������ֵ */
void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}