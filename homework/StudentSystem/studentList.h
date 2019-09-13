#include<stdio.h>
#include<malloc.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include<ctype.h>

#define True 1
#define False 0

#define INSERT_ACTION 1
#define MODIFY_ACTION 2
#define TRAVERSE_ACTION 3
#define SORT_ACTION 4
#define DELETE_ACTION 5
#define SEARCH_PERSONAL_INFOMATION_ACTION 6
#define SEARCH_PERSONAL_SCORE_ACTION 7

#define SORT_STUDENT_ASCEND(head,expression) Sort(head,expression,False)
#define SORT_STUDENT_DESCEND(head,expression) Sort(head,expression,True)

typedef struct student
{
	char examno[10];// ׼��֤��
	char name[7];// ����
	char sex[5];
	char age[2];
	int subjectCount;
	char subject[12][5];
}StudentType;

typedef struct ChainListNode
{
	StudentType student;
	struct ChainListNode *next;// nextΪָ����һ����ָ��
}Node;

/* ��ʼ��һ������ */
Node* InitList();

/* �ж������Ƿ�Ϊ�� */
int ListEmpty(Node * Head);

/* ��ȡ������ */
int ListLength(Node *Head);

/* ��ָ��λ�ò������� */
int ListInsert(Node *Head, int pos, StudentType item);

/* �ҵ�ָ��λ�õĽ�� */
Node* FindItem(Node *H, int pos);

/* ɾ����� */
int ListDelete(Node *Head, char *examno);

Node* FindStudentByName(Node *Head, char name[10]);

Node* FindStudentByExanno(Node *Head, char examno[10]);

void TraverseStudent(Node *Head);

int StrMatch(char *a, char *b);

void MainFunction(Node *Head);

char** StrSplit(char* a_str, const char a_delim);

void InsertScoreFile(Node *Head,char *fileName);

/* �޸� */
int Modify(Node *temp, char *key, char *value);

void Sort(Node *head, char *expression,int condition);

void swap(StudentType *a, StudentType *b);

int compare(char *a, char *b);

double CompareScore(char *a, char *b);

char *GetData(char *fileName);

char* Strip(char *str);