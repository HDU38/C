#include "MazeDataStruct.h"


/* ��ʼ��һ��ջ */
Status InitStack(LinkStack top)
{
	top->next = NULL;
	return TRUE;
}

/* �ж�ջ�Ƿ�Ϊ�� */
Status IsEmpty(LinkStack top)
{
	if (top->next == NULL)
		return TRUE;
	else
		return FALSE;
}

/* ������ѹ��ջ�� */
Status Push(LinkStack top, SElemType *element)
{
	StackNode *temp = (StackNode *)malloc(sizeof(StackNode));/* ����һ���½��,������洢�ռ� */
	if (temp == NULL)
		return FALSE;
	temp->data = element;/* element�ǽṹָ������ǽṹ */
	temp->next = top->next;/* ����ջ��Ԫ�� */
	top->next = temp;
	return TRUE;
}

/* ջ����ջ,topΪջ��ָ��,����ջ��Ԫ�ظ�ֵ��elementָ��Ľṹ */
Status Pop(LinkStack top, SElemType *element)
{
	StackNode *temp = NULL;
	if (IsEmpty(top)==TRUE)
		return FALSE;
	temp = top->next;/* ��ʱ����ջ��ָ�� */
	*element = *(temp->data);/* Ҫ����ָ��ָ��Ķ��󣬶����ܲ�����ַ */
	top->next = temp->next;/* ����ջ��Ԫ�� */
	free(temp);/* �ͷŴ洢�ռ� */
	return TRUE;
}