#include<stdio.h>
int main612() 
{
	while (1)
	{
		char str[100], max_char = 'a', temp[100];
		int i = 0, index = 0, j;
		scanf("%s", str);
		strcpy(temp, str);
		while (str[i])
		{
			if (str[i++] > max_char)
			{
				max_char = str[i - 1];
				index = i;
			}
		}
		i = 0;
		j = index - 1;
		temp[index] = '\0';
		strcat(temp, "(max)");
		index += 5;
		while (str[++j]) temp[index++] = str[j];
		temp[index] = '\0';
		printf("%s\n", temp);
	}
	getch();
	return 0;
}