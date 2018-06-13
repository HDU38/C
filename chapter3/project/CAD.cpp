#include "CADDataStruct.h"

/* ��ʱָ��ѡ�е�ͼ�����ڵĽ�� */
/* ��Բ */
EllipseNode *EllipseTemp = NULL;
/* ������ */
RectangleNode *RectangleTemp = NULL;
/* ֱ�� */
LineNode *LineTemp = NULL;
/* �ı� */
TextNode *TextTemp = NULL;

BOOL isMove = FALSE; /* �ƶ���־ */
BOOL isChangeSize = FALSE; /* ���ű�־ */

DWORD WINDOWSWIDTH = GetSystemMetrics(SM_CXSCREEN);/* �� */
DWORD WINDOWSHEIGHT = GetSystemMetrics(SM_CYSCREEN);/* �� */

/* ��ʼ������ͼ������ */
GraphList list = { InitEllipseList(),InitRectangleList(),InitLineList(),InitTextList() };

/* ������ͼ�� */
RectangleT sideRectangle = { 10,130,30,100,FALSE,FALSE };/* ������ */
EllipseT sideEllipse = { 10,160,30,140,FALSE,FALSE };/* ��Բ */
LineT sideLine = { 10,190,30,170,FALSE,FALSE };/* ֱ�� */
RECT sideRec = { 10, 220, 30, 200 };
TextT sideText = { "T",&sideRec,DT_CENTER | DT_VCENTER | DT_SINGLELINE,FALSE,FALSE,25,0 };/* �ı� */
SideBar sideBar = { sideRectangle,sideEllipse,sideLine,sideText };

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
	MOUSEMSG m;
	while (true)
	{
		if (_kbhit())
		{
			KeyboardEventProcess(_getch()); /* ������Ϣ */
		}
		if (MouseHit())
		{
			m = GetMouseMsg();
			MouseEventProcess(m);/* �����Ϣ */
		}
	}
	return 0;
}

/* ��ȡһ�������Ϣ������
*/
void KeyboardEventProcess(int keyboardMsg)
{
	switch (keyboardMsg)
	{
	case 'a':/* a: �������ֱ�� */
		LineGenertator();
		break;
	case 's':/* s: ������ɾ���*/
		RectangleGenertator();
		break;
	case 'd':/* d: ���������Բ */
		EllipseGenertator();
		break;
	case 'w':/* w: ��������ı� */
		TextGenertator();
		break;
	default:
		break;
	}
	DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
}

