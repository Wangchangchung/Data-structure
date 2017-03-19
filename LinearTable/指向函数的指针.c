#include<stdio.h>

int add(int value, int value2);

int sub(int value, int value2);

//定义一个以函数为参数的函数
int function(int value, int value2, int (*p)(int ,int));

int function(int value, int value2, int (*p)(int, int)){
	
	return p(value, value2);
}

int sub(int value, int value2){
	return value - value2;
}

int add(int value, int value2){
	return value + value2;
}
 
void main(void){

	int (*p)(int ,int);
	int  res;
	//int *p(int, int);这里的f是一个函数声明，声明的是名字为p，返回值类型为int*,两个参数
	//分别为int, int
	//int(int, int)     *p; 左边定义的意义：f是一个指针，
	//其指类是int(int, int)；
	//int(int, int)的意思是，一个返回值类型
	//为int的，需要两个参数，每个参数类型分别为int和int的函数。
	//结论：p是一个指针，指向一个函数！

	int (*a)[4];	//int[4]   *a;
	
	 p = add;       //将add的值赋值给p空间
					//add本质上是add()函数的第一条指令的地址
					//结论：将add()函数的首地址值赋值给p,使p指向add函数。

	res = p(1,2);	//调用以p的值为首地址的函数：  p(1,2)<=> add(1,2),调用add()函数
	printf("%d\n", res);

	res = function(1,2,sub);    //把函数名称传入，在外面指定哪个函数来调用它。
	printf("%d\n", res);


}