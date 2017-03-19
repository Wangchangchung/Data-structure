#include<stdio.h>


#define RED			0
#define BLACK		1

#define  TRUE		2
#define  FALSE		-1
#define      boolean          unsigned  char

typedef   int   Elementype;

typedef struct RedBlackTree{

	int color;
	Elementype  data;
	RedBlackTree  *left;
	RedBlackTree *right;
	RedBlackTree *parent;

}RedBlackTree;

//进行插入操作
boolean rbTreeInsertNode(RedBlackTree **rbTree, Elementype data);

//插入修正
void rbTreeInsertFixup(RedBlackTree **rbTree, RedBlackTree *node);

//进行左旋转
void rbTreeLeftRotate(RedBlackTree **rbTree, RedBlackTree *node);

//进行右旋转
void rbTreeRightRotate(RedBlackTree **rbTree, RedBlackTree *node);



void rbTreeRightRotate(RedBlackTree **rbTree, RedBlackTree *node){

	RedBlackTree *y;

	y = node->left;
	node->left = y->right;
	if(y->right != NULL){
		y->right->parent = node;
	}
	y->parent = node->parent;

	// node为树根
	if(node->parent == NULL){
		*rbTree = y;
	}else{
		if(node->parent->left == node){
			node->parent->left = y;
		}else{
			node->parent->right = y;
		}
	}

	y->right= node;
	node->parent = y;

}


void rbTreeLeftRotate(RedBlackTree **rbTree, RedBlackTree *node){
	
	RedBlackTree *y;

	y = node->right;
	node->right = y->left;
	if(y->left != NULL){
		y->left->parent = node;
	}
	y->parent = node->parent;

	// node为树根
	if(node->parent == NULL){
		*rbTree = y;
	}else{
		if(node->parent->left == node){
			node->parent->left = y;
		}else{
			node->parent->right = y;
		}
	}

	y->left = node;
	node->parent = y;
	
}



void rbTreeInsertFixup(RedBlackTree **rbTree, RedBlackTree *node){
	
	RedBlackTree *p = NULL;
	RedBlackTree *gparent = NULL;
	RedBlackTree *uncle = NULL;

	//纠正 性质2

	while((p = node->parent) != NULL && p->color == RED){
		gparent = p->parent;
		//如果父节点是祖父节点的左孩子(因为父节点是红色节点，所以肯定有祖父节点
		if(p == gparent->left){
			//uncle 父亲的兄弟节点
			uncle = gparent->right;
			//情况1: 如果存在叔父节点，并且叔父节点颜色为红色，则可以通过改变祖父
			//和叔父节点的颜色
			
			//使得 当前存在破坏性质的节点沿树上升，由 node 变为祖父
			if(uncle != NULL && uncle->color == RED){
				gparent->color = RED;
				p->color = BLACK;
				uncle->color = BLACK;
				node = gparent;

				//叔父不存在或者存在但是 颜色是黑色的，则必须通过旋转来配合改变来保持性质2
			}else{
				// 情况2   x为其 父节点的右孩子，通过左旋转转换为情况3
				if(node == p->right){
					// 基于x的父节点的左旋，记原x结点为 x'
					node = p;
					rbTreeLeftRotate(rbTree, node);
					// 旋转后，重置node ，使其任然为node结点的父节点()
					p = node->parent;
				}
			}			
		}
	}
}

boolean rbTreeInsertNode(RedBlackTree **rbTree, Elementype data){
	
	//创建一个新节点
	RedBlackTree* node = NULL;
	RedBlackTree* curNode = NULL;
	RedBlackTree* p = NULL;

	if(node = (RedBlackTree *)malloc(sizeof(RedBlackTree))){
		node->data = data;
		node->color = RED;
		node->left = NULL;
		node->right = NULL;
		node->parent = NULL;
	}

	curNode = *rbTree;

	//找到新节点的插入位置，p 保存着带插入界定的父节点
	while(curNode != NULL){
		p = curNode;
		if(data < curNode->data){
			curNode = curNode->left;
		}else{
			curNode = curNode->right;
		}
	}

	//如果为空树，新节点直接为根节点
	if(NULL == p){
		*rbTree = node;
	}else{
		//比较大小，然后决定是插入左边还是右边
		if(data < p->data){
			p->left = node;
		}else{
			p->right = node;
		}
	}

	node->parent = p;
	
	// 调整红黑树 ，以保持其性质

	//rbTreeInsertFixup();

	return TRUE;

}


void main(void){


}




