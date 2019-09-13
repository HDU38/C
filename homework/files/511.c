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

int main12()

{

	printf("%d\n", digit(231456, 3));



	printf("%d\n", digit(1456, 5));



	printf("%d\n", digit(1000, 3));



	system("pause");

	return 0;

}

