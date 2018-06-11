#include "sortfunction.h"


int a[MAX_ARRAY_LENGTH] = { 0 };

FILE   *stream;

int main()
{
	/* ���ļ� */
	FILE *fpRead = fopen("array.txt", "r");
	/* ��ʧ�� */
	if (fpRead == NULL)
	{
		return FALSE;
	}

	/* ����һ������Ϊһ��������� */
	for (int i = 0; i<1000000; i++)
	{
		fscanf(fpRead, "%d ", &a[i]);
	}

	double start, end, tcost;

	start = clock();/* ��ʼʱ�� */
	if (quicksort(a, 0, sizeof(a) / sizeof(a[0])) == 0)
	{
		return FALSE;
	}
	end = clock();/* ����ʱ�� */
	tcost = (double)(end - start) / CLOCKS_PER_SEC;/* ��ʱ */

	printf("\n�����ʱ��%lf\n", tcost);
	printf("�����������飬���������ַ�����\n");
	getchar();
	traverse(a, sizeof(a) / sizeof(a[0]));
	assert(a, sizeof(a) / sizeof(a[0]));
	system("pause");
	return TRUE;
}
