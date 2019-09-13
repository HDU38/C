#include<stdio.h>

double pow(int n, double x)
{
	if (n == 0) return 1;
	if (n > 0) return x * pow(n - 1, x);
	else return pow(n + 1, x) / x;
}

int main515() 
{
	int n;
	double x;
	while (1)
	{
		scanf("%d %lf", &n, &x);
		printf("%g\n", pow(n, x));
	}
}