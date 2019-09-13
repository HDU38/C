#include <stdio.h>
#include<math.h>
#include<stdlib.h>

int main1(){
	float x;
	while (1) {
		printf("ÇëÊäÈëx\n");
		scanf("%f", &x);
		if (x >= 0 && x <= 8) {
			printf("x=%0.2f,y=%0.2f\n", x, x + 2 * pow(x, 2) + 10);
		}
		else {
			printf("x=%0.2f,y=%0.2f\n", x, x - 3 * pow(x, 3) - 9);
		}
	}
	system("pause");
	return 0;
}