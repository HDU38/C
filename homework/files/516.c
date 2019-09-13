#include<stdio.h>

int fibonacci(n) 
{
	if (n == 1 || n == 2) return 1;
	else return fibonacci(n - 1) + fibonacci(n - 2);
}
int main516() 
{
	int n;
	while (1)
	{
		scanf("%d", &n);
		printf("µÚ%dÏîÎª%d\n", n,fibonacci(n));
	}
}