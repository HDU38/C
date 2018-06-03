#include "drawstruct.h"
#include <windows.h>

BOOL isMove = FALSE; // 移动标志
BOOL isChangeSize = FALSE; // 缩放标志

/* 临时指向被选中的图形所在的结点 */
/* 椭圆 */
EllipseNode *EllipseTemp = NULL;
/* 长方形 */
RectangleNode *RectangleTemp = NULL;
/* 直线 */
LineNode *LineTemp = NULL;
/* 文本 */
TextNode *TextTemp = NULL;

/* 初始化所有图形链表 */
GraphList list = { InitEllipseList(),InitRectangleList(),InitLineList(),InitTextList() };

/* 工具栏图形 */
RectangleT sideRectangle = { 10,130,30,100,FALSE,FALSE };/* 长方形 */
EllipseT sideEllipse = { 10,160,30,140,FALSE,FALSE };/* 椭圆 */
LineT sideLine = { 10,190,30,170,FALSE,FALSE };/* 直线 */
SideBar sideBar = { sideRectangle,sideEllipse,sideLine };/* 文本 */

int main()
{
	DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);/* 获取显示屏宽 */
	DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);/* 获取显示屏长 */
	initgraph(screenWidth, screenHeight);/* 图形界面初始化 */
	setlinecolor(RED); /* 初始化画笔颜色 */
	setbkcolor(WHITE);/*  初始化背景颜色 */
	settextcolor(BLACK);/* 初始化文本颜色 */
	cleardevice();
	DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);/* 画出工具栏 */
	while (true)
	{
		if (_kbhit())
			KeyboardEventProcess(); /* 键盘消息 */
		if (MouseHit()) MouseEventProcess();/* 鼠标消息 */
	}
	return 0;
}

/* 产生随机的x坐标
*/
int RandomX()
{
	srand((unsigned)time(NULL) + rand());/* 制作种子 */
	int x = MIN_X + (rand() % (MAX_X + MIN_X - 1)) - 1;/* 产生随机坐标 */
	return x;
}

/* 产生随机的y坐标
*/
int RandomY()
{
	srand((unsigned)time(NULL) + rand());/* 制作种子 */
	int y = MIN_Y + (rand() % (MAX_Y + MIN_Y - 1)) - 1;/* 产生随机坐标 */
	return y;
}

/* 画出所有图形,参数依次为长方形图形的链表头指针,
*  椭圆图形的链表的头指针,直线图形的链表头指针,文
*  本图形链表的头指针
*/
void DrawAll(RectangleNode *RectangleHead, EllipseNode *EllipseHead, LineNode *LineHead, TextNode *TextHead)
{
	RectangleNode *RectangleHeadTemp = RectangleHead;
	EllipseNode *EllipseHeadTemp = EllipseHead;
	LineNode *LineHeadTemp = LineHead;
	TextNode *TextHeadTemp = TextHead;

	DrawSideBar();
	/* 与链表的遍历类似 */
	while ((RectangleHeadTemp = RectangleHeadTemp->next) != NULL)/* 只要指针非空就画出对应的图形 */
		rectangle(
			RectangleHeadTemp->rectangle->left,
			RectangleHeadTemp->rectangle->top,
			RectangleHeadTemp->rectangle->right,
			RectangleHeadTemp->rectangle->bottom
		);
	while ((EllipseHeadTemp = EllipseHeadTemp->next) != NULL)
		ellipse(
			EllipseHeadTemp->ellipse->left,
			EllipseHeadTemp->ellipse->top,
			EllipseHeadTemp->ellipse->right,
			EllipseHeadTemp->ellipse->bottom
		);
	while ((LineHeadTemp = LineHeadTemp->next) != NULL)
		line(LineHeadTemp->line->x1,
			LineHeadTemp->line->y1,
			LineHeadTemp->line->x2,
			LineHeadTemp->line->y2);

	while ((TextHeadTemp = TextHeadTemp->next) != NULL)
		drawtext(TextHeadTemp->text->str,
			TextHeadTemp->text->pRect,
			TextHeadTemp->text->uFormat);
}

