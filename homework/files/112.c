#include<stdio.h>
#include<stdlib.h>

int main112()
{
	FILE *fp;
	char c;
	fp = fopen("E:/test111.txt", "w");
	if (!fp) return;
	while ((c = getchar()) != EOF)
		fputc(c, fp);
	fclose(fp);
	return 0;
}