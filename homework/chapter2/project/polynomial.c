#include "Polynomial.h"

int main() 
{

	PolynList PA, PB, PC, PD, PE;

	PA = CreatePolyn();
	SortPolyn(PA);
	printf("����Ķ���ʽ1Ϊ:");
	PolynTraverse(PA);
	printf("\n");

	PB = CreatePolyn();
	SortPolyn(PB);
	printf("����Ķ���ʽ2Ϊ:");
	PolynTraverse(PB);
	printf("\n");

	PC = MultiPolyn(PA, PB);
	SortPolyn(PC);
	MergePolyn(PC);
	RemoveZero(PC);
	printf("��˺�Ķ���ʽΪ:");
	PolynTraverse(PC);
	printf("\n");

	PD = AddPolyn(PA, PB);
	printf("��Ӻ�Ķ���ʽΪ:");
	PolynTraverse(PD);
	printf("\n");

	PE = SubPolyn(PA, PB);
	printf("����ʽ1��ȥ����ʽ2��Ķ���ʽΪ:");
	PolynTraverse(PE);
	printf("\n");

	system("pause");
	return 0;

}