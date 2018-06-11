#include<graphics.h>
#include<conio.h>

#define TRUE 1
#define FALSE 0

int main()
{
	DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);/* 获取显示屏宽 */
	DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);/* 获取显示屏长 */
	MOUSEMSG m;/* 定义鼠标消息 */
	initgraph(screenWidth, screenHeight);/* 图形界面初始化 */
	setlinecolor(BLACK);/* 设置画笔颜色 */
	setbkcolor(WHITE);/*  初始化背景颜色 */
	setlinestyle(PS_SOLID,5);/* 画笔粗细 */
	cleardevice();
	while (TRUE) 
	{
		m = GetMouseMsg();/* 获取鼠标消息 */
		switch (m.uMsg)
		{
			case WM_MOUSEMOVE:
				if (m.mkLButton == TRUE)
					lineto(m.x, m.y);
				break;
			default:
				 moveto(m.x,m.y);/* 画图起始点随鼠标位置移动 */
		}
	}
}