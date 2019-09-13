#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main9() {
	int i;
	double sum = 0;
	for (i = 1; i <= 40;i++) {
		if (i % 2 == 0)sum -= 1 / (double)i;
		else sum += 1 / (double)i;
	}
	printf("½á¹ûÊÇ%0.4f", sum);
	system("pause");
	return 0;
}