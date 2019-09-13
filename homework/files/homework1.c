#include<stdio.h>
#include<stdlib.h>

int day_sum[12] = { 0,31,28,31,30,31,30,31,31,30,31,30 };

void output(int w) 
{
	switch (w-1)
	{
	case 0:
		printf("星期一\n");
		break;
	case 1:
		printf("星期二\n");
		break;
	case 2:
		printf("星期三\n");
		break;
	case 3:
		printf("星期四\n");
		break;
	case 4:
		printf("星期五\n");
		break;
	case 5:
		printf("星期六\n");
		break;
	case 6:
		printf("星期日\n");
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
	/* 是闰年且月份大于二，加一天 */
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
		printf("请输入年份:");
		scanf("%d", &year);
		if (isLeap(year)) printf("%d是闰年\n", year);
		else printf("%d不是闰年\n", year);
		break;
	case 2:
		printf("请输入年份:");
		scanf("%d", &year);
		output(whenNewYear(year));
		break;
	case 3:
		printf("请输入年月日:");
		scanf("%d %d %d", &year,&month,&day);
		remainder = getDay(year, month, day) % 7;
		output((whenNewYear(year)+remainder-1)%7);
		break;
	case 4:
		exit(0);
	default:
		printf("输入有误，请重试\n");
		break;
	}
}

int main_homewok1()
{
	int choice;
	printf("输入1进入闰年信息查询；输入2进入元旦是星期几的查询；输入3进入年月日是星期几的查询;输入4程序结束。\n");
	while (1)
	{
		scanf("%d", &choice);
		application(choice);
	}
	return 0;
}