/* 产生随机大小的矩形
*/
void RectangleGenertator()
{
	int x1 = RandomX();
	int y1 = RandomY();
	int x2 = RandomX();
	int y2 = RandomY();
	RectangleT *rptr = (RectangleT*)malloc(sizeof(RectangleT));
	rptr->top = y1 > y2 ? y1 : y2;
	rptr->bottom = y1 < y2 ? y1 : y2;
	rptr->left = x1 < x2 ? x1 : x2;
	rptr->right = x1 > x2 ? x1 : x2;
	rptr->isMove = FALSE;
	rptr->isChangeSize = FALSE;
	RectangleListInsert(list.RectangleList, rptr);
}

/* 产生随机大小的椭圆
*/
void EllipseGenertator()
{
	int x1 = RandomX();
	int y1 = RandomY();
	int x2 = RandomX();
	int y2 = RandomY();
	EllipseT *eptr = (EllipseT*)malloc(sizeof(EllipseT));
	eptr->top = y1 > y2 ? y1 : y2;
	eptr->bottom = y1 < y2 ? y1 : y2;
	eptr->left = x1 < x2 ? x1 : x2;
	eptr->right = x1 > x2 ? x1 : x2;
	eptr->isMove = FALSE;
	eptr->isChangeSize = FALSE;
	EllipseListInsert(list.EllipseList, eptr);
}

/* 产生随机长度的直线
*/
void LineGenertator()
{
	// 产生随机坐标
	int x1 = RandomX();
	int y1 = RandomY();
	int x2 = RandomX();
	int y2 = RandomY();
	LineT *lptr = (LineT*)malloc(sizeof(LineT));
	lptr->x1 = x1 < x2 ? x1 : x2;
	lptr->y1 = y1;
	lptr->x2 = x1 > x2 ? x1 : x2;
	lptr->y2 = y2;
	lptr->isMove = FALSE;
	lptr->isChangeSize = FALSE;
	LineListInsert(list.LineList, lptr);
}

/* 产生文本框
*/
void TextGenertator()
{
	int x1 = RandomX();
	int y1 = RandomY();
	int x2 = RandomX();
	int y2 = RandomY();
	char  s[10];
	int i = 0, j = 0;
	InputBox(s, 10,_T("请输入内容"));
	TextT *textr = (TextT*)malloc(sizeof(TextT));
	RECT *rec = (RECT*)malloc(sizeof(RECT));
	rec->top = y1 > y2 ? y1 : y2;
	rec->bottom = y1 < y2 ? y1 : y2;
	rec->left = x1 < x2 ? x1 : x2;
	rec->right = x1 > x2 ? x1 : x2;
	textr->pRect = rec;
	strcpy(textr->str,s);
	textr->uFormat = DT_CENTER | DT_VCENTER | DT_SINGLELINE;
	textr->isMove = FALSE;
	textr->isChangeSize = FALSE;
	TextListInsert(list.TextList, textr);
}

/* 处理键盘消息
*/
void KeyboardEventProcess()
{
	switch (_getch())
	{
		/* a: 随机生成直线 */
	case 'a':
		LineGenertator();
		break;
		/* s: 随机生成矩形*/
	case 's':
		RectangleGenertator();
		break;
		/* d: 随机生成椭圆 */
	case 'd':
		EllipseGenertator();
		break;
		/* w: 随机生成空的文本对象 */
	case 'w':
		TextGenertator();
		break;
	default:
		break;
	}
	DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
}

