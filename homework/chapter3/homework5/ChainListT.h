#include<stdio.h>
#include<malloc.h>
#include <stdlib.h>

#define True 1
#define False 0
#define PI 3.1415926535897932384626433832795028841971693993751058209

typedef double DataType;

typedef struct ChainListNode
{
	DataType data;//data代表数据元素
	struct ChainListNode *next;//next为指向下一结点的指针
}Node;

/* 初始化一个链表 */
Node* InitList();

/* 判断链表是否为空 */
int ListEmpty(Node * Head);

/* 获取链表长度 */
int ListLength(Node *Head);

/* 往指定位置插入数据 */
int ListInsert(Node *Head, int pos, DataType item);

/* 找到指定位置的结点 */
Node* FindItem(Node *H, int pos);

/* 每两个结点之间增加三个结点，以此扩充结点 */
void ExpandList(Node *SnowList);
