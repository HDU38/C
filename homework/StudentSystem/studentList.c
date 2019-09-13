#include "studentList.h"

/* 初始化一个链表 */
Node* InitList()
{
	Node *Head = (Node*)malloc(sizeof(Node));// 申请存储空间，得到头结点
	if (!Head)
	{
		printf("初始化错误");
		return NULL;
	}
	Head->next = NULL;
	return Head;
}

/* 判断链表是否为空 */
int ListEmpty(Node * Head)
{
	if (Head->next)
		return False;
	else
		return True;
}

/* 获取链表长度 */
int ListLength(Node *Head)
{
	Node *temp = Head->next;
	int total = 0;
	while (temp)
	{
		total++;
		temp = temp->next;
	}
	return total;
}

/* 往指定位置插入数据 */
int ListInsert(Node *Head, int pos, StudentType item)
{
	Node *temp = Head;
	int i = 0;
	while (temp)
	{
		if (i + 1 == pos)
			break;
		temp = temp->next;
		i++;
	}
	if (temp == NULL)
	{
		return False;
	}
	Node *t = (Node*)malloc(sizeof(Node));
	t->student = item;
	t->next = temp->next;
	temp->next = t;
	return True;
}

/* 删除结点 */
int ListDelete(Node *H, char *examno)
{
	Node *p = H, *t;
	int i = 0;
	while (p->next)
	{
		if (StrMatch(p->next->student.examno,examno))
			break;
		p = p->next;
	}
	if (p->next == NULL)
	{
		return False;
	}
	t = p->next;
	p->next = t->next;
	free(t);
	return True;
}

/* 找到指定位置的结点 */
Node* FindItem(Node *H, int pos)
{
	Node *p = H->next;
	int temppos = 0;
	while (p)
	{
		if (++temppos == pos)
			return p;
		p = p->next;
	}
	return NULL;
}

Node* FindStudentByName(Node *Head, char name[10])
{
	Node *p = Head->next;
	while (p)
	{
		if (StrMatch(name,p->student.name))
			return p;
		p = p->next;
	}
	return NULL;
}

Node* FindStudentByExanno(Node *Head, char examno[10])
{
	Node *p = Head->next;
	while (p)
	{
		if (StrMatch(examno,p->student.examno))
			return p;
		p = p->next;
	}
	return NULL;
}

void TraverseStudent(Node *Head)
{
	int query = 0;
	Node *temp = Head;
	printf("查询信息(1),查询成绩(2)\n");
	scanf("%d", &query);
	switch (query)
	{
	case 1:
		printf("准考证号|姓名  |性别|年龄\n");
		while (temp = temp->next)
			printf("%s   |%s |%s |%s \n", temp->student.examno, temp->student.name, temp->student.sex, temp->student.age);
		break;
	case 2:
		printf("准考证号|姓名  |语文|数学|英语|物理|化学|生物\n");
		while (temp = temp->next)
		{
			printf("%s   |%s |", temp->student.examno,temp->student.name);
			for (int i = 0; i < temp->student.subjectCount * 2 - 1; i++)
			{
				printf("%s ", temp->student.subject[i]);
				i++;
				printf("%s|", temp->student.subject[i]);
			}
			printf("\n");
		}
		break;
	default:
		break;
	}
}

/* b与a匹配 */
int StrMatch(char *a, char *b)
{	
	int i = 0;
	int lenA = strlen(a);
	int lenB = strlen(b);
	if (lenA != lenB) return False;
	while (*(a + i) == *(b + i)&&i<lenA)
		i++;
	if(i-lenA) return False;
	else return True;
}

