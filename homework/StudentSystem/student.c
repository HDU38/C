#include "studentList.h"

int main()
{
	char input[5];
	Node *studentListHead = InitList();
	printf("是否导入成绩\n");
	scanf("%s", input);
	if (StrMatch("是", input))
	{
		InsertScoreFile(studentListHead, "E:\\score.csv");
		printf("导入成功\n");
	}
	else
		printf("未导入成绩\n");
	MainFunction(studentListHead);
	getchar();
	return 0;
}