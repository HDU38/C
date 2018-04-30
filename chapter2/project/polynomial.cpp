#include "polynomial.h"

int main() 
{

	PolynList PA = CreatePolyn();
	SortPolyn(PA);
	printf("输入的多项式为:");
	PolynTraverse(PA);
	printf("\n");

	PolynList PB = CreatePolyn();
	SortPolyn(PB);
	printf("输入的多项式为:");
	PolynTraverse(PB);
	printf("\n");

	PolynList PC = MultiPolyn(PA, PB);
	SortPolyn(PC);
	MergePolyn(PC);
	RemoveZero(PC);
	printf("相乘后的多项式为:");
	PolynTraverse(PC);
	printf("\n");

	PolynList PD =AddPolyn(PA, PB);
	printf("相加后的多项式为:");
	PolynTraverse(PD);
	printf("\n");

	system("pause");
	return 0;

}