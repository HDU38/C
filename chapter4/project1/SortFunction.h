#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define TRUE 1/* �����ɹ� */
#define FALSE 0/* ����ʧ�� */
#define MAX_ARRAY_LENGTH 1000000/* ������󳤶� */

/* ����Ԫ�� */
int swap(int *, int *);

/*
* ��������,aΪ�����һ��Ԫ�ص�ָ�룬loΪ����
* ��Ԫ�ص������±�,hiΪ���ҵ�Ԫ�ص������±�
*/
int quicksort(int *, int, int);

/* ��������,aΪ�����һ��Ԫ�ص�ָ��,lengthΪ���鳤�� */
int traverse(int *, int);

/* ����Ƿ�����ɹ�,aΪ�����һ��Ԫ�ص�ָ��,lengthΪ���鳤�� */
int assert(int *, int);

