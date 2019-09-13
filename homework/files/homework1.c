#include<stdio.h>
#include<stdlib.h>

int day_sum[12] = { 0,31,28,31,30,31,30,31,31,30,31,30 };

void output(int w) 
{
	switch (w-1)
	{
	case 0:
		printf("����һ\n");
		break;
	case 1:
		printf("���ڶ�\n");
		break;
	case 2:
		printf("������\n");
		break;
	case 3:
		printf("������\n");
		break;
	case 4:
		printf("������\n");
		break;
	case 5:
		printf("������\n");
		break;
	case 6:
		printf("������\n");
		break;
	default:
		break;
	}
}

int isLeap(int year)
{
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) return 1;
	else return 0;
}

int getDay(int year, int month, int day)
{
	int result = day, i;
	for (i = 0; i<month; i++)
	{
		result += day_sum[i];
	}
	/* ���������·ݴ��ڶ�����һ�� */
	if (month > 2 && isLeap(year))
	{
		result++;
	}
	return result;
}

int whenNewYear(int year)
{
	return (year + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400) % 7;
}

void application(int choice)
{
	int year = 0, month = 0, day = 0, left = 0, remainder = 0;
	switch (choice)
	{
	case 1:
		printf("���������:");
		scanf("%d", &year);
		if (isLeap(year)) printf("%d������\n", year);
		else printf("%d��������\n", year);
		break;
	case 2:
		printf("���������:");
		scanf("%d", &year);
		output(whenNewYear(year));
		break;
	case 3:
		printf("������������:");
		scanf("%d %d %d", &year,&month,&day);
		remainder = getDay(year, month, day) % 7;
		output((whenNewYear(year)+remainder-1)%7);
		break;
	case 4:
		exit(0);
	default:
		printf("��������������\n");
		break;
	}
}

int main_homewok1()
{
	int choice;
	printf("����1����������Ϣ��ѯ������2����Ԫ�������ڼ��Ĳ�ѯ������3���������������ڼ��Ĳ�ѯ;����4���������\n");
	while (1)
	{
		scanf("%d", &choice);
		application(choice);
	}
	return 0;
}

