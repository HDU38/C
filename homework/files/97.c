#include<stdio.h>
#include<stdlib.h>
typedef struct
{
	char Sno[9];
	char Sname[7];
	char Ssex[3];
	int age;
	int scores[5];
}student;

void swap_student(student *a, student *b)
{
	student tmp= *a;
	*a = *b;
	*b = tmp;
}
void swap_double(double *a, double *b)
{
	double tmp = *a;
	*a = *b;
	*b = tmp;
}

int main97()
{
	int student_num,i,j,count=0,k;
	student students[100];
	student girls[100];
	double average[100] = {0};
	char sex[2] = "女";
	scanf("%d", &student_num);
	if (student_num > 100) return;
	for (i = 0; i < student_num; i++)
	{
		scanf("%s", students[i].Sno);
		scanf("%s", students[i].Sname);
		scanf("%s", students[i].Ssex);
		scanf("%d", &students[i].age);
		for (j = 0; j < 5; j++) scanf("%d", &students[i].scores[j]);
		if (students[i].Ssex[0] == sex[0]&& students[i].Ssex[1]==sex[1])
		{
			girls[count++] = students[i];
			for (j = 0; j < 5; j++)
			{
				average[count - 1] += (double)girls[count - 1].scores[j];
			}
			average[count - 1] /= 5.0;
		}
	}
	for (i = 1; i < count; i++)
	{
		while (i > 0 && average[i] > average[i-1])
		{
			swap_double(&average[i], &average[i - 1]);
			swap_student(&girls[i], &girls[i - 1]);
			i--;
		}
	}
	for (i = 0; i<3&&i < count; i++)
	{
		printf("%s %s 女 %d ", girls[i].Sno, girls[i].Sname, girls[i].age);
		for (j = 0; j < 5; j++) printf("%d ", girls[i].scores[j]);
		printf("平均分：%0.2f", average[i]);
		printf("\n");
	}
	system("pause");
	return 0;
}