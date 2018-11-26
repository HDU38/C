#include <graphics.h>
#include <conio.h>
#include "chess.h"

int g_board[10][9] = 
{
	{2,2,2,2,2,2,2,2,2},
    {0,0,0,0,0,0,0,0,0},
	{0,2,0,0,0,0,0,2,0},
	{2,0,2,0,2,0,2,0,2},/* 黑棋为2 */
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{1,0,1,0,1,0,1,0,1},/* 红棋为1 */
	{0,1,0,0,0,0,0,1,0},
	{0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1}

};
chessNode* g_redChessListHead;/* 红棋链表 */
chessNode* g_blackChessListHead;/* 黑棋链表 */
stackNode* g_blackSpace;
wchar_t g_blackChessText[] = { L'車',L'馬',L'象',L'士',L'將',L'砲',L'卒' };
wchar_t g_redChessText[] = { L'俥',L'傌',L'相',L'仕',L'帥',L'炮',L'兵' };
int g_status = RED_TAG;
int count = 1;
int g_redAlive = 16;
int g_blackAlive = 16;

/* 棋子链表 */
chessNode *InitList()
{
	chessNode *head = (chessNode*)malloc(sizeof(chessNode));/* 申请存储空间，得到头结点 */
	head->next = NULL;
	return head;
}
/* 增加一个棋子 */
void ListInsert(chessNode *head, CHESS *chess)
{
	chessNode *temp = head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	chessNode *t = (chessNode*)malloc(sizeof(chessNode));
	t->chess = chess;
	t->next = temp->next;
	temp->next = t;
}
/* 删除一个棋子 */
void ListDelete(chessNode *head, chessNode *node)
{
	chessNode *temp = head;
	chessNode *t;
	while (temp->next != NULL)
	{
		if (temp->next == node) break;
		temp = temp->next;
	}
	if (!temp->next) return;
	t = temp->next;
	temp->next = t->next;
	free(t);
}
/* 画出一个红棋 */
void DrawRedChess(CHESS *chess)
{
	circle(chess->x, chess->y, CHESS_RADIUS);
	moveto(chess->x - GRID_WIDTH / 4, chess->y - GRID_WIDTH / 5);
	settextcolor(RED);
	settextstyle(30, 0, _T("宋体"));
	outtext(g_redChessText[chess->index]);
	
	/*switch (tag)
	{
	case 0:
		outtext(_T("俥"));
		break;
	case 1:
		outtext(_T("傌"));
		break;
	case 2:
		outtext(_T("相"));
		break;
	case 3:
		outtext(_T("仕"));
		break;
	case 4:
		outtext(_T("帥"));
		break;
	case 5:
		outtext(_T("炮"));
		break;
	case 6:
		outtext(_T("兵"));
		break;
	}*/
}
/* 画出一个黑棋 */
void DrawBlackChess(CHESS *chess)
{
	circle(chess->x, chess->y, CHESS_RADIUS);
	moveto(chess->x - GRID_WIDTH / 4, chess->y - GRID_WIDTH / 5);
	settextcolor(BLACK);
	settextstyle(30, 0, _T("宋体"));
	outtext(g_blackChessText[chess->index]);
	/*switch (tag)
	{
	case 0:
		outtext(_T("車"));
		strcpy(chess->text, "車");
		break;
	case 1:
		outtext(_T("馬"));
		strcpy(chess->text, "馬");
		break;
	case 2:
		outtext(_T("象"));
		strcpy(chess->text, "象");
		break;
	case 3:
		outtext(_T("士"));
		strcpy(chess->text, "士");
		break;
	case 4:
		outtext(_T("將"));
		strcpy(chess->text, "將");
		break;
	case 5:
		outtext(_T("砲"));
		strcpy(chess->text, "砲");
		break;
	case 6:
		outtext(_T("卒"));
		strcpy(chess->text, "卒");
		break;
	}*/
}
/* 创建黑棋 */
void MakeBlackChess(CHESS *chess, int x, int y,int tag)
{
	chess = (CHESS*)malloc(sizeof(CHESS));
	chess->x = x;
	chess->y = y;
	chess->index = tag;
	DrawBlackChess(chess);
	ListInsert(g_blackChessListHead, chess);
}
/* 创建红棋 */
void MakeRedChess(CHESS *chess, int x, int y,int tag)
{
	chess = (CHESS*)malloc(sizeof(CHESS));
	chess->x = x;
	chess->y = y;
	chess->index = tag;
	DrawRedChess(chess);
	ListInsert(g_redChessListHead, chess);
}

