#include<stdio.h>
#include<stdlib.h>

double fun(double x, int n)
{
	int i;
	double result = 1.0;
	if (n == 0) return 1;
	if (n < 0)
	{
		for (i = n; i < 0; i++) result = result / x;
	}
	else
	{
		for (i = 0; i < n; i++) result = x * result;
	}
	return result;
}

int main58()
{
	printf("%f\n%f\n%f\n%f\n%0.8f", fun(3.2, 1), fun(3.2, 5), fun(3.25, 0), fun(3.2, -1), fun(3.2, -2));
	system("pause");
}

