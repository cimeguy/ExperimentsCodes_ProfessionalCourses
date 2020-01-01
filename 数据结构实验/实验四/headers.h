#pragma once

#ifndef HEARDERS_H_INCLUDED
#define HEARDERS_H_INCLUDED
#include <vector>

using namespace std;//using std::vector;

/*---------ջ---------*/
//#define MAXSTACKSIZE 4   ͣ������С
#define MAXSTACKSIZE  15  //ʵ���� ��������  ����������

typedef char SElemType;
typedef struct {
	SElemType * base;//�洢�ռ��ַ
	int top;         //ջ��ָ�� ( ��ǰջ��Ԫ�ظ��� )
	int stacksize;   //��������洢�ռ� ��Ԫ��Ϊ��λ

}SqStack;

/*--------����--------*/
#define MAXQUEUESIZE 5
typedef car QElemType;
typedef struct {
	QElemType *base; //��ʼ���Ķ�̬����洢�ռ�
	int front;  //ͷָ�룬�����в��գ�ָ�����ͷԪ��  (ͷԪ��ǰһ��)
	int rear;   //βָ�룬�����в��գ�ָ�����βԪ�ص���һ��λ�ã�βԪ�أ�
}SqQueue;

/*--------------------------���Ĵ���ҵ-------------------------------*/
/*-------������----------*/
typedef char TElemType;
typedef struct Tnode{
	TElemType data;
	struct Tnode *lchild, *rchild;
}BiTnode;
typedef BiTnode *BinTree;

/*-------��������----------*/
typedef char HuElemType;
#define leafnumber 30  //Ĭ��Ҷ�ӽڵ����   Ȩֵ���ϴ�С     
#define totalnumber 59   //�������� = 2*leaf number -1
typedef struct {
	char data;   //����ֵ
	int weight;  //����Ȩֵ
	int parent, lchild, rchild;  //˫�ף����ҽ����Ůָ��
}HTNode;
typedef struct {
	HTNode elem[totalnumber];  //Huffman���洢����
	int num,root;   //num ��ڵ��� root �Ǹ�
 }HFTree;
#endif // DECLARATION_H_INCLUDED
