#include<stdio.h>
#include<malloc.h>

//十字交叉链中的元素节点类型
typedef struct SM_CR_ELEMENT{

	int value;
	struct SM_CR_ELEMENT *nextRow;
	struct SM_CR_ELEMENT *nextCol;

}SM_CR_ELEMENT;

//十字交叉链的左上角的控制头节点
typedef struct SM_CR_HEADER{

	int rowCount;
	int colCount;
	SM_CR_ELEMENT **rowHeadPoint;
	SM_CR_ELEMENT **colHeadPoint;
}SM_CR_HEADER;

#define FOUND_ROW    0
#define FOUND_COL    1
#define NOT_FOUND   -1
#define FALSE		 0
#define TRUE		 1
#define USER_TYPE    int


void initCrossLink(SM_CR_HEADER **head);										//初始化

int getRowOrCol(SM_CR_HEADER head, SM_CR_ELEMENT *node, int maxIndex, int findType);   //得到节点的行值和列值得合并方法

int get_CR_RowIndex(SM_CR_HEADER head, SM_CR_ELEMENT *node);					//得到节点的行值

int get_CR_ColIndex(SM_CR_HEADER head, SM_CR_ELEMENT *node);					//得到节点的列值

void in_Put_One_Element(SM_CR_HEADER head, void (*input)(USER_TYPE *));			//将一个节点保存到十字交叉链中

void init_Element_Value(int *value);											//用户输入给每一个元素赋值

void creat_One_Element(SM_CR_HEADER head, USER_TYPE  value, int row, int col);							//为一个节点申请空间

void insert_Element_Into_CRLink(SM_CR_HEADER head, SM_CR_ELEMENT *newNode, int row, int col);			//将一个节点直接插入到十字交叉链中。

void insert_Element_Into_RowLink(SM_CR_HEADER head, SM_CR_ELEMENT *newNode, int row, int col);			//插入到行

void insert_Element_Into_ColLink(SM_CR_HEADER head, SM_CR_ELEMENT *newNode, int row, int col);			//插入到列

void init_Matrix(SM_CR_HEADER head);											//初始化矩阵

void show_SMCR_Matrix(SM_CR_HEADER head);										//显示矩阵

void destory_Matrix(SM_CR_HEADER **head);										//销毁矩阵


void destory_Matrix(SM_CR_HEADER **head){

	if((*head)==NULL){
		return ;
	}

	//释放行列的控制头指针。
	if((*head)->colHeadPoint && (*head)->rowHeadPoint){
		free((*head)->colHeadPoint);
		free((*head)->rowHeadPoint);
	}
	//释放十字交叉链的控制头
	free(*head);
	*head = NULL;
}


void show_SMCR_Matrix(SM_CR_HEADER head){

	int col;
	int row;
	SM_CR_ELEMENT *node = NULL;

	printf("\n");
	for(row = 0; row < head.rowCount; row++){
		//先得到每一行的头指针
		node = head.rowHeadPoint[row];
		for(col = 0; col < head.colCount; col++){
			//根据得到node的列下标值  与循环col的比较，当遇到存储元素的节点的时候就输出
			if(get_CR_ColIndex(head, node) == col){
				printf("%d\t", node->value);
				node = node->nextCol;			//同时 node指向下一个节点,虽然col循环一直在判断，但是没有值得位置与col是
			}else{
				printf("0\t");
			}
			//注意，不能再这里写  node = node->nextCol;
		}
		printf("\n");
	}

}

void init_Matrix(SM_CR_HEADER head){
	int count;
	int i;

	printf("请输入有效元素个数:");
	scanf("%d", &count);

	for(i = 0 ; i < count; i++){
		in_Put_One_Element(head, init_Element_Value);
	}
}

void insert_Element_Into_ColLink(SM_CR_HEADER head, SM_CR_ELEMENT *newNode, int row, int col){

	
	SM_CR_ELEMENT *preElement =NULL;		//用于保存前一个节点的指针(地址)
	
	SM_CR_ELEMENT *curElement = NULL;		//用于保存当前节点的指针(地址)

	//如果该列中没有元素， 或者第一个插入的位置是原有列元素的最前面，那么直接更改head.colHeadPoint[col] 的指向
	//将元素进行插入
	if(head.colHeadPoint[col] == NULL || get_CR_RowIndex(head, head.colHeadPoint[col]) > row ){
		newNode->nextRow = head.colHeadPoint[col];
		head.colHeadPoint[col] = newNode;
	}else{
		
		//插入已有元素的中间 或者是在末尾插入。
		//当是要在列的末尾插入的时候最后 curElement = curElement->nextRow = null; 这个的get_CR_RowIndex()返回的是NOT_FOUND
		//调出循环,while循环的后面是为了保证中间的插入的情况。
		preElement = head.colHeadPoint[col];
		curElement = preElement;
		while(get_CR_RowIndex(head, curElement)!= NOT_FOUND && get_CR_RowIndex(head, curElement) < row){
			preElement = curElement;
			curElement = curElement->nextRow;
		}
		//将节点链接
		newNode->nextRow = preElement->nextRow;
		preElement->nextRow = newNode;
	}

}

void insert_Element_Into_RowLink(SM_CR_HEADER head, SM_CR_ELEMENT *newNode, int row, int col){


	//找的方法上面的方法是一样的。 注意找Row的时候用的方法不要搞混了。
	SM_CR_ELEMENT *preElement =NULL;
	SM_CR_ELEMENT *curElement = NULL;


	if(head.rowHeadPoint[row] == NULL || get_CR_ColIndex(head, head.colHeadPoint[row]) > col){
		newNode->nextCol= head.rowHeadPoint[row];
		head.rowHeadPoint[row] = newNode;
	}else{
		
		preElement = head.rowHeadPoint[row];
		curElement = preElement;
		while(get_CR_ColIndex(head, curElement)!= NOT_FOUND && get_CR_ColIndex(head, curElement) < col){
			preElement = curElement;
			curElement = curElement->nextCol;
		}
		newNode->nextCol = preElement->nextCol;
		preElement->nextCol= newNode;

	}

}

