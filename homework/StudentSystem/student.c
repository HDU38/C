#include "studentList.h"

int main()
{
	char input[5];
	Node *studentListHead = InitList();
	printf("�Ƿ���ɼ�\n");
	scanf("%s", input);
	if (StrMatch("��", input))
	{
		InsertScoreFile(studentListHead, "E:\\score.csv");
		printf("����ɹ�\n");
	}
	else
		printf("δ����ɼ�\n");
	MainFunction(studentListHead);
	getchar();
	return 0;
}