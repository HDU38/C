#include "polynomial.h"

int main() 
{

	PolynList PA = CreatePolyn();
	SortPolyn(PA);
	printf("����Ķ���ʽΪ:");
	PolynTraverse(PA);
	printf("\n");

	PolynList PB = CreatePolyn();
	SortPolyn(PB);
	printf("����Ķ���ʽΪ:");
	PolynTraverse(PB);
	printf("\n");

	PolynList PC = MultiPolyn(PA, PB);
	SortPolyn(PC);
	MergePolyn(PC);
	RemoveZero(PC);
	printf("��˺�Ķ���ʽΪ:");
	PolynTraverse(PC);
	printf("\n");

	PolynList PD =AddPolyn(PA, PB);
	printf("��Ӻ�Ķ���ʽΪ:");
	PolynTraverse(PD);
	printf("\n");

	system("pause");
	return 0;

}