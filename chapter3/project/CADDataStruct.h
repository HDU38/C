#ifndef _CADDATASTRUCT_H_
#define _CADDATASTRUCT_H

#include<stdio.h>
#include<malloc.h>
#include "conio.h"
#include <stdlib.h>
#include <windows.h>

#include "graphics.h"
#include "time.h"

#define MAX(a, b) a > b ? a : b
#define MIN(a, b) a < b ? a : b

#define TRUE 1
#define FALSE 0

#define RECTANGLETAG 1/* 工具栏-矩形标签 */
#define ELLIPSETAG 2/* 工具栏-椭圆标签 */
#define LINETAG 3/* 工具栏-直线标签 */
#define TEXTTAG 4/* 工具栏-文本标签 */
#define GRAPHNOTFOUND -1/* 未找到图形 */


/* 矩形链表结点 */
typedef struct RectangleNode
{
	struct RectangleT *rectangle;
	struct RectangleNode *next;/* next为指向下一结点的指针 */
}RectangleNode;

/* 椭圆链表结点 */
typedef struct EllipseNode
{
	struct EllipseT *ellipse;
	struct EllipseNode *next;/* next为指向下一结点的指针 */
}EllipseNode;

/* 直线链表结点 */
typedef struct LineNode
{
	struct LineT *line;
	struct LineNode *next;/* next为指向下一结点的指针 */
}LineNode;

/* 文本链表结点 */
typedef struct TextNode
{
	struct TextT *text;
	struct TextNode *next;/* next为指向下一结点的指针 */
}TextNode;

/* 椭圆类型 */
typedef struct EllipseT
{
	int left; /* 椭圆外切矩形左部的x坐标 */
	int top; /* 椭圆外切矩形上部的y坐标 top>bottom */
	int right; /* 椭圆外切矩形右部的x坐标 */
	int bottom; /* 椭圆外切矩形下部的y坐标 */
	int isMove;/* 移动标志 */
	int isChangeSize;// 缩放标志 */
}EllipseT;

/* 矩形类型 */
typedef struct RectangleT{
	int left; /* 矩形左部 x 坐标 */
	int top;/* 矩形上部 x 坐标top>bottom */
	int right;/* 矩形右部 x 坐标 */
	int bottom;/* 矩形下部 x 坐标 */
	int isMove;/* 移动标志 */
	int isChangeSize;/* 缩放标志 */
}RectangleT;

/* 直线类型 */
typedef struct LineT
{
	int x1;
	int y1; /* 第一个点坐标,规定x1<x2 */
	int x2;
	int y2; /* 第二个点坐标 */
	int isMove;/* 移动标志 */
	int isChangeSize;/* 缩放标志 */
}LineT;

/* 文本类型 */
typedef struct TextT 
{
	char str[20];/* 字符串 */
	RECT* pRect;/* 矩形区域 */
	UINT uFormat;/* 文本格式 */
	int isMove;/* 移动标志 */
	int isChangeSize;/* 缩放标志 */
	int nHeight;/* 字体高 */
	int nWidth;/* 字体宽 */
}TextT;

/* 所有链表 */
typedef struct GraphList
{
	EllipseNode *EllipseList;
	RectangleNode *RectangleList;
	LineNode *LineList;
	TextNode *TextList;
}GraphList;

/* 工具栏 */
typedef struct SideBar
{
	struct RectangleT rectangle;
	struct EllipseT ellipse;
	struct LineT line;
	struct TextT text;
}SideBar;

/* 初始化一个链表 */
RectangleNode* InitRectangleList();
EllipseNode* InitEllipseList();
LineNode* InitLineList();
TextNode *InitTextList();

/* 插入图形 */
void RectangleListInsert(RectangleNode *, RectangleT *item);
void EllipseListInsert(EllipseNode *, EllipseT *item);
void LineListInsert(LineNode *, LineT *item);
void TextListInsert(TextNode *, TextT *item);

/* 删除数据 */
void RectangleListDelete(RectangleNode *, RectangleNode *item);
void EllipseListDelete(EllipseNode *, EllipseNode *item);
void LineListDelete(LineNode *, LineNode *item);
void TextListDelete(TextNode *, TextNode *item);

/* 获取图形 */
RectangleNode* FindRectangle(RectangleNode *Head, int x, int y);
EllipseNode* FindEllipse(EllipseNode *Head, int x, int y);
LineNode* FindLine(LineNode *Head, int x, int y);
TextNode* FindTextN(TextNode *Head, int x, int y);

/* 产生随机大小的矩形 */
void RectangleGenertator();

/* 产生随机大小的椭圆 */
void EllipseGenertator();

/* 产生随机长度的直线 */
void LineGenertator();

/* 产生文本框 */
void TextGenertator();

/* 随机x坐标 */
int RandomX();

/* 随机产生y坐标 */
int RandomY();

/* 画出所有图形 */
void DrawAll(RectangleNode *, EllipseNode *, LineNode *, TextNode *);

/* 画出工具栏 */
void DrawSideBar();

/* 回应鼠标事件 */
void MouseEventProcess(MOUSEMSG mouseMsg);

/* 回应键盘事件*/
void KeyboardEventProcess(int keyboardMsg);

/* 获取工具栏的图形 */
int FindSideGraph(int x, int y);

#endif
