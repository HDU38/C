#include<stdlib.h>
#include<time.h>
#include<stdio.h>

#define TRUE 1/* �����ɹ� */
#define FALSE 0/* ����ʧ�� */
#define MAX_ARRAY_LENGTH 100000/* ������󳤶� */


/* ������a��ֵ���Ƶ�����b��,paΪ�����һ��Ԫ�ص�ָ��,bΪ������ */
int copyArray(int *, int length ,int *pb);

/* ����Ԫ�� */
int swap(int *pa, int *pb);

/* �鲢��������, paΪ�����һ��Ԫ�ص�ָ��, loΪ��С�±�, hiΪ��������±꣬midΪ�м�Ԫ�ص��±� */
int mergeArray(int *pa, int lo, int mid, int hi);

/* �鲢����,paΪ�����һ��Ԫ�ص�ָ��,loΪ��С�±�,hiΪ��������±� */
int mergeSort(int *pa, int lo ,int hi);

/* ��������,paΪ�����һ��Ԫ�ص�ָ��,lengthΪ���鳤�� */
int traverse(int *pa, int length);

/* ����Ƿ�����ɹ�,aΪ�����һ��Ԫ�ص�ָ��,lengthΪ���鳤�� */
int assert(int *pa, int length);