void MainFunction(Node *Head)
{
	int choice = 0;
	int addSubjct = 0;

	char inputString[10];
	Node *temp = (Node*)malloc(sizeof(Node));

	char key[10];
	char value[10];

	char field[10];
	do
	{
		printf("新建学生信息(1)，修改学生信息(2)，遍历(3)，排序(4)，删除(5)，查找学生信息(6)，查找学生成绩(7),退出(-1)\n");
		scanf("%d", &choice);
		switch(choice)
		{
		case INSERT_ACTION:
			printf("请输入学生的准考证号，姓名，性别，年龄(用空格分开)\n");
			StudentType *newStudent = (StudentType*)malloc(sizeof(StudentType));/* 一定要申请存储空间 */
			scanf("%s %s %s %s", newStudent->examno, newStudent->name, newStudent->sex, newStudent->age);
			newStudent->subjectCount = 0;
			printf("是否添加科目成绩?是(1)\n");
			scanf("%d", &addSubjct);
			if (addSubjct!=0)
			{
				int subjectCount = 0;
				printf("请输入科目数:");
				scanf("%d", &newStudent->subjectCount);
				printf("请输入科目名称和成绩\n");
				for(int subjectNum=0;subjectNum<newStudent->subjectCount;subjectNum++)
					scanf("%s %s", newStudent->subject[subjectNum * 2], newStudent->subject[subjectNum * 2+1]);
			}
			ListInsert(Head, ListLength(Head) + 1, *newStudent);
			printf("OK\n");
			break;
		case MODIFY_ACTION:
			printf("请输入学生的姓名或准考证号");
			scanf("%s", inputString);
			if ('0'<=inputString[0]&&inputString[0]<='9')/* 判断是准考证号还是名字 */
			{
				if (temp = FindStudentByExanno(Head, inputString))
				{
					printf("找到该学生的信息\n%s |%s |%s |%s |", temp->student.examno, temp->student.name,
						temp->student.sex, temp->student.age);
					for (int i = 0; i < temp->student.subjectCount * 2 - 1; i++)
					{
						printf("%s ", temp->student.subject[i]);
						i++;
						printf("%s|", temp->student.subject[i]);
					}
					printf("\n请输入字段名和修改后的值\n");
					scanf("%s %s", key,value);
					if(Modify(temp, key, value)) printf("修改成功！\n");
				}
				else
					printf("没有找到该学生的信息\n");
			}
			else
			{
				if (temp = FindStudentByName(Head, inputString))
				{
					printf("找到该学生的信息\n%s |%s |%s |%s |", temp->student.examno, temp->student.name,
						temp->student.sex, temp->student.age);
					for (int i = 0; i < temp->student.subjectCount * 2 - 1; i++)
					{
						printf("%s ", temp->student.subject[i]);
						i++;
						printf("%s|", temp->student.subject[i]);
					}
					printf("\n请输入字段名和修改后的值\n");
					scanf("%s %s", key, value);
					if (Modify(temp, key, value)) printf("修改成功！\n");
				}
				else
					printf("没有找到该学生的信息\n");
			}
			break;
		case TRAVERSE_ACTION:
			TraverseStudent(Head);
			break;
		case SORT_ACTION:
			printf("请输入排序的字段(默认从小到大排序)");
			scanf("%s", field);
			char c=field[0];
			if (c == '-')
			{
				for (unsigned i = 0; i < strlen(field); i++)
					field[i] = field[i + 1];
				SORT_STUDENT_DESCEND(Head, field);
			}
			else
				SORT_STUDENT_ASCEND(Head,field);
			break;
		case DELETE_ACTION:
			printf("请输入学生的准考证号");
			scanf("%s", inputString);
			if (ListDelete(Head, inputString)) printf("删除成功\n");
			else printf("未找到该学生的信息\n");
			break;
		case SEARCH_PERSONAL_INFOMATION_ACTION:
			printf("请输入学生的姓名或准考证号");
			scanf("%s", inputString);
			if ('0' <= inputString[0] && inputString[0] <= '9')/* 判断是准考证号还是名字 */
			{
				if (temp = FindStudentByExanno(Head, inputString))
				{
					printf("找到该学生的信息\n%s |%s |%s |%s \n", temp->student.examno, temp->student.name,
						temp->student.sex, temp->student.age);
				}
				else
					printf("没有找到该学生的信息\n");
			}
			else
			{
				if (temp = FindStudentByName(Head, inputString))
				{
					printf("找到该学生的信息\n%s |%s |%s |%s \n", temp->student.examno, temp->student.name,
						temp->student.sex, temp->student.age);
				}
				else
					printf("没有找到该学生的信息\n");
			}
			break;
		case SEARCH_PERSONAL_SCORE_ACTION:
			printf("请输入学生的姓名或准考证号");
			scanf("%s", inputString);
			if ('0' <= inputString[0] && inputString[0] <= '9')/* 判断是准考证号还是名字 */
			{
				if (temp = FindStudentByExanno(Head, inputString))
				{
					printf("%s   |%s |", temp->student.examno, temp->student.name);
					for (int i = 0; i < temp->student.subjectCount * 2 - 1; i++)
					{
						printf("%s ", temp->student.subject[i]);
						i++;
						printf("%s|", temp->student.subject[i]);
					}
					printf("\n");
				}
				else
					printf("没有找到该学生的成绩\n");
			}
			else
			{
				if (temp = FindStudentByName(Head, inputString))
				{
					printf("%s   |%s |", temp->student.examno, temp->student.name);
					for (int i = 0; i < temp->student.subjectCount * 2 - 1; i++)
					{
						printf("%s ", temp->student.subject[i]);
						i++;
						printf("%s|", temp->student.subject[i]);
					}
					printf("\n");
				}
				else
					printf("没有找到该学生的成绩\n");
			}
			break;
		default:
			printf("输入有误\n");
			break;
		}
	} while (choice != -1);
	exit(0);
}

