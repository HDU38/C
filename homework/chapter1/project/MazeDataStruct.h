#include<stdio.h>
#include<malloc.h>

#define TRUE 1
#define FALSE 0
#define MAZEROWNUM 18/* �Թ��ĳ��Ϳ� */

typedef int Status;

/* λ�ýṹ */
typedef struct Position
{
	int x;/* �� */
	int y;/* �� */
	int derection;/* ����1��2��3��4���δ������ϡ������� */
}SElemType, *ElemType;

/* ջ�ṹ */
typedef struct node
{
	struct Position *data;/* ��Ϊ�����漰λ�÷���ı仯����˴���ָ��λ�ýṹ��ָ����ӷ��� */
	struct node *next;
}StackNode, *LinkStack;

/* �Թ� */
static char maze[MAZEROWNUM][MAZEROWNUM] =
{
	{ 'x' , 'x' , 'x' , 'x' , 'x' , 'x' ,'x' , 'x' , 'x' , 'x' , 'x' , 'x' ,'x' , 'x' , 'x' , 'x' , 'x' , 'x' },
{ 'x' , ' ' , ' ' , ' ' , 'x' , ' ' ,' ' , ' ' , ' ' , ' ' , ' ' , ' ' ,' ' , 'x' , ' ' , ' ' , ' ' , 'x' },
{ 'x' , 'x' , ' ' , ' ' , 'x' , ' ' ,'x' , 'x' , 'x' , 'x' , 'x' , 'x' ,' ' , 'x' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , 'x' , 'x' , ' ' , 'x' , ' ' ,'x' , 'x' , 'x' , ' ' , ' ' , ' ' ,' ' , 'x' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , 'x' , 'x' , ' ' , 'x' , ' ' ,'x' , 'x' , ' ' , ' ' , 'x' , 'x' ,' ' , 'x' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , ' ' , 'x' , ' ' , ' ' , ' ' ,' ' , 'x' , ' ' , 'x' , 'x' , 'x' ,' ' , 'x' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , ' ' , 'x' , 'x' , 'x' , ' ' ,' ' , 'x' , ' ' , ' ' , 'x' , 'x' ,' ' , 'x' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , ' ' , 'x' , 'x' , ' ' , 'x' ,' ' , 'x' , 'x' , ' ' , 'x' , 'x' ,' ' , 'x' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , ' ' , 'x' , 'x' , ' ' , 'x' ,' ' , 'x' , 'x' , ' ' , 'x' , ' ' ,' ' , 'x' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , ' ' , 'x' , 'x' , ' ' , 'x' ,' ' , 'x' , 'x' , ' ' , 'x' , ' ' ,'x' , 'x' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , ' ' , 'x' , 'x' , ' ' , ' ' ,' ' , 'x' , 'x' , ' ' , ' ' , ' ' ,' ' , 'x' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , ' ' , 'x' , ' ' , ' ' , ' ' ,'x' , 'x' , ' ' , 'x' , ' ' , 'x' ,' ' , 'x' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , ' ' , ' ' , 'x' , ' ' , ' ' ,' ' , 'x' , ' ' , ' ' , ' ' , 'x' ,' ' , 'x' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , 'x' , ' ' , 'x' , ' ' , 'x' ,' ' , 'x' , ' ' , ' ' , ' ' , 'x' ,' ' , 'x' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , ' ' , ' ' , 'x' , ' ' , 'x' ,' ' , 'x' , ' ' , ' ' , ' ' , 'x' ,' ' , ' ' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , ' ' , ' ' , 'x' , ' ' , 'x' ,' ' , 'x' , ' ' , ' ' , ' ' , ' ' ,' ' , 'x' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , ' ' , ' ' , ' ' , ' ' , 'x' ,' ' , 'x' , ' ' , ' ' , ' ' , 'x' ,' ' , 'x' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , 'x' , 'x' , 'x' , 'x' , 'x' ,'x' , 'x' , 'x' , 'x' , 'x' , 'x' ,'x' , 'x' , 'x' , 'x' , 'x' , 'x' }

};

/* ��ʼ��һ��ջ�ṹ */
Status InitStack(LinkStack);

/* ջ����ջ */
Status Pop(LinkStack top, SElemType *element);

/* �ж�ջ�Ƿ�Ϊ�� */
Status IsEmpty(LinkStack);

/* ������ѹ��ջ�� */
Status Push(LinkStack, SElemType*);

/* �������·�� */
void MarkFoot(SElemType);

/* ����޷�������ڵ���ͨ��· */
void NotAccessible(SElemType);

/* ����λ�� */
void NextPosition(SElemType *);

/* �ж��Ƿ��ͨ */
Status IsAccessible(SElemType);

/* Ѱ��·�� */
Status MazePath(SElemType, SElemType);

/* ��ʾ·�� */
void DisplayPath(void);