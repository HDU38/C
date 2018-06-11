#include<stdlib.h>
#include<time.h>
#include<stdio.h>

#define TRUE 1/* 操作成功 */
#define FALSE 0/* 操作失败 */
#define MAX_ARRAY_LENGTH 100000/* 数组最大长度 */


/* 将数组a的值复制到数组b中,pa为数组第一个元素的指针,b为空数组 */
int copyArray(int *, int length ,int *pb);

/* 交换元素 */
int swap(int *pa, int *pb);

/* 归并两个数组, pa为数组第一个元素的指针, lo为最小下标, hi为数组最大下标，mid为中间元素的下标 */
int mergeArray(int *pa, int lo, int mid, int hi);

/* 归并排序,pa为数组第一个元素的指针,lo为最小下标,hi为数组最大下标 */
int mergeSort(int *pa, int lo ,int hi);

/* 遍历数组,pa为数组第一个元素的指针,length为数组长度 */
int traverse(int *pa, int length);

/* 检测是否排序成功,a为数组第一个元素的指针,length为数组长度 */
int assert(int *pa, int length);