char** StrSplit(char* a_str, const char a_delim)
{
	char** result = 0;
	size_t count = 0;
	char* tmp = a_str;
	char* last_comma = 0;
	char delim[2];
	delim[0] = a_delim;
	delim[1] = 0;

	/* Count how many elements will be extracted. */
	while (*tmp)
	{
		if (a_delim == *tmp)
		{
			count++;
			last_comma = tmp;
		}
		tmp++;
	}

	/* Add space for trailing token. */
	count += last_comma < (a_str + strlen(a_str) - 1);

	/* Add space for terminating null string so caller
	knows where the list of returned strings ends. */
	count++;

	result = malloc(sizeof(char*) * count);

	if (result)
	{
		size_t idx = 0;
		char* token = strtok(a_str, delim);

		while (token)
		{
			assert(idx < count);
			*(result + idx++) = _strdup(token);
			token = strtok(0, delim);
		}
		assert(idx == count - 1);
		*(result + idx) = 0;
	}

	return result;
}

void InsertScoreFile(Node *Head,char *fileName)
{
	char str[10000];
	StudentType *newStudent = NULL;
	char *result = NULL;
	int i = 0;
	strcpy(str, GetData(fileName));

	char** tokens;
	int j = 0;
	tokens = StrSplit(str, ',');
	if (tokens)
	{
		int i;
		for (i = 0; *(tokens + i); i+=18)
		{
			if (i % 18==0)
			{
				if (!*(tokens + i + 1))
					break;
				newStudent = (StudentType*)malloc(sizeof(StudentType));
				strcpy(newStudent->examno , *(tokens + i));
				strcpy(newStudent->name, *(tokens + i + 1));
				newStudent->subjectCount = 6;
				strcpy(newStudent->subject[j++], "语文");
				strcpy(newStudent->subject[j++], *(tokens + i +2));
				strcpy(newStudent->subject[j++], "数学");
				strcpy(newStudent->subject[j++], *(tokens + i + 3));
				strcpy(newStudent->subject[j++], "英语");
				strcpy(newStudent->subject[j++], *(tokens + i + 4));
				strcpy(newStudent->subject[j++], "物理");
				strcpy(newStudent->subject[j++], *(tokens + i + 6));
				strcpy(newStudent->subject[j++], "化学");
				strcpy(newStudent->subject[j++], *(tokens + i + 7));
				strcpy(newStudent->subject[j++], "生物");
				strcpy(newStudent->subject[j], *(tokens + i + 8));
				strcpy(newStudent->age, " ");
				strcpy(newStudent->sex, " ");
				ListInsert(Head, ListLength(Head) + 1, *newStudent);
				j = 0;
			}
		}
		free(tokens);
	}
}

