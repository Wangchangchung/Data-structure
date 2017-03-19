#include<stdio.h>
#include<malloc.h>

#define USER_TYPE          int
#define boolean            unsigned  char 
#define  TRUE               1
#define  FALSE              0

typedef struct MATRIX{
	
	USER_TYPE *data;
	int rowCount;
	int colCount;

}MATRIX;

boolean initMatrix(MATRIX **matrix, int rowCount, int colCount);                 //初始化矩阵

void destoryMatrix(MATRIX **matrix);

boolean getMatrixElement(MATRIX matrix, int row, int col, USER_TYPE *value);

boolean setMatrixElement(MATRIX matrix, int rowIndex, int colIndex, USER_TYPE value);

boolean setMatrixElement(MATRIX matrix, int rowIndex, int colIndex, USER_TYPE value){
	
	if(rowIndex >= matrix.rowCount || rowIndex < 0 || colIndex >= matrix.colCount || colIndex < 0){
		return FALSE;
	}
	 matrix.data[rowIndex*matrix.colCount + colIndex] = value;
	return TRUE;
}

boolean getMatrixElement(MATRIX matrix, int row, int col, USER_TYPE *value){

	if(row >= matrix.rowCount || row < 0 || col >= matrix.colCount || col < 0){
		return FALSE;
	}
	*value = matrix.data[row*matrix.colCount + col];
	return TRUE;
}

void  destoryMatrix(MATRIX **matrix){
	if(*matrix){
		if((*matrix)->data){
			free((*matrix)->data);
		}
		free(*matrix);
		*matrix =NULL;
	
	}
}


boolean initMatrix(MATRIX **matrix, int rowCount, int colCount){

	if(*matrix){
		return FALSE;
	}
	
	if(*matrix = (MATRIX *)malloc(sizeof(MATRIX))){
		(*matrix)->data = (USER_TYPE *)malloc(sizeof(USER_TYPE)*rowCount*colCount);
		(*matrix)->colCount = colCount;
		(*matrix)->rowCount = rowCount;
		return TRUE;
	}
	return FALSE;
}

void main(void){

	MATRIX *head  = NULL;
	MATRIX *head1 = NULL;
	int i,j, n= 0;

	//初始化
	initMatrix(&head, 4,4);

	
	//赋值0 - 15;
	for( i = 0; i< 4; i++){
		for(j = 0; j < 4; j++){
			setMatrixElement(*head, i, j, n);
			n++;
		}
	}

	//取得数值。
	getMatrixElement(*head, 3 ,1 ,&n);
	printf("%d\n", n);

	getMatrixElement(*head, 1 ,1 ,&n);
	printf("%d\n", n);

	getMatrixElement(*head, 2 ,1, &n);
	printf("%d\n", n);

	getMatrixElement(*head, 3 ,3, &n);
	printf("%d\n", n);
		
	//销毁二维数组。
	destoryMatrix(&head);
	

}