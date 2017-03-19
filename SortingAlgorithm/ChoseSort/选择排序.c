#include<stdio.h>
#include"base.h"

/*
	选择排序：
		原理： 首先，找到数组中最小的那个元素，其次，将它和数组的第一个元素交换位置
		(如果第一个元素就是最小的，那么它就和他自己交换)。再次，在剩下的元素中找到最小的
		元素，将它与数组的第二个元素交换位置。如此反复，直到将整个数组排序。

	选择排序的特点：1、运行时间和输入无关。
						为了找出最小元素而扫描一遍数组并不能为下一遍提供什么信息。
						这这种性质在某些情况下是缺点，因为使用选择排序可能会发现，一个已经
						有序的数组或是主键全部相等的数组和一个元素随机排列的数组所用的排序时间竟然
						一样长。
					2、数据移动是最少的。
						每次交换都会改变两个元素的值，因此选择排序用了N次交换----交换次数和数组大小是线性关系。
						我们将研究的其他任何算法都不具备这个特征（大部分的增长数量级都是线性对数或是平方级别）

		选择排序的特点是：左边（或右边）总是有序的。
*/
void selectionSort(int *ar, int count);

void selectionSort(int *ar, int count)
{
	int i;										
	int j;
	int temp;

	for(i = 0; i < count; i++)
	{
		for(j = i + 1; j < count; j++){   
			if(ar[i] > ar[j] ){
				temp = ar[i];
				ar[i] = ar[j];
				ar[j] = temp;
			}
		}
	}
}

void main(void)
{
	int ar[20];

	initData(ar, 20);

	printf("排序之前:\n");
	showArray(ar, 20);

	selectionSort(ar, 20);

	printf("排序后:\n");
	showArray(ar, 20);
}