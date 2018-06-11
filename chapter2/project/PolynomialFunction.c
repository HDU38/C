#include "Polynomial.h"

/* ��������ʽ */
PolynList  CreatePolyn() 
{
	PolynList Head = (PolynList)malloc(sizeof(PolynNode));/* ����ͷ��� */
	PolynList Tail = Head;/* ָ�����һ����� */
	PolynList newnode = NULL;/* �½�� */
	int i, n;
	if (Head == NULL)
		printf("�ڴ����ʧ��");
	Tail->next = NULL;/* ���һ�����ָ��NULL */
	printf("���������ʽ����\n");
	scanf("%d", &n);
	printf("��ֱ��������ʽ��ϵ����ָ��(�ÿո����)\n");
	for (i = 0; i < n; i++) {
		newnode = (PolynList)malloc(sizeof(PolynNode));/* ����洢�ռ� */
		scanf("%d %d", &newnode->coef, &newnode->expn);/* ��ֵ */
		Tail->next = newnode;/* ָ���µĽ�� */
		newnode->next = NULL;
		Tail = newnode;
	}
	return Head;/* ����ͷ��� */

}

/* ɾ��ָ��λ�õĽ��,PΪͷָ��,posΪ���λ�ã�λ�ô�1��ʼ */
void DeleteNode(PolynList P, int pos)
{
	int i;
	PolynList temp = NULL;/* ��ʱ��� */
	if (P == NULL)
	{
		printf("����ʽΪ��");
		return;
	}
	/* ������ȡҪɾ���Ľ���ǰһ����� */
	for (i = 1; i <= pos - 1; i++)
	{
		P = P->next;
	}
	temp = P;
	/* Ҫɾ���Ľ�� */
	P = P->next;
	/* ��1��2��3��Ϊ1��3 */
	temp->next = P->next;
	/* �ͷŴ洢�ռ� */
	free(P);
}

