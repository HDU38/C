#include<graphics.h>
#include<conio.h>

#define TRUE 1

int main()
{
	DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);/* 获取显示屏宽 */
	DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);/* 获取显示屏长 */
	initgraph(screenWidth, screenHeight);/* 图形界面初始化 */
	setlinecolor(0xAA00AA);/* 设置画笔颜色 */
	setbkcolor(WHITE);/*  初始化背景颜色 */
	cleardevice();
	MOUSEMSG m;/* 定义鼠标消息 */
	while (TRUE) 
	{
		m = GetMouseMsg();
		int preX = m.x;
		int preY = m.y;
		switch (m.uMsg)
		{
			m = GetMouseMsg();
			case WM_MOUSEMOVE:
				if (m.mkLButton == TRUE) 
				{
					int dx = m.x - preX;
					int dy = m.y - preY;
					putpixel(m.x+dx, m.y+dy,BLACK);
				}
				break;
		}
	}
}