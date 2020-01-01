#pragma once

#ifndef HEARDERS_H_INCLUDED
#define HEARDERS_H_INCLUDED

/*--------------------------第二次作业-------------------------------*/
/*---------单链表---------*/
typedef int ElemType;
typedef struct node {//链表节点
	ElemType data;   //节点数据域
	struct node * nextnode;//节点指针域
}ListNode;
typedef ListNode * LinkList;//链表指针
							
/*---------多项式---------*/
typedef struct term {
	double coef;
	int exp;
	struct term * next;

} ListTerm;
typedef ListTerm * Polynomial;


#endif // DECLARATION_H_INCLUDED
