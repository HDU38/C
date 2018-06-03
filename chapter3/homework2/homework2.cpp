#include<stdio.h>
#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<math.h>

#define PI 3.141592653589793

/* 沿当前方向画线，长度为distance，当distance为负数时后退 */
void forward(double distance);

/* 顺时针旋转角度angle，角度单位为DEG，当angle为负数时逆时针旋转 */
void turn(double angle);

/* 沿当前方向移动笔（不画线），长度为distance，当distance为负数时后退 */
void move(double distance);

/* 画出一个六边形 */
void drawWidget(double r);

double CURRENT_ANGLE = 0;/* 当前角度 */

int main()
{
	DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);/* 获取显示屏宽 */
	DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);/* 获取显示屏长 */
	initgraph(screenWidth, screenHeight);/* 图形界面初始化 */
	setlinecolor(0xAA00AA);/* 设置画笔颜色 */
	setbkcolor(WHITE);/*  初始化背景颜色 */
	settextcolor(BLACK);/* 初始化文本颜色 */
	cleardevice();
	moveto(screenWidth/2, screenHeight/2);
	double dangle = PI / 9;/* 每次旋转的角度 */
	for (int i = 0; i < 18; i++)
	{
		drawWidget(159.63);
		CURRENT_ANGLE += dangle;
	}
	_getch();
}

/* 沿当前方向画线，长度为distance，当distance为负数时后退 */
void forward(double distance)
{
	int dx = distance * cos(CURRENT_ANGLE);
	int dy = distance * sin(CURRENT_ANGLE);
	linerel(dx, dy);
}

/* 顺时针旋转角度angle，角度单位为DEG，当angle为负数时逆时针旋转 */
void turn(double angle)
{
	CURRENT_ANGLE = CURRENT_ANGLE - angle;
}

/* 沿当前方向移动笔（不画线），长度为distance，当distance为负数时后退 */
void move(double distance)
{
	double dx = distance * cos(CURRENT_ANGLE);
	double dy = distance * sin(CURRENT_ANGLE);
	moverel(dx, dy);
}

/* 画出一个六边形 */
void drawWidget(double r)
{
	forward(r);
	for (int i = 0; i < 6; i++)
	{
		turn(-PI / 3);
		if (i == 2)
			forward(2 * r);
		else
			forward(r);
	}
}