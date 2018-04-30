#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct PolynNode 
{
	int coef;//系数	
	int expn;//指数
	struct PolynNode *next;//下一个结点
}PolynNode, *PolynList;


/* 创建多项式 */
PolynList CreatePolyn(void);
/* 多项式相加 */
PolynList AddPolyn(PolynList PA, PolynList PB);
/* 多项式相乘 */
PolynList MultiPolyn(PolynList PA, PolynList PB);
/* 多项式按按指数大小排序 */
void SortPolyn(PolynList PC);
/* 交换值 */
void swap(int *a, int *b);
/* 遍历多项式 */
void PolynTraverse(PolynList P);
/* 删除指定位置的结点 */
void DeleteNode(PolynList P,int pos);
/* 合并同类项 */
void MergePolyn(PolynList P);
/* 删除系数为0的项 */
void RemoveZero(PolynList P);