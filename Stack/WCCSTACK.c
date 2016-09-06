#include<stdio.h>
#include<malloc.h>


//定义一个"boolean类型"的数据类型
typedef unsigned char boolean;
typedef int           USER_TYPE;

//用于 boolean的取值 TRUE FALSE
#define TRUE			  1
#define FALSE			  0


//定义一个控制头
typedef struct STACK{

	USER_TYPE *data;
	int maxRoom;
	int top;


}STACK;

boolean initStack(STACK **head, int maxRo);

void destoryStack(STACK **head);

boolean isStackEmpty(STACK stack);

boolean isStackFull(STACK stack);

boolean push(STACK *head,USER_TYPE userData);

boolean pop(STACK *head, USER_TYPE *value);							//如何确定pop()操作中的参数的个数问题
																	//一个是，返回值赋值给用户所接受对的变量，另一种是，在函数的时候传入参数，

//USER_TYPE readTop(STACK  head);
boolean readTop(STACK head, USER_TYPE *data);

boolean readTop(STACK head, USER_TYPE *data){
	if(isStackFull(head)){
		return FALSE;
	}
	*data = head.data[head.top-1];                           //注意这里不能是 --head.top
	return TRUE;
}

boolean pop(STACK *head, USER_TYPE *value){

	if(NULL == head){
		return FALSE;
	}
	if(isStackEmpty(*head)){
		return FALSE;
	}
	//因为 top所指向的是堆栈中的栈顶元素的下一位，所以要先 -- 在进行取操作
	*value = head->data[--head->top];
	return TRUE;
}

//入栈
boolean push(STACK *head, USER_TYPE userData){
	
	//如果传入的*head是一个空的，根本就没有申请过用户的空间，那么就不能够进行下面对data[]进行赋值了。
	if(NULL == head){
		return FALSE;
	}
	//如果栈已经满了的化，也就不能入栈了。 注意里面传入的参数是*head，通过*,将指针降为实例了。
	if(isStackFull(*head)){
		return FALSE;
	}
	//对数据区域进行赋值，并将top的值进行++
	head->data[head->top++] = userData;
	return TRUE;


	/*if(head->top < head->maxRoom){
		head->data[head->top] = userData;
		(head->top)++;
		上面的是这个的简化版。
	}*/
}

boolean isStackFull(STACK stack){
	return stack.top >= stack.maxRoom;
}

boolean isStackEmpty(STACK stack){
		return stack.top <= 0;
}


void destoryStack(STACK **head){

	//将控制头和用户数据空间进行释放，注意先释放用户自定义空间，再释放控制头空间
	//先要判断，如果为NULL的话就直接不用进行下面的操作了，这样效率更高些
	//虽然free(NULL)是什么也不做，直接返回的。
	if(*head){
		if((*head)->data){
			free((*head)->data);
			free(*head);
			*head = NULL;
		}
	}
	
}

boolean initStack(STACK **head, int maxRo){

	//这种是比下面的更具“投机取巧”的行为。
	//原理都是一样的。
	if(*head){
		return FALSE;
	}

	if((*head = (STACK *)calloc(sizeof(STACK), 1)) == NULL){
		return FALSE;	
	}
	
	(*head)->maxRoom = maxRo;
	(*head)->top = 0;

	if(((*head)->data = (USER_TYPE *)calloc(sizeof(USER_TYPE), maxRo)) == NULL){
		free(*head);
		*head = NULL;
		return FALSE;
	}
	return TRUE;
	/*
	//判断控制头是否已经经过初始化了
	if(NULL == *head){

		//申请控制头空间
		*head = (STACK *)calloc(sizeof(STACK), 1);
		//如果申请成功的话，进行用户定义的类型申请空间
		if(*head){
		
			//申请用户所需要的类型的stack空间
			(*head)->stack = (USER_TYPE *)calloc(sizeof(USER_TYPE), maxRo); 
			//判断申请用户空间是否成功。
			if(!((*head)->stack)){
				printf("申请失败！请重新确定。");
				//释放之前申请的空间
				free(*head);
				*head = NULL;
				return FALSE;

			}else{
				//申请空间都成功之后，再对控制头其他的数据进行初始化。
				(*head)->maxRoom = maxRo;
				(*head)->top = 0;
			}

		}else{
			printf("申请控制头失败！");
			return FALSE;
		}

		//控制头进行过初始化了，就不必进行初始化
	}else{
		printf("控制头已经经过申请了，请不要再进行申请了！");
		return FALSE;
	}
	return TRUE;
	*/

}

void main(void)
{
	STACK *head = NULL;
	STACK *head2 = NULL;
	
	int value;
	int full;

	int i = initStack( &head, 4);
	printf("是否成功进行初始化：%d\n", i);
	printf("入栈了(虽然你没看到 ^_^ )：\n");
	for(value = 1;  value <= 4;  value++){
		push(head, value);
	}
	

	full = isStackFull(*head);
	printf("堆栈是否满了呢？%d\n",full);
	
	printf("出栈了,出了下面的一些元素：\n");
	for(value = 0; value < 4; value++){
		pop(head, &full);
		printf("%d\n", full);
	}

	full = isStackEmpty(*head);
	printf("栈是否为空呢？%d\n", full);

	printf("我要销毁堆栈了!");
	destoryStack(&head);
	printf("你看到了这里，说明王长春写的堆栈是现在没有问题的！\n");
	


}