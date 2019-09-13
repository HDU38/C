#include<stdio.h>

int fac(int n)/* 计算阶乘 */
{
	int result = 1;
	if (n < 0) return 0;
	if (n == 0) return 1;
	while (n) result = n--*result;
	return result;
}
double pow(int n, double x)
{
	if (n == 0) return 1;
	if (n > 0) return x * pow(n - 1, x);
	else return pow(n + 1, x) / x;
}
double cal(double p) 
{
	int i;
	double sum = 0,temp = 0,sub = 0;
	for (i = 1; i < 100; i++) 
	{
		sum += 1/(double)fac(i);
		sub = sum - temp;/* 计算差值 */
		temp = sum;
		if (sub <= p)
			return sum;/* 达到最高精度要求 */
	}
	printf("超出计算范围\n");
	return 0;
}
int main513() 
{
	int i,n;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) 
	{
		printf("%f\n",cal(pow(-i,10)));
	}
	getch();
}