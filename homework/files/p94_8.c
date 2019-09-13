#include<stdio.h>
#include<stdlib.h>

int main4(){
	int n, input, i, result = 1;
	printf("输入n和相应的n个数:");
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &input);
		if (input % 2 == 0) continue;
		result *= input;
	}
	printf("结果为%d", result);
	system("pause");
	return 0;
}