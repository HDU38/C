#include "drawstruct.h"
#include <windows.h>

BOOL isMove = FALSE; // �ƶ���־
BOOL isChangeSize = FALSE; // ���ű�־

/* ��ʱָ��ѡ�е�ͼ�����ڵĽ�� */
/* ��Բ */
EllipseNode *EllipseTemp = NULL;
/* ������ */
RectangleNode *RectangleTemp = NULL;
/* ֱ�� */
LineNode *LineTemp = NULL;
/* �ı� */
TextNode *TextTemp = NULL;

/* ��ʼ������ͼ������ */
GraphList list = { InitEllipseList(),InitRectangleList(),InitLineList(),InitTextList() };

/* ������ͼ�� */
RectangleT sideRectangle = { 10,130,30,100,FALSE,FALSE };/* ������ */
EllipseT sideEllipse = { 10,160,30,140,FALSE,FALSE };/* ��Բ */
LineT sideLine = { 10,190,30,170,FALSE,FALSE };/* ֱ�� */
SideBar sideBar = { sideRectangle,sideEllipse,sideLine };/* �ı� */

int main()
{
	DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);/* ��ȡ��ʾ���� */
	DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);/* ��ȡ��ʾ���� */
	initgraph(screenWidth, screenHeight);/* ͼ�ν����ʼ�� */
	setlinecolor(RED); /* ��ʼ��������ɫ */
	setbkcolor(WHITE);/*  ��ʼ��������ɫ */
	settextcolor(BLACK);/* ��ʼ���ı���ɫ */
	cleardevice();
	DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);/* ���������� */
	while (true)
	{
		if (_kbhit())
			KeyboardEventProcess(); /* ������Ϣ */
		if (MouseHit()) MouseEventProcess();/* �����Ϣ */
	}
	return 0;
}

/* ���������x����
*/
int RandomX()
{
	srand((unsigned)time(NULL) + rand());/* �������� */
	int x = MIN_X + (rand() % (MAX_X + MIN_X - 1)) - 1;/* ����������� */
	return x;
}

/* ���������y����
*/
int RandomY()
{
	srand((unsigned)time(NULL) + rand());/* �������� */
	int y = MIN_Y + (rand() % (MAX_Y + MIN_Y - 1)) - 1;/* ����������� */
	return y;
}

