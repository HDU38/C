#include "Polynomial.h"

int main() 
{

	PolynList PA, PB, PC, PD, PE;

	PA = CreatePolyn();
	SortPolyn(PA);
	printf("输入的多项式1为:");
	PolynTraverse(PA);
	printf("\n");

	PB = CreatePolyn();
	SortPolyn(PB);
	printf("输入的多项式2为:");
	PolynTraverse(PB);
	printf("\n");

	PC = MultiPolyn(PA, PB);
	SortPolyn(PC);
	MergePolyn(PC);
	RemoveZero(PC);
	printf("相乘后的多项式为:");
	PolynTraverse(PC);
	printf("\n");

	PD = AddPolyn(PA, PB);
	printf("相加后的多项式为:");
	PolynTraverse(PD);
	printf("\n");

	PE = SubPolyn(PA, PB);
	printf("多项式1减去多项式2后的多项式为:");
	PolynTraverse(PE);
	printf("\n");

	system("pause");
	return 0;

}