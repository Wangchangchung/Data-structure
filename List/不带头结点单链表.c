#include<stdio.h>
#include<malloc.h>
#include"Point.h"
/*
	函数的创建，首先要解决的是函数的参数问题和返回值类型问题，
	参数问题：1、参数类型（参数意义）
			  2、参数个数
	返回值：  1、返回值类型
	如果函数参数及函数返回值没有确定，那么这个函数就根本是不知道在干什么的了。
	怎么确定一个函数的参数和返回值类型呢？
	要从函数功能出发，要结果！
	initPonitLink（）函数的功能是干什么？	
*/

void initPointLink(POINT **h);				//初始化链表

void setPoint(POINT *p,int row, int col);	//设置节点值

void showPoints(POINT *head);				//显示链表的数据

void showPoint(POINT point);				//显示一个节点的数据,只需传递一个实例就行了

boolean destoryPointLink(POINT **head);     //删除链表

void insertPointLink(POINT **head);			//插入节点到链表中  注意这里传入的参数为什么是 **head

POINT *locationPoint(POINT *head);          //因为我们是要在loactionPint()函数里面要求用户定位哪一个点
											//所以在创建这个函数的时候传入的参数就因该只用一个，不然的化可以
											//传入节点做坐标， 其实在里面询问用户定位哪个节点更提高代码的复用

boolean removePoint(POINT **head);			//删除指定节点，删除指定节点是传入 POINT *head还是传入POINT **head呢？
											//这个参数肯定是要看你会处理的请款来讲，但有一种情况是删除第一个节点得时间，你必须更改头指针的指向。
											//所以传入的参数是 POINT **head;
				
void sortPointLinkByRowUp(POINT *head);			//对链表进行排序，是传入POINT *head,还是传入POINT **head呢？
											//因为我们是交换，结构体之间是可以相互赋值的，所以交换过程中链域也是交换过来的。
											//但是我们的头指针的指向不许要改变，始终指向那块内存空间，里面的值是不用管的。
											//还有一点是我们交换后，链时候要交换回来的，不然指向都是乱的了。


void sortPointLinkByRowUp(POINT *head)
{
	POINT  temp;							//用于保存交换节点其中的一个值，
	POINT *p = NULL;
	POINT *next;							//用于保存链域值（指针）

	for(p = head; head; head = head->next){             
		for(p = head->next; p ; p = p->next)     //这里非常要注意的是 p = head->next; 因为在这里用的是选择排序，所以一次循环之后，p的值
											     //为 p = head->next 而不能 p = p->next  不能因为第一次循环中 p = head ，而这样，这样的只能是循环一次的
												 //循环一次后 p = null 那怎么还能够进行p = p->next的操作呢？所以的话就只能p = head；不能耍小聪明哦。
		{
			if(head->row >= p->row)
			{
				temp = *head;					//两个节点进行交换。
				*head = *p;						//  或者是这样的	t = p[0];		// p[0] <=> *(p+0) <=> *p
												//                  p[0] = q[0];
												//                  q[0] = t;
				*p = temp; 
				
				next= head->next;				//交换回链域
				head->next = p->next;
				p->next = next;
			}
		}
	}
	/*
	POINT *p;
	POINT *q;
	POINT *r;
	POINT t;

	for(p = head; p; p = p->next)
		for(q = p->next; q; q = q->next)
			if(p->row < q->row)
			{
				t = p[0];		// p[0] <=> *(p+0) <=> *p
				p[0] = q[0];
				q[0] = t;

				r = p->next;
				p->next = q->next;
				q->next = r;
			}*/

}

boolean removePoint(POINT **head)
{
	POINT *p;
	POINT *q;

	 p = locationPoint(*head);					//因为之前编写的函数是可以重复利用的，所以可以利用这个函数定位我们要
												//删除节点的前驱节点。
	 if(NULL == p){								//第一种情况，删除第一个元素
		q =  *head;
		*head = q->next;                        //(*head)->next; 也行
		free(q);
	 
	 }else if(NULL == p->next){                 //链表中没有要指定删除的节点
		 printf("您要删除的元素不在链表中，请确认再执行删除工作。");
		return FALSE;
	 }else{										 //这个是最普遍的一种情况
		q = p->next;                             //保存要释放（删除）的空间的地址
		p->next = q->next;				         //或者是这个样的也行p->next = p->next->next; 但是既然q都指向这个要被删除的点了，那么就快一点
		free(q);						         //释放空间		
	 }
	 return TRUE;
}

POINT *locationPoint(POINT *head)
{
	int row;
	int col;
	POINT *p = NULL;
	POINT *q = NULL;						//这里的q为什么要呢？ 因为是当要插入在最前面的时候，如果直接
											//用for(p = head; head && head->row != row && head->col != col; head = head->next)
											// p的值是第一个元素了，就会出现第二种插入情况，而不是从前面插入了。
											//所以要用一个变量来进行保存，不然第一种情况就不能为返回的值NULL

	printf("请输入你要插入(删除)点位置坐标(前插入):");
	scanf("%d %d", &row, &col);
												//没有照完 并且没有找到， 就继续往下找。
												//而且 && 运算的短路运算性质很好的防止了当head为NULL时 head->row 和 head->col的操作。
	for(p = head; p && (p->row != row || p->col != col); p = p->next){
				q = p;						//p 始终保存的是用户所定位点的前驱节点。
	} 
	return q;									//当找到的时候就跳出循环 此时的p 就是要找点的前驱节点。

	/*
		找点有三个情况：
			1、找到的是第一个点												p = NULL;
			2、找到的是除第一个节点外的其他节点								p != NULL && p->next != NULL;
			3、没有找到节点(此时p所指的是最后一个节点)。                    p != NULL && p -> next = NULL;

		根据这个返回值得性质，我们就可以在插入函数中做出针对不同情况的插入操作。
		
	*/
}
										
