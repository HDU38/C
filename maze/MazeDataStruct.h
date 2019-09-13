#ifndef COMMONDATA_H_
#define COMMONDATA_H_

#include<stdio.h>
#include<time.h>
#include<malloc.h>
#include "conio.h"
#include "graphics.h"
#include<math.h>

#define TRUE 1
#define FALSE 0
#define MAZEROWNUM 18// �Թ��ĳ��Ϳ�
#define DIGITROW 13// ������ռ����
#define DIGITCOL 8// ������ռ����
#define WINDOWSWIDTH 960// ���ڳ�
#define WINDOWSHEIGHT 520// ���ڿ�
#define LEFTMARGIN 10//�Թ���߾�
#define RIGHTMARGIN 110// �Թ��ұ߾�
#define TOPMARGIN 50// �Թ��±߾�
#define BOTTOMTMARGIN 50// �Թ��ϱ߾�

typedef  int Status;

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

/* �����ɫ */
typedef struct mazeColor
{
	int r;
	int g;
	int b;
}mazeColor;

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
void DisplayPath(SElemType);

void DrawMaze();

void MazeGenerator(int ,int);

void SetMazeColor();

void Start(int,int);

void ArrayCopy(char(*a)[DIGITCOL], char(*b)[DIGITCOL]);

void SwitchDay(int);

void SwitchMonth(int);

extern char
ZERO[DIGITROW][DIGITCOL],
ONE[DIGITROW][DIGITCOL],
TWO[DIGITROW][DIGITCOL],
THREE[DIGITROW][DIGITCOL],
FOUR[DIGITROW][DIGITCOL],
FIVE[DIGITROW][DIGITCOL],
SIX[DIGITROW][DIGITCOL],
SEVEN[DIGITROW][DIGITCOL],
EIGHT[DIGITROW][DIGITCOL],
NINE[DIGITROW][DIGITCOL];

#endif