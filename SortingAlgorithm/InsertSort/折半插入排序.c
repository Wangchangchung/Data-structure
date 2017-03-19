#include<stdio.h>
#include"base.h"

/*
	折半插入排序：
	折半插入排序和直接插入排序的不同点在"查找"上，在有关键字序列中，

  每次插入的关键字采用折半查找的方法来定位。虽然折半查找的时间复杂度为O(logN)
  但是定位循环数据后移任然要花费O(N)的代价，因此:
	时间复杂度任然是O(N^2)
	空间复杂度为O(1)
	是稳定的排序算法。
*/


void binear_Insert_Sort(int *arr, int size);

void binear_Insert_Sort(int *arr, int size){
	
	int temp;
	int head;
	int tail;
	int mid;
	int i;
	int j;

	for(i = 1; i < size; i++){
		temp = arr[i];
		head = 0;
		tail = i-1;   //在前面有序的数组中进行二分查找

		while(head<=tail){
			//mid = (head + tail)/2;
			mid = (head+tail)>>1;   //注意右移一位表示除以2 >> 运算符的右边是移动的位数，
			if(arr[mid] > arr[i]){
			  tail = mid-1;
			}else{
			   head = mid+1;
			} 
		}

		for(j = i-1; j >= tail+1; j-- ){
			arr[j+1] = arr[j];
		}
		arr[tail+1] = temp;
	}
}

void main(void){
	
	int arr[20];
	
	initData(arr, 20);
	
	printf("####");
	showArray(arr, 20);
	binear_Insert_Sort(arr, 20);

	printf("@@@@");
	showArray(arr, 20);
	printf("\n!!!!!!");
}
