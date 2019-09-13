#include <stdio.h> 
void swap(int* array,int size)
{
	int i;
	int num;
	int max = 0, min = 0;
	for (i = 1; i < size; i++)
	{
		num = *(array + i);
		if (num < array[min]) min = i;
		if (num > array[max]) max = i;
	}
	num = *(array + max);
	*(array + max) = *(array + min);
	*(array + min) = num;
}
int main85()
{
	int a[] = { 2,3,5,7,9,3,1,4,6 };
	int i;
	for (i = 0; i < sizeof(a) / sizeof(a[0]); i++)
		printf("%d ", a[i]);
	printf("\n");
	swap(a, sizeof(a) / sizeof(a[0]));
	for (i = 0; i < sizeof(a) / sizeof(a[0]); i++)
		printf("%d ", a[i]);
	getchar();
}