/* ���������Ϣ
*/
void MouseEventProcess(MOUSEMSG m)
{
	LineT *lptr = NULL;/* ֱ�� */
	RectangleT *rptr = NULL;/* ���� */
	EllipseT *eptr = NULL;/* ��Բ */
	TextT *textr = NULL;/* �ı� */

	int dx, dy;/* ƫ���� */
	int preX, preY;/* ��ǰ���� */
	{
		switch (m.uMsg)/* ƥ�������Ϣ */
		{
		case WM_MOUSEMOVE: /* ����ƶ� */
			if (m.mkLButton || m.mkRButton)
			{
				preX = m.x;/* ֮ǰ������ */
				preY = m.y;
				m = GetMouseMsg();
				dx = 2 * (m.x - preX);
				dy = 2 * (m.y - preY);/* �ʵ�����ƫ����*/
			}
			else break;
			if (m.mkLButton)/* �ƶ� */
			{
				if (isMove == TRUE)
				{
					if (TextTemp != NULL && TextTemp->text->isMove == TRUE)
					{
						TextTemp->text->pRect->left += dx;
						TextTemp->text->pRect->top += dy;
						TextTemp->text->pRect->right += dx;
						TextTemp->text->pRect->bottom += dy;
						DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
						break;
					}
					if (RectangleTemp != NULL && RectangleTemp->rectangle->isMove == TRUE)
					{
						RectangleTemp->rectangle->left += dx;
						RectangleTemp->rectangle->top += dy;
						RectangleTemp->rectangle->right += dx;
						RectangleTemp->rectangle->bottom += dy;
						DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
						break;
					}
					EllipseTemp = FindEllipse(list.EllipseList, m.x, m.y);
					if (EllipseTemp != NULL && EllipseTemp->ellipse->isMove == TRUE)
					{
						EllipseTemp->ellipse->left += dx;
						EllipseTemp->ellipse->top += dy;
						EllipseTemp->ellipse->right += dx;
						EllipseTemp->ellipse->bottom += dy;
						DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
						break;
					}
					LineTemp = FindLine(list.LineList, m.x, m.y);
					if (LineTemp != NULL && LineTemp->line->isMove == TRUE)
					{
						LineTemp->line->x1 += dx;
						LineTemp->line->y2 += dy;
						LineTemp->line->x2 += dx;
						LineTemp->line->y1 += dy;
						DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
						break;
					}
				}
			}
			if (m.mkRButton)/* ���� */
			{
				if (isChangeSize == TRUE)
				{
					if (RectangleTemp != NULL && RectangleTemp->rectangle->isChangeSize == TRUE)
					{
						RectangleTemp->rectangle->right += dx;
						RectangleTemp->rectangle->bottom += dy;
						/* ��ֹ����ߵ� */
						RectangleTemp->rectangle->left = MIN(RectangleTemp->rectangle->left,
							RectangleTemp->rectangle->right);
						RectangleTemp->rectangle->right = MAX(RectangleTemp->rectangle->left,
							RectangleTemp->rectangle->right);
						RectangleTemp->rectangle->top = MAX(RectangleTemp->rectangle->top,
							RectangleTemp->rectangle->bottom);
						RectangleTemp->rectangle->bottom = MIN(RectangleTemp->rectangle->top,
							RectangleTemp->rectangle->bottom);
						DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
						break;
					}
					EllipseTemp = FindEllipse(list.EllipseList, m.x, m.y);
					if (EllipseTemp != NULL && EllipseTemp->ellipse->isChangeSize == TRUE)
					{
						EllipseTemp->ellipse->right += dx;
						EllipseTemp->ellipse->bottom += dy;
						EllipseTemp->ellipse->left = MIN(EllipseTemp->ellipse->left,
							EllipseTemp->ellipse->right);
						EllipseTemp->ellipse->right = MAX(EllipseTemp->ellipse->left,
							EllipseTemp->ellipse->right);
						EllipseTemp->ellipse->top = MAX(EllipseTemp->ellipse->top,
							EllipseTemp->ellipse->bottom);
						EllipseTemp->ellipse->bottom = MIN(EllipseTemp->ellipse->top,
							EllipseTemp->ellipse->bottom);
						DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
						break;
					}
					LineTemp = FindLine(list.LineList, m.x, m.y);
					if (LineTemp != NULL && LineTemp->line->isChangeSize == TRUE)
					{
						LineTemp->line->x2 += dx;
						LineTemp->line->y1 += dy;
						DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
						break;
					}
					TextTemp = FindTextN(list.TextList, m.x, m.y);
					if (TextTemp != NULL && TextTemp->text->isChangeSize == TRUE)
					{
						if (
							TextTemp->text->pRect->left <= m.x &&
							TextTemp->text->pRect->right >= m.x &&
							TextTemp->text->pRect->bottom <= m.y &&
							TextTemp->text->pRect->top >= m.y)
						{
							TextTemp->text->nHeight+=dy;
						}
						else
						{
							TextTemp->text->nWidth+=dx;
						}
						TextTemp->text->pRect->right = TextTemp->text->pRect->left +
							textwidth(TextTemp->text->str);
						TextTemp->text->pRect->top = TextTemp->text->pRect->bottom +
							textheight(TextTemp->text->str);
						DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
						break;
					}
				}
			}
			break;
		case WM_LBUTTONDOWN:/* ����������-�ƶ� */
			if (FindSideGraph(m.x, m.y) > 0)/* ���ȼ���û��Ƿ����˹����� */
			{
				switch (FindSideGraph(m.x, m.y))
				{
				case LINETAG:
					LineGenertator();
					break;
				case RECTANGLETAG:
					RectangleGenertator();
					break;
				case ELLIPSETAG:
					EllipseGenertator();
					break;
				case TEXTTAG:
					TextGenertator();
					break;
				default:
					break;
				}
				DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
				break;
			}
			/* Ѱ���û������ͼ�� */
			TextTemp = FindTextN(list.TextList, m.x, m.y);
			if (TextTemp != NULL)
			{
				isMove = TRUE; /* ������£������ƶ�״̬ */
				TextTemp->text->isMove = TRUE;
				break;
			}
			RectangleTemp = FindRectangle(list.RectangleList, m.x, m.y);
			if (RectangleTemp != NULL)
			{
				isMove = TRUE; /* ������£������ƶ�״̬ */
				RectangleTemp->rectangle->isMove = TRUE;
				break;
			}
			EllipseTemp = FindEllipse(list.EllipseList, m.x, m.y);
			if (EllipseTemp != NULL)
			{
				isMove = TRUE; /* ������£������ƶ�״̬ */
				EllipseTemp->ellipse->isMove = TRUE;
				break;
			}
			LineTemp = FindLine(list.LineList, m.x, m.y);
			if (LineTemp != NULL)
			{
				isMove = TRUE; /* ������£������ƶ�״̬ */
				LineTemp->line->isMove = TRUE;
				break;
			}
			break;
		case WM_RBUTTONDOWN:/* ��������Ҽ�-���� */
			RectangleTemp = FindRectangle(list.RectangleList, m.x, m.y);
			if (RectangleTemp != NULL)
			{
				isChangeSize = TRUE; /* �Ҽ����£���������״̬ */
				RectangleTemp->rectangle->isChangeSize = TRUE;
				break;
			}
			EllipseTemp = FindEllipse(list.EllipseList, m.x, m.y);
			if (EllipseTemp != NULL)
			{
				isChangeSize = TRUE; /* �Ҽ����£���������״̬ */
				EllipseTemp->ellipse->isChangeSize = TRUE;
				break;
			}
			LineTemp = FindLine(list.LineList, m.x, m.y);
			if (LineTemp != NULL)
			{
				isChangeSize = TRUE; /* �Ҽ����£���������״̬ */
				LineTemp->line->isChangeSize = TRUE;
				break;
			}
			TextTemp = FindTextN(list.TextList, m.x, m.y);
			if (TextTemp != NULL)
			{
				isChangeSize = TRUE; /* �Ҽ����£���������״̬ */
				TextTemp->text->isChangeSize = TRUE;
				break;
			}
			break;
		case WM_LBUTTONDBLCLK:/* ˫�����-ɾ��ͼ�� */
			if (RectangleTemp != NULL)
			{
				RectangleListDelete(list.RectangleList, RectangleTemp);
				RectangleTemp = NULL;
				DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
				break;
			}
			if (EllipseTemp != NULL)
			{
				EllipseListDelete(list.EllipseList, EllipseTemp);
				EllipseTemp = NULL;
				DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
				break;
			}
			if (LineTemp != NULL)
			{
				LineListDelete(list.LineList, LineTemp);
				LineTemp = NULL;
				DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
				break;
			}
			if (TextTemp != NULL)
			{
				TextListDelete(list.TextList, TextTemp);
				TextTemp = NULL;
				DrawAll(list.RectangleList, list.EllipseList, list.LineList, list.TextList);
				break;
			}
			break;
		default:
			break;
		}
	}
}

