#include<stdio.h>
#include<malloc.h>

/*
	用线性存储结构实现线性表（用数组实现）
	线性表应该保证其完整性和独立性和非可改性
	
*/

typedef    unsigned char       boolean;

//定义的用户类型
typedef  struct USER_TYPE{
		int a[10];
		int count;
}USER_TYPE;


#define     TRUE                   1
#define     FALSE                  0
//要先定义USER_TYPE l类型，不然的话，编译的时候下面的结构体，不能够识别的。

//定义线性控制头
typedef struct LINEAR{

	USER_TYPE *data;
	int MaxRoom;
	int count;

}LINEAR;

void initLinear(LINEAR **head,  int maxRoom);							//初始化线性表

void desrotyLinear(LINEAR **head);										//销毁线性表

boolean isLinearFull(LINEAR head);									    //判断线性表是否满了

boolean isLinearEmpty(LINEAR head);										//判断线性表是否为空

boolean insertLinearElementAt(LINEAR *head, USER_TYPE value, int index);//向指定下标插入元素

boolean appendLinearElement(LINEAR *head, USER_TYPE value);				//向线性表末尾追加元素

boolean removeLinearElementAt(LINEAR *head, int index);					//删除指定下标的元素

boolean indexOf(LINEAR head, USER_TYPE vlaue, boolean (*cmp)(USER_TYPE, USER_TYPE));//寻找用户指定的数组下标，因为用户的数据类型是用户自己定义的，我们的
																				   //程序是无法得知的，所以，元素的比较，所定义的函数因该由用户自己定义，传入给我们
																				   //其中，这里利用到了指向函数的指针

boolean setLinearElementAt(LINEAR head, int index, USER_TYPE value);				//对指定位置进行设置

void sortLinearElement(LINEAR head, boolean (*cmp)(USER_TYPE, USER_TYPE));          //对线性表进行排序，按照升序，这里写这个函数的时候特别要注意括号

int getLinearElementCount(LINEAR head);													//返回线性表的个数

int getLinearElementMaxRoom(LINEAR head);											//返回线性表的最大空间


void clearLinear(LINEAR *head);														//将线性表清空。

//用户自定义的比较函数
boolean compareTwoArray(USER_TYPE element1, USER_TYPE element2);

/*
boolean appendLinearElement(LINEAR *h, USER_TYPE value);
typedef struct ABC
{
	...;
}USER_TYPE;

typedef int USER_TYPE;
typedef int USER_TYPE[10];
int a[10], b[10];
USER_TYPE a, b;
b = a;
typedef char UESER_TYPE[80];
USER_TYPE str1, str2;
char str1[80], str2[80];
strcpy(str1, str2);
从上述可知，不能简单的通过赋值操作，实现对data（线性表空间）中的元素的赋值！
这个赋值过程，应该由用户自己实现！
boolean appendLinearElement(LINEAR *h, USER_TYPE value)
{
	boolean Ok = TRUE;

	if(isLinearFull(*h) == FALSE)
		h->data[h->count++] = value;
	// 上条语句存在巨大缺陷：若USER_TYPE类型不是简单类型，也不是结构体或共用体类型，
	// 若是数组、字符串，则，由于数组名称不能赋值，因此，上述语句会失败。
	// 解决这个问题的办法，只能是：让用户（使用Linear的编程者）自行编写赋值函数，
	// 通过指向函数的指针方式，传递和调用。
	else
		Ok = FALSE;

	return Ok;
}
*/


boolean compareTwoArray(USER_TYPE element1, USER_TYPE element2)
{
	int i;

	if(element1.count != element2.count)
		return FALSE;

	for(i = 0; i < element1.count; i++)
		if(element1.a[i] != element2.a[i])
			return FALSE;

	return TRUE;
}



void clearLinear(LINEAR *head){
	if(head){
		head->count = 0;
	}
}

int getLinearElementMaxRoom(LINEAR head){
		return head.MaxRoom;
}

int getLinearElementCount(LINEAR head){
	return head.count;
}

void sortLinearElement(LINEAR head, boolean (*cmp)(USER_TYPE, USER_TYPE)){

	int i;
	int j;
	USER_TYPE temp;

	for(i = 0; i < head.count; i++){
		for(j = i + 1; j < head.count; j++){
			if(cmp(head.data[i] , head.data[j]) > 0){
				temp = head.data[i];
				head.data[i] = head.data[j];
				head.data[j] = temp;
			}
		}
	}
}