int Modify(Node *temp,char *key ,char *value)
{
	if (StrMatch("准考证号", key)) strcpy((temp->student.examno), value);
	else if (StrMatch("名字", key)) strcpy((temp->student.name), value);
	else if (StrMatch("年龄", key)) strcpy((temp->student.age), value);
	else if (StrMatch("性别", key)) strcpy((temp->student.sex), value);
	else 
	{
		for(int i =0;i<2*temp->student.subjectCount-1;i+=2)
			if (StrMatch(temp->student.subject[i], key))
			{
				strcpy((temp->student.subject[i+1]), value);
				return True;
			}
		printf("未找到该字段，修改失败");
		return False;
	}
	return True;
}

void swap(StudentType *a, StudentType *b)
{
	StudentType temp = *a;
	*a = *b;
	*b = temp;
}

/* 比较a和b，返回a-b */
int compare(char *a, char *b)
{
	int i = 0;
	int lenA = strlen(a);
	int lenB = strlen(b);
	while (*(a + i) == *(b + i) && i<lenA&&i<lenB)
		i++;
	if ((i - lenA)!=0) return *(a + i) - *(b + i);
	else return 0;
}

/* 排序 */
void Sort(Node *head,char *expression,int condition)
{
	int j=0;
	int fieldIndex=0;
	int i=0, length = ListLength(head);
	char *field[8] = { "examno","name","Chinese","Math","English","Physics","Chemistry","Biology" };
	for (fieldIndex = 0; fieldIndex < 8; fieldIndex++)
		if (StrMatch(expression, field[fieldIndex]))
			break;
	if (fieldIndex >= 8)
	{
		printf("未找到该字段，排序失败\n");
		return;
	}
	switch (fieldIndex)
	{
	case 0:
		for (i = 1; i < length; i++)
		{
			if(!condition)
			for (j = i; j>0 &&
				compare(FindItem(head, j + 1)->student.examno, FindItem(head, j)->student.examno)<0;
				j--)
				swap(&FindItem(head, j + 1)->student, &FindItem(head, j)->student);
			else
				for (j = i; j>0 &&
					compare(FindItem(head, j + 1)->student.examno, FindItem(head, j)->student.examno)>0;
					j--)
					swap(&FindItem(head, j + 1)->student, &FindItem(head, j)->student);
		}
		break;
	case 1:
		for (i = 1; i < length; i++)
		{
			if (!condition)
				for (j = i; j>0 &&
					compare(FindItem(head, j + 1)->student.name, FindItem(head, j)->student.name)<0;
					j--)
					swap(&FindItem(head, j + 1)->student, &FindItem(head, j)->student);
			else
				for (j = i; j>0 &&
					compare(FindItem(head, j + 1)->student.name, FindItem(head, j)->student.name)>0;
					j--)
					swap(&FindItem(head, j + 1)->student, &FindItem(head, j)->student);
		}
		break;
	case 2:
		for (i = 1; i < length; i++)
		{
			if (!condition)
				for (j = i; j>0 &&
					CompareScore(FindItem(head, j + 1)->student.subject[1], FindItem(head, j)->student.subject[1])<0;
					j--)
					swap(&FindItem(head, j + 1)->student, &FindItem(head, j)->student);
			else
				for (j = i; j>0 &&
					CompareScore(FindItem(head, j + 1)->student.subject[1], FindItem(head, j)->student.subject[1])>0;
					j--)
					swap(&FindItem(head, j + 1)->student, &FindItem(head, j)->student);
		}
		break;
	case 3:
		for (i = 1; i < length; i++)
		{
			if (!condition)
				for (j = i; j>0 &&
					CompareScore(FindItem(head, j + 1)->student.subject[3], FindItem(head, j)->student.subject[3])<0;
					j--)
					swap(&FindItem(head, j + 1)->student, &FindItem(head, j)->student);
			else
				for (j = i; j>0 &&
					CompareScore(FindItem(head, j + 1)->student.subject[3], FindItem(head, j)->student.subject[3])>0;
					j--)
					swap(&FindItem(head, j + 1)->student, &FindItem(head, j)->student);
		}
		break;
	case 4:
		for (i = 1; i < length; i++)
		{
			if (!condition)
				for (j = i; j>0 &&
					CompareScore(FindItem(head, j + 1)->student.subject[5], FindItem(head, j)->student.subject[5])<0;
					j--)
					swap(&FindItem(head, j + 1)->student, &FindItem(head, j)->student);
			else
				for (j = i; j>0 &&
					CompareScore(FindItem(head, j + 1)->student.subject[5], FindItem(head, j)->student.subject[5])>0;
					j--)
					swap(&FindItem(head, j + 1)->student, &FindItem(head, j)->student);
		}
		break;
	case 5:
		for (i = 1; i < length; i++)
		{
			if (!condition)
				for (j = i; j>0 &&
					CompareScore(FindItem(head, j + 1)->student.subject[7], FindItem(head, j)->student.subject[7])<0;
					j--)
					swap(&FindItem(head, j + 1)->student, &FindItem(head, j)->student);
			else
				for (j = i; j>0 &&
					CompareScore(FindItem(head, j + 1)->student.subject[7], FindItem(head, j)->student.subject[7])>0;
					j--)
					swap(&FindItem(head, j + 1)->student, &FindItem(head, j)->student);
		}
		break;
	case 6:
		for (i = 1; i < length; i++)
		{
			if (!condition)
				for (j = i; j>0 &&
					CompareScore(FindItem(head, j + 1)->student.subject[9], FindItem(head, j)->student.subject[9])<0;
					j--)
					swap(&FindItem(head, j + 1)->student, &FindItem(head, j)->student);
			else
				for (j = i; j>0 &&
					CompareScore(FindItem(head, j + 1)->student.subject[9], FindItem(head, j)->student.subject[9])>0;
					j--)
					swap(&FindItem(head, j + 1)->student, &FindItem(head, j)->student);
		}
		break;
	case 7:
		for (i = 1; i < length; i++)
		{
			if (!condition)
				for (j = i; j>0 &&
					CompareScore(FindItem(head, j + 1)->student.subject[11], FindItem(head, j)->student.subject[11])<0;
					j--)
					swap(&FindItem(head, j + 1)->student, &FindItem(head, j)->student);
			else
				for (j = i; j>0 &&
					CompareScore(FindItem(head, j + 1)->student.subject[11], FindItem(head, j)->student.subject[11])>0;
					j--)
					swap(&FindItem(head, j + 1)->student, &FindItem(head, j)->student);
		}
		break;
	}
	printf("排序成功\n");
}

