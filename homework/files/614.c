#include<stdio.h>

int strLength(char *a)
{
	int i = 0;
	while (*(a++)) i++;
	return i;
}
int isSub(char *a, char *b)
{
	int i = 0, j = 0;
	int length_a = strLength(a);
	int length_b = strLength(b);
	while (j < length_b)
	{
		while (a[i++] == b[j++])
			if (i == length_a) return j - length_a;
		j = j - i + 1;// »ØÍË
		i = 0;
	}
	return -1;
}
int main614()
{
	printf("%d ", isSub("add","addnumber"));
	printf("%d ", isSub("add#", "addnumber"));
	printf("%d ", isSub("add", "jsdfaddnumber"));
	getch();
	return 0;
}
