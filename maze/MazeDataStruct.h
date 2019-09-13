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
#define MAZEROWNUM 18// 迷宫的长和宽
#define DIGITROW 13// 数字所占行数
#define DIGITCOL 8// 数字所占列数
#define WINDOWSWIDTH 960// 窗口长
#define WINDOWSHEIGHT 520// 窗口宽
#define LEFTMARGIN 10//迷宫左边距
#define RIGHTMARGIN 110// 迷宫右边距
#define TOPMARGIN 50// 迷宫下边距
#define BOTTOMTMARGIN 50// 迷宫上边距

typedef  int Status;

/* 位置结构 */
typedef struct Position
{
	int x;/* 行 */
	int y;/* 列 */
	int derection;/* 方向：1、2、3、4依次代表东、南、西、北 */
}SElemType, *ElemType;

/* 栈结构 */
typedef struct node
{
	struct Position *data;/* 因为后面涉及位置方向的变化，因此储存指向位置结构的指针更加方便 */
	struct node *next;
}StackNode, *LinkStack;

/* 填充颜色 */
typedef struct mazeColor
{
	int r;
	int g;
	int b;
}mazeColor;

/* 初始化一个栈结构 */
Status InitStack(LinkStack);

/* 栈顶出栈 */
Status Pop(LinkStack top, SElemType *element);

/* 判断栈是否为空 */
Status IsEmpty(LinkStack);

/* 将数据压入栈顶 */
Status Push(LinkStack, SElemType*);

/* 标记已走路径 */
void MarkFoot(SElemType);

/* 标记无法到达出口但可通的路 */
void NotAccessible(SElemType);

/* 更新位置 */
void NextPosition(SElemType *);

/* 判断是否可通 */
Status IsAccessible(SElemType);

/* 寻找路径 */
Status MazePath(SElemType, SElemType);

/* 显示路径 */
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