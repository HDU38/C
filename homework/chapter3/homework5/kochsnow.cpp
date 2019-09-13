extern "C" 
{
#include "ChainListT.h"
}

#include "graphics.h"
#include "conio.h"
#include <math.h>


Node *THETALIST = InitList();/* �Ƕ����� */
int LENGTH = 0;/* �߳� */

/* ���Ƽ�����ֱ�ߣ�����r���Ƕ�theta */
void DrawPolarLine(double r, double theta);

/* ÿ�������֮������������㣬�Դ������� */
void ExpandList(Node *SnowList);

/*
* ���������η���Ϊ�ıߡ���ÿ�߽Ƕ�����Ϊ��theta, theta-60, theta+60, theta���У�theta
* Ϊԭ�ߵĽǶȣ�Ҳ����n-1�״����������ڵ��еĸ��߽Ƕ�
*/
void SplitEdges(Node *SnowList);

/* �ݹ�����n��Kochѩ�����߽Ƕȵĺ��� */
void KochSnow(Node *SnowList, int n);

/* �������˳�򻭳����б� */
void ListTraverse(Node *SnowList);

int main()
{
	int n;/* ���� */
	char s[10];/* �����ַ������������������û����� */
	Node* SnowList = InitList();; /* �����������δ�Ÿ��߶εĽǶ� */
	DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);/* ��ȡ��ʾ���� */
	DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);/* ��ȡ��ʾ���� */
	initgraph(screenWidth, screenHeight);/*ͼ�γ�ʼ��*/
	setlinecolor(RED); /*���û�����ɫ*/
	setbkcolor(WHITE);/* ���ñ�����ɫ */
	cleardevice();
	moveto(screenWidth/5, screenHeight/5);
	InputBox(s, 10, "���������(����С��6)�ͳ���(����4����5������)");
	sscanf(s, "%d %d", &n,&LENGTH);/* ���û�����ת��Ϊ���� */
	int a = LENGTH;
	int b = a;
	if (n == NULL)
		exit(0);
	KochSnow(SnowList, n);
	ListTraverse(SnowList);
	getchar();
	return 0;
}

/* ���Ƽ�����ֱ�ߣ�����r���Ƕ�theta */
void DrawPolarLine(double r, double theta)
{
	double radians;
	printf("%f,%f ", r, theta);
	radians = theta / 180 * PI;
	linerel(r * cos(radians), r * sin(radians));
}

/* ÿ�������֮������������㣬�Դ������� */
void ExpandList(Node *SnowList)
{
	Node *temp = SnowList->next;
	int preLength = ListLength(SnowList);/* ԭ���������� */
	int pos;
	for (pos = 1; pos <= preLength; pos++)
	{
		int i;
		for (i = 1; i <= 3; i++)/* ��������3���ս�� */
		{
			DataType data = FindItem(THETALIST, (pos - 1) * 3 + i)->data;
			ListInsert(SnowList, pos + 3 * (pos - 1) + i, data);
		}
	}
}

/* 
* ���������η���Ϊ�ıߡ���ÿ�߽Ƕ�����Ϊ��theta, theta-60, theta+60, theta���У�theta
* Ϊԭ�ߵĽǶȣ�Ҳ����n-1�״����������ڵ��еĸ��߽Ƕ�
*/
void SplitEdges(Node *SnowList)
{
	Node *thetaList = (Node*)malloc(sizeof(Node));
	Node *preThetaList = (Node*)malloc(sizeof(Node));
	Node *temp = SnowList;
	int i = 0;
	int length = ListLength(SnowList);
	while (++i <= length)
	{
		temp = temp->next;
		ListInsert(preThetaList, i, temp->data);
	}
	int k;
	for (k = 0; k < length; k++)
	{
		/* ����Ϊ4���Ƕ�,����һ���Ƕ��Ѵ���ԭ������,������� */
		ListInsert(THETALIST, 3 * k + 1, FindItem(preThetaList, k + 1)->data - 60.0);
		ListInsert(THETALIST, 3 * k + 2, FindItem(preThetaList, k + 1)->data + 60.0);
		ListInsert(THETALIST, 3 * k + 3, FindItem(preThetaList, k + 1)->data);
	}
	ExpandList(SnowList);/* ��������׼����һ�ַ��� */
}

/* �ݹ�����n��Kochѩ�����߽Ƕȵĺ��� */
void KochSnow(Node *SnowList, int n)
{
	double ptheta;
	int i = 0;
	/* 0��ѩ������ʼ�����Σ������¶˿�ʼ���߽Ƕ�����Ϊ0��120��240 */
	if (n == 0)
	{ 
		ptheta = 0;
		ListInsert(SnowList, 1, ptheta);
		ptheta = 120;
		ListInsert(SnowList, 2, ptheta);
		ptheta = 240;
		ListInsert(SnowList, 3, ptheta);
	}
	else
	{
		KochSnow(SnowList, n - 1);/* ���ɵ�n-1��Kochѩ������ */
		SplitEdges(SnowList);/* ����n�ס��������߷��ѳ��ı� */
	}
}

/* �������˳�򻭳����б� */
void ListTraverse(Node *SnowList)
{
	Node *temp = SnowList;
	while (temp = temp->next)
		DrawPolarLine(LENGTH, temp->data);
}