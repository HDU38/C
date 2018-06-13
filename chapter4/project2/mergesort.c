#include "MergeSort.h"

int TO_BE_SORTED_ARRAY[MAX_ARRAY_LENGTH];/* ����������� */
FILE   *stream;
int main()
{
	int i;
	double start, end, tcost;

	/* ���ļ� */
	FILE *fpRead = fopen("array.txt", "r");
	/* ��ʧ�� */
	if (fpRead == NULL)
	{
		return FALSE;
	}
	/* ����һ������ */
	for (i = 0; i<MAX_ARRAY_LENGTH; i++)
	{
		fscanf(fpRead, "%d ", &TO_BE_SORTED_ARRAY[i]);
	}
	start = clock();/* ��ʼʱ�� */
	printf("--------������---------\n");
	if (mergeSort(TO_BE_SORTED_ARRAY, 0, sizeof(TO_BE_SORTED_ARRAY) / sizeof(TO_BE_SORTED_ARRAY[0])-1) == 0)
	{
		return FALSE;
	}
	end = clock();/* ����ʱ�� */
	tcost = (double)(end - start) / CLOCKS_PER_SEC;/* ��ʱ */
	printf("\n�����ʱ��%lf\n", tcost);
	printf("�����������飬���������ַ�����\n");
	getchar();
	traverse(TO_BE_SORTED_ARRAY, sizeof(TO_BE_SORTED_ARRAY) / sizeof(TO_BE_SORTED_ARRAY[0]));
	assert(TO_BE_SORTED_ARRAY, sizeof(TO_BE_SORTED_ARRAY) / sizeof(TO_BE_SORTED_ARRAY[0]));
	system("pause");
	return TRUE;
}