/* 处理鼠标消息
*/
void MouseEventProcess()
{
	MOUSEMSG m = GetMouseMsg();	/* 定义鼠标消息 */

	LineT *lptr = NULL;/* 直线 */
	RectangleT *rptr = NULL;/* 矩形 */
	EllipseT *eptr = NULL;/* 椭圆 */
	TextT *textr = NULL;
	int x1, y1, x2, y2;
	int dx;
	int dy;
	{
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:/* 移动标志 */
			if (FindSideGraph(m.x, m.y) > 0)
				switch (FindSideGraph(m.x, m.y))
				{
				case 1:/* s: 随机生成矩形*/
					x1 = RandomX();
					y1 = RandomY();
					x2 = RandomX();
					y2 = RandomY();
					rptr = (RectangleT*)malloc(sizeof(RectangleT));
					rptr->top = y1 > y2 ? y1 : y2;
					rptr->bottom = y1 < y2 ? y1 : y2;
					rptr->left = x1 < x2 ? x1 : x2;
					rptr->right = x1 > x2 ? x1 : x2;
					rptr->isMove = FALSE;
					rptr->isChangeSize = FALSE;
					RectangleListInsert(list.RectangleList, rptr);
					DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
					break;
				case 2: /* d: 随机生成椭圆 */
					x1 = RandomX();
					y1 = RandomY();
					x2 = RandomX();
					y2 = RandomY();
					eptr = (EllipseT*)malloc(sizeof(EllipseT));
					eptr->top = y1 > y2 ? y1 : y2;
					eptr->bottom = y1 < y2 ? y1 : y2;
					eptr->left = x1 < x2 ? x1 : x2;
					eptr->right = x1 > x2 ? x1 : x2;
					eptr->isMove = FALSE;
					eptr->isChangeSize = FALSE;
					EllipseListInsert(list.EllipseList, eptr);
					DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
					break;
				case 3:/* a: 随机生成直线 */
					x1 = RandomX();
					y1 = RandomY();
					x2 = RandomX();
					y2 = RandomY();
					lptr = (LineT*)malloc(sizeof(LineT));
					lptr->x1 = x1 < x2 ? x1 : x2;
					lptr->y1 = y1;
					lptr->x2 = x1 > x2 ? x1 : x2;
					lptr->y2 = y2;
					lptr->isMove = FALSE;
					lptr->isChangeSize = FALSE;
					LineListInsert(list.LineList, lptr);
					DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
					break;
				default:
					break;
				}
			TextTemp = FindTextN(list.TextList, m.x, m.y);
			if (TextTemp != NULL)
			{
				isMove = TRUE; // 左键按下，进入移动状态
				TextTemp->text->isMove = true;
				break;
			}
			RectangleTemp = FindRectangle(list.RectangleList, m.x, m.y);
			if (RectangleTemp != NULL)
			{
				isMove = TRUE; // 左键按下，进入移动状态
				RectangleTemp->rectangle->isMove = true;
				break;
			}
			EllipseTemp = FindEllipse(list.EllipseList, m.x, m.y);
			if (EllipseTemp != NULL)
			{
				isMove = TRUE; // 左键按下，进入移动状态
				EllipseTemp->ellipse->isMove = true;
				break;
			}
			LineTemp = FindLine(list.LineList, m.x, m.y);
			if (LineTemp != NULL)
			{
				isMove = TRUE; // 左键按下，进入移动状态
				LineTemp->line->isMove = true;
				break;
			}
		case WM_MOUSEMOVE: /* 移动图形 */
			if (m.mkLButton)
			{
				if (isMove == TRUE)
				{
					if (TextTemp != NULL && TextTemp->text->isMove == TRUE)
					{
						dx = (TextTemp->text->pRect->right - TextTemp->text->pRect->left) / 2;
						dy = (TextTemp->text->pRect->top - TextTemp->text->pRect->bottom) / 2;
						TextTemp->text->pRect->left = m.x - dx;
						TextTemp->text->pRect->top = m.y + dy;
						TextTemp->text->pRect->right = m.x + dx;
						TextTemp->text->pRect->bottom = m.y - dy;
						cleardevice();
						DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
						break;
					}
					if (RectangleTemp != NULL && RectangleTemp->rectangle->isMove == TRUE)
					{
						dx = (RectangleTemp->rectangle->right - RectangleTemp->rectangle->left) / 2;
						dy = (RectangleTemp->rectangle->top - RectangleTemp->rectangle->bottom) / 2;
						RectangleTemp->rectangle->left = m.x - dx;
						RectangleTemp->rectangle->top = m.y + dy;
						RectangleTemp->rectangle->right = m.x + dx;
						RectangleTemp->rectangle->bottom = m.y - dy;
						cleardevice();
						DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
						break;
					}
					EllipseTemp = FindEllipse(list.EllipseList, m.x, m.y);
					if (EllipseTemp != NULL)
					{
						dx = (EllipseTemp->ellipse->right - EllipseTemp->ellipse->left) / 2;
						dy = (EllipseTemp->ellipse->top - EllipseTemp->ellipse->bottom) / 2;
						EllipseTemp->ellipse->left = m.x - dx;
						EllipseTemp->ellipse->top = m.y + dy;
						EllipseTemp->ellipse->right = m.x + dx;
						EllipseTemp->ellipse->bottom = m.y - dy;
						cleardevice();
						DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
						break;
					}
					LineTemp = FindLine(list.LineList, m.x, m.y);
					if (LineTemp != NULL)
					{
						dx = (LineTemp->line->x2 - LineTemp->line->x1) / 2;
						dy = (LineTemp->line->y2 - LineTemp->line->y1) / 2;
						LineTemp->line->x1 = m.x - dx;
						LineTemp->line->y2 = m.y + dy;
						LineTemp->line->x2 = m.x + dx;
						LineTemp->line->y1 = m.y - dy;
						cleardevice();
						DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
						break;
					}
				}
			}
			if (m.mkRButton)/* 缩放 */
			{
				if (isChangeSize == TRUE)
				{
					if (RectangleTemp != NULL && RectangleTemp->rectangle->isMove == TRUE)
					{
						dx = (RectangleTemp->rectangle->right - RectangleTemp->rectangle->left) / 2;
						dy = (RectangleTemp->rectangle->top - RectangleTemp->rectangle->bottom) / 2;
						RectangleTemp->rectangle->right = m.x + dx;
						RectangleTemp->rectangle->bottom = m.y - dy;
						cleardevice();
						DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
						break;
					}
					EllipseTemp = FindEllipse(list.EllipseList, m.x, m.y);
					if (EllipseTemp != NULL)
					{
						dx = (EllipseTemp->ellipse->right - EllipseTemp->ellipse->left) / 2;
						dy = (EllipseTemp->ellipse->top - EllipseTemp->ellipse->bottom) / 2;
						EllipseTemp->ellipse->right = m.x + dx;
						EllipseTemp->ellipse->bottom = m.y - dy;
						cleardevice();
						DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
						break;
					}
					LineTemp = FindLine(list.LineList, m.x, m.y);
					if (LineTemp != NULL)
					{
						dx = (LineTemp->line->x2 - LineTemp->line->x1) / 2;
						dy = (LineTemp->line->y2 - LineTemp->line->y1) / 2;
						LineTemp->line->x2 = m.x + dx;
						LineTemp->line->y1 = m.y - dy;
						cleardevice();
						DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
						break;
					}
					TextTemp = FindTextN(list.TextList, m.x, m.y);
					if (TextTemp != NULL)
					{
						dx = (TextTemp->text->pRect->right - TextTemp->text->pRect->left) / 2;
						dy = (TextTemp->text->pRect->top - TextTemp->text->pRect->bottom) / 2;
						TextTemp->text->pRect->right = m.x + dx;
						TextTemp->text->pRect->bottom = m.y - dy;
						cleardevice();
						DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
						break;
					}
				}
			}
			break;
		case WM_RBUTTONDOWN:/* 缩放标志 */
			RectangleTemp = FindRectangle(list.RectangleList, m.x, m.y);
			if (RectangleTemp != NULL)
			{
				isChangeSize = TRUE; // 右键按下，进入缩放状态
				RectangleTemp->rectangle->isMove = true;
				break;
			}
			EllipseTemp = FindEllipse(list.EllipseList, m.x, m.y);
			if (EllipseTemp != NULL)
			{
				isChangeSize = TRUE; // 右键按下，进入缩放状态
				EllipseTemp->ellipse->isMove = true;
				break;
			}
			LineTemp = FindLine(list.LineList, m.x, m.y);
			if (LineTemp != NULL)
			{
				isChangeSize = TRUE; // 右键按下，进入缩放状态
				LineTemp->line->isMove = true;
				break;
			}
			TextTemp = FindTextN(list.TextList, m.x, m.y);
			if (TextTemp != NULL)
			{
				isChangeSize = TRUE; // 右键按下，进入缩放状态
				TextTemp->text->isMove = true;
				break;
			}
			break;
		case WM_LBUTTONDBLCLK:/* 删除图形 */
			if (RectangleTemp != NULL)
			{
				RectangleListDelete(list.RectangleList, RectangleTemp);
				RectangleTemp = NULL;
				cleardevice();
				DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
				break;
			}
			if (EllipseTemp != NULL)
			{
				EllipseListDelete(list.EllipseList, EllipseTemp);
				EllipseTemp = NULL;
				cleardevice();
				DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
				break;
			}
			if (LineTemp != NULL)
			{
				LineListDelete(list.LineList, LineTemp);
				LineTemp = NULL;
				cleardevice();
				DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
				break;
			}
			if (TextTemp != NULL)
			{
				TextListDelete(list.TextList, TextTemp);
				TextTemp = NULL;
				cleardevice();
				DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
				break;
			}
			break;
		case WM_RBUTTONDBLCLK:
			break;
		default:
			break;
		}
	}
}

