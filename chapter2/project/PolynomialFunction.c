#include "Polynomial.h"

/* 创建多项式 */
PolynList  CreatePolyn() 
{
	PolynList Head = (PolynList)malloc(sizeof(PolynNode));/* 创建头结点 */
	PolynList Tail = Head;/* 指向最后一个结点 */
	PolynList newnode = NULL;/* 新结点 */
	int i, n;
	if (Head == NULL)
		printf("内存分配失败");
	Tail->next = NULL;/* 最后一个结点指向NULL */
	printf("请输入多项式项数\n");
	scanf("%d", &n);
	printf("请分别输入多项式的系数和指数(用空格隔开)\n");
	for (i = 0; i < n; i++) {
		newnode = (PolynList)malloc(sizeof(PolynNode));/* 申请存储空间 */
		scanf("%d %d", &newnode->coef, &newnode->expn);/* 赋值 */
		Tail->next = newnode;/* 指向新的结点 */
		newnode->next = NULL;
		Tail = newnode;
	}
	return Head;/* 返回头结点 */

}

/* 删除指定位置的结点,P为头指针,pos为结点位置，位置从1开始 */
void DeleteNode(PolynList P, int pos)
{
	int i;
	PolynList temp = NULL;/* 临时结点 */
	if (P == NULL)
	{
		printf("多项式为空");
		return;
	}
	/* 遍历获取要删除的结点的前一个结点 */
	for (i = 1; i <= pos - 1; i++)
	{
		P = P->next;
	}
	temp = P;
	/* 要删除的结点 */
	P = P->next;
	/* 由1→2→3变为1→3 */
	temp->next = P->next;
	/* 释放存储空间 */
	free(P);
}

/* 遍历多项式，P为头指针 */
void PolynTraverse(PolynList P)
{
	if (P == NULL)
	{
		printf("多项式为空");
		return;
	}
	P = P->next;/* 头结点 */
	while (P->next != NULL) 
	{
		if (P->expn != 0)
		{
			if (P->next->coef > 0)
				printf("%dx^%d + ", P->coef, P->expn);/* 为了形式好看 */
			else
				printf("%dx^%d ", P->coef, P->expn);
		}
		else
		{
			if (P->next->coef > 0)
				printf("%d+ ", P->coef);
			else
				printf("%d+ ", P->coef);
		}
		P = P->next;
	}
	printf("%dx^%d\n", P->coef, P->expn);
}

/* 多项式相加,PA为多项式A的头指针，PB为多项式B的头指针 */
PolynList AddPolyn(PolynList PA, PolynList PB)
{
	PolynList ha = PA->next;/* 指向头结点*/
	PolynList hb = PB->next;/* 同上 */
	PolynList hc = (PolynList)malloc(sizeof(PolynNode));/* 创建新的多项式链表的头指针*/
	PolynList tail = hc;
	PolynList temp = NULL;/* 临时结点 */
	int sum;/* 系数和 */
	tail->next = NULL;
	while (ha&&hb)
	{
		temp = (PolynList)malloc(sizeof(PolynNode));
		/* 多项式PA的指数小于多项式PB的指数 */
		if (ha->expn < hb->expn)
		{
			temp->expn = ha->expn;/* 储存PA的数据 */
			temp->coef = ha->coef;
			ha = ha->next;/* PA链表结点后移 */
			tail->next = temp;
			temp->next = NULL;
			tail = temp;
		}
		/* 多项式PA的指数大于多项式PB的指数 */
		else if (ha->expn > hb->expn)
		{
			temp->expn = hb->expn;/* 储存PB的数据 */
			temp->coef = hb->coef;
			hb = hb->next;/* PB链表结点后移 */
			tail->next = temp;
			temp->next = NULL;
			tail = temp;
		}
		else
		{/* 多项式PA的指数等于多项式PB的指数 */
			sum = ha->coef + hb->coef;/* 求和 */
			/* 不等于0就直接储存相加后的数据 */
			if (sum != 0)
			{
				temp->coef = ha->coef + hb->coef;
				temp->expn = ha->expn;
				ha = ha->next;/*PA，PB的结点同时后移 */
				hb = hb->next;
				tail->next = temp;
				temp->next = NULL;
				tail = temp;
			}
			/* 系数相加为0则不必储存 */
			else
			{
				free(temp);/* 释放结点 */
				ha = ha->next;/* 后移 */
				hb = hb->next;
			}
		}
	}
	/* 多项式项数可能不等，因为PA和PB只有一个链表可能有数据未使用，因此直接储存剩下的数据即可 */
	while (ha)
	{
		temp = (PolynList)malloc(sizeof(PolynNode));
		temp->coef = ha->coef;
		temp->expn = ha->expn;
		ha = ha->next;
		tail->next = temp;
		temp->next = NULL;
		tail = temp;
	}
	while (hb)
	{
		temp = (PolynList)malloc(sizeof(PolynNode));
		temp->coef = hb->coef;
		temp->expn = hb->expn;
		hb = hb->next;
		tail->next = temp;
		temp->next = NULL;
		tail = temp;
	}
	return hc;
}

