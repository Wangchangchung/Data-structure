#ifndef _WCC_BASE_H
#define _WCC_BASE_H

#include<stdio.h>

//定义一个"boolean类型"的数据类型
typedef unsigned char boolean;

//定义错误类型
typedef int ERRNO;

//用于 boolean的取值 TRUE FALSE
#define TRUE			  1
#define FALSE			  0

#define NO_ERROR						-1
#define ERROR_HEAD_ALLREAD_EXIT			-2
#define ERROR_STACK_FAILE				-3
#define ERROR_NO_ROOM					-4

ERRNO errNo;

char *erroMS[]={

		"申请成功！",
		"申请失败！控制头已经存在。"
		"堆栈申请失败！"
		"没有空间了！"
}


#endif