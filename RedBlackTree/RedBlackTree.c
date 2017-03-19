#include<stdio.h>
#include<stdlib.h>

#define RED			0
#define BLACK		1

typedef   int   Elementype;

typedef struct RedBlackTree{

	Elementype  data;
	int color;
	RedBlackTree*  child[2];

}RedBlackTree;


RedBlackTree* creatOneNode(Elementype data);

RedBlackTree* creatOneNode(Elementype data){
	
	RedBlackTree* node = NULL;
	if(node = (RedBlackTree *)malloc(sizeof(RedBlackTree))){
		node->data = data;
		node->color = RED;
		node->child[0] = node->child[1] = NULL;
	}
	return node;
}

void main(void){


}




