#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main11() {
	int i, j;
	for (i = 1; i < 10; i++) {
		for (j = 1; j < i + 1; j++) {
			printf("%d * %d = %d   ", j, i, i*j);
		}
		printf("\n");
	}
	system("pause");
	return 0;
}