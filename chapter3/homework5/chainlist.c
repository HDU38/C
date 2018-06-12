#include "ChainListT.h"

/* ��ʼ��һ������ */
Node* InitList()
{
	Node *Head = (Node*)malloc(sizeof(Node));/* ����洢�ռ䣬�õ�ͷָ�� */
	if (Head == NULL)
	{
		printf("��ʼ������");
		return NULL;
	}
	Head->next = NULL;
	return Head;
}

/* �ж������Ƿ�Ϊ�� */
int ListEmpty(Node * Head)
{
	if (Head->next)
		return False;
	else
		return True;
}

/* ��ȡ������ */
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

/* ��ָ��λ�ò�������,pos��1��ʼ���� */
int ListInsert(Node *Head, int pos, DataType item)
{
	Node *temp = Head;
	Node *t = NULL;
	int i = 0;
	while (temp != NULL)
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
	t = (Node*)malloc(sizeof(Node));
	t->data = item;
	t->next = temp->next;
	temp->next = t;
	return True;
}

/* �ҵ�ָ��λ�õĽ�� */
Node* FindItem(Node *H, int pos)
{
	Node *p = H->next;
	int temppos = 0;
	while (p!=NULL)
	{
		if (++temppos == pos)
			return p;
		p = p->next;
	}
	return NULL;
}