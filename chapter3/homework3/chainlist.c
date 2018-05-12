#include "ADT.h"

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
int ListInsert(Node *Head, int pos, DataType item)
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
	t->data = item;
	t->next = temp->next;
	temp->next = t;
	return True;
}

/* 找到指定元素的位置 */
Node* FindItem(Node *H, int pos)
{
	Node *p = H->next;
	int temppos = 0;
	while (p)
	{
		pos++;
		if (temppos == pos)
			break;
		p = p->next;
	}
	if (p)
		return p;
	else
		return NULL;
}