#ifndef _BASE_H_
#define _BASE_H_

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 300
#define NOT_FOUND -1

void initData(int *data, int count); 
void showArray(int *data, int count);

void showArray(int *data, int count){
	int i;

	puts("array:");
	for(i = 0; i < count; i++){
		printf("%d ", data[i]);
	}
	puts("");
}

void initData(int *data, int count){
	int i;

	srand(time(0));
	for(i = 0; i < count ;i++){
		data[i] = rand() % 900 + 100;
	}
}

#endif