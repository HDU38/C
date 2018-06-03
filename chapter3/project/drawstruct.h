#ifndef _DRAWSTRUCT_H_
#define _DRAWSTRUCT_H

#include<stdio.h>
#include<malloc.h>
#include "conio.h"
#include <stdlib.h>
#include <windows.h>

#include "graphics.h"
#include "time.h"

DWORD WINDOWSWIDTH = GetSystemMetrics(SM_CXSCREEN);
DWORD WINDOWSHEIGHT = GetSystemMetrics(SM_CYSCREEN);

#define TRUE 1
#define FALSE 0
#define PI 3.14159265358979323846264338327950288419716939937510

#define RECTANGLETAG 1
#define ELLIPSETAG 2
#define LINETAG 3
#define GRAPHNOTFOUND -1

#define MIN_X 0
#define MAX_X WINDOWSWIDTH
#define MIN_Y 0
#define MAX_Y WINDOWSHEIGHT


/* ���������� */
typedef struct RectangleNode
{
	struct RectangleT *rectangle;
	struct RectangleNode *next;//nextΪָ����һ����ָ��
}RectangleNode;

/* ��Բ������ */
typedef struct EllipseNode
{
	struct EllipseT *ellipse;
	struct EllipseNode *next;//nextΪָ����һ����ָ��
}EllipseNode;

/* ֱ�������� */
typedef struct LineNode
{
	struct LineT *line;
	struct LineNode *next;//nextΪָ����һ����ָ��
}LineNode;

/* �ı������� */
typedef struct TextNode
{
	struct TextT *text;
	struct TextNode *next;
}TextNode;

/* ��Բ���� */
typedef struct EllipseT
{
	int left; // ��Բ���о����󲿵�x����
	int top; // ��Բ���о����ϲ���y���� top>bottom
	int right; // ��Բ���о����Ҳ���x����
	int bottom; // ��Բ���о����²���y����
	int isMove;// �ƶ���־
	int isChangeSize;// ���ű�־
}EllipseT;

/* �������� */
typedef struct RectangleT{
	int left; // ������ x ����
	int top;// �����ϲ� x ����top>bottom
	int right;// �����Ҳ� x ����
	int bottom;// �����²� x ����
	int isMove;// �ƶ���־
	int isChangeSize;// ���ű�־
}RectangleT;

/* ֱ������ */
typedef struct LineT
{
	int x1;
	int y1; // ��һ��������,�涨x1<x2
	int x2;
	int y2; // �ڶ���������
	int isMove;// �ƶ���־
	int isChangeSize;// ���ű�־
}LineT;

/* �ı����� */
typedef struct TextT 
{
	char str[10];// �ַ���
	RECT* pRect;// ��������
	UINT uFormat;// �ı���ʽ
	int isMove;// �ƶ���־
	int isChangeSize;// ���ű�־
}TextT;

/* �������� */
typedef struct GraphList
{
	EllipseNode *EllipseList;
	RectangleNode *RectangleList;
	LineNode *LineList;
	TextNode *TextList;
}GraphList;

/* ������ */
typedef struct SideBar
{
	struct RectangleT rectangle;
	struct EllipseT ellipse;
	struct LineT line;
}SideBar;

/* ��ʼ��һ������ */
RectangleNode* InitRectangleList();
EllipseNode* InitEllipseList();
LineNode* InitLineList();
TextNode *InitTextList();

/* ����ͼ�� */
void RectangleListInsert(RectangleNode *, RectangleT *item);
void EllipseListInsert(EllipseNode *, EllipseT *item);
void LineListInsert(LineNode *, LineT *item);
void TextListInsert(TextNode *, TextT *item);

/* ɾ������ */
void RectangleListDelete(RectangleNode *, RectangleNode *item);
void EllipseListDelete(EllipseNode *, EllipseNode *item);
void LineListDelete(LineNode *, LineNode *item);
void TextListDelete(TextNode *, TextNode *item);

/* ��ȡͼ�� */
RectangleNode* FindRectangle(RectangleNode *Head, int x, int y);
EllipseNode* FindEllipse(EllipseNode *Head, int x, int y);
LineNode* FindLine(LineNode *Head, int x, int y);
TextNode* FindTextN(TextNode *Head, int x, int y);

/* ���������С�ľ��� */
void RectangleGenertator();

/* ���������С����Բ */
void EllipseGenertator();

/* ����������ȵ�ֱ�� */
void LineGenertator();

/* �����ı��� */
void TextGenertator();

/* ���x���� */
int RandomX();

/* �������y���� */
int RandomY();

/* ��������ͼ�� */
void DrawAll(RectangleNode *, EllipseNode *, LineNode *, TextNode *);

/* ���������� */
void DrawSideBar();

/* ��Ӧ����¼� */
void MouseEventProcess();

/* ��Ӧ�����¼�*/
void KeyboardEventProcess();

/* ��ȡ��������ͼ�� */
int FindSideGraph(int x, int y);

#endif
