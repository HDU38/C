#include<stdio.h>
#include<stdlib.h>

void split(int n, int k);
void output(int *pArray);
int arrayLength(int *pArray);

int result[100] = { 0 };/* ���滮�ֺ�õ������� */
int num = 0;/* �����ֵ��� */

int main()
{
	int k;
	printf("������Ҫ���ֵ�������С�ڵ���100��:");
	scanf("%d", &num);
	result[0] = num;
	for (k = 2; k <= num; k++)
		split(num, k);
	system("pause");
	return 0;
}

/* ������n����Ϊk�������ĺ� */
void split(int n, int k)
{
	int i;
	if (k == 1)
		output(result);/* ������ */
	for (i = 1; 2 * i <= n; i++)
	{
		if (i < result[arrayLength(result) - 2])/* ���ֻ������ĵ����� */
			continue;
		result[arrayLength(result) - 1] = i;/* �Ƚ����һ��������Ϊ������ */
		result[arrayLength(result)] = n - i;
		split(n - i, k - 1);/* �ֽ⵹����һ���� */
		result[arrayLength(result) - 2] = n;/* �ָ�Ϊ����֮ǰ��״̬ */
		result[arrayLength(result) - 1] = 0;/* ׼����һ�ֻ��� */
	}

}

/* ������ֽ�� */
void output(int *pArray)
{
	int i = 0;
	printf("%d=",num);
	while (pArray[i] != 0)
	{
		printf("%d", pArray[i++]);
		if(pArray[i] != 0)/* �������һ�����������������������Ӻ� */
			printf("+");
	}
	printf("\n");
}

/* ������鳤�� */
int arrayLength(int *pArray)
{
	int length = 0;
	while (pArray[length] != 0)
		length++;
	return length;
}

