#include<stdio.h>
#include<stdlib.h>

int main4(){
	int n, input, i, result = 1;
	printf("����n����Ӧ��n����:");
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &input);
		if (input % 2 == 0) continue;
		result *= input;
	}
	printf("���Ϊ%d", result);
	system("pause");
	return 0;
}