void insertPointLink(POINT **head)
{
	int row;
	int col;
	POINT *p;								 //保存新插入点申请空间的地址
	POINT *q;								 //保存定位插入点的地址

	printf("请输入新插入点的坐标(坐标值不为负数)：\n");    
	scanf("%d %d",&row, &col);               //输入新点坐标

	p = (POINT *)malloc(sizeof(POINT));      //为新节点申请空间
	setPoint(p, row, col);
	
	q = locationPoint(*head);

	if(NULL == q){                          //    针对插入点是第一个点的前面的情况。
		p->next = *head;                    //先保存 头指针指向第一个节点的地址，存入新节点的链域，不然覆盖了后就找不到了。
		*head = p;							//再将头指针指向新申请空间的，这样就将新申请的空间链入链表的第一个元素了。
	}else if(NULL == q->next){				//    针对的是没有找到定位点的情况
		//没有找到定位点就直接链入末尾
		q->next = p;
	}else {									//这个情况是找到节点，
		p->next = q->next;					//先将后面的节点地址保存新节点链域中。
		q->next = p;						//再将前驱的节点的链域更改为新节点的地址
	}	
}

boolean desrotyPointLink(POINT **head)
{
	POINT  *p;
	
	while(*head){
		p = *head;					//从头往后一个一个的删除链表的节点 p用于保存前一个节点,*head一个一个的指向下一个节点。
		*head = (*head)->next;		//或者 *head = p->next;
		free(p);
	}
	if(NULL == *head){              //删除链表成功， 返回 TRUE(1)    
	   return TRUE;   
	}
	return FALSE;					//删除链表失败， 返回 FALS(0)
}

void showPoint(POINT point)					
{
	//	printf("(%d, %d) ", point->row, point->col); 
	//传过来的是一个实例了，而不是指针，所以这里直接是用
	// "."运算符访问数据，而不是 "->"来访问数据了
	printf("(%d, %d) ", point.row, point.col);
}

void showPoints(POINT *head)
{
	//POINT *p = head; 这里面可以不用再声明一个POINT指针了，可以直接用传过来的head
	//如果链表来没有初始化的话就，下面的for循环是能够不输出，但是没有任何的提示信息，所以
	//还是可以在这里做一下判断的。
	if(head == NULL)  
	{
		printf("您还未初始化链表，请先初始化链表。\n");
		return ;
	}

	printf("您的链表为以下数据：\n");
	for(; head; head = head->next)			//循环条件 head不为NULL就继续执行
		showPoint(*head);
	
	printf("\n");
}

void setPoint(POINT *p, int row, int col)
{
	p->row = row;
	p->col = col;
	p->next = NULL;
}

void initPointLink(POINT **h)
{
	int row;
	int col;
	POINT *p;									// 保存申请空间的地址
	POINT *q;									//保存新链入节点的地址，因为P的地址会在第二次申请空间的时候被覆盖了。
							
	if(NULL == *h){								//如果链表为空才将这个链表进行初始化。
		printf("请输入点坐标（输入任意一个负数坐标为结束输入。）：例如：（2,4）");
		scanf("%d %d", &row, &col);

		while(row > 0 && col > 0){
			
			p = (POINT *)malloc(sizeof(POINT));	//申请空间
			
			setPoint(p, row, col);				//将数据填充到POINT中。

			if(NULL == *h)						//处理的是第一个节点
			{
				*h = p;
			}
			else{
				q->next = p;                    //这里是为了处理除了第一个节点之外的其余节点
												//将新申请的节点链入之前申请节点链入的节点的后面。
			}
			q = p;								//将申请的空间保存给q ,q随着链的增长，始终是指向最后一个节点的
												//这个也是为而来能够直接实现上面else中的 q->next = p;这一步的原因所在了。
			printf("请输入点坐标（输入任意一个负数坐标为结束输入。）：例如：（2,4）");
			scanf("%d %d", &row, &col);
		}
	}
}

void main(void)
{
	POINT *head = NULL;
	POINT *head2 = NULL;
	char a;
	//error C2143: syntax error : missing ';' before 'type'
	//出现这个错误多半是变量没有先声明而在下面使用了，这个不是java哦！

	initPointLink(&head);
//	insertPointLink(&head);
	showPoints(head);
//	removePoint(&head);
	sortPointLinkByRowUp(head);
	showPoints(head);
	a = desrotyPointLink(&head);
	printf("%d \n", a);            // 删除成功，这里输出的就是 1 
//	printf("%d \n",head);          //此时的head 为NULL = 0 即哪里都不指向。

//	showPoints(head);
//	showPoints(head2);


}