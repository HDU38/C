#include<stdio.h>

int main64()
{
	int cow[10000] = { 0 };
	int i, j = 0;
	int cow_sum = 1;/* ĸţͷ�� */
	cow[0] = 3;/* ���ڵ���3��ʾ����ֳ���� */
	for (i = 0; i < 20; i++)
	{
	
		while (j < cow_sum && cow[j++] >= 3)
			cow_sum++;
		printf("��%d����%dͷĸţ\n", i + 1, cow_sum);
		for (j = 0; j < cow_sum; j++) cow[j]++;/* ����ĸţ��һ�� */
		j = 0;
	}
	getchar();
	return 0;
}