/* ��������ͼ��,��������Ϊ������ͼ�ε�����ͷָ��,
*  ��Բͼ�ε������ͷָ��,ֱ��ͼ�ε�����ͷָ��,��
*  ��ͼ�������ͷָ��
*/
void DrawAll(RectangleNode *RectangleHead, EllipseNode *EllipseHead, LineNode *LineHead, TextNode *TextHead)
{
	RectangleNode *RectangleHeadTemp = RectangleHead;
	EllipseNode *EllipseHeadTemp = EllipseHead;
	LineNode *LineHeadTemp = LineHead;
	TextNode *TextHeadTemp = TextHead;

	DrawSideBar();
	/* ������ı������� */
	while ((RectangleHeadTemp = RectangleHeadTemp->next) != NULL)/* ֻҪָ��ǿվͻ�����Ӧ��ͼ�� */
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

/* ���������С�ľ���
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

/* ���������С����Բ
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

/* ����������ȵ�ֱ��
*/
void LineGenertator()
{
	// �����������
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

/* �����ı���
*/
void TextGenertator()
{
	int x1 = RandomX();
	int y1 = RandomY();
	int x2 = RandomX();
	int y2 = RandomY();
	char  s[10];
	int i = 0, j = 0;
	InputBox(s, 10,_T("����������"));
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

/* ���������Ϣ
*/
void KeyboardEventProcess()
{
	switch (_getch())
	{
		/* a: �������ֱ�� */
	case 'a':
		LineGenertator();
		break;
		/* s: ������ɾ���*/
	case 's':
		RectangleGenertator();
		break;
		/* d: ���������Բ */
	case 'd':
		EllipseGenertator();
		break;
		/* w: ������ɿյ��ı����� */
	case 'w':
		TextGenertator();
		break;
	default:
		break;
	}
	DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
}

/* ���������Ϣ
*/
void MouseEventProcess()
{
	MOUSEMSG m = GetMouseMsg();	/* ���������Ϣ */

	LineT *lptr = NULL;/* ֱ�� */
	RectangleT *rptr = NULL;/* ���� */
	EllipseT *eptr = NULL;/* ��Բ */
	TextT *textr = NULL;
	int x1, y1, x2, y2;
	int dx;
	int dy;
	{
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:/* �ƶ���־ */
			if (FindSideGraph(m.x, m.y) > 0)
				switch (FindSideGraph(m.x, m.y))
				{
				case 1:/* s: ������ɾ���*/
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
				case 2: /* d: ���������Բ */
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
				case 3:/* a: �������ֱ�� */
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
				isMove = TRUE; // ������£������ƶ�״̬
				TextTemp->text->isMove = true;
				break;
			}
			RectangleTemp = FindRectangle(list.RectangleList, m.x, m.y);
			if (RectangleTemp != NULL)
			{
				isMove = TRUE; // ������£������ƶ�״̬
				RectangleTemp->rectangle->isMove = true;
				break;
			}
			EllipseTemp = FindEllipse(list.EllipseList, m.x, m.y);
			if (EllipseTemp != NULL)
			{
				isMove = TRUE; // ������£������ƶ�״̬
				EllipseTemp->ellipse->isMove = true;
				break;
			}
			LineTemp = FindLine(list.LineList, m.x, m.y);
			if (LineTemp != NULL)
			{
				isMove = TRUE; // ������£������ƶ�״̬
				LineTemp->line->isMove = true;
				break;
			}
		case WM_MOUSEMOVE: /* �ƶ�ͼ�� */
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
			if (m.mkRButton)/* ���� */
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
		case WM_RBUTTONDOWN:/* ���ű�־ */
			RectangleTemp = FindRectangle(list.RectangleList, m.x, m.y);
			if (RectangleTemp != NULL)
			{
				isChangeSize = TRUE; // �Ҽ����£���������״̬
				RectangleTemp->rectangle->isMove = true;
				break;
			}
			EllipseTemp = FindEllipse(list.EllipseList, m.x, m.y);
			if (EllipseTemp != NULL)
			{
				isChangeSize = TRUE; // �Ҽ����£���������״̬
				EllipseTemp->ellipse->isMove = true;
				break;
			}
			LineTemp = FindLine(list.LineList, m.x, m.y);
			if (LineTemp != NULL)
			{
				isChangeSize = TRUE; // �Ҽ����£���������״̬
				LineTemp->line->isMove = true;
				break;
			}
			TextTemp = FindTextN(list.TextList, m.x, m.y);
			if (TextTemp != NULL)
			{
				isChangeSize = TRUE; // �Ҽ����£���������״̬
				TextTemp->text->isMove = true;
				break;
			}
			break;
		case WM_LBUTTONDBLCLK:/* ɾ��ͼ�� */
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

/* ����������
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

/* ���û������������ͼ��ʱ,�ú�����
* ���û������ͼ������һ��,������һ
* ������,(x,y)Ϊ���λ�õ�����
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

/* ��ʼ��һ���������ͼ�ε�����
*/
RectangleNode* InitRectangleList()
{
	RectangleNode *Head = (RectangleNode*)malloc(sizeof(RectangleNode));/* ����洢�ռ䣬�õ�ͷ��� */
	if (!Head)
	{
		printf("��ʼ������");
		return NULL;
	}
	Head->next = NULL;
	return Head;
}

/* ��ʼ��һ��������Բͼ�ε�����
*/
EllipseNode* InitEllipseList()
{
	EllipseNode *Head = (EllipseNode*)malloc(sizeof(EllipseNode));/* ����洢�ռ䣬�õ�ͷ��� */
	if (!Head)
	{
		printf("��ʼ������");
		return NULL;
	}
	Head->next = NULL;
	return Head;
}

/* ��ʼ��һ������ֱ��ͼ�ε�����
*/
LineNode* InitLineList()
{
	LineNode *Head = (LineNode*)malloc(sizeof(LineNode));/* ����洢�ռ䣬�õ�ͷ��� */
	if (!Head)
	{
		printf("��ʼ������");
		return NULL;
	}
	Head->next = NULL;
	return Head;
}

/* ��ʼ��һ�������ı�ͼ�ε�����
*/
TextNode* InitTextList()
{
	TextNode *Head = (TextNode*)malloc(sizeof(TextNode));/* ����洢�ռ䣬�õ�ͷ��� */
	if (!Head)
	{
		printf("��ʼ������");
		return NULL;
	}
	Head->next = NULL;
	return Head;
}

/* ����������ͽ��
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

/* ������Բ���ͽ��
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

/* ����ֱ�����ͽ��
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

/* �����ı����ͽ��
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

/* ��ȡ�������ͽ��
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

/* ��ȡ��Բ���ͽ��
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

/* ��ȡֱ�����ͽ��
*/
LineNode* FindLine(LineNode *Head, int x, int y)
{
	LineNode* temp = Head->next;
	while (temp != NULL)
	{
		LineT *pline = temp->line;
		if (pline->x1 != pline->x2)
		{
			double k = (pline->y2 - pline->y1) / (pline->x2 - pline->x1);// ֱ��б��
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

/* ��ȡ�ı����ͽ��
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

/* ɾ���������ͽ��
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

/* ɾ����Բ���ͽ��
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

/* ɾ��ֱ�����ͽ��
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

/* ɾ���ı����ͽ��
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
