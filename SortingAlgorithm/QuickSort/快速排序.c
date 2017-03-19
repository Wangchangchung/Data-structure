#include <stdio.h>


void  quickSort(int *arr, int left, int right);		//参数： 第一个：数组(子数组)最左边下标值， 第二个参数：数组（子数组）最右边下标值。

void  quickSort(int *arr, int left, int right)
{	
	int i = left;									//寻找比“标准数”小时左边遍历的下标(左哨兵)
	int j = right;									//寻找比“标准数”大的右遍历下的标(右哨兵)
	int temp  = arr[left];                          //存储"标准数"用于后面的交换
	int change;
	if(left > right || arr == NULL)
		return ;

	while(i != j){
	
		while(temp <= arr[j] && i < j){				//右"哨兵"开始从数组的右边开始寻找比标准数小的数，一找到就跳出循环，记录下标。
			j--;
		}
		while(temp >= arr[i] && i < j){				//左"哨兵"开始从数组的右边开始寻找比标准数大的数，一找到就跳出循环，记录下标。
			i++;
		}

		if(i < j)                                  //如果 i < j(i = j 时指向同一个位置时，就把这个数和标准数交换)
												   //将比标准数大的和小的进行交换。	
		{
			change = arr[i];
			arr[i] = arr[j];
			arr[j] = change;
		}
	}
	
	arr[left] = arr[i];                          //此时跳出while()循环是指当两个哨兵都指向同一个地方(相遇了)，
	arr[i] = temp;								 //相遇了就说明找到数组中满足左边数比标准值小，右边数比标准值大的位置了。所以可以交换。
	
	quickSort(arr, left, i-1);					 //递归处理左边的数组
	quickSort(arr, i+1, right);					 //递归处理右边的数组
}

void main(void)
{
	int arr[] = {13,24,5,1,42,56,78,51,90,45,32,22,4};
	int i;

	quickSort(arr, 0, 12);

	for(i = 0; i < 13; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}