/* 画出工具栏
*/
void DrawSideBar()
{
	rectangle(
		sideBar.rectangle.left,
		sideBar.rectangle.top,
		sideBar.rectangle.right,
		sideBar.rectangle.bottom);
	ellipse(
		sideBar.ellipse.left,
		sideBar.ellipse.top,
		sideBar.ellipse.right,
		sideBar.ellipse.bottom);
	line(
		sideBar.line.x1,
		sideBar.line.y1,
		sideBar.line.x2,
		sideBar.line.y2);
}

/* 当用户点击工具栏的图形时,该函数查
* 找用户点击的图形是哪一个,并返回一
* 个整数,(x,y)为点击位置的坐标
*/
int FindSideGraph(int x, int y)
{
	int tempx = x;
	int tempy = y;
	if (
		sideBar.rectangle.left <= x &&
		sideBar.rectangle.right >= x &&
		sideBar.rectangle.bottom <= y &&
		sideBar.rectangle.top >= y)
		return RECTANGLETAG;
	else if (
		sideBar.ellipse.left <= x &&
		sideBar.ellipse.right >= x &&
		sideBar.ellipse.bottom <= y &&
		sideBar.ellipse.top >= y)
		return ELLIPSETAG;
	else if (
		sideBar.line.x1 <= x &&
		sideBar.line.x2 >= x &&
		sideBar.line.y1 >= y &&
		sideBar.line.y2 <= y)
		return LINETAG;
	else return GRAPHNOTFOUND;

}

