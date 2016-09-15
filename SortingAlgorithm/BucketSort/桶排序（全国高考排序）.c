#include<stdio.h>
#include<malloc.h>

/*
	桶排序的基本思想：
		假设有一组长度为N的待排关键字序列k[1...n]. 首先将这序列划分成M个
		个的子区间（桶），然后基于某种映射函数，将待排序列的关键字k映射到
		第i个桶中（即桶数组B的下标i),那么该关键字k就作为B[i]中的元素（每个桶B[i]
		都是一组大小为N/M的序列）。接着对每个桶中的所有元素进行比较排序（可以使用快排）
		然后依次枚举输出B[0]...B[M]中的全部内容即时一个有序序列。
	
	桶排序的平均时间复杂度为线性的O(N+C),其中 C=N*(logN-logM).如果相对于同样的N
	桶数量M越大，其效率越高，最好的时间复杂度O(N).当然桶排序的空间复杂度为O(N+M),
	如果输入数据非常庞大，而桶的数量也非常多，则空间代价无疑是昂贵的，此外，桶排序是稳定的。
*/

typedef struct Node{

	int count ;
	struct Node  *next;

}Node;

void bucket_sort(int *arr, int size, int bucket_size);

void bucket_sort(int *arr, int size, int bucket_size)
{
	int i;
	int index;
	Node *p;

	Node **bucket_table = (Node **)malloc(bucket_size*sizeof(Node *));      //申请保存桶的头指针的内存空间
	
	for(i = 0; i < bucket_size; i++){										//对所有的桶进行初始化
		bucket_table[i] = (Node *)coalloc(sizeof(Node));
		bucket_table[i]->count = 0;											//记录当前桶中数据量（有多少个元素）
		bucket_table[i]->next = NULL;
	}


	for(i = 0; i < size; i++){
		Node *node = (Node *)malloc(sizeof(Node));                           //对数组元素进行遍历，每个元素申请内存空间
		node->count = arr[i];
		node->next = NULL;
	
		index = arr[i]/10;													//映射函数 计算桶号；
		p = bucket_table[index] ;

		if(0 == p->count ){							//说明里面还没有元素。
			bucket_table[index]->next = node;
			(bucket_table[index]->count)++;			//每个桶中拥有的元素数量要++
		}else{
		
			while(p->next != NULL && p->next->count <= node->count)			//桶中的元素是有序的，是升序，所以要找到当前节点合适的位置
			{
				p = p->next;
			}
			
			node->next = p->next;											//跳出循环之后，即是找到因插入位置的前驱节点
			p->next = node;
			
		(bucket_table[index]->count)++;
		}

	}


	//打印结果
	for(i = 0; i < bucket_size; i++){
		for(p = bucket_table[i]->next; p ; p = p->next){
			printf("%d ", p->count);
		}
	}
}


void main(void)
{
	int arr[] = {12,35,56,53,67,38,85,99,95,32,76,48};

	bucket_sort(arr, 12, 10);
	
}