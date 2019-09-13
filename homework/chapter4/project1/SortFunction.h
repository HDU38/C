#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define TRUE 1/* 操作成功 */
#define FALSE 0/* 操作失败 */
#define MAX_ARRAY_LENGTH 1000000/* 数组最大长度 */

/* 交换元素 */
int swap(int *, int *);

/*
* 快速排序,a为数组第一个元素的指针，lo为最左
* 的元素的数组下标,hi为最右的元素的数组下标
*/
int quicksort(int *, int, int);

/* 遍历数组,a为数组第一个元素的指针,length为数组长度 */
int traverse(int *, int);

/* 检测是否排序成功,a为数组第一个元素的指针,length为数组长度 */
int assert(int *, int);

