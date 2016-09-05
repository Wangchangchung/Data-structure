#ifndef _POINT_H_
//如果没有定义宏： _POINT_H_
//则，下面的代码加入编译的行列中
//否则，下面的代码（在endif值钱啊的代码）就不用加入编译的行列中。

#define _POINT_H_

typedef struct POINT{
		int row;
		int col;
		struct POINT *next;
}POINT;

//类似java中的boolean类型
typedef unsigned char boolean;

#define TRUE     1
#define FALSE    0


#endif