/* 寻找被点击的棋子 */
chessNode *FindChessNode(int x, int y,int tag)
{
	chessNode *temp;
	int dr;
	if(tag==RED_TAG) temp = g_redChessListHead;
	else if (tag == BLACK_TAG) temp = g_blackChessListHead;
	else return NULL;
	while ((temp = temp->next) != NULL)
	{
		dr = (x - temp->chess->x)*(x - temp->chess->x) + (y - temp->chess->y)*(y - temp->chess->y) - CHESS_RADIUS * CHESS_RADIUS;
		if (dr <= 0) return temp;
	}
	return NULL;
}

/* 画出链表中的所有棋子 */
void DrawAllChess(chessNode *red, chessNode *black)
{
	chessNode *tempRed = red;
	chessNode *tempBlack = black;
	BeginBatchDraw();
	cleardevice();
	DrawBoard();
	while ((tempBlack = tempBlack->next) != NULL) DrawBlackChess(tempBlack->chess);
	while ((tempRed = tempRed->next) != NULL) DrawRedChess(tempRed->chess);
	FlushBatchDraw();
}

/* 判断走法是否合理 */
int IsCorrect(chessNode* node, int x, int y)
{
	chessNode *destinationChess = NULL;
	int preX = node->chess->x;
	int preY = node->chess->y;
	int i = 0;
	int chessNum;
	if (x < GRID_WIDTH || x>9 * GRID_WIDTH || y < GRID_WIDTH || y>10 * GRID_WIDTH || (x == preX && y == preY)) return FALSE;
	switch (g_status)
	{
	case BLACK_TAG:
		if (FindChessNode(x, y, BLACK_TAG)) return FALSE;
		break;
	case RED_TAG:
		if (FindChessNode(x, y, RED_TAG)) return FALSE;
		break;
	}
	switch (node->chess->index)
	{
	case ROOKS_TAG:/* 车 */
		if (!(y == preY) && !(x == preX))/* 只能走直线 */
			return FALSE;
		/* 查看中间是否有棋子 */
		if (y == preY)
			for (i = MIN(preX, x) + GRID_WIDTH; i < MAX(preX, x); i += GRID_WIDTH)
				if (FindChessNode(i, y, BLACK_TAG) || FindChessNode(i, y, RED_TAG)) return FALSE;
		if (x == preX)
			for (i = MIN(preY, y) + GRID_WIDTH; i < MAX(preY, y); i += GRID_WIDTH)
				if (FindChessNode(x, i, BLACK_TAG) || FindChessNode(x, i, RED_TAG)) return FALSE;
		break;
	case KNIGHTS_TAG:/* 马 */
		/* 向东南或西南 */
		if (((x - preX) == GRID_WIDTH && (y - preY) == 2 * GRID_WIDTH) ||
			((x - preX) == -GRID_WIDTH && (y - preY) == 2 * GRID_WIDTH))
		{
			if (FindChessNode(preX, preY + GRID_WIDTH, BLACK_TAG) || FindChessNode(preX, preY + GRID_WIDTH, RED_TAG)) return FALSE;
		}
		/* 向西北或东北 */
		else if (((x - preX) == -GRID_WIDTH && (y - preY) == -2 * GRID_WIDTH) ||
			((x - preX) == GRID_WIDTH && (y - preY) == -2 * GRID_WIDTH))
		{
			if (FindChessNode(preX, preY - GRID_WIDTH, BLACK_TAG) || FindChessNode(preX, preY - GRID_WIDTH, RED_TAG)) return FALSE;
		}
		else return FALSE;
		break;
	case ELEPHANTS_TAG:/* 象 */
		switch (g_status)
		{
		case RED_TAG:
			if (y < 6 * GRID_WIDTH) return FALSE;
			break;
		case BLACK_TAG:
			if (y > 5 * GRID_WIDTH) return FALSE;
			break;
		}
		/* 向东南 */
		if (((x - preX) == 2 * GRID_WIDTH && (y - preY) == 2 * GRID_WIDTH))
		{
			if (FindChessNode(preX + GRID_WIDTH, preY + GRID_WIDTH, BLACK_TAG) || FindChessNode(preX + GRID_WIDTH, preY + GRID_WIDTH, RED_TAG)) return FALSE;
		}
		/* 向西南 */
		else if ((x - preX) == -2 * GRID_WIDTH && (y - preY) == 2 * GRID_WIDTH)
		{
			if (FindChessNode(preX - GRID_WIDTH, preY + GRID_WIDTH, BLACK_TAG) || FindChessNode(preX - GRID_WIDTH, preY + GRID_WIDTH, RED_TAG)) return FALSE;
		}
		/* 向西北 */
		else if (((x - preX) == -2 * GRID_WIDTH && (y - preY) == -2 * GRID_WIDTH))
		{
			if (FindChessNode(preX - GRID_WIDTH, preY - GRID_WIDTH, BLACK_TAG) || FindChessNode(preX - GRID_WIDTH, preY - GRID_WIDTH, RED_TAG)) return FALSE;
		}
		/* 向东北 */
		else if ((x - preX) == GRID_WIDTH && (y - preY) == -2 * GRID_WIDTH)
		{
			if (FindChessNode(preX + GRID_WIDTH, preY - GRID_WIDTH, BLACK_TAG) || FindChessNode(preX + GRID_WIDTH, preY - GRID_WIDTH, RED_TAG)) return FALSE;
		}
		else return FALSE;
		break;
	case ADVISORS_TAG:/* 士 */
		if (!InPalace(x, y)) return FALSE;
		if (!(abs(x - preX) == GRID_WIDTH && abs(y - preY) == GRID_WIDTH) &&
			!(abs(x - preX) == GRID_WIDTH && abs(y - preY) == GRID_WIDTH))/* 只能走对角 */
			return FALSE;
		break;
	case KING_TAG:/* 将 */
		if (!InPalace(x, y)) return FALSE;
		if ((abs(x - preX) == GRID_WIDTH && y == preY) ||
			(abs(y - preY) == GRID_WIDTH && x == preX))/* 只走一步 */
			break;
	case CANNONS_TAG:/* 炮 */
		if (!(y == preY) && !(x == preX))/* 只能走直线 */
			return FALSE;
		chessNum = 0;
		if (y == preY)
		{
			for (i = MIN(preX, x) + GRID_WIDTH; i < MAX(preX, x); i += GRID_WIDTH)
			{
				if (FindChessNode(i, y, BLACK_TAG) || FindChessNode(i, y, RED_TAG))
					chessNum++;
			}
		}
		if (x == preX)
		{
			for (i = MIN(preY, y) + GRID_WIDTH; i < MAX(preY, y); i += GRID_WIDTH)
			{
				if (FindChessNode(x, i, BLACK_TAG) || FindChessNode(x, i, RED_TAG))
					chessNum++;
			}
		}
		if (chessNum != 1 && chessNum != 0)
			return FALSE;
		if (chessNum == 0)
		{
			if ((destinationChess = FindChessNode(x, y, BLACK_TAG)) ||
				(destinationChess = FindChessNode(x, y, RED_TAG)))
				return FALSE;
		}
		if (chessNum == 1)
		{
			switch (g_status)
			{
			case RED_TAG:
				if (!(destinationChess = FindChessNode(x, y, BLACK_TAG))) return FALSE;
				break;
			case BLACK_TAG:
				if (!(destinationChess = FindChessNode(x, y, RED_TAG))) return FALSE;
				break;
			}
		}
		break;
	case PAWNS_TAG:/* 兵 */
		/* 只能向前、左、右走一步 */
		switch (g_status)
		{
		case RED_TAG:
			if (!(abs(x - preX) == GRID_WIDTH && y == preY) &&
				!(y - preY == -GRID_WIDTH && x == preX))
				return FALSE;
			break;
		case BLACK_TAG:
			if (!(abs(x - preX) == GRID_WIDTH && y == preY) &&
				!(y - preY == GRID_WIDTH && x == preX))
				return FALSE;
			break;
		}
		break;
	}
	return TRUE;
}
/* 移动棋子 */
void MoveChess(chessNode* node,int x, int y,int colorTag)
{
	CHESS *chess = NULL;
	x = CalCoordinate(x - GRID_WIDTH, y - GRID_WIDTH)[0];
	y = CalCoordinate(x - GRID_WIDTH, y - GRID_WIDTH)[1];
	if (!IsCorrect(node, x, y)) return;
	Eat(x, y);
	if (colorTag == RED_TAG) 
	{
		MakeRedChess(chess, x, y, node->chess->index);/* 在指定位置画一个棋子 */
		g_board[y / GRID_WIDTH - 1][x / GRID_WIDTH - 1] = RED_TAG;
		g_board[node->chess->y / GRID_WIDTH - 1][node->chess->x / GRID_WIDTH - 1] = 0;
		ListDelete(g_redChessListHead, node);/* 删除原先的棋子 */
		count++;
	}
	else if (colorTag == BLACK_TAG)
	{
		MakeBlackChess(chess, x, y, node->chess->index);/* 在指定位置画一个棋子 */
		g_board[y / GRID_WIDTH - 1][x / GRID_WIDTH - 1] = BLACK_TAG;
		g_board[node->chess->y / GRID_WIDTH - 1][node->chess->x / GRID_WIDTH - 1] = 0;
		ListDelete(g_blackChessListHead, node);/* 删除原先的棋子 */
		count++;
	}
	DrawAllChess(g_redChessListHead, g_blackChessListHead);/* 画出所有棋子 */
	return;
}
/* 初始化 */
void Setup()
{
	int i;
	CHESS *chess = NULL;
	g_redChessListHead = InitList();
	g_blackChessListHead = InitList();
	g_blackSpace = (stackNode*)malloc(sizeof(stackNode));
	InitStack(g_blackSpace);
	initgraph(WIDTH, HEIGHT);
	setbkcolor(WHITE);
	settextcolor(BLACK);
	setlinecolor(BLACK);
	cleardevice();

	DrawBoard();
	/* 黑棋 */
	for (i = 0; i < 9; i++)
	{
		if(i<=4) MakeBlackChess(chess, (i + 1) * GRID_WIDTH, GRID_WIDTH, i);
		else MakeBlackChess(chess, (i + 1) * GRID_WIDTH, GRID_WIDTH, 8-i);
	}
	MakeBlackChess(chess, 2 * GRID_WIDTH, 3 * GRID_WIDTH, 5);
	MakeBlackChess(chess, 8 * GRID_WIDTH, 3 * GRID_WIDTH, 5);
	for (i = 0; i < 9; i += 2)
		MakeBlackChess(chess, (i + 1)*GRID_WIDTH, 4 * GRID_WIDTH, 6);
	/* 红棋 */
	for (i = 0; i < 9; i += 2)
		MakeRedChess(chess, (i + 1)*GRID_WIDTH, 7 * GRID_WIDTH, 6);
	MakeRedChess(chess, 2 * GRID_WIDTH, 8 * GRID_WIDTH,5);
	MakeRedChess(chess, 8 * GRID_WIDTH, 8 * GRID_WIDTH,5);
	for (i = 0; i < 9; i++)
	{
		if (i <= 4) MakeRedChess(chess, (i + 1)*GRID_WIDTH, GRID_WIDTH + BOARD_HEIGHT,i);
		else MakeRedChess(chess, (i + 1)*GRID_WIDTH, GRID_WIDTH + BOARD_HEIGHT, 8-i);
	}
}
/* 开始游戏 */
void StartUp()
{
	MOUSEMSG m;
	chessNode *currentChess = NULL;
	chessNode *previousChess = NULL;
	int chessAvailable = FALSE;

	while (TRUE)
	{
		if (count % 2 == 1)
		{
			g_status = RED_TAG;
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				currentChess = FindChessNode(m.x, m.y, g_status);
				if (currentChess != NULL)
					chessAvailable = TRUE;
				else if (chessAvailable&&previousChess)
					MoveChess(previousChess, m.x, m.y, g_status);
				previousChess = currentChess;
			}
			Sleep(10);
		}
		else
		{
			g_status = BLACK_TAG;
			AI();
		}
	}
}
/* 画出棋盘 */
void DrawBoard()
{
	int i, j;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (j == 4) continue;
			rectangle((i + 1)*GRID_WIDTH, (j + 1)*GRID_WIDTH, (i + 2)*GRID_WIDTH, (j + 2)*GRID_WIDTH);
		}
	}
	line(4 * GRID_WIDTH, GRID_WIDTH, 6 * GRID_WIDTH, 3 * GRID_WIDTH);
	line(6 * GRID_WIDTH, GRID_WIDTH, 4 * GRID_WIDTH, 3 * GRID_WIDTH);
	line(4 * GRID_WIDTH, 8 * GRID_WIDTH, 6 * GRID_WIDTH, 10 * GRID_WIDTH);
	line(6 * GRID_WIDTH, 8 * GRID_WIDTH, 4 * GRID_WIDTH, 10 * GRID_WIDTH);
}

