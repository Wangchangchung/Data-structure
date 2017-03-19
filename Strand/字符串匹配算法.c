#include<stdio.h>
#include<string.h>

/*
	查找子串在主串中出现的位置。
	1、BF算法(最常规的方法、最暴力的方法、最笨的方法)
		主串遍历一遍。从第一个开始 然后一个一个的子串进行比较
		向后面，如果匹配失败，那么就主串的下一个继续继续和子串一个一个的比较
		知道找到匹配的位置，但是这里找到的是第一次出现的地方(程序直接就返回了)
		，后面的没有再进行查找，如果想得打从主串的第几个到主串的第几个是子串的位置
		那么找到后面的后，就直接减-子串长度就可以。
	时间复杂度： O(m*n) 
	空间复杂度   O(1);

	
	2、KMP算法



*/
	
					
int string_Matching_BF(char *mainString, const char * childString);	//串匹配： 第一个字符串主串， 第二个 子串

int string_Matching_BF(char *mainString, const char * childString){
	int mainLength;
	int childLength;
	int mainIndex = 0;
	int childIndex = 0;

	mainLength = strlen(mainString);	//主串长度
	childLength =strlen(childString);	//子串长度

	//遍历主串	
	while(mainIndex <= mainLength){
		childIndex = 0;
		//依次和子串进行比较
		while(childString[childIndex++] == mainString[mainIndex++]){
			//childIndex == childLength  说明这个是匹配成功了，返回最后的位置
			if(childIndex == childLength){
				return mainIndex -1 ;
			}
			//这个大于子串的长度，说明是没有匹配成功，这一步是在
			/*if(childIndex > childLength){
				printf("你是子啊if里传来的");
				return -1;	
			}*/
		}
		//++mainIndex; 这里不用再 加了 因为mainString[mainIndex++] 中 已经加了。
	}
	printf("你是从后里传来的");
	return -1;
	
}

void main(void)
{
	char * str = "asdasdfafdasfasdffs";
	char * hel = "dasdfafd";

	int index;

	//index = string_Matching(hel, str);
	 index = string_Matching_BF(str,hel);
	printf("%d\n", index);

}