boolean getLinearElementAt(LINEAR head, int index, USER_TYPE *value){
	
	//这里可以防止对任意位置的插入
	if(index < 0 || index >= head.count){
		return FALSE;
	}
	*value = head.data[index];
	return TRUE;
}

boolean setLinearElementAt(LINEAR head, int index, USER_TYPE value){
	
	//判断不合理的情况
	if(index < 0 || index >= head.count){
		return FALSE;
	}
	//将index位置处的值设置为 value
	head.data[index] = value;
    
	return TRUE;
}

boolean indexOf(LINEAR head, USER_TYPE value, boolean (*cmp)(USER_TYPE, USER_TYPE)){

	int index;
	for(index = 0; index < head.count; index++){
		if(TRUE == cmp(head.data[index], value)) //比较head.data[index]与value的值是否相等
			return index;
	}
	return FALSE;
}

boolean removeLinearElementAt(LINEAR *head, int index){
	
	int i;

	if(NULL == head)
		return FALSE;

	if(head && isLinearEmpty(*head)){
		return FALSE;
	}
	if(index < 0 || index >= head->count){
		return FALSE;
	}
	//删除指定下标的元素，后面的直接向前移动一位。
	for(i = index; i < head->count - 1; i++){
		head->data[i] = head->data[i+1];
	}
	
	head->count--;
	
	return TRUE;
}

boolean appendLinearElement(LINEAR *head, USER_TYPE value){

	//从线性表中的count和数组下标可以看出，往后面追加元素，可以直接将其添加到count处
	//因为无论是追加还是插入，count的值都是++的，所以直接插入到count中。
	return insertLinearElementAt(head, value, head->count);
}

boolean insertLinearElementAt(LINEAR *head, USER_TYPE value, int index){
	
	int i;
	if(NULL == head)
		return FALSE;
	//一个没有初始化的控制头和 线性表为满的时候不能够插入
	if(head && isLinearFull(*head))
		return FALSE;
	//下标出现插入的常识性的问题
	if(index < 0 || index > head->count)
		return FALSE;

	//排除上面的一些"特殊情况"后，怎么将元素插入线性表中呢？
	//c插入位置之后的元素都是要向后一位移动的，所以可以考虑从后面来遍历

	for(i = head->count; i > index; i--){
		head->data[i] = head->data[i-1];
	}
	//给要插入的位置赋值
	head->data[index] = value;
	//线性表位置++
	head->count++;

	return TRUE;
}


boolean isLinearEmpty(LINEAR head){

	return head.count <= 0;
}

boolean isLinearFull(LINEAR head){
	
		return head.count >= head.MaxRoom;
}

void deatoryLinear(LINEAR **head){
	//指针不为NULL的时候才能进行销毁的操作
	if(*head){
		//先释放用户定义的数据类型空间
		free((*head)->data);
		//再释放控制头的空间
		free(*head);
		//让指针不要乱指
		*head = NULL;

	}
}

void initLinear(LINEAR **head,  int maxRoom){

	if(NULL == *head){
		//申请一个控制头空间
		*head = (LINEAR *)calloc(sizeof(LINEAR),1);
		(*head)->MaxRoom = maxRoom;
		(*head)->count = 0;
		(*head)->data = (USER_TYPE *)calloc(sizeof(USER_TYPE), maxRoom);
	}
}

void main(void)
{
	USER_TYPE value = {{15,6,3,1,3},5};
	USER_TYPE value1 = {{12,3,4,5,6},5};
	USER_TYPE value2 = {{1,2,3,4,5,},5};

	int index;
	LINEAR *linear1 =NULL;
	LINEAR *linear2 = NULL;
	
	initLinear(&linear1,80);

	//先向线性表中添加元素
	for(index = 0; index < 5; index++){
		printf("appendLinearElement(linear1, value):%d\n",appendLinearElement(linear1,value));
		
	}

	//将vaalue1添加到线性表的末尾
	appendLinearElement(linear1,value1);
		
	//这个是能够找到的。
	index = indexOf(*linear1, value1,compareTwoArray);
	printf("index=%d\n", index);
	//这个是属于找不到的
	index = indexOf(*linear1,value2,compareTwoArray);
	printf("index1 = %d\n", index);



}