int *CalCoordinate(int x, int y)
{
	int temp[4];
	int result[2];
	int x_value[4];
	int y_value[4];
	int minDr;
	int i;

	x_value[0] = (x / 60)*GRID_WIDTH;
	y_value[0] = (y / 60)*GRID_WIDTH;
	temp[0] = (x_value[0] - x)*(x_value[0] - x) + (y_value[0] - y)*(y_value[0] - y);

	x_value[1] = (x_value[0]/ GRID_WIDTH + 1)*GRID_WIDTH;
	y_value[1] = (y_value[0] / GRID_WIDTH) *GRID_WIDTH;
	temp[1] = (x_value[1] - x)*(x_value[1] - x) + (y_value[1] - y)*(y_value[1] - y);


	x_value[2] = (x_value[0]/ GRID_WIDTH) *GRID_WIDTH;
	y_value[2] = (y_value[0] / GRID_WIDTH + 1)*GRID_WIDTH;
	temp[2] = (x_value[2] - x)*(x_value[2] - x) + (y_value[2] - y)*(y_value[2] - y);

	x_value[3] = (x_value[0] / GRID_WIDTH + 1)*GRID_WIDTH;
	y_value[3] = (y_value[0] / GRID_WIDTH + 1)*GRID_WIDTH;
	temp[3] = (x_value[3] - x)*(x_value[3] - x) + (y_value[3] - y)*(y_value[3] - y);

	minDr = MIN(MIN(MIN(temp[0], temp[1]), temp[2]), temp[3]);
	for (i = 0; i < 4;i++) 
	{
		if (temp[i] == minDr) 
		{
			result[0] = x_value[i] + GRID_WIDTH;
			result[1] = y_value[i] + GRID_WIDTH;
			return result;
		}
	}
	return NULL;
}

