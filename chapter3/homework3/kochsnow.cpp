#include "graphics.h"

extern "C" {
#include "ADT.h"
}

Node *THETALIST = InitList();
int length = 3;

/*绘制极坐标直线，长度r，角度theta*/
static void DrawPolarLine(double r, double theta)
{
	double radians;
	printf("%f,%f ", r, theta);
	radians = theta / 180 * PI;
	linerel(r * cos(radians), r * sin(radians));
}

/*为TraverseLinkedList调用函数参数定制的绘制直线函数
*obj是角度指针，length是直线长度（全局变量）
*/
static void DrawKochSnowLine(double theta)
{
	DrawPolarLine(length, theta);
}

/* 每两个结点之间增加三个结点，以此扩充结点 */
static void ExpandList(Node *SnowList)
{
	Node *temp = SnowList->next;
	int preLength = ListLength(SnowList);
	int pos;
	for (pos = 1; pos <= preLength; pos++)
	{
		int i;
		for (i = 1; i <= 3; i++)/* 连续插入3个空结点 */
		{
			DataType data = FindItem(THETALIST,(pos - 1) * 3 + i)->data;
			ListInsert(SnowList, pos + 3 * (pos - 1) + i, data);
		}
	}
}

/* 将各边依次分裂为四边——每边角度依次为：theta, theta-60, theta+60, theta
* 其中，theta为原边的角度，也就是n-1阶存放于链表各节点中的各边角度
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

/*递归生成n阶Koch雪花各边角度的函数*/
static void KochSnow(Node *SnowList, int n)
{
	double ptheta;
	int i = 0;
	if (n == 0)
	{ /*0阶雪花即初始三角形，从左下端开始各边角度依次为0，120，240*/
		ptheta = 0;
		ListInsert(SnowList, 1,ptheta);
		ptheta = 120;
		ListInsert(SnowList, 2,ptheta);
		ptheta = 240;
		ListInsert(SnowList, 3,ptheta);
	}
	else
	{
		KochSnow(SnowList, n - 1);/*生成第n-1阶Koch雪花各边*/
		SplitEdges(SnowList);/*生成n阶——将各边分裂成四边*/
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
	initgraph(1600, 960);/*图形初始化*/
	setlinecolor(RED); /*设置画笔颜色*/
	setbkcolor(WHITE);/* 设置背景颜色 */
	cleardevice();
	moveto(320, 180);

	Node* SnowList; /* 链表各结点依次存放各线段的角度 */
	double length;  /* 初始边长（inch）*/
	SnowList = InitList();
	KochSnow(SnowList, 6);

	ListTraverse(SnowList);
	getchar();
	return 0;
}