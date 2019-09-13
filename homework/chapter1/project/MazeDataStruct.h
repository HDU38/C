#include<stdio.h>
#include<malloc.h>

#define TRUE 1
#define FALSE 0
#define MAZEROWNUM 18/* 迷宫的长和宽 */

typedef int Status;

/* 位置结构 */
typedef struct Position
{
	int x;/* 行 */
	int y;/* 列 */
	int derection;/* 方向：1、2、3、4依次代表东、南、西、北 */
}SElemType, *ElemType;

/* 栈结构 */
typedef struct node
{
	struct Position *data;/* 因为后面涉及位置方向的变化，因此储存指向位置结构的指针更加方便 */
	struct node *next;
}StackNode, *LinkStack;

/* 迷宫 */
static char maze[MAZEROWNUM][MAZEROWNUM] =
{
	{ 'x' , 'x' , 'x' , 'x' , 'x' , 'x' ,'x' , 'x' , 'x' , 'x' , 'x' , 'x' ,'x' , 'x' , 'x' , 'x' , 'x' , 'x' },
{ 'x' , ' ' , ' ' , ' ' , 'x' , ' ' ,' ' , ' ' , ' ' , ' ' , ' ' , ' ' ,' ' , 'x' , ' ' , ' ' , ' ' , 'x' },
{ 'x' , 'x' , ' ' , ' ' , 'x' , ' ' ,'x' , 'x' , 'x' , 'x' , 'x' , 'x' ,' ' , 'x' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , 'x' , 'x' , ' ' , 'x' , ' ' ,'x' , 'x' , 'x' , ' ' , ' ' , ' ' ,' ' , 'x' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , 'x' , 'x' , ' ' , 'x' , ' ' ,'x' , 'x' , ' ' , ' ' , 'x' , 'x' ,' ' , 'x' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , ' ' , 'x' , ' ' , ' ' , ' ' ,' ' , 'x' , ' ' , 'x' , 'x' , 'x' ,' ' , 'x' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , ' ' , 'x' , 'x' , 'x' , ' ' ,' ' , 'x' , ' ' , ' ' , 'x' , 'x' ,' ' , 'x' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , ' ' , 'x' , 'x' , ' ' , 'x' ,' ' , 'x' , 'x' , ' ' , 'x' , 'x' ,' ' , 'x' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , ' ' , 'x' , 'x' , ' ' , 'x' ,' ' , 'x' , 'x' , ' ' , 'x' , ' ' ,' ' , 'x' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , ' ' , 'x' , 'x' , ' ' , 'x' ,' ' , 'x' , 'x' , ' ' , 'x' , ' ' ,'x' , 'x' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , ' ' , 'x' , 'x' , ' ' , ' ' ,' ' , 'x' , 'x' , ' ' , ' ' , ' ' ,' ' , 'x' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , ' ' , 'x' , ' ' , ' ' , ' ' ,'x' , 'x' , ' ' , 'x' , ' ' , 'x' ,' ' , 'x' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , ' ' , ' ' , 'x' , ' ' , ' ' ,' ' , 'x' , ' ' , ' ' , ' ' , 'x' ,' ' , 'x' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , 'x' , ' ' , 'x' , ' ' , 'x' ,' ' , 'x' , ' ' , ' ' , ' ' , 'x' ,' ' , 'x' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , ' ' , ' ' , 'x' , ' ' , 'x' ,' ' , 'x' , ' ' , ' ' , ' ' , 'x' ,' ' , ' ' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , ' ' , ' ' , 'x' , ' ' , 'x' ,' ' , 'x' , ' ' , ' ' , ' ' , ' ' ,' ' , 'x' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , ' ' , ' ' , ' ' , ' ' , 'x' ,' ' , 'x' , ' ' , ' ' , ' ' , 'x' ,' ' , 'x' , ' ' , 'x' , ' ' , 'x' },
{ 'x' , 'x' , 'x' , 'x' , 'x' , 'x' ,'x' , 'x' , 'x' , 'x' , 'x' , 'x' ,'x' , 'x' , 'x' , 'x' , 'x' , 'x' }

};

/* 初始化一个栈结构 */
Status InitStack(LinkStack);

/* 栈顶出栈 */
Status Pop(LinkStack top, SElemType *element);

/* 判断栈是否为空 */
Status IsEmpty(LinkStack);

/* 将数据压入栈顶 */
Status Push(LinkStack, SElemType*);

/* 标记已走路径 */
void MarkFoot(SElemType);

/* 标记无法到达出口但可通的路 */
void NotAccessible(SElemType);

/* 更新位置 */
void NextPosition(SElemType *);

/* 判断是否可通 */
Status IsAccessible(SElemType);

/* 寻找路径 */
Status MazePath(SElemType, SElemType);

/* 显示路径 */
void DisplayPath(void);