#include <graphics.h>
#include <conio.h>
#include <math.h>

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

#define ROOKS_TAG     0
#define KNIGHTS_TAG   1 
#define ELEPHANTS_TAG 2 
#define ADVISORS_TAG  3 
#define KING_TAG      4
#define CANNONS_TAG   5
#define PAWNS_TAG     6


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
typedef struct chessList
{
	CHESS *chess;
	chessList *next;
}chessNode;

typedef struct stackNode
{
	chessNode *node;/* ��Ϊ�����漰λ�÷���ı仯����˴���ָ��λ�ýṹ��ָ����ӷ��� */
	stackNode *next;
	int x;
	int y;
}stackNode;

void Setup();/* �������� */

void MakeBlackChess(CHESS *, int, int ,int);

void MakeRedChess(CHESS *, int, int,int);

chessNode *FindChessNode(int, int, int);
void DrawAllChess(chessNode *, chessNode *);

chessNode *InitList();

void ListInsert(chessNode *,CHESS *);

void StartUp();

void MoveChess(chessNode* node, int x, int y, int colorTag);
void DrawRedChess(CHESS *chess);
void DrawBlackChess(CHESS *chess);
void DrawBoard();
int *CalCoordinate(int x,int y);
int InPalace(int x, int y);
void Eat(int x, int y);
int IsCorrect(chessNode* node, int x, int y);
void GenerateMoves();
/* ��ʼ��һ��ջ�ṹ */
int InitStack(stackNode*);

/* ջ����ջ */
stackNode* Pop(stackNode* top);

/* �ж�ջ�Ƿ�Ϊ�� */
int IsEmpty(stackNode*);

/* ������ѹ��ջ�� */
int Push(stackNode*, stackNode*);

void AI();
