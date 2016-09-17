#include<stdio.h>
#include<malloc.h>


#define      boolean          unsigned  char
#define    	 ACTION_IN   	    1
#define      ACTION_OUT         0
#define      USER_TYPE          int
#define      FALSE              -1 
#define      TRUE                2

/*
	这个创建的是一个循环队列：
	初始时：head == tail == 0
	其中为了判断队列是否为空或是否为满了， 有必要记录上一次的操作是什么
	1、如果上次操作是：入队列 &&  head == tail :说明是队列满了
	2、如果上次操作是：出队列 && head == tail : 说明是队列为空了。
	
*/

typedef struct QUEUE{
	USER_TYPE *data;
	int maxRoom;
	int head;
	int tail;
	boolean lastAction;

}QUEUE;

boolean iniQueue(QUEUE **head, int maxRoom);					//对队列进行初始化

void destoryQueue(QUEUE **head);								//销毁队列

boolean isQueueFull(QUEUE head);								//判断队列是否满了

boolean isQueueEmpty(QUEUE head);								//判断队列是否为空

boolean inQueue(QUEUE *head, USER_TYPE data);					//入队列

boolean outQueue(QUEUE *head, USER_TYPE *data);					//出队列

boolean readQueue(QUEUE queue, USER_TYPE *value);				//读取队列最头位置

boolean readQueue(QUEUE queue, USER_TYPE *value){
	if(isQueueEmpty(queue)){
		return FALSE;
	}
	*value = queue.data[queue.head];
	return TRUE;

}

boolean outQueue(QUEUE *head, USER_TYPE *data){
	//一个没有初始化的队列
	if(NULL == head){
		return FALSE;
	}
	//队列还不是空的
	if(!isQueueEmpty(*head)){
		*data = head->data[head->head];
		head->lastAction = ACTION_OUT;
		head->head = (head->head + 1)% head->maxRoom;
		return TRUE;
	}
	return FALSE;

}

boolean inQueue(QUEUE *head, USER_TYPE data){
	if(NULL == head){
		return FALSE;
	}
	//说明队列还没有满
	if(!isQueueFull(*head)){
		head->data[head->tail] = data;
		//注意,创建的是一个循环队列
		head->tail = (head->tail+1) % head->maxRoom;
		head->lastAction = ACTION_IN;
		return TRUE;
	}
	return  FALSE;
}

boolean isQueueEmpty(QUEUE head){
	return head.head == head.tail && head.lastAction == ACTION_OUT;
}

boolean isQueueFull(QUEUE head){
	return head.head == head.tail && head.lastAction == ACTION_IN;
}

void destoryQueue(QUEUE **head){
	//如果传入的是一个没有初始化的队列，那么就不用销毁了，直接返回
	if(*head == NULL){
		return  ;
	}
	//先释放USER_TYPE的空间
	if((*head)->data){
		free((*head)->data);
	}
	//释放控制头
	free(*head);
	*head = NULL;
}

boolean iniQueue(QUEUE **head, int maxRoom){
	
	//如果是之前经过初始化的队列，那么就不能再进行初始化了。
	if(*head){
		return FALSE;
	}
	//如果申请的空间为0或者小于0那是不允许的。
	if(maxRoom <= 0){
		return FALSE;
	}
	//申请控制头不成功的时候
	if((*head = (QUEUE *)malloc(sizeof(QUEUE))) == NULL){
		return FALSE;
	}
	if(((*head)->data = (USER_TYPE *)malloc(sizeof(USER_TYPE)*maxRoom)) == NULL){
		//释放控制头的内存空间
		free(*head);
		*head = NULL;
		return FALSE;
	}
	//将控制头进行初始化
	(*head)->head = 0;
	(*head)->maxRoom = maxRoom;
	(*head)->lastAction = ACTION_OUT;
	(*head)->tail = 0;

	return TRUE;
}


void  main(void){
	int i;
	int n;
	QUEUE  *queun1 = NULL;
	QUEUE  *queun2 = NULL;
	
	//初始化队列。
	iniQueue(&queun1, 10);
	//入队列
	inQueue(queun1, 12);
	inQueue(queun1, 1);
	inQueue(queun1, 2);
	inQueue(queun1, 9);
	inQueue(queun1, 6);
	inQueue(queun1, 121);
	//读取最前面的元素
	 readQueue(*queun1, &n);
	 printf("%d\n", n);

	 //出队列
	for( i = 0; i < 6; i++){
		 outQueue(queun1, &n);
		 printf("%d ", n);
	}
	//销毁队列
	destoryQueue(&queun1);


}