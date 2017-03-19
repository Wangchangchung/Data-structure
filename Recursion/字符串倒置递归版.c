/*
	递归调用版将字符串倒置，但C语言已经拥有一个函数strrev(char  *);
	递归最先考虑的是递归结束的条件。
*/

#include<stdio.h>

void convertArryLitter(char *p, int n);

void convertArryLitter(char *p, int count)
{
	char temp;

	if(count > 1)  //当一串字符串最后只有一个字符时，就可以结束递归了。
	{
		temp = p[0];
		p[0] = p[count-1];    //首尾相互调换。
		p[count-1] = temp;

		convertArryLitter(p+1, count-2);
	}
}

void main(void)
{
	char  a[20];
	int n;

	printf("请输入一串字符串：");
	gets(a);

	n = sizeof(a);

	convertArryLitter(a, n);
	printf("%s\n",a);
}
/*
	s : "abcdefg" count :7

	char s[] = "abcdefg";
	converTArryLitter(s, 7)

s -> a b c d e f g \0
	 0 1 2 3 4 5 6 7
	s1 count1;7
	   0 1 2 3 4 5 6
	   s2,count2;5
	     0 1 2 
		s3 count3;3
		   0 1 
		  s4 count4;1
*/
/*
	不用传递长度的，但是还是传递长度的更合理些，应为有些可能是要将
	字符串的一部分倒置。
  
	char * conver(char *string);
    char * conver(char *string)
	{
		char * p = string ;
		char * left = p;
		char temp;
	
		if( p != NULL)  //判断一下这个指针非空还是要的。
		{
			
			while(*string++)
				;
			string-=2;   //找到末尾。注意是-2遇到零结束标志后string还进行了一次++
			while(left < string)
			{
				temp = *left;
				*left++ = *string;
				*string-- = temp;     //指针的操作 和滞后自减 滞后自增
			  }
		}

		return p;
			
	}


	
*/
/*
这道题目通常是考察三个方面，一是对指针和字符串的理解，二是是否进行合法性检查，
例如输入参数为空指针时是否进行检查，三是返回值是否是恰当，即使你通过参数
返回了反转后的字符串指针，也建议在返回值里再返回一下，就像strcpy函数实现的那样。
其实还有第四点往往是大家都忽略了的，那就是Unicode问题，如果传入的字符串指针指向的是Unicode字符串，
那么反转的时候就不能一个字符一个字符的处理了，不过似乎大多数面试官都没对这一点有过要求，
如果你在笔试或面试中遇到这个问题，我建议你想监考或面试官询问一下是否需要考虑Unicode。
我面试的时候因为被面试官弄的很紧张，也忘记了这点，写完后检查代码准备交过去时才想起来。
*/