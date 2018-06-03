#include<stdio.h>
#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<math.h>

#define PI 3.141592653589793

/* �ص�ǰ�����ߣ�����Ϊdistance����distanceΪ����ʱ���� */
void forward(double distance);

/* ˳ʱ����ת�Ƕ�angle���Ƕȵ�λΪDEG����angleΪ����ʱ��ʱ����ת */
void turn(double angle);

/* �ص�ǰ�����ƶ��ʣ������ߣ�������Ϊdistance����distanceΪ����ʱ���� */
void move(double distance);

/* ����һ�������� */
void drawWidget(double r);

double CURRENT_ANGLE = 0;/* ��ǰ�Ƕ� */

int main()
{
	DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);/* ��ȡ��ʾ���� */
	DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);/* ��ȡ��ʾ���� */
	initgraph(screenWidth, screenHeight);/* ͼ�ν����ʼ�� */
	setlinecolor(0xAA00AA);/* ���û�����ɫ */
	setbkcolor(WHITE);/*  ��ʼ��������ɫ */
	settextcolor(BLACK);/* ��ʼ���ı���ɫ */
	cleardevice();
	moveto(screenWidth/2, screenHeight/2);
	double dangle = PI / 9;/* ÿ����ת�ĽǶ� */
	for (int i = 0; i < 18; i++)
	{
		drawWidget(159.63);
		CURRENT_ANGLE += dangle;
	}
	_getch();
}

/* �ص�ǰ�����ߣ�����Ϊdistance����distanceΪ����ʱ���� */
void forward(double distance)
{
	int dx = distance * cos(CURRENT_ANGLE);
	int dy = distance * sin(CURRENT_ANGLE);
	linerel(dx, dy);
}

/* ˳ʱ����ת�Ƕ�angle���Ƕȵ�λΪDEG����angleΪ����ʱ��ʱ����ת */
void turn(double angle)
{
	CURRENT_ANGLE = CURRENT_ANGLE - angle;
}

/* �ص�ǰ�����ƶ��ʣ������ߣ�������Ϊdistance����distanceΪ����ʱ���� */
void move(double distance)
{
	double dx = distance * cos(CURRENT_ANGLE);
	double dy = distance * sin(CURRENT_ANGLE);
	moverel(dx, dy);
}

/* ����һ�������� */
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