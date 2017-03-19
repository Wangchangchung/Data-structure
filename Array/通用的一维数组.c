#include <stdio.h>
#include <malloc.h>
#include "../mecbase.h"

/*
#define COUNT	100

void main(void){
	int ar[COUNT];
	...
}

#define ROW_COUNT	3
#define COL_COUNT	3

...
	int m[ROW_COUNT][COL_COUNT];

	typedef int[COL_COUNT] M;
	M m[ROW_COUNT];

  
...m[i][j]...

  int a[3][4]; <=> int[4]  a[3];
*/

typedef int USER_TYPE;

typedef struct ARRAY{
	USER_TYPE *array;
	int count;
}ARRAY;

void initArray(ARRAY **array, int count);
boolean setArrayElementAt(ARRAY array, int index, USER_TYPE value);
boolean getArrayElementAt(ARRAY array, int index, USER_TYPE *value);
void destoryArray(ARRAY **array);

void destoryArray(ARRAY **array){
	if(*array == NULL){
		return;
	}

	free((*array)->array);
	free(*array);
	*array = NULL;
}

boolean getArrayElementAt(ARRAY array, int index, USER_TYPE *value){
	if(index < 0 || index >= array.count){
		return FALSE;
	}

	*value = array.array[index];

	return TRUE;
}

boolean setArrayElementAt(ARRAY array, int index, USER_TYPE value){
	if(index < 0 || index >= array.count){
		return FALSE;
	}

	array.array[index] = value;

	return TRUE;
}

void initArray(ARRAY **array, int count){
	if(*array){
		return;
	}

	*array = (ARRAY *)malloc(sizeof(ARRAY));
	(*array)->array = (USER_TYPE *)malloc(sizeof(USER_TYPE) * count);
}

void main(void){
	ARRAY *ar = NULL;

	initArray(&ar, 10);
}