double CompareScore(char *a, char *b)
{
	int aHaveDot = False;
	int bHaveDot = False;
	int i = 0,j=0,k=0;
	while (*(a + j))
	{
		if (*(a + j) == '.')
		{
			aHaveDot = True;
			break;
		}
		j++;
	}
	while (*(b + k))
	{
		if (*(b + k) == '.')
		{
			bHaveDot = True;
			break;
		}
		k++;
	}
	int lenA = strlen(a);
	int lenB = strlen(b);
	if (lenA < lenB&&(!aHaveDot&&!bHaveDot||lenA==1)) return -1.0;
	else if (lenA > lenB && !aHaveDot && !bHaveDot) return 1.0;
	while (*(a + i) == *(b + i) && i<lenA&&i<lenB)
		i++;
	if ((i - lenA) != 0) return (double)*(a + i) - (double)*(b + i);
	else return 0;
}

char *GetData(char *fileName)
{
	/*
	FILE *fp=NULL;
	char *str;
	char txt[10000];
	int filesize;
	if ((fp = fopen(fileName, "r")) == NULL)
		exit(False);
	fseek(fp, 0, SEEK_END);
	filesize = ftell(fp);
	str = (char*)malloc(filesize);
	str[0] = 0;

	rewind(fp);
	while ()
	{
		strcat(str, txt);
	}
	fclose(fp);
	return str;

	*/

	FILE * pfile;
	char  data[5000];
	char c;
	int i = 0;
	pfile = fopen(fileName, "rb");
	if (pfile == NULL)
	{
		return NULL;
	}
	while ((c = fgetc(pfile)) != EOF)
		if (c != '\n'&&c!='\r')
			data[i++] = c;
	data[i] = '\0';
	return data;
}

char *Strip(char *s)
{
	size_t size;
	char *end;

	size = strlen(s);

	if (!size)
		return s;

	end = s + size - 1;
	while (end >= s && isspace(*end))
		end--;
	*(end + 1) = '\0';

	while (*s && isspace(*s))
		s++;

	return s;
}