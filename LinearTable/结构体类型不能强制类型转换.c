#include<stdio.h>

typedef struct Node{
	
	int x;
	char y;

}Node; 

typedef struct Link{

	char x;
	int y;
}Link;

void main(void)
{
	Link link = {0, 0};
	Link li = {12, 4};
	Node no = {11,22};
	Node node  = {1,2};

	//error C2440: 'type cast' : cannot convert from 'struct Link ' to 'struct Link '
	//结构体之间是不能够强制类型转换的呢。详细原因请看该文件夹下的bmp文件。
	//node = (Link)li;
	
	//下面这种呢，是上升到指针指向的层次上了，那么不同结构体上也是可以赋值的。
	node = *((Node *)&li);

	li.x = no.x;
	no.y = li.y;

	//或者直接赋值
	link = li;
	
	printf("li.x = %d, li.y = %d\n", li.x, li.y);
	printf("no.x = %d, no.y = %d\n", no.x, no.y);
	printf("node.x = %d, node.y = %d\n", node.x, node.y);
	printf("link.x = %d, link.y = %d\n", link.x, link.y);
}