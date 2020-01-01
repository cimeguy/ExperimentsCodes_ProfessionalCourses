#pragma once

#ifndef HEARDERS_H_INCLUDED
#define HEARDERS_H_INCLUDED
#include <vector>

using namespace std;//using std::vector;

/*---------栈---------*/
//#define MAXSTACKSIZE 4   停车场大小
#define MAXSTACKSIZE  15  //实验四 哈夫曼树  哈夫曼编码

typedef char SElemType;
typedef struct {
	SElemType * base;//存储空间基址
	int top;         //栈顶指针 ( 当前栈中元素个数 )
	int stacksize;   //允许的最大存储空间 以元素为单位

}SqStack;

/*--------队列--------*/
#define MAXQUEUESIZE 5
typedef car QElemType;
typedef struct {
	QElemType *base; //初始化的动态分配存储空间
	int front;  //头指针，若队列不空，指向队列头元素  (头元素前一个)
	int rear;   //尾指针，若队列不空，指向队列尾元素的下一个位置（尾元素）
}SqQueue;

/*--------------------------第四次作业-------------------------------*/
/*-------二叉树----------*/
typedef char TElemType;
typedef struct Tnode{
	TElemType data;
	struct Tnode *lchild, *rchild;
}BiTnode;
typedef BiTnode *BinTree;

/*-------哈夫曼树----------*/
typedef char HuElemType;
#define leafnumber 30  //默认叶子节点个数   权值集合大小     
#define totalnumber 59   //树结点个数 = 2*leaf number -1
typedef struct {
	char data;   //结点的值
	int weight;  //结点的权值
	int parent, lchild, rchild;  //双亲，左右结点子女指针
}HTNode;
typedef struct {
	HTNode elem[totalnumber];  //Huffman树存储数组
	int num,root;   //num 外节点数 root 是根
 }HFTree;
#endif // DECLARATION_H_INCLUDED