/* 初始化一个储存矩形图形的链表
*/
RectangleNode* InitRectangleList()
{
	RectangleNode *Head = (RectangleNode*)malloc(sizeof(RectangleNode));/* 申请存储空间，得到头结点 */
	if (!Head)
	{
		printf("初始化错误");
		return NULL;
	}
	Head->next = NULL;
	return Head;
}

/* 初始化一个储存椭圆图形的链表
*/
EllipseNode* InitEllipseList()
{
	EllipseNode *Head = (EllipseNode*)malloc(sizeof(EllipseNode));/* 申请存储空间，得到头结点 */
	if (!Head)
	{
		printf("初始化错误");
		return NULL;
	}
	Head->next = NULL;
	return Head;
}

/* 初始化一个储存直线图形的链表
*/
LineNode* InitLineList()
{
	LineNode *Head = (LineNode*)malloc(sizeof(LineNode));/* 申请存储空间，得到头结点 */
	if (!Head)
	{
		printf("初始化错误");
		return NULL;
	}
	Head->next = NULL;
	return Head;
}

/* 初始化一个储存文本图形的链表
*/
TextNode* InitTextList()
{
	TextNode *Head = (TextNode*)malloc(sizeof(TextNode));/* 申请存储空间，得到头结点 */
	if (!Head)
	{
		printf("初始化错误");
		return NULL;
	}
	Head->next = NULL;
	return Head;
}

/* 插入矩形类型结点
*/
void RectangleListInsert(RectangleNode *Head, RectangleT *item)
{
	RectangleNode *temp = Head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	RectangleNode *t = (RectangleNode*)malloc(sizeof(RectangleNode));
	t->rectangle = item;
	t->next = temp->next;
	temp->next = t;
}

/* 插入椭圆类型结点
*/
void EllipseListInsert(EllipseNode *Head, EllipseT *item)
{
	EllipseNode *temp = Head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	EllipseNode *t = (EllipseNode*)malloc(sizeof(EllipseNode));
	t->ellipse = item;
	t->next = temp->next;
	temp->next = t;
}