int InPalace(int x, int y)
{
	switch (g_status)
	{
	case RED_TAG:
		if(IN_RED_PALACE(x,y))
			return TRUE;
		else
			return FALSE;
	case BLACK_TAG:
		if (IN_BLACK_PALACE(x, y))
			return TRUE;
		else
			return FALSE;
	}
	return FALSE;
}

void Eat(int x, int y)
{
	chessNode *destinationChess = NULL;
	/* 查看目的地坐标是否有敌方棋子 */
	switch (g_status)
	{
	case RED_TAG:
		if (destinationChess = FindChessNode(x, y, BLACK_TAG))
		{
			ListDelete(g_blackChessListHead, destinationChess);
			g_blackAlive--;
		}
		break;
	case BLACK_TAG:
		if (destinationChess = FindChessNode(x, y, RED_TAG))
		{
			ListDelete(g_redChessListHead, destinationChess);
			g_redAlive--;
		}
		break;
	}
}
/* 生成所有走法 */
void GenerateMoves()
{
	int x, y;
	chessNode *temp = g_blackChessListHead;
	stackNode *tempStackNode = NULL;
	while ((temp = temp->next) != NULL) 
	{
		switch (temp->chess->index)
		{
		case ROOKS_TAG:/* 车 */
			for (x = GRID_WIDTH; x < 10 * GRID_WIDTH; x += GRID_WIDTH)
			{
				if (x == temp->chess->x) continue;
				if (IsCorrect(temp, x, temp->chess->y))
				{
					tempStackNode = (stackNode*)malloc(sizeof(stackNode));
					tempStackNode->x = x;
					tempStackNode->y = temp->chess->y;
					tempStackNode->node = temp;
					Push(g_blackSpace, tempStackNode);//入栈
				}
			}
			for (y = GRID_WIDTH; y < 11 * GRID_WIDTH; y += GRID_WIDTH)
			{
				if (y == temp->chess->y) continue;
				if (IsCorrect(temp, temp->chess->x, y))
				{
					tempStackNode = (stackNode*)malloc(sizeof(stackNode));
					tempStackNode->x = temp->chess->x;
					tempStackNode->y = y;
					tempStackNode->node = temp;
					Push(g_blackSpace, tempStackNode);//入栈
				}
			}
			break;
		case KNIGHTS_TAG:/* 马 */
			//入栈
			break;
		case ELEPHANTS_TAG:/* 象 */
			//入栈
			break;
		case ADVISORS_TAG:/* 士 */
			//入栈
			break;
		case KING_TAG:/* 将 */
			//入栈
		case CANNONS_TAG:/* 炮 */
			//入栈
			break;
		case PAWNS_TAG:/* 兵 */
			//入栈
			break;
		}
	}
}
void AI()
{
	GenerateMoves();
	stackNode* temp = Pop(g_blackSpace);
	while (temp)
	{
		if(temp->node) MoveChess(temp->node, temp->x, temp->y,BLACK_TAG);
		temp = Pop(g_blackSpace);
	}
}
/* 初始化一个栈 */
int InitStack(stackNode* top)
{
	top->next = NULL;
	return TRUE;
}

/* 判断栈是否为空 */
int IsEmpty(stackNode* top)
{
	if (top->next == NULL)
		return TRUE;
	else
		return FALSE;
}

/* 将数据压入栈顶 */
int Push(stackNode *top,stackNode* element)
{
	stackNode *temp = (stackNode *)malloc(sizeof(stackNode));/* 创建一个新结点,并分配存储空间 */
	if (temp == NULL)
		return FALSE;
	temp->node = element->node;/* element是结构指针而不是结构 */
	temp->x = element->x;
	temp->y = element->y;
	temp->next = top->next;/* 更换栈顶元素 */
	top->next = temp;
	return TRUE;
}

/* 栈顶出栈,top为栈顶指针,将出栈的元素赋值给element指向的结构 */
stackNode* Pop(stackNode* top)
{
	stackNode* element = (stackNode*)malloc(sizeof(stackNode));
	stackNode *temp = NULL;
	if (IsEmpty(top) == TRUE)
		return FALSE;
	temp = top->next;/* 暂时储存栈顶指针 */
	*element = *temp;/* 要操作指针指向的对象，而不能操作地址 */
	top->next = temp->next;/* 更换栈顶元素 */
	free(temp);/* 释放存储空间 */
	return element;
}