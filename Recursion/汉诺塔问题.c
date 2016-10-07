#include<stdio.h>

void Hanio(int n, char head, char accsist, char aim );
void Hanio(int n, char head, char accsist, char aim)
{
	if(n > 0)
	{
		Hanio(n-1, head, aim, accsist);
		printf("%c->%c\n",head, aim);
		Hanio(n-1, accsist,head, aim);
	}
}

void main(void)
{
	int n;
	printf("请输入你要的汉诺塔数量：");
	scanf("%d", &n);

	Hanio(n, 'A', 'B','C');
}
/*
	设有n个盘子从源柱子移动到目标柱子，以辅助柱子为辅助；
	1.把n-1个盘子从源柱子移动到目标柱子，以目标柱子为辅助；
	2.把第n个盘子从源柱子移动到目标柱；
	3.把n-1个盘子从辅助柱子移动到目的柱子，以源柱子为辅助。
*/