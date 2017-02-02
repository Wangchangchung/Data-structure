#include <stdio.h>  
#include <malloc.h>  
#define VERTEXNUM 5  
//存放顶点的邻接表元素    
typedef struct edge{  
        int vertex;  
        struct edge* next;  
}st_edge;  
  
void createGraph(st_edge** edge, int start, int end);  
void displayGraph(st_edge** edge);  
void delGraph(st_edge** edge);  
void DFT(st_edge** edge,int* vertexStatusArr);  
void DFTcore(st_edge** edge,int i,int* vertexStatusArr);  
  
int main(void){  
        //动态创建存放边的指针数组     
        st_edge** edge = (st_edge**)malloc(sizeof(st_edge*)*VERTEXNUM);  
        int i;  
        for(i=0;i<VERTEXNUM;i++){  
                edge[i] = NULL;  
        }  
        //存放顶点的遍历状态，0：未遍历，1：已遍历    
        int* vertexStatusArr = (int*)malloc(sizeof(int)*VERTEXNUM);  
        for(i=0;i<VERTEXNUM;i++){  
                vertexStatusArr[i] = 0;  
        }  
  
        printf("after init:\n");  
        displayGraph(edge);  
        //创建图    
        createGraph(edge,0,3);  
        createGraph(edge,0,4);  
        createGraph(edge,3,1);  
        createGraph(edge,3,2);  
        createGraph(edge,4,1);  
  
        printf("after create:\n");  
        displayGraph(edge);  
        //深度优先遍历   
        DFT(edge,vertexStatusArr);  
        //释放邻接表占用的内存    
        delGraph(edge);  
        edge = NULL;  
        free(vertexStatusArr);  
        vertexStatusArr = NULL;  
        return 0;  
}  
//创建图   
void createGraph(st_edge** edge, int start, int end){  
        st_edge* newedge = (st_edge*)malloc(sizeof(st_edge));  
        newedge->vertex = end;  
        newedge->next = NULL;  
        edge = edge + start;  
        while(*edge != NULL){  
                edge = &((*edge)->next);  
        }  
        *edge = newedge;  
}  
//打印存储的图   
void displayGraph(st_edge** edge){  
        int i;  
        st_edge* p;  
        for(i=0;i<VERTEXNUM;i++){  
                printf("%d:",i);  
                p = *(edge+i);  
                while(p != NULL){  
                        printf("%d ",p->vertex);  
                        p = p->next;  
                }  
                printf("\n");  
        }  
}  
//释放邻接表占用的内存   
void delGraph(st_edge** edge){  
        int i;  
        st_edge* p;  
        st_edge* del;  
        for(i=0;i<VERTEXNUM;i++){  
                p = *(edge+i);  
                while(p != NULL){  
                        del = p;  
                        p = p->next;  
                        free(del);  
                }  
                edge[i] = NULL;  
        }  
        free(edge);  
}  
//深度优先遍历   
void DFT(st_edge** edge,int* vertexStatusArr){  
        printf("start BFT graph:\n");  
        int i;  
        for(i=0;i<VERTEXNUM;i++){  
                DFTcore(edge,i,vertexStatusArr);  
        }  
        printf("\n");  
}  
  
void DFTcore(st_edge** edge,int i,int* vertexStatusArr){  
        if(vertexStatusArr[i] == 1){  
                return;  
        }  
        printf("%d ",i);  
        vertexStatusArr[i] = 1;  
        st_edge* p = *(edge+i);  
        while(p != NULL){  
                DFTcore(edge, p->vertex, vertexStatusArr);  
                p = p->next;  
        }  
}  