extern "C" 
{
#include "ChainListT.h"
}

#include "graphics.h"
#include "conio.h"
#include <math.h>


Node *THETALIST = InitList();/* 角度链表 */
int LENGTH = 0;/* 边长 */

/* 绘制极坐标直线，长度r，角度theta */
void DrawPolarLine(double r, double theta);

/* 每两个结点之间增加三个结点，以此扩充结点 */
void ExpandList(Node *SnowList);

/*
* 将各边依次分裂为四边——每边角度依次为：theta, theta-60, theta+60, theta其中，theta
* 为原边的角度，也就是n-1阶存放于链表各节点中的各边角度
*/
void SplitEdges(Node *SnowList);

/* 递归生成n阶Koch雪花各边角度的函数 */
void KochSnow(Node *SnowList, int n);

/* 按链表的顺序画出所有边 */
void ListTraverse(Node *SnowList);

int main()
{
	int n;/* 阶数 */
	char s[10];/* 定义字符串缓冲区，并接收用户输入 */
	Node* SnowList = InitList();; /* 链表各结点依次存放各线段的角度 */
	DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);/* 获取显示屏宽 */
	DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);/* 获取显示屏长 */
	initgraph(screenWidth, screenHeight);/*图形初始化*/
	setlinecolor(RED); /*设置画笔颜色*/
	setbkcolor(WHITE);/* 设置背景颜色 */
	cleardevice();
	moveto(screenWidth/5, screenHeight/5);
	InputBox(s, 10, "请输入阶数(建议小于6)和长度(阶数4长度5较理想)");
	sscanf(s, "%d %d", &n,&LENGTH);/* 将用户输入转换为数字 */
	int a = LENGTH;
	int b = a;
	if (n == NULL)
		exit(0);
	KochSnow(SnowList, n);
	ListTraverse(SnowList);
	getchar();
	return 0;
}

/* 绘制极坐标直线，长度r，角度theta */
void DrawPolarLine(double r, double theta)
{
	double radians;
	printf("%f,%f ", r, theta);
	radians = theta / 180 * PI;
	linerel(r * cos(radians), r * sin(radians));
}

/* 每两个结点之间增加三个结点，以此扩充结点 */
void ExpandList(Node *SnowList)
{
	Node *temp = SnowList->next;
	int preLength = ListLength(SnowList);/* 原来的链表长度 */
	int pos;
	for (pos = 1; pos <= preLength; pos++)
	{
		int i;
		for (i = 1; i <= 3; i++)/* 连续插入3个空结点 */
		{
			DataType data = FindItem(THETALIST, (pos - 1) * 3 + i)->data;
			ListInsert(SnowList, pos + 3 * (pos - 1) + i, data);
		}
	}
}

/* 
* 将各边依次分裂为四边——每边角度依次为：theta, theta-60, theta+60, theta其中，theta
* 为原边的角度，也就是n-1阶存放于链表各节点中的各边角度
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
		/* 分裂为4个角度,其中一个角度已存在原链表中,无需插入 */
		ListInsert(THETALIST, 3 * k + 1, FindItem(preThetaList, k + 1)->data - 60.0);
		ListInsert(THETALIST, 3 * k + 2, FindItem(preThetaList, k + 1)->data + 60.0);
		ListInsert(THETALIST, 3 * k + 3, FindItem(preThetaList, k + 1)->data);
	}
	ExpandList(SnowList);/* 扩充链表，准备下一轮分裂 */
}

/* 递归生成n阶Koch雪花各边角度的函数 */
void KochSnow(Node *SnowList, int n)
{
	double ptheta;
	int i = 0;
	/* 0阶雪花即初始三角形，从左下端开始各边角度依次为0，120，240 */
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
		KochSnow(SnowList, n - 1);/* 生成第n-1阶Koch雪花各边 */
		SplitEdges(SnowList);/* 生成n阶——将各边分裂成四边 */
	}
}

/* 按链表的顺序画出所有边 */
void ListTraverse(Node *SnowList)
{
	Node *temp = SnowList;
	while (temp = temp->next)
		DrawPolarLine(LENGTH, temp->data);
}