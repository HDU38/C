#include<graphics.h>
#include<conio.h>

#define TRUE 1
#define FALSE 0

int main()
{
	DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);/* ��ȡ��ʾ���� */
	DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);/* ��ȡ��ʾ���� */
	MOUSEMSG m;/* ���������Ϣ */
	initgraph(screenWidth, screenHeight);/* ͼ�ν����ʼ�� */
	setlinecolor(BLACK);/* ���û�����ɫ */
	setbkcolor(WHITE);/*  ��ʼ��������ɫ */
	setlinestyle(PS_SOLID,5);/* ���ʴ�ϸ */
	cleardevice();
	while (TRUE) 
	{
		m = GetMouseMsg();/* ��ȡ�����Ϣ */
		switch (m.uMsg)
		{
			case WM_MOUSEMOVE:
				if (m.mkLButton == TRUE)
					lineto(m.x, m.y);
				break;
			default:
				 moveto(m.x,m.y);/* ��ͼ��ʼ�������λ���ƶ� */
		}
	}
}