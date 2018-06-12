#include<stdio.h>
#include<malloc.h>
#include <stdlib.h>

#define True 1
#define False 0
#define PI 3.1415926535897932384626433832795028841971693993751058209

typedef double DataType;

typedef struct ChainListNode
{
	DataType data;//data��������Ԫ��
	struct ChainListNode *next;//nextΪָ����һ����ָ��
}Node;

/* ��ʼ��һ������ */
Node* InitList();

/* �ж������Ƿ�Ϊ�� */
int ListEmpty(Node * Head);

/* ��ȡ������ */
int ListLength(Node *Head);

/* ��ָ��λ�ò������� */
int ListInsert(Node *Head, int pos, DataType item);

/* �ҵ�ָ��λ�õĽ�� */
Node* FindItem(Node *H, int pos);

/* ÿ�������֮������������㣬�Դ������� */
void ExpandList(Node *SnowList);
