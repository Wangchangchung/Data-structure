#include<stdio.h>
#include<malloc.h>

#define  TRUE		 1;
#define  FALSE		 0;

typedef   unsigned char   boolean;
typedef int user_type;

//一个节点
typedef struct BSTreeNode{

	user_type  data;			//用户类型
	struct BSTreeNode* left;	//左子树
	struct BSTreeNode* right;	//右子树
	
}BSTreeNode;

//初始化节二叉查找树
BSTreeNode *init_BSTree(BSTreeNode **tree, user_type data);

//创建一个节点
BSTreeNode *create_BSTree(user_type data, BSTreeNode *left, BSTreeNode *right);

//插入
BSTreeNode *insert_BSTree(BSTreeNode **tree, BSTreeNode *node);

//销毁
void destor_BSTree(BSTreeNode *tree);

//输出
void prin_BSTree(BSTreeNode *tree, user_type value, int type);

//查找
BSTreeNode* search_BSTree(BSTreeNode *tree, user_type value);

//有序数组变成二叉查找树
BSTreeNode* sorted_Array_To_BSTree(BSTreeNode **tree, user_type *arr, int head, int tail);

//二叉查找树变成有序数组
user_type * BSTree_To_Sorted_Array(BSTreeNode *tree, user_type *arr, int head, int tail);



user_type * BSTree_To_Sorted_Array(BSTreeNode *tree, user_type *arr, int head, int tail){
	
	int temp = (head + tail)>>1;
	//BSTreeNode *node = NULL;
	printf("temp = %d\n",temp);

	if(head > tail){
		return arr;
	}else{
		arr[temp] = tree->data;
		//printf("执行了%d\n",arr[temp]);
		BSTree_To_Sorted_Array(tree->right, arr, temp + 1, tail);
		BSTree_To_Sorted_Array(tree->left, arr, head, temp-1);
	}	
}

BSTreeNode* sorted_Array_To_BSTree(BSTreeNode **tree, user_type *arr, int head, int tail){

	int temp = (head + tail)>>1;

	BSTreeNode *node = NULL;

	//printf("temp = %d\n", temp);
	
	if(head > tail ){
		return node;
	}else{
		node = init_BSTree(tree, arr[temp]);
		sorted_Array_To_BSTree(tree, arr, temp + 1, tail);
		sorted_Array_To_BSTree(tree, arr, head, temp - 1);
	}
	//return node;	
}

BSTreeNode* search_BSTree(BSTreeNode *tree, user_type value){
	
	BSTreeNode *node = NULL;

	if(NULL != tree){

		if(tree->data == value){
			return tree;	
		}else if(tree->data < value){
			node = search_BSTree(tree->right, value);
		//	printf("这里右子树查找\n");
		}else if(tree->data > value){
			node = search_BSTree(tree->left, value);
		//	printf("这里左子树查找\n");
		}
		//return node;
	}

	return node;
	

}

void prin_BSTree(BSTreeNode *tree, user_type value, int type){

	if(NULL !=tree){

		if(type == 0){
			printf("%d 是根节点\n", tree->data);
		}
		else{
			printf("%d 是 %d的 %s 节点\n", tree->data, value, type == 1 ? "left" : "rigth");
		}

		//先打印右子树
		prin_BSTree(tree->right, tree->data, -1);
		//再打印左子树
		prin_BSTree(tree->left, tree->data, 1);
	} 
}

void destor_BSTree(BSTreeNode *tree){
	
	//二叉树不为空就进行释放。
	if(NULL != tree){
		if(NULL != (tree->right)){
			destor_BSTree(tree->right);
		}
		if(NULL != (tree->left)){
			destor_BSTree(tree->left);
		}
		free(tree);
	}
}

BSTreeNode *insert_BSTree(BSTreeNode **tree, BSTreeNode *node){

	//如果二叉查找树中为空则，第一个节点作为根节点
	if(NULL == (*tree)){
		*tree = node;

	//如果插入的值的大于这个节点，那么就放到右子树
	}else if(node->data > (*tree)->data ){
		insert_BSTree(&((*tree)->right), node);

	//如果插入的值小于这个节点，那么就放到左子树
	}else if(node->data < (*tree)->data){
		insert_BSTree(&((*tree)->left), node);
	}

	return *tree;
}


BSTreeNode *create_BSTree(user_type data, BSTreeNode *left, BSTreeNode *right){
	
	BSTreeNode * node = NULL;
	//申请空间,失败就直接返回
	if(NULL == (node = (BSTreeNode *)malloc(sizeof(BSTreeNode))))
		return NULL;

	//创建一个节点初始化节点信息
	node->data = data;
	node->left = left;
	node->right = right;

	return node;
}

BSTreeNode *init_BSTree(BSTreeNode **tree, user_type data){
	
	BSTreeNode *node = NULL;

	if(NULL == (node=create_BSTree(data, NULL, NULL)))
		return *tree;
	return insert_BSTree(tree, node);
}

void main(void){

	BSTreeNode * tree = NULL;
	BSTreeNode * t = NULL;

	int arr[6] = {2,3,6,7,1,5};

	int test[7] = {1,2,3,5,6,7, 8};
	int sorce2[7];
	int test2[10] = {1,2,3,4,5,6,7,8,9,10};
	int sorce[10];
	
	int i;

	for(i = 0; i < 6; ++i){
		 init_BSTree(&tree,arr[i]);
	}

	prin_BSTree(tree, tree->data, 0);

	t = search_BSTree(tree, 5);
	printf("%d 找到了\n", t->data);

	//销毁二叉横树。
	destor_BSTree(tree);

	//有序数组转变成二叉查找树
	sorted_Array_To_BSTree(&tree, test, 0, 6);
	//sorted_Array_To_BSTree(&tree, test2, 0, 9);
	prin_BSTree(tree, tree->data, 0);
	//二叉查找树变成有序数组
	BSTree_To_Sorted_Array(tree, sorce2, 0, 6);

	for(i = 0; i < 7; ++i){
		printf("%d\n", sorce2[i]);
	}
	destor_BSTree(tree);
}
