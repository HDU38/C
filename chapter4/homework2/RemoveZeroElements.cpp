#include<stdio.h>
#include<stdlib.h>

int RemoveZeroElements(int *pScores, int nScores);

int main(void)
{
	/* ���鳤�� */
	int nScores;
	int scores[13] = { 65,0,95,0,0,79,82,0,84,94,86,90,0 };
	int i;

	/* δɾ��ǰ�ȱ���һ�� */
	printf("scoresΪ:");
	for (i = 0; i < sizeof(scores) / sizeof(scores)[0]; i++)
		printf("%d ", scores[i]);
	printf("\n����nScoresΪ%d\n", sizeof(scores) / sizeof(scores[0]));

	/* ɾ��0Ԫ��֮�� */
	nScores = RemoveZeroElements(scores, sizeof(scores) / sizeof(scores[0]));
	if (nScores != 0) 
	{
		printf("scoresΪ:");
		for (int i = 0; i < nScores; i++)
		{
			printf("%d ", scores[i]);
		}
		printf("\n��Ч����nScoresΪ%d\n", nScores);
	}
	else
	{
		printf("������Ч����Ϊ0��������ʧ��");
	}
	system("pause");
	return 0;
}

/* �Ƴ�������ֵΪ0��Ԫ�أ���������Ч���ȣ�scoresΪ����ָ�룬nScoresΪ����ԭ������ */
int RemoveZeroElements(int *pScores, int nScores)
{
	int i;
	int count = 0;/* ��¼��Ч���� */
	if (pScores == NULL)
	{
		printf("ָ�봫��ʧ��");
		return 0;
	}
	for (i = 0; i<nScores; i++)//��������Ԫ��
	{
		count++;
		if (*(pScores + i) == 0)
		{
			int j;
			for (j = i; j < nScores-1; j++)
			{
				/* 0֮���Ԫ��ǰ�� */
				*(pScores + j) = *(pScores + j + 1);
			}
			/* ���鳤�ȼ�С */
			nScores--;
			/* ��Ч���ȼ�С */
			count--;
			/* ����һ���ⲽ�ܹؼ�*/
			i--;
		}
	}
	/* ������Ч���� */
	return count;
}