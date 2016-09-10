#include<stdio.h>
/*
		归并排序：Q,D,F,X,A,P,N,B,Y,M,C,W
		1、将两个有序的数组进行归并排序，思路很简单，一次比较两个元素的对应下标元素，谁小就先放进目标数组中
		   再将用这个数组的下一个元素和它进行比较，同时目标数组的计数值增加，
		   等一个数组的元素都比较完了之后，就将剩余数组的元素全部给
		   放入目标数组中。

		2、再来看归并排序，其的基本思路就是将数组分成二组A，B，如果这二组组内的数据都是有序的，
		   那么就可以很方便的将这二组数据进行排序。如何让这二组组内数据有序了？
	       可以将A，B组各自再分成二组。依次类推，当分出来的小组只有一个数据时，
		   可以认为这个小组组内已经达到了有序，然后再合并相邻的二个小组就可以了。
		   这样通过先递归的分解数列，再合并数列就完成了归并排序。 
		
		  归并排序的分析：
		  
			一个N关键字的序列，两两归并，可以构造一棵高度为[logN]的归并排序树，
			而每一次归并的时间复杂符为o(m+n).因此，每一趟归并的时间复杂度为o(N)。
			归并排序算法的时间复杂度为O(N*logN),其所需要的辅助空间就是一个能容纳
			中间合并结果的数量为N的连续空间，因此，空间复杂度为O(N). 是稳定的排序算法。
*/

//   对于两个数组已经有序的情况下可以进行的排序，这个是很简单的，
void Merge_Sort_In_Order(int *arrS, int sizeS, int *arrN, int sizeN, int *arrT);

//   d对于一个数组是无序的情况下的排序算法
void Merge_Sort(int *arr, int head, int tail, int *temp);

void Merge_Sort_Array(int *arr, int start, int mid, int last, int *temp);

void Merge_Sort_Array(int *arr, int start, int mid, int last, int *temp){
		
	int index = 0;
	int i = start;
	int j = mid +1;

	while(i <= mid && j <= last){
		if(arr[i] >= arr[j]){
			temp[index++] = arr[j++];
		}else{
			temp[index++] = arr[i++];
		}
	}

	while(i <= mid){
		temp[index++] = arr[i++];
	}
	while(j <= last){
		temp[index++] = arr[j++];
	}

	for(i = 0; i < index; i++){
		arr[start + i] = temp[i];
	}
}




void Merge_Sort(int *arr, int head, int tail, int *temp){

	int mid = (head + tail) /2;
	if(head < tail){
		//使数组的左边有序
		Merge_Sort(arr, head, mid, temp);
		//使数组的右边有序
		Merge_Sort(arr, mid + 1, tail, temp);
		//合并数组
		Merge_Sort_Array(arr, head, mid, tail, temp);
			
	}
	
}

void Merge_Sort_In_Order(int *arrS, int sizeS, int *arrN, int sizeN, int *arrT){

	int i =0;
	int j =0;
	int n = 0;

	while(i < sizeS && j < sizeN){
		
	/*if(arrS[i] >= arrN[j]){
			arrT[n] = arrN[j];
			j++;
		}else{
			arrT[n] = arrS[i]; 
			i++;
		}
		n++;
		*/

		//上面的代码可以简写成这个样子的形式。
		if(arrS[i] >= arrN[j]){
			arrT[n++] = arrN[j++];
		}else{
			arrT[n++] = arrS[i++];
		}
	}

	//那个数组有剩余的就直接将剩余的元素，赋值给arrT数组就行了。
	// 因位每个数组都是有序的。
	while(i < sizeS){
		arrT[n++] = arrS[i++]; 
	}

	while(j < sizeN){
		arrT[n++] = arrN[j++];
	}
}

void main(void){

	int a[5] = {23,24,56,57,59};
	int b[5] = {1,23,45,78,90};
	int c[10] = {0};
	int arr[10] = {4,12,2,1,34,54,34,21,78,99};
	int i ;

	Merge_Sort_In_Order(a,5,b,5,c);

	printf("有序数组的归并排序结果是:\n");
	for(i = 0; i < 10; i++){
		printf("%d ", c[i]);
	}
	printf("\n");

	printf("无序数组的归并排序结果是:\n");
	Merge_Sort(arr, 0, 9, c);

	for(i = 0; i<10; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");

}