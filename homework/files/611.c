#include<stdio.h>
#define ISLETTER(c)  (c>='a'&&c<='z')|| (c>= 'A'&&c <= 'Z')
#define ISNUMBER(c)  (c>='0'&&c<='9')

void isLegal(char *str)
{
	int i = 0;
	char c;
	if (!(ISLETTER(str[i]) || str[i] == '_'))
	{
		printf("���ǺϷ���ʶ��\n");
		getch();
		return 0;
	}
	while ((c = str[i++]) != '\0')
		if (!(ISLETTER(c) || ISNUMBER(c) || c == '_'))
		{
			printf("���ǺϷ���ʶ��\n");
			getch();
			return 0;
		}
	printf("�ǺϷ���ʶ��\n");
}
int main611()
{
	char str[100];
	scanf("%s", str);
	while (1) 
	{
		isLegal(str);
		scanf("%s", str);
	}
	getch();
	return 0;
}