/* 插入直线类型结点
*/
void LineListInsert(LineNode *Head, LineT *item)
{
	LineNode *temp = Head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	LineNode *t = (LineNode*)malloc(sizeof(LineNode));
	t->line = item;
	t->next = temp->next;
	temp->next = t;
}

/* 插入文本类型结点
*/
void TextListInsert(TextNode *Head, TextT *item)
{
	TextNode *temp = Head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	TextNode *t = (TextNode*)malloc(sizeof(TextNode));
	t->text = item;
	t->next = temp->next;
	temp->next = t;
}

/* 获取矩形类型结点
*/
RectangleNode* FindRectangle(RectangleNode *Head, int x, int y)
{
	RectangleNode* temp = Head->next;
	while (temp != NULL) {
		if (
			temp->rectangle->left <= x &&
			temp->rectangle->right >= x &&
			temp->rectangle->bottom <= y &&
			temp->rectangle->top >= y)
			return temp;
		temp = temp->next;
	}
	return NULL;
}

/* 获取椭圆类型结点
*/
EllipseNode* FindEllipse(EllipseNode *Head, int x, int y)
{
	EllipseNode* temp = Head->next;
	while (temp != NULL) {
		if (
			temp->ellipse->left <= x &&
			temp->ellipse->right >= x &&
			temp->ellipse->bottom <= y &&
			temp->ellipse->top >= y)
			return temp;
		temp = temp->next;
	}
	return NULL;
}

/* 获取直线类型结点
*/
LineNode* FindLine(LineNode *Head, int x, int y)
{
	LineNode* temp = Head->next;
	while (temp != NULL)
	{
		LineT *pline = temp->line;
		if (pline->x1 != pline->x2)
		{
			double k = (pline->y2 - pline->y1) / (pline->x2 - pline->x1);// 直线斜率
			if (pline->x1 <= x &&
				pline->x2 >= x &&
				(
				(pline->y1 + k * (x - pline->x1 + 55) >= y &&
					pline->y1 + k * (x - pline->x1 - 55) <= y) ||
					(pline->y1 + k * (x - pline->x1 + 55) <= y &&
						pline->y1 + k * (x - pline->x1 - 55) >= y)))
				return temp;
		}
		if (pline->x1 == pline->x2 && (pline->x1 - 10) <= x && (pline->x2 + 10) >= x)
		{
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

/* 获取文本类型结点
*/
TextNode* FindTextN(TextNode *Head, int x, int y)
{
	TextNode* temp = Head->next;
	while (temp != NULL) {
		if (
			temp->text->pRect->left <= x &&
			temp->text->pRect->right >= x &&
			temp->text->pRect->bottom <= y &&
			temp->text->pRect->top >= y)
			return temp;
		temp = temp->next;
	}
	return NULL;
}

/* 删除矩形类型结点
*/
void RectangleListDelete(RectangleNode *Head, RectangleNode *item)
{
	RectangleNode *temp = Head;
	RectangleNode *t;
	while (temp->next != NULL)
	{
		if (temp->next == item) break;
		temp = temp->next;
	}
	if (!temp->next) return;
	t = temp->next;
	temp->next = t->next;
	free(t);
}

/* 删除椭圆类型结点
*/
void EllipseListDelete(EllipseNode *Head, EllipseNode *item)
{
	EllipseNode *temp = Head;
	EllipseNode *t;
	while (temp->next != NULL)
	{
		if (temp->next == item) break;
		temp = temp->next;
	}
	if (!temp->next) return;
	t = temp->next;
	temp->next = t->next;
	free(t);
}

/* 删除直线类型结点
*/
void LineListDelete(LineNode *Head, LineNode *item)
{
	LineNode *temp = Head;
	LineNode *t;
	while (temp->next != NULL)
	{
		if (temp->next == item) break;
		temp = temp->next;
	}
	if (!temp->next) return;
	t = temp->next;
	temp->next = t->next;
	free(t);
}

/* 删除文本类型结点
*/
void TextListDelete(TextNode *Head, TextNode *item)
{
	TextNode *temp = Head;
	TextNode *t;
	while (temp->next != NULL)
	{
		if (temp->next == item) break;
		temp = temp->next;
	}
	if (!temp->next) return;
	t = temp->next;
	temp->next = t->next;
	free(t);
}
