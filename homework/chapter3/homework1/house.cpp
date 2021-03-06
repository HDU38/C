#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include "conio.h"

#define HOUSE_HEIGHT         200 /* 房子高度 */
#define HOUSE_WIDTH          160 /* 房子宽度 */
#define ATTIC_HEIGHT         120 /* 房顶三角形高度 */
#define WINDOW_LENGTH        40 /* 窗户边长 */
#define DOOR_WIDTH           40 /* 门宽 */
#define DOOR_HEIGHT          160 /* 门高 */
#define CHIMNEY_WIDTH        25 /* 烟囱宽 */

/* 所有函数 */
void DrawHouse(int x, int y);
void DrawOutline(int x, int y);
void DrawWindows(int x, int y);
void DrawDoor(int x, int y);
void DrawBox(int x, int y, int width, int height);
void DrawTriangle(int x, int y, int base, int height);
void DrawChimney(int x, int y, int width, int leftheight, int rightheight);

int main()
{
	initgraph(960,480);/* 初始化界面 */
	setbkcolor(0xFFFFFF);/* 设置背景颜色 */
	setlinecolor(0);/* 设置画笔颜色 */
	cleardevice();/* 清屏 */
	DrawHouse(360,400);
	if (_getch()) exit(0);
}

/* 画一个房子,x,y为房子左下角坐标 */
void DrawHouse(int x, int y)
{
	DrawOutline(x, y);
	DrawDoor(x + 85, y);
	DrawWindows(x + 30, y - 120);
}

/* 画房子的轮廊 */
void DrawOutline(int x, int y)
{
	int lefthigh = ATTIC_HEIGHT * 2 / 3;/* 烟囱左边的高度 */
	int righthigh = lefthigh - 25 * ATTIC_HEIGHT * 2 / HOUSE_WIDTH;/* 烟囱右边的高度 */
	int dy = 215;/* 设置坐标偏移量 */
	int dx = 10;/* 同上 */
	DrawBox(x, y, HOUSE_WIDTH, HOUSE_HEIGHT);/* 画一个矩形 */
	DrawTriangle(x, y - HOUSE_HEIGHT, HOUSE_WIDTH, ATTIC_HEIGHT);/* 画房顶 */
	DrawChimney(x + dx, y - dy, CHIMNEY_WIDTH,lefthigh,righthigh);/* 画烟囱 */
}

/* 画门 */
void DrawDoor(int x, int y)
{
	DrawBox(x, y, DOOR_WIDTH, DOOR_HEIGHT);
}

/* 画窗户 */
void DrawWindows(int x, int y)
{
	DrawBox(x, y, WINDOW_LENGTH, WINDOW_LENGTH);
}

/* 画矩形,x,y为矩形左下角坐标 */
void DrawBox(int x, int y, int width, int height)
{
	moveto(x, y);
	linerel(0, -height);
	linerel(width, 0);
	linerel(0, height);
	linerel(-width, 0);
}

/* 画三角形,x,y为三角形左下角坐标,base为底,height为高 */
void DrawTriangle(int x, int y, int base, int height)
{
	moveto(x, y);
	linerel(base, 0);
	linerel(-base / 2, -height);
	linerel(-base / 2, height);
}

/* 画烟囱,x,y为左下角坐标,width为宽,leftheight为左高,rightheight为右高 */
void DrawChimney(int x, int y, int width, int leftheight, int rightheight) 
{
	moveto(x, y);
	linerel(0,-leftheight);
	linerel(width, 0);
	linerel(0, rightheight);
	DrawBox(x - width / 3, y - leftheight, 5 * width / 3, leftheight / 8);
}