void insert_Element_Into_CRLink(SM_CR_HEADER head, SM_CR_ELEMENT *node, int row, int col){
	//插入行
	insert_Element_Into_RowLink(head, node, row,  col);
	//插入列
	insert_Element_Into_ColLink(head, node, row,  col);
	printf("插入一个节点成功！");

}

void creat_One_Element(SM_CR_HEADER head, USER_TYPE  value, int row, int col){

	SM_CR_ELEMENT *newElement = NULL;

	newElement = (SM_CR_ELEMENT *)calloc(sizeof(SM_CR_ELEMENT), 1);
	newElement->value = value;
	newElement->nextRow = NULL;
	newElement->nextCol = NULL;
	printf("创建一个节点成功！");
	//链入进十字交叉链中
	insert_Element_Into_CRLink(head, newElement, row, col);

}

void init_Element_Value(int *value){

	printf("请输入节点的值:");
	scanf("%d", value);

}

void in_Put_One_Element(SM_CR_HEADER head, void (*input)(USER_TYPE *)){

	USER_TYPE value;
	int row;
	int col;

	//调用我在外面定义的方法完成输入一个用户类型的数值。
	input(&value);
	printf("请输入该节点的行值,列值,列如(3 4):");
	scanf("%d %d", &row, &col);

	//调用创建一个节点的方法
	creat_One_Element(head, value, row, col);

}



int get_CR_ColIndex(SM_CR_HEADER head, SM_CR_ELEMENT *node){
	int colIndex;
	SM_CR_ELEMENT *colPoint=NULL;
	
	if(!node){
		return NOT_FOUND;
	}

	//遍历每一列列
	for(colIndex = 0; colIndex < head.colCount; colIndex++){
		for(colPoint = head.colHeadPoint[colIndex]; colPoint; colPoint=colPoint->nextRow){
			if(colPoint == node){
				return colIndex;
			}
		}
	}
	return NOT_FOUND;
}
	
int get_CR_RowIndex(SM_CR_HEADER head, SM_CR_ELEMENT *node){
	int rowIndex = 0;
	SM_CR_ELEMENT *rowPoint=NULL;
	
	if(!node){
		return NOT_FOUND;
	}

	for(rowIndex =0; rowIndex < head.rowCount; rowIndex++){
		for(rowPoint = head.rowHeadPoint[rowIndex]; rowPoint; rowPoint= rowPoint->nextCol){
			if(rowPoint == node){
				return rowIndex;
			}	
		}
	}
	return NOT_FOUND;
}


int getRowOrCol(SM_CR_HEADER head, SM_CR_ELEMENT *node, int maxIndex, int findType){

	SM_CR_ELEMENT *p = NULL;
	int result  = NOT_FOUND;
	int index = 0;
	unsigned char  found =  FALSE;
	
	//没有找到，没有找完
	while(!found &&  index < maxIndex){
		
		//如果是找的类型是col 就选择colHeadPoint 列的头指针
		p = (findType == FOUND_COL ? head.colHeadPoint : head.rowHeadPoint)[index];

		//如果这个链里没有元素就不找了
		//这里循环的条件还有就是没有
		while(p && !found){
			if(p== node){
				found = TRUE;
			}else{
				//往下面找
				p = (findType  == FOUND_COL ? p->nextRow : p->nextCol);
			}
		}
		//判断在该列/行中是否找到对应的下标值了，如果没找到就找下一列或行。
		if(!found){
			index++;
		}
	}
		
	result = index;
	return result;

	/*
	一般的做法是通过下面的方式:分别来找到行列的值，但是都是可以提取到上面的函数。
	if(findType == FOUND_COL){
		
		index = 0;
		while(!found && index < maxIndex){
		
			while(p && !found){
			
				if(p == node){
					found = TRUE;
				}else{
					p = p->nextRow;
				}
			}

			if(!found){
				index++;
			}
		}
	}
	result = index;
	return result;
	*/
}

void initCrossLink(SM_CR_HEADER **head){

	SM_CR_HEADER  *p = NULL;
	
	if(NULL == (*head)){
		
		int colCount;
		int rowCount;

		p = (SM_CR_HEADER *)calloc(sizeof(SM_CR_HEADER), 1);

		printf("请输入矩阵的行数和列数,如(3 5):");
		scanf("%d %d", &rowCount, &colCount);
		
		p->rowCount = rowCount;
		p->colCount = colCount;

		//申请行和列值针空间，  每个元素都是指针
		p->rowHeadPoint = (SM_CR_ELEMENT **)calloc(sizeof(SM_CR_ELEMENT *), rowCount);
		p->colHeadPoint = (SM_CR_ELEMENT **)calloc(sizeof(SM_CR_ELEMENT *), colCount);
		(*head) = p;
	}
}

void main(void){

	SM_CR_HEADER *head = NULL;
	SM_CR_HEADER *head1 = NULL;
	
	//初始化十字交叉链的控制头和 列和行的指针
	initCrossLink(&head);
	//初始化矩阵(节点)
	init_Matrix(*head);
	//显示矩阵
	show_SMCR_Matrix(*head);
	//销毁矩阵
	destory_Matrix(&head);

}