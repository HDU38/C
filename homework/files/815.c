#include<stdio.h>
#include<stdlib.h>

getLength(char* a)
{
	int i = 0;
	while (*(a++) != '\0'&&++i);
	return i;
}
int main815()
{
	int i,j;
	char tmp[5][100];
	int max;
	int len=0;
	for (i = 0; i < 5; i++)
	{
		scanf("%s", tmp[i]);
		if (getLength(tmp[i]) > len)
		{
			len = getLength(tmp);
			max = i;
		}
	}
	printf("%s", tmp[max]);
	system("pause");
	return 0;
}