/* ��������ʽ��PΪͷָ�� */
void PolynTraverse(PolynList P)
{
	if (P == NULL)
	{
		printf("����ʽΪ��");
		return;
	}
	P = P->next;/* ͷ��� */
	while (P->next != NULL) 
	{
		if (P->expn != 0)
		{
			if (P->next->coef > 0)
				printf("%dx^%d + ", P->coef, P->expn);/* Ϊ����ʽ�ÿ� */
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

/* ����ʽ���,PAΪ����ʽA��ͷָ�룬PBΪ����ʽB��ͷָ�� */
PolynList AddPolyn(PolynList PA, PolynList PB)
{
	PolynList ha = PA->next;/* ָ��ͷ���*/
	PolynList hb = PB->next;/* ͬ�� */
	PolynList hc = (PolynList)malloc(sizeof(PolynNode));/* �����µĶ���ʽ�����ͷָ��*/
	PolynList tail = hc;
	PolynList temp = NULL;/* ��ʱ��� */
	int sum;/* ϵ���� */
	tail->next = NULL;
	while (ha&&hb)
	{
		temp = (PolynList)malloc(sizeof(PolynNode));
		/* ����ʽPA��ָ��С�ڶ���ʽPB��ָ�� */
		if (ha->expn < hb->expn)
		{
			temp->expn = ha->expn;/* ����PA������ */
			temp->coef = ha->coef;
			ha = ha->next;/* PA��������� */
			tail->next = temp;
			temp->next = NULL;
			tail = temp;
		}
		/* ����ʽPA��ָ�����ڶ���ʽPB��ָ�� */
		else if (ha->expn > hb->expn)
		{
			temp->expn = hb->expn;/* ����PB������ */
			temp->coef = hb->coef;
			hb = hb->next;/* PB��������� */
			tail->next = temp;
			temp->next = NULL;
			tail = temp;
		}
		else
		{/* ����ʽPA��ָ�����ڶ���ʽPB��ָ�� */
			sum = ha->coef + hb->coef;/* ��� */
			/* ������0��ֱ�Ӵ�����Ӻ������ */
			if (sum != 0)
			{
				temp->coef = ha->coef + hb->coef;
				temp->expn = ha->expn;
				ha = ha->next;/*PA��PB�Ľ��ͬʱ���� */
				hb = hb->next;
				tail->next = temp;
				temp->next = NULL;
				tail = temp;
			}
			/* ϵ�����Ϊ0�򲻱ش��� */
			else
			{
				free(temp);/* �ͷŽ�� */
				ha = ha->next;/* ���� */
				hb = hb->next;
			}
		}
	}
	/* ����ʽ�������ܲ��ȣ���ΪPA��PBֻ��һ���������������δʹ�ã����ֱ�Ӵ���ʣ�µ����ݼ��� */
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

/* ����ʽ���,PAΪ����ʽA��ͷָ�룬PBΪ����ʽB��ͷָ�� */
PolynList SubPolyn(PolynList PA, PolynList PB)
{
	PolynList ha = PA->next;/* ָ��ͷ���*/
	PolynList hb = PB->next;/* ͬ�� */
	PolynList hc = (PolynList)malloc(sizeof(PolynNode));/* �����µĶ���ʽ�����ͷָ��*/
	PolynList tail = hc;
	PolynList temp = NULL;/* ��ʱ��� */
	int sub;/* ϵ���� */
	tail->next = NULL;
	while (ha&&hb)
	{
		temp = (PolynList)malloc(sizeof(PolynNode));
		/* ����ʽPA��ָ��С�ڶ���ʽPB��ָ�� */
		if (ha->expn < hb->expn)
		{
			temp->expn = ha->expn;/* ����PA������ */
			temp->coef = ha->coef;
			ha = ha->next;/* PA��������� */
			tail->next = temp;
			temp->next = NULL;
			tail = temp;
		}
		/* ����ʽPA��ָ�����ڶ���ʽPB��ָ�� */
		else if (ha->expn > hb->expn)
		{
			temp->expn = hb->expn;/* ����PB������ */
			temp->coef = hb->coef;
			hb = hb->next;/* PB��������� */
			tail->next = temp;
			temp->next = NULL;
			tail = temp;
		}
		else
		{/* ����ʽPA��ָ�����ڶ���ʽPB��ָ�� */
			sub = ha->coef - hb->coef;/* ��� */
			/* ������0��ֱ�Ӵ�����Ӻ������ */
			if (sub != 0)
			{
				temp->coef = ha->coef - hb->coef;
				temp->expn = ha->expn;
				ha = ha->next;/*PA��PB�Ľ��ͬʱ���� */
				hb = hb->next;
				tail->next = temp;
				temp->next = NULL;
				tail = temp;
			}
			/* ϵ�����Ϊ0�򲻱ش��� */
			else
			{
				free(temp);/* �ͷŽ�� */
				ha = ha->next;/* ���� */
				hb = hb->next;
			}
		}
	}
	/* ����ʽ�������ܲ��ȣ���ΪPA��PBֻ��һ���������������δʹ�ã����ֱ�Ӵ���ʣ�µ����ݼ��� */
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

/* ����ʽ���,PAΪ����ʽA��ͷָ�룬PBΪ����ʽB��ͷָ��*/
PolynList MultiPolyn(PolynList PA, PolynList PB)
{
	/* ԭ��ʹ�������ʽ���ƣ�ֻ�Ǹ�ֵ������ͬ�����յõ�һ������Ķ���ʽ */
	PolynList ha = PA->next;
	PolynList hb = PB->next;
	PolynList hc = (PolynList)malloc(sizeof(PolynNode));
	PolynList tail = hc;
	PolynList HbTemp = NULL;/* ����ʽB�������ʱ��� */
	PolynList temp;/* ����ʽC�������ʱ��� */
	tail->next = NULL;
	for (; ha != NULL; ha = ha->next)/* ��������ʽPA�������� */
	{
		HbTemp = PB->next;
		while (HbTemp!=NULL)/* �����ʽPB��������� */
		{
			temp = (PolynList)malloc(sizeof(PolynNode));
			temp->coef = (ha->coef)*(HbTemp->coef);
			temp->expn = ha->expn + HbTemp->expn;
			tail->next = temp;
			temp->next = NULL;
			tail = temp;
			HbTemp = HbTemp->next;
		}
		HbTemp = PB->next;/* ��HbTemp�޸�ΪPB��ͷ����ָ�룬׼���´���� */
	}
	return hc;
}

/* 
����ʽ���ָ����С�ŵ���
ԭ����ѡ���������� 
*/
void SortPolyn(PolynList P)
{
	PolynList temp;
	PolynList MinExpnNode;/* �������ʽϵ����С�������ڵĽ��ָ�� */
	int min;/* ��¼ϵ������Сֵ */
	P = P->next;/* ͷ��� */
	while (P!=NULL)
	{
		temp = P;/* ����P֮������н�㣬��ֹ�޸�P��ֵ */
		min = temp->expn;
		MinExpnNode = temp;

		while (temp!=NULL)/* tempΪNULL˵���������� */
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

/* ����ʽ�ϲ���PΪͷָ�� */
void MergePolyn(PolynList P)
{
	PolynList HEAD = P;/* ͷָ�� */
	P = P->next;/* ��һ��Ľ�� */
	while (P!=NULL)
	{
		if (P->next!=NULL)/* ����ý����н�㣬��Ҫ���Ƿ��ܺϲ�ͬ���� */
		{
			while (P->next&&P->expn == P->next->expn)/* ֻҪָ����Ⱦ�Ҫ�ϲ�ͷ������������ϲ� */
			{
				P->next->coef = P->coef + P->next->coef;/* ϵ����� */
				P->coef = 0;/* �ȸ�ֵΪ0���Ⱥ�����ɾ���ý�� */
				P = P->next;
			}
		}
		P = P->next;
	}
}

/* ɾ��ϵ��Ϊ0�Ľ�� */
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
			pos--;/* �ⲽ�ܹؼ���ɾ���������λ�ò��˻�ȥ����ô���õ��ı�ɾ������λ�þͻ����� */
		}
		P = temp;
	}
}

/* ����ֵ */
void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}