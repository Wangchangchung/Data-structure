#include<stdio.h>
#include<malloc.h>

typedef struct STRING_UNIT{
	char strings[16];
	struct SRTING_UNIT *next;
	char len;

}STRING_UNIT;


typedef unsigned char boolean;

#define TRUE				1
#define FALSE				0
#define NOT_FOUND_INDEX		-1


typedef struct STRING{
	char * string;
	int stringLength;
	int MaxLength;
	
}STRING;

   


boolean init_String(STRING **str, int MaxStringLength);

boolean destory_String(STRING **str);

int get_String_Length(STRING str);

boolean is_String_Full(STRING str);

boolean is_String_Empty(STRING str);

STRING * string_Copy(STRING *target_String, const STRING resource);

STRING * string_Copy(STRING *target_String, const STRING resource){

	int i ;

		//原串和目的串的复制，这里要考虑的问题就有些多了。
		//如果原串的长度比目标串的长度更长，那么目标串的大小要重新申请
	if(target_String == NULL){
		//初始化target_string  申请它的空间长度为 resource大小的空幻
		//申请一块控制头 再申请string空间  但是这里的操作还没对s1的指向没有更改 ，、
		//更改的只是target_String的指向。
		init_String( &target_String, resource.MaxLength);
	}else if(target_String->MaxLength< resource.MaxLength){
		/*
			STRING *s1 = NULL;
			STRING *s2 = NULL;

		  ini_String(&s1, 12);
		  ini_String(&s2, 22);
		  ...
		  string_Copy(s1, *s2);

		  在 string_Copy()函数中如果进行下面的操作的话
		  没有在外部正真的更改s1的指向空间的，target_string是一个复制本局部变量
		  ，在通过target_string s释放空间之后 ，s1指向的是一个释放的空间了。，所以
		  这种方案是错误的，有两种解决方案
		  1、将destory_Copy()中的参数更改为二级指针，直接修该s1的指向
		  2、将s1中的存储string的空间重新申请，s1的指向没有改变

		  这里建议采用第二种个方法
		*/

		//销毁原来的申请的string空间, 重新申请
		free(target_String->string);
		target_String->string = (char *)malloc(sizeof(char)*resource.MaxLength);
		target_String->MaxLength = resource.MaxLength;
		//target_String->stringLength = resource.stringLength;
		//上面这句话不要放到这里，放在在下面的话就可以减少一句代码了。

	}

	//将元素拷过去
	for(i = 0; i < resource.stringLength;++i){
		target_String->string[i] = resource.string[i];
	}
	//将字符串的长度重新复制
	target_String->stringLength = resource.stringLength;
	return target_String;
}

boolean is_String_Empty(STRING str){
	return str.stringLength <= 0;
}

boolean is_String_Full(STRING str){
	return str.MaxLength <= str.stringLength;
}

int get_String_Length(STRING str){
	return str.stringLength;
}

boolean destory_Stirng(STRING **str){
	
	//判断是否为已经初始化的串
	if(*str){
		//如果string中有内存空间的使用就先释放string的空间。
		if((*str)->string)
			free((*str)->string);
		free(*str);
		return TRUE;
	}
	return FALSE;
}

boolean init_String(STRING **str, int MaxStringLength){

	//判断是否是已经初始化过的串，没有进过初始化的串才能进行初始化。
	if(*str){
		return FALSE;
	}
	*str = (STRING *)malloc(sizeof(STRING));
	(*str)->string = (char *)malloc(sizeof(char)*MaxStringLength);
	(*str)->stringLength = 0;
	(*str)->MaxLength = MaxStringLength;
	return TRUE;
}

void main(void)
{


}