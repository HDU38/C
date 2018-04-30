#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct PolynNode 
{
	int coef;//ϵ��	
	int expn;//ָ��
	struct PolynNode *next;//��һ�����
}PolynNode, *PolynList;


/* ��������ʽ */
PolynList CreatePolyn(void);
/* ����ʽ��� */
PolynList AddPolyn(PolynList PA, PolynList PB);
/* ����ʽ��� */
PolynList MultiPolyn(PolynList PA, PolynList PB);
/* ����ʽ����ָ����С���� */
void SortPolyn(PolynList PC);
/* ����ֵ */
void swap(int *a, int *b);
/* ��������ʽ */
void PolynTraverse(PolynList P);
/* ɾ��ָ��λ�õĽ�� */
void DeleteNode(PolynList P,int pos);
/* �ϲ�ͬ���� */
void MergePolyn(PolynList P);
/* ɾ��ϵ��Ϊ0���� */
void RemoveZero(PolynList P);