#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main10() {
	int i;
	double num = 81.0;
	double sum = num;
	for (i = 0; i < 19; i++) {
		sum += sqrt(num);
		num = sqrt(num);
	}
	printf("½á¹ûÊÇ%0.4f", sum);
	system("pause");
	return 0;
}