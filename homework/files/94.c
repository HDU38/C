#include<stdio.h>
#include<stdlib.h>

#define LENGTH 6

typedef struct
{
	int data;
	int pos;
}integer;



void swap__(integer *a, integer *b)
{
	integer tmp = *a;
	*a = *b;
	*b = tmp;
}



int main94()
{
	int i, j;
	integer a[6];
	for (i = 0; i < LENGTH; i++)
	{
		scanf("%d ", &a[i].data);
		a[i].pos = i;
	}
	for (i = 0; i < LENGTH; i++)

		printf("%d ", a[i].data);

	printf("\n");

	for (i = 1; i < LENGTH; i++)
	{
		while (i > 0 && a[i].data > a[i - 1].data)
		{
			swap__(&a[i], &a[i - 1]);
			i--;
		}
	}
	for (i = 0; i < LENGTH; i++)

		printf("%d %d\n", a[i].data, a[i].pos);
	system("pause");
	return 0;
}