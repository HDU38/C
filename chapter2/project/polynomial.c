#include "Polynomial.h"

int main() 
{

	PolynList PA = CreatePolyn();
	PolynList PB = CreatePolyn();
	PolynList PC = MultiPolyn(PA, PB);
	PolynList PD = AddPolyn(PA, PB);
	PolynList PE = SubPolyn(PA, PB);

	SortPolyn(PA);
	printf("����Ķ���ʽ1Ϊ:");
	PolynTraverse(PA);
	printf("\n");

	SortPolyn(PB);
	printf("����Ķ���ʽ2Ϊ:");
	PolynTraverse(PB);
	printf("\n");

	SortPolyn(PC);
	MergePolyn(PC);
	RemoveZero(PC);
	printf("��˺�Ķ���ʽΪ:");
	PolynTraverse(PC);
	printf("\n");

	printf("��Ӻ�Ķ���ʽΪ:");
	PolynTraverse(PD);
	printf("\n");

	printf("����ʽ1��ȥ����ʽ2��Ķ���ʽΪ:");
	PolynTraverse(PE);
	printf("\n");

	system("pause");
	return 0;

}