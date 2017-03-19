#include<stdio.h>
#include<malloc.h>

typedef struct SM_ELEMENT{

	int row;
	int col;
	int value;

}SM_ELEMENT;

typedef struct SM_HEADER{
	
	SM_ELEMENT *elememts;
	int rowCount;
	int colCount;
	int elememtCount;

}SM_HEADER;

//

void initSparseMatrix(SM_HEADER **head);											   //初始化三元组矩阵

SM_HEADER *initSparseMatrixHead(int rowCount, int colCount, int elementCount);         //初始化三元组矩阵的控制头

void destory_Sparse_Matrix_Head(SM_HEADER *head);									   //销毁矩阵
	
void show_Sparse_Matrix(SM_HEADER head);											   //显示矩阵

SM_HEADER *revange_Sparse_Matrix(SM_HEADER head);

SM_HEADER *revange_Sparse_Matrix(SM_HEADER head){

	SM_HEADER * revangeSparse = NULL;
	int *postion;
	int i;
	int index;


	//为转置之后的矩阵申请一个空间
	revangeSparse = initSparseMatrixHead(head.colCount, head.rowCount, head.elememtCount);
	
	
	/*revangeSparse = (SM_HEADER *)calloc(sizeof(SM_HEADER),1);
	revangeSparse->rowCount = head.colCount;
	revangeSparse->colCount = head.rowCount;
	revangeSparse->elememts = (SM_ELEMENT *)calloc(sizeof(SM_ELEMENT),head.elememtCount);
	*/

	//为数组申请空间
	postion = (int *)calloc(head.colCount + 1,sizeof(int));


	/*
		下面代码的具体思路分析，请看该文件下的三元组矩阵.bmp文件。
	*/

	
	/*
	for(i = 0; i < revangeSparse->elememts; i++){
		postion[head.elememts[i].col + 1]++;
	}*/
	
	//用数组统计每个元素出现在有效元素的次数，保存在col+ 1的下标下，具体为什么，请看解析图
	//这个位置有"东西"通知下面的要让出位置来。
	for(i = 0; i < head.elememtCount; i++){
		postion[head.elememts[i].col + 1]++;
	}

	for(i = 1; i <= head.colCount ; i++){
		//求和，因为后面要看当前的元素前面有多少个，才好直接进行过位置的插入。
		postion[i] += postion[i-1];
	}

	for(i = 0; i < head.elememtCount; i++){
		index = postion[head.elememts[i].col];
		revangeSparse->elememts[index].row = head.elememts[i].col;
		revangeSparse->elememts[index].col = head.elememts[i].row;
		revangeSparse->elememts[index].value = head.elememts[i].value;

		postion[head.elememts[i].col]++;
		//这里可不是postion[index+1]++;   就是因为这个的原因，使你找了半天的问题
	}
	free(postion);

	return revangeSparse;

}



void show_Sparse_Matrix(SM_HEADER head){

	int i;
	int j;
	
	int index = 0;		//记录在用于存储在有效元素数组中的下标

	printf("\n");
	
	for(i = 0; i < head.rowCount; i++){		//循环遍历矩阵 行和列
		for(j = 0; j < head.colCount; j++){
			
			if(i == head.elememts[index].row && j == head.elememts[index].col){//当遍历到和有效元素中的保存的行和列的值相同的时候，就是找到一个有效的元素
				
				printf("%d\t", head.elememts[index++].value);//输出有效个数，同时index++
			}else{
				printf("0\t");                               //不是有效元素的输出0
			}
		}
		printf("\n");
	}

}

void destory_Sparse_Matrix_Head(SM_HEADER *head){
	
	if(head){							//不能释放一个没有初始化矩阵的头结点
		if(head->elememts){			//释放存储有效节点元素的空间
			free(head->elememts);
		}
		free(head);					//释放控制头的空间。
	}
	
}

SM_HEADER *initSparseMatrixHead(int rowCount, int colCount, int elementCount){

	SM_HEADER *head = NULL;

	//申请控制头空间， 并初始化
	head = (SM_HEADER *)malloc(sizeof(SM_HEADER));
	head->rowCount = rowCount;
	head->colCount = colCount;
	head->elememtCount = elementCount;
	//申请有效节点的空间
	head->elememts = (SM_ELEMENT *)malloc(sizeof(SM_ELEMENT)*elementCount);

	//返回指针。
	return head;
}

void initSparseMatrix(SM_HEADER **head){

	/*
		1、确定矩阵行数，列数。
	*/
	int rowCount;
	int colCount;
	int elememtCount;
	int i;
	int row;
	int col;
	int value;


	if(NULL == *head){
		printf("请输入矩阵的行数，列数及有效元素个数,如(2 3 4):\n");
		scanf("%d %d %d", &rowCount, &colCount, &elememtCount);

		(*head) = initSparseMatrixHead(rowCount, colCount, elememtCount);

		if(*head){
			printf("请输入%d个有效元素的行值，列值，数据值,如(1 2 89):\n", elememtCount);

			//用户进行输入有效元素。
			for(i = 0; i < elememtCount; i++){
				printf("请输入第%d个元素:",i + 1);
				scanf("%d %d %d", &row, &col, &value);
				
				//这里本来因该对输入的韩烈值进行有效性的验证。
				if(row < rowCount && row >= 0 && col < colCount && col >= 0){
					(*head)->elememts[i].row = row;
					(*head)->elememts[i].col = col;
					(*head)->elememts[i].value = value;
				}else{
					printf("你输入的行列值超出你所设定的行列值！");
					return ;
				}
			}
		}
	}
}

void main(void){

	SM_HEADER * head = NULL;
	SM_HEADER * head1 = NULL;
	//初始化矩阵
	initSparseMatrix(&head);
	
	//显示矩阵
	show_Sparse_Matrix(*head);

	head1 = revange_Sparse_Matrix(*head);

	printf("矩阵转置后:\n");
	show_Sparse_Matrix(*head1);
	
	//销毁矩阵
	destory_Sparse_Matrix_Head(head);
	destory_Sparse_Matrix_Head(head1);

}
