#include<stdio.h>
#include<stdlib.h>

int main6() {
	int max = 0, min, i, score, sum = 0;
	for (i = 0; i < 10; i++) {
		scanf("%d", &score);
		max = score > max ? score : max;
		if (i == 0) min = score;
		else min = score < min ? score : min;
		sum += score;
	}
	printf("µÃ·ÖÎª%0.2f", ((double)(sum - min - max))/ 8);
	system("pause");
	return 0;
}