#include<stdio.h>
#include<stdlib.h>

int RemoveDuplicates(int *pScores, int nScores);

int main(void)
{
	/* ���鳤�� */
	int nScores;
	int scores[] = { 65,72,75,79,82,82,84,84,84,86,90,94,95 };
	int i;

	/* δɾ��ǰ�ȱ���һ�� */
	printf("scoresΪ:");
	for (i = 0; i < sizeof(scores) / sizeof(scores)[0]; i++)
		printf("%d ", scores[i]);
	printf("\n����nScoresΪ%d\n", sizeof(scores) / sizeof(scores[0]));

	/* ɾ���ظ�Ԫ��֮�� */
	nScores = RemoveDuplicates(scores, sizeof(scores) / sizeof(scores[0]));

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
}
int RemoveDuplicates(int *pScores, int nScores)
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
		if (*(pScores + i) == *(pScores+i+1))
		{
			int j;
			for (j = i; j < nScores - 1; j++)
			{
				*(pScores + j) = *(pScores + j + 1);/* �����Ԫ�غ���*/
			}
			/* �������Ԫ�ظ�ֵΪ0 */
			*(pScores + j)=0;
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