/* 多项式相减,PA为多项式A的头指针，PB为多项式B的头指针 */
PolynList SubPolyn(PolynList PA, PolynList PB)
{
	PolynList ha = PA->next;/* 指向头结点*/
	PolynList hb = PB->next;/* 同上 */
	PolynList hc = (PolynList)malloc(sizeof(PolynNode));/* 创建新的多项式链表的头指针*/
	PolynList tail = hc;
	PolynList temp = NULL;/* 临时结点 */
	int sub;/* 系数差 */
	tail->next = NULL;
	while (ha&&hb)
	{
		temp = (PolynList)malloc(sizeof(PolynNode));
		/* 多项式PA的指数小于多项式PB的指数 */
		if (ha->expn < hb->expn)
		{
			temp->expn = ha->expn;/* 储存PA的数据 */
			temp->coef = ha->coef;
			ha = ha->next;/* PA链表结点后移 */
			tail->next = temp;
			temp->next = NULL;
			tail = temp;
		}
		/* 多项式PA的指数大于多项式PB的指数 */
		else if (ha->expn > hb->expn)
		{
			temp->expn = hb->expn;/* 储存PB的数据 */
			temp->coef = hb->coef;
			hb = hb->next;/* PB链表结点后移 */
			tail->next = temp;
			temp->next = NULL;
			tail = temp;
		}
		else
		{/* 多项式PA的指数等于多项式PB的指数 */
			sub = ha->coef - hb->coef;/* 求差 */
			/* 不等于0就直接储存相加后的数据 */
			if (sub != 0)
			{
				temp->coef = ha->coef - hb->coef;
				temp->expn = ha->expn;
				ha = ha->next;/*PA，PB的结点同时后移 */
				hb = hb->next;
				tail->next = temp;
				temp->next = NULL;
				tail = temp;
			}
			/* 系数相加为0则不必储存 */
			else
			{
				free(temp);/* 释放结点 */
				ha = ha->next;/* 后移 */
				hb = hb->next;
			}
		}
	}
	/* 多项式项数可能不等，因为PA和PB只有一个链表可能有数据未使用，因此直接储存剩下的数据即可 */
	while (ha)
	{
		temp = (PolynList)malloc(sizeof(PolynNode));
		temp->coef = ha->coef;
		temp->expn = ha->expn;
		ha = ha->next;
		tail->next = temp;
		temp->next = NULL;
		tail = temp;
	}
	while (hb)
	{
		temp = (PolynList)malloc(sizeof(PolynNode));
		temp->coef = -hb->coef;
		temp->expn = hb->expn;
		hb = hb->next;
		tail->next = temp;
		temp->next = NULL;
		tail = temp;
	}
	return hc;
}

/* 多项式相乘,PA为多项式A的头指针，PB为多项式B的头指针*/
PolynList MultiPolyn(PolynList PA, PolynList PB)
{
	/* 原理和创建多项式类似，只是赋值方法不同，最终得到一个乱序的多项式 */
	PolynList ha = PA->next;
	PolynList hb = PB->next;
	PolynList hc = (PolynList)malloc(sizeof(PolynNode));
	PolynList tail = hc;
	PolynList HbTemp = NULL;/* 多项式B链表的临时结点 */
	PolynList temp;/* 多项式C链表的临时结点 */
	tail->next = NULL;
	for (; ha != NULL; ha = ha->next)/* 遍历多项式PA的所有项 */
	{
		HbTemp = PB->next;
		while (HbTemp!=NULL)/* 与多项式PB所有项相乘 */
		{
			temp = (PolynList)malloc(sizeof(PolynNode));
			temp->coef = (ha->coef)*(HbTemp->coef);
			temp->expn = ha->expn + HbTemp->expn;
			tail->next = temp;
			temp->next = NULL;
			tail = temp;
			HbTemp = HbTemp->next;
		}
		HbTemp = PB->next;/* 将HbTemp修改为PB的头结点的指针，准备下次相乘 */
	}
	return hc;
}

/* 
多项式的项按指数从小排到大
原理与选择排序类似 
*/
void SortPolyn(PolynList P)
{
	PolynList temp;
	PolynList MinExpnNode;/* 储存多项式系数最小的项所在的结点指针 */
	int min;/* 记录系数的最小值 */
	P = P->next;/* 头结点 */
	while (P!=NULL)
	{
		temp = P;/* 遍历P之后的所有结点，防止修改P的值 */
		min = temp->expn;
		MinExpnNode = temp;

		while (temp!=NULL)/* temp为NULL说明遍历结束 */
		{
			if (temp->expn < min)
			{
				min = temp->expn;
				MinExpnNode = temp;
			}
			temp = temp->next;
		}
		swap(&(P->expn), &(MinExpnNode->expn));
		swap(&(P->coef), &(MinExpnNode->coef));
		P = P->next;
	}

}

/* 多项式合并，P为头指针 */
void MergePolyn(PolynList P)
{
	PolynList HEAD = P;/* 头指针 */
	P = P->next;/* 第一项的结点 */
	while (P!=NULL)
	{
		if (P->next!=NULL)/* 如果该结点后还有结点，则要看是否能合并同类项 */
		{
			while (P->next&&P->expn == P->next->expn)/* 只要指数相等就要合并头类项，并且是向后合并 */
			{
				P->next->coef = P->coef + P->next->coef;/* 系数相加 */
				P->coef = 0;/* 先赋值为0，等后面再删除该结点 */
				P = P->next;
			}
		}
		P = P->next;
	}
}

/* 删除系数为0的结点 */
void RemoveZero(PolynList P)
{
	PolynList HEAD = P;
	PolynList temp = P;
	int pos = 0;
	P = P->next;
	while (P!=NULL)
	{
		temp = P->next;
		pos++;
		if (P->coef == 0)
		{
			DeleteNode(HEAD, pos);
			pos--;/* 这步很关键，删除结点后如果位置不退回去，那么所得到的被删除结点的位置就会有误 */
		}
		P = temp;
	}
}

/* 交换值 */
void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}