#include<stdio.h>
#include"base.h"

/*
        朱洪写的插入排序是有错误的。
	希尔排序是的实质是分组插入排序， 该方法又被称为缩小增量排序,由DL.Shell于1959年提出而得名。
	思想:先将整个待排序元素分割成若干子序列(由相隔某个"增量"的元素组成的)分别进行直接插入排序，然后依次缩减再
	进行排序，待整序列的元素基本有序(增量足够小)时，再对全体元素进行一次直接插入排序。
	因为直接插入排序在元素基本有序的情况下（接近最好情况），效率很高得的，因此希尔排序在时间
	效率上比前面的插入排序都高。
	详细的请看 关于希尔排序的图解。

  平均时间复杂度：希尔排序的时间复杂度和其增量序列有关系，这个涉及到数学上尚未解决的难题
  不过在某些序列上为 O(N^1.25)

*/

void Sell_Sort(int * arr, int size);

void Sell_Sort(int * arr, int size){
	
	//以数组长度的一半来作为初始的步长。
	int grap = size>>1;
	int i;
	int j;
	int temp;

	//这个是最简洁的版本了。
	while(1<=grap){
		for(i = grap; i < size; i++){
			temp = arr[i];
			for(j = i - grap; j>=0 && temp < arr[j]; j-= grap){
				arr[j+grap] = arr[j];
			}
			arr[j+grap] = temp;
		}
		//每次取一半
		grap = grap>>1;
	}

}

void main(void){
	int arr[20];		

	initData(arr, 20);

    showArray(arr, 20);
	Sell_Sort(arr, 20);

	showArray(arr, 20);
}