/* ���������x����
*/
int RandomX()
{
	srand((unsigned)time(NULL) + rand());/* �������� */
	int x = (rand() % (WINDOWSWIDTH - 1)) - 1;/* ����������� */
	return x;
}

/* ���������y����
*/
int RandomY()
{
	srand((unsigned)time(NULL) + rand());/* �������� */
	int y = (rand() % (WINDOWSHEIGHT - 1)) - 1;/* ����������� */
	return y;
}

/* ��������ͼ��,��������Ϊ������ͼ�ε�����ͷָ��,
*  ��Բͼ�ε������ͷָ��,ֱ��ͼ�ε�����ͷָ��,��
*  ��ͼ�������ͷָ��
*/
void DrawAll(RectangleNode *RectangleHead, EllipseNode *EllipseHead, LineNode *LineHead, TextNode *TextHead)
{
	BeginBatchDraw();
	cleardevice();

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
	{
		settextstyle(TextHeadTemp->text->nHeight, 0, TextHeadTemp->text->str);
		drawtext(TextHeadTemp->text->str,
			TextHeadTemp->text->pRect,
			TextHeadTemp->text->uFormat);
	}
	FlushBatchDraw();
}

/* ���������С�ľ���
*/
void RectangleGenertator()
{
	int x1 = RandomX();
	int y1 = RandomY();
	int x2 = RandomX();
	int y2 = RandomY();
	RectangleT *rptr = (RectangleT*)malloc(sizeof(RectangleT));/* ����洢�ռ� */
	rptr->top = MAX(y1, y2);
	rptr->bottom = MIN(y1, y2);
	rptr->left = MIN(x1, x2);
	rptr->right = MAX(x1, x2);
	rptr->isMove = FALSE;
	rptr->isChangeSize = FALSE;
	RectangleListInsert(list.RectangleList, rptr);/* �������� */
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
	eptr->top = MAX(y1, y2);
	eptr->bottom = MIN(y1, y2);
	eptr->left = MIN(x1, x2);
	eptr->right = MAX(x1, x2);
	eptr->isMove = FALSE;
	eptr->isChangeSize = FALSE;
	EllipseListInsert(list.EllipseList, eptr);
}

