#include "graphics.h"

extern "C" {
#include "ADT.h"
}

Node *THETALIST = InitList();
int length = 3;

/*���Ƽ�����ֱ�ߣ�����r���Ƕ�theta*/
static void DrawPolarLine(double r, double theta)
{
	double radians;
	printf("%f,%f ", r, theta);
	radians = theta / 180 * PI;
	linerel(r * cos(radians), r * sin(radians));
}

/*ΪTraverseLinkedList���ú����������ƵĻ���ֱ�ߺ���
*obj�ǽǶ�ָ�룬length��ֱ�߳��ȣ�ȫ�ֱ�����
*/
static void DrawKochSnowLine(double theta)
{
	DrawPolarLine(length, theta);
}

/* ÿ�������֮������������㣬�Դ������� */
static void ExpandList(Node *SnowList)
{
	Node *temp = SnowList->next;
	int preLength = ListLength(SnowList);
	int pos;
	for (pos = 1; pos <= preLength; pos++)
	{
		int i;
		for (i = 1; i <= 3; i++)/* ��������3���ս�� */
		{
			DataType data = FindItem(THETALIST,(pos - 1) * 3 + i)->data;
			ListInsert(SnowList, pos + 3 * (pos - 1) + i, data);
		}
	}
}

/* ���������η���Ϊ�ıߡ���ÿ�߽Ƕ�����Ϊ��theta, theta-60, theta+60, theta
* ���У�thetaΪԭ�ߵĽǶȣ�Ҳ����n-1�״����������ڵ��еĸ��߽Ƕ�
*/
static void SplitEdges(Node *SnowList)
{
	Node *thetaList = (Node*)malloc(sizeof(Node));
	Node *preThetaList = (Node*)malloc(sizeof(Node));
	Node *temp = SnowList;
	int i = 0;
	int length = ListLength(SnowList);
	while (++i<=length)
	{
		temp = temp->next;
		//preThetaList[i-1] = temp->data;
		ListInsert(preThetaList, i, temp->data);
	}
	int k;
	for (k = 0; k < length; k++)
	{
		ListInsert(THETALIST,3 * k + 1, FindItem(preThetaList,k + 1)->data - 60.0);
		ListInsert(THETALIST,3 * k + 2, FindItem(preThetaList, k + 1)->data + 60.0);
		ListInsert(THETALIST,3 * k + 3, FindItem(preThetaList, k + 1)->data);
	}
	ExpandList(SnowList);
}

/*�ݹ�����n��Kochѩ�����߽Ƕȵĺ���*/
static void KochSnow(Node *SnowList, int n)
{
	double ptheta;
	int i = 0;
	if (n == 0)
	{ /*0��ѩ������ʼ�����Σ������¶˿�ʼ���߽Ƕ�����Ϊ0��120��240*/
		ptheta = 0;
		ListInsert(SnowList, 1,ptheta);
		ptheta = 120;
		ListInsert(SnowList, 2,ptheta);
		ptheta = 240;
		ListInsert(SnowList, 3,ptheta);
	}
	else
	{
		KochSnow(SnowList, n - 1);/*���ɵ�n-1��Kochѩ������*/
		SplitEdges(SnowList);/*����n�ס��������߷��ѳ��ı�*/
	}
}

static void ListTraverse(Node *SnowList)
{
	Node *temp = SnowList;
	while (temp = temp->next)
		DrawKochSnowLine(temp->data);
}

int main()
{
	initgraph(1600, 960);/*ͼ�γ�ʼ��*/
	setlinecolor(RED); /*���û�����ɫ*/
	setbkcolor(WHITE);/* ���ñ�����ɫ */
	cleardevice();
	moveto(320, 180);

	Node* SnowList; /* �����������δ�Ÿ��߶εĽǶ� */
	double length;  /* ��ʼ�߳���inch��*/
	SnowList = InitList();
	KochSnow(SnowList, 6);

	ListTraverse(SnowList);
	getchar();
	return 0;
}