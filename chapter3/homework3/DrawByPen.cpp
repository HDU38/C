#include<graphics.h>
#include<conio.h>

#define TRUE 1

int main()
{
	DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);/* ��ȡ��ʾ���� */
	DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);/* ��ȡ��ʾ���� */
	initgraph(screenWidth, screenHeight);/* ͼ�ν����ʼ�� */
	setlinecolor(0xAA00AA);/* ���û�����ɫ */
	setbkcolor(WHITE);/*  ��ʼ��������ɫ */
	cleardevice();
	MOUSEMSG m;/* ���������Ϣ */
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