#pragma once

#ifndef HEARDERS_H_INCLUDED
#define HEARDERS_H_INCLUDED

/*--------------------------�ڶ�����ҵ-------------------------------*/
/*---------������---------*/
typedef int ElemType;
typedef struct node {//����ڵ�
	ElemType data;   //�ڵ�������
	struct node * nextnode;//�ڵ�ָ����
}ListNode;
typedef ListNode * LinkList;//����ָ��
							
/*---------����ʽ---------*/
typedef struct term {
	double coef;
	int exp;
	struct term * next;

} ListTerm;
typedef ListTerm * Polynomial;


#endif // DECLARATION_H_INCLUDED
