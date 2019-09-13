#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main8() {
	int a, b, c, d;
	int i;
	int units, tens, hundreds;
	scanf("%d %d", &c, &d);
	a = c > d ? c : d;
	b = c > d ? d : c;
	for (i = b; i < a; i++) {
		units = i % 10;
		tens = (i / 10) % 10;
		hundreds = (i / 100) % 10;
		if ((int)pow(units, 3) + (int)pow(tens, 3) + (int)pow(hundreds, 3) == i)
			printf("%d ", i);
	}
	system("pause");
	return 0;
}