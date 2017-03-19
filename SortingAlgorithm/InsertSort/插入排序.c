#include<stdio.h>
#include"base.h"


/*
	直接插入排序：将数直接插入有序的数列中
    假设有一个数组：3 5 7 2 1 6 4 9 8 0
	               (3)(5 7 2 1 6 4 9 8 0)
	               (3 5)(7 2 1 6 4 9 8 0)
				   (3 5 7)(2 1 6 4 9 8 0)
	               (2 3 5 7)(1 6 4 9 8 0)
	               (1 2 3 5 7)(6 4 9 8 0)
					......
				   (0 1 2 3 4 5 6 7 8 9)
	 
	   直接插入排序的时间复杂度为：O(N^2)
	   由于不占用额外的存储空间，所以空间复杂度为：O(1)
	   极端情况下：
	        完全顺序 比较次数最多
			完全逆序 移动次数最多
		问：这个是稳定排序还是非稳定排序？
		     直接插入排序是稳定的排序。
	      



*/


void derict_insert_sort(int *arr, int count);

void derict_insert_sort(int *arr, int count){
	int temp;
	int i;
	int j;
	int n;
	
	//升序排序。
	//遍历数组。

	//方法一
	for(i = 1; i < count; i++){
		temp = arr[i];

		for(j = i -1; j >= 0; j--){
			if(temp < arr[j])
				arr[j+1] = arr[j];
			else 
				break;
		}

		arr[j+1] = temp;
		/*
		方法二：
		//遍历前面已经有序的数组，找到一个比他大的位置，将它插入到她的前面。
		for(j = 0; j < i && arr[j] < temp ; j++){
				;
		}
		//找到为位置后 j， 将后面有序的数，整体向后移动一个位置
		//朱洪的课件中，这个n > j ，了这个是错误的，还没有完全的移到位置上
		for(n = i-1; n >= j; n--){
			arr[n+1] = arr[n];
		}

		//将这个数插入它 应该在的位置上。
		arr[j] = temp;

		*/
	}
}

void main(void){
	//int arr[10] = {12,34,2,32,1,3,33,45,30,23};
	int i;

	int arr[10];

	initData(arr, 10);
	printf("排序之前的数组为:\n");
	for(i = 0 ; i< 10; i++){
		printf("%d ", arr[i]);
	}

	printf("\n直接插入排序之后的数组为:\n");

	derict_insert_sort(arr, 10);
	for(i = 0 ; i< 10; i++){
		printf("%d ", arr[i]);
	}

	
}