/* ����������ȵ�ֱ��
*/
void LineGenertator()
{
	int x1 = RandomX();
	int y1 = RandomY();
	int x2 = RandomX();
	int y2 = RandomY();
	LineT *lptr = (LineT*)malloc(sizeof(LineT));
	lptr->x1 = MIN(x1, x2);/* �涨x1С��x2 */
	lptr->x2 = MAX(x1, x2);
	lptr->y1 = y1;
	lptr->y2 = y2;
	lptr->isMove = FALSE;
	lptr->isChangeSize = FALSE;
	LineListInsert(list.LineList, lptr);
}

/* �����ı���
*/
void TextGenertator()
{
	char s[20];/* �ַ��� */
	InputBox(s, 20, _T("����������(������20���ַ�)"));/* ���� */
	TextT *textr = (TextT*)malloc(sizeof(TextT));/* �ı����� */
	strcpy(textr->str,s);/* �����ַ��� */
	textr->uFormat = DT_CENTER | DT_VCENTER | DT_SINGLELINE;
	RECT *rec = (RECT*)malloc(sizeof(RECT));/* �ı��� */
	int x1 = RandomX();
	int x2 = x1 + textwidth(textr->str);/* x1�����ı���� */
	int y1 = RandomY();
	int y2 = y1 + textheight(textr->str);/* y1�����ı��߶� */
	rec->top = y2;
	rec->bottom = y1;
	rec->left = x1;
	rec->right = x2;
	textr->pRect = rec;
	textr->isMove = FALSE;
	textr->isChangeSize = FALSE;
	textr->nHeight = 32;
	textr->nWidth = 0;
	TextListInsert(list.TextList, textr);
}

/* ����������
*/
void DrawSideBar()
{
	FlushBatchDraw();
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
	settextstyle(sideBar.text.nHeight, sideBar.text.nWidth, _T(sideBar.text.str));
	drawtext(
		sideBar.text.str,
		sideBar.text.pRect,
		sideBar.text.uFormat);
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
	else if (
		sideBar.text.pRect->left <= x &&
		sideBar.text.pRect->right >= x &&
		sideBar.text.pRect->bottom <= y &&
		sideBar.text.pRect->top >= y)
		return TEXTTAG;
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
			double k = ((double)pline->y2 - (double)pline->y1) / ((double)pline->x2 - (double)pline->x1);// ֱ��б��
			if (pline->x1 <= x &&
				pline->x2 >= x && (
				((double)pline->y1 + k * ((double)x - pline->x1 + 55) >= y &&
					(double)pline->y1 + k * ((double)x - pline->x1 - 55) <= y) ||
					((double)pline->y1 + k * ((double)x - pline->x1 + 55) <= y &&
					(double)pline->y1 + k * ((double)x - pline->x1 - 55) >= y)))
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
