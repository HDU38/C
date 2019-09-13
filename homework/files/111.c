#include<stdio.h>
#include<stdlib.h>

int main111()
{
	FILE *fp;
	char c;
	char line[1024];
	fp = fopen("E:/test111.txt", "r");
	if (!fp) return 0;
	while (!feof(fp))
	{
		fgets(line, 1024, fp);  
		printf("%s", line); 
	}
	fclose(fp);
	system("pause");
	return 0;
}