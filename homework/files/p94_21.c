#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main7() {
	int a, b, c, d;
	int i, j, sum = 0;
	scanf("%d %d", &c, &d);
	a = c > d ? c : d;
	b = c > d ? d : c;
	for (i = b; i < a; i++) {
		for (j = 2; j < (int)sqrt(i)+1; j++) {
			if (i%j == 0) break;/* ��������  */
		}
		/* ������ */
		if (j == (int)sqrt(i)+1) sum += i;
	}
	printf("���Ϊ%d\n", sum);
	system("pause");
	return 0;
}