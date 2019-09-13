#include "MazeDataStruct.h"


/* 初始化一个栈 */
Status InitStack(LinkStack top)
{
	top->next = NULL;
	return TRUE;
}

/* 判断栈是否为空 */
Status IsEmpty(LinkStack top)
{
	if (top->next == NULL)
		return TRUE;
	else
		return FALSE;
}

/* 将数据压入栈顶 */
Status Push(LinkStack top, SElemType *element)
{
	StackNode *temp = (StackNode *)malloc(sizeof(StackNode));/* 创建一个新结点,并分配存储空间 */
	if (temp == NULL)
		return FALSE;
	temp->data = element;/* element是结构指针而不是结构 */
	temp->next = top->next;/* 更换栈顶元素 */
	top->next = temp;
	return TRUE;
}

/* 栈顶出栈,top为栈顶指针,将出栈的元素赋值给element指向的结构 */
Status Pop(LinkStack top, SElemType *element)
{
	StackNode *temp = NULL;
	if (IsEmpty(top)==TRUE)
		return FALSE;
	temp = top->next;/* 暂时储存栈顶指针 */
	*element = *(temp->data);/* 要操作指针指向的对象，而不能操作地址 */
	top->next = temp->next;/* 更换栈顶元素 */
	free(temp);/* 释放存储空间 */
	return TRUE;
}