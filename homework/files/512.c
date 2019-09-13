#include<stdio.h>
#include<stdlib.h>
#include<math.h>



int digit(int n, int k)
{
	int i;
	for (i = 0; i < k - 1; i++)

		n = n / 10;
	return n % 10;
}

int detect_digit(int n)

{

	int i = 1, k = 1, temp = n;

	while (temp&&i++) temp = temp / 10;

	i--;// i为数字位数

	while (k <= i / 2 && digit(n, k) == digit(n, i - k + 1) && k++);

	if (k - 1 == i / 2) return 1;

	else return 0;

}

int main()
{
	int a, b, i;
	scanf("%d %d", &a, &b);
	for (i = a; i <= b; i++)
		if (detect_digit(i)) printf("%d ", i);
	system("pause");
	return 0;
}

