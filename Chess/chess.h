#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>

#define MIN(a,b) (a > b ? b : a)
#define MAX(a,b) (a > b ? a : b)
#define IN_RED_PALACE(x,y) (x>=4*GRID_WIDTH&&x<=6*GRID_WIDTH&&y>=8*GRID_WIDTH&&y<=10*GRID_WIDTH)
#define IN_BLACK_PALACE(x,y) (x>=4*GRID_WIDTH&&x<=6*GRID_WIDTH&&y>=GRID_WIDTH&&y<=3*GRID_WIDTH)

#define GRID_WIDTH 60
#define WIDTH GRID_WIDTH * 10
#define HEIGHT GRID_WIDTH * 11
#define BOARD_WIDTH GRID_WIDTH * 8
#define BOARD_HEIGHT GRID_WIDTH * 9
#define CHESS_RADIUS GRID_WIDTH / 2 - 4

#define ROOKS_TAG     1
#define KNIGHTS_TAG   2 
#define ELEPHANTS_TAG 3 
#define ADVISORS_TAG  4 
#define KING_TAG      5
#define CANNONS_TAG   6
#define PAWNS_TAG     7


#define RED_TAG 1
#define BLACK_TAG 2

#define FALSE 0
#define TRUE 1


typedef struct chessTag
{
	int x;
	int y;
	int index;
}CHESS;
typedef struct
{
	CHESS *chess;
	int x;
	int y;
}moveAction;

typedef struct chessList
{
	CHESS *chess;
	chessList *next;
}chessNode;

typedef struct stackNode
{
	chessNode *node;/* 因为后面涉及位置方向的变化，因此储存指向位置结构的指针更加方便 */
	stackNode *next;
	int x;
	int y;
}stackNode;

struct TNode
{
	moveAction *move;
	struct chequerList* childList;
};

 struct chequerList
{
	TNode* node;
	struct chequerList* next;
};

 typedef TNode TNodeVar;
 typedef chequerList chequerListVar;

void Setup();/* 画出棋盘 */

void MakeBlackChess(CHESS *, int, int ,int);

void MakeRedChess(CHESS *, int, int,int);

chessNode *FindChessNode(int, int, int);
void DrawAllChess(chessNode *, chessNode *);

chessNode *InitChessList();

void ChessListInsert(chessNode *,CHESS *);

void StartUp();

void MoveChess(chessNode* node, int x, int y, int colorTag);
void DrawRedChess(CHESS *chess);
void DrawBlackChess(CHESS *chess);
void DrawBoard();
int *CalCoordinate(int x,int y);
int InPalace(int x, int y);
void Eat(int x, int y);
int IsCorrect(chessNode* node, int x, int y);
void GenerateMoves(int(*board)[9]);
/* 初始化一个栈结构 */
int InitStack(stackNode*);

/* 栈顶出栈 */
stackNode* Pop(stackNode* top);

/* 判断栈是否为空 */
int IsEmpty(stackNode*);

/* 将数据压入栈顶 */
int Push(stackNode*, stackNode*);

/* 初始化一棵树 */
TNodeVar* InitTree(moveAction* move,int x,int y);
/* 在指定深度插入一个结点 */
void TreeInsert(TNodeVar* currentNode, chequerList* list);
/* 删除一个结点 */
void TreeDelete();
void ArrayCopy(int(*a)[9], int(*b)[9]);
void AI();
/* 在数组中寻找棋子 */
int FindChess(int x, int y);
void Move(int(*a)[9], int x1, int y1, int x2, int y2);
chequerList *InitList();
void ListInsert(chequerList *head, TNode *node);
void ListDelete(chequerList *head, chequerList *node);
void DrawChess();
void WriteToFile(CHESS* chess, int x, int y);
