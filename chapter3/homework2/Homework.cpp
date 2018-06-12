#include<stdio.h>
#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<math.h>

#define PI 3.141592653589793

/* 沿当前方向画线，长度为distance，当distance为负数时后退 */
void forward(int distance);
/* 顺时针旋转角度angle，角度单位为DEG，当angle为负数时逆时针旋转 */
void turn(double angle);
/* 沿当前方向移动笔（不画线），长度为distance，当distance为负数时后退 */
void move(int distance);
/* 画出一个六边形 */
void drawWidget(int r);

/* 当前角度 */
double CURRENT_ANGLE = 0;


int main()
{
	DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);/* 获取显示屏宽 */
	DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);/* 获取显示屏长 */
	initgraph(screenWidth, screenHeight);/* 图形界面初始化 */
	setlinecolor(0xAA00AA);/* 设置画笔颜色 */
	setbkcolor(WHITE);/*  初始化背景颜色 */
	settextcolor(BLACK);/* 初始化文本颜色 */
	cleardevice();
	moveto(screenWidth/2, screenHeight/2);/* 移动至屏幕中心 */
	double dangle = PI / 9;/* 每次旋转的角度 */
	for (int i = 0; i < 18; i++)
	{
		drawWidget(160);
		CURRENT_ANGLE += dangle;
	}
	if (_getch()) exit(0);
}

/* 沿当前方向画线，长度为distance，当distance为负数时后退 */
void forward(int distance)
{
	double dx = (double)distance * cos(CURRENT_ANGLE);
	double dy = (double)distance * sin(CURRENT_ANGLE);
	linerel(dx, dy);
}

/* 顺时针旋转角度angle，角度单位为DEG，当angle为负数时逆时针旋转 */
void turn(double angle)
{
	CURRENT_ANGLE = CURRENT_ANGLE - angle;
}

/* 沿当前方向移动笔（不画线），长度为distance，当distance为负数时后退 */
void move(int distance)
{
	double dx = (double)distance * cos(CURRENT_ANGLE);
	double dy = (double)distance * sin(CURRENT_ANGLE);
	moverel(dx, dy);
}

/* 画出一个六边形,r为边长 */
void drawWidget(int r)
{
	int i;
	forward(r);
	for (i = 0; i < 6; i++)
	{
		turn(-PI / 3);
		if (i == 2)
			forward(2 * r);
		else
			forward(r);
	}
}