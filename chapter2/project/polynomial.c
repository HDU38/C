#include "Polynomial.h"

int main() 
{

	PolynList PA = CreatePolyn();
	PolynList PB = CreatePolyn();
	PolynList PC = MultiPolyn(PA, PB);
	PolynList PD = AddPolyn(PA, PB);
	PolynList PE = SubPolyn(PA, PB);

	SortPolyn(PA);
	printf("输入的多项式1为:");
	PolynTraverse(PA);
	printf("\n");

	SortPolyn(PB);
	printf("输入的多项式2为:");
	PolynTraverse(PB);
	printf("\n");

	SortPolyn(PC);
	MergePolyn(PC);
	RemoveZero(PC);
	printf("相乘后的多项式为:");
	PolynTraverse(PC);
	printf("\n");

	printf("相加后的多项式为:");
	PolynTraverse(PD);
	printf("\n");

	printf("多项式1减去多项式2后的多项式为:");
	PolynTraverse(PE);
	printf("\n");

	system("pause");
	return 0;

}