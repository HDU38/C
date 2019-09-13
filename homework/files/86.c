#include<stdio.h>

int* cal_(int a, int b)
{
	int* p[2];
	*p = a * b;
	*(p + 1) = a + b;
	return p;
}

int main86()
{
	int* p = cal_(2, 3);
	printf("2*3 = %d 2+3 = %d", *p, *(p + 1));
	getchar();
	return 0;
}