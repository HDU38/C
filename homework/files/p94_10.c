#include<stdio.h>
#include<stdlib.h>

int main2() {
	int n, i,input;
	int negative_numbers = 0, positive_numbers = 0, zero_numbers = 0;
	printf("������n��");
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &input);
		negative_numbers += (input < 0 ? 1 : 0);
		positive_numbers += (input > 0 ? 1 : 0);
		zero_numbers += (input == 0 ? 1 : 0);
	}
	printf("\n������%d����������%d��������%d��\n", positive_numbers, negative_numbers, zero_numbers);
	system("pause");
	return 0;
}