#include<iostream>
#include "headers.h"
using namespace std;
typedef int ElemType;
void InitList(LinkList &L) {    //��ʼ�������� ��ͷ��
	L = new ListNode;
	if (!L) exit(-1);
	L->nextnode = NULL;
}
void DestroyList(LinkList &L) {       //��յ����� ����ͷ�ڵ�
	ListNode *q;
	while (L->nextnode != NULL) {
		q = L->nextnode;
		L->nextnode = q->nextnode;
		delete q;
	}
}
int ListLength(LinkList L) {           //�����ĳ���(Ԫ�ظ���)
	ListNode *q = L; //ָ��ͷ�ڵ�
	int count = 0;
	while (q->nextnode != NULL) {
		q = q->nextnode;
		count++;
	}
	return count;
}
bool GetElem(LinkList L, int i, ElemType &e) {//���L��i��Ԫ��ֵ
	if (i<1)return false;
	ListNode *p = L;//ָ��ͷ�ڵ�
	int count = 0;
	while (p != NULL&&count<i) {
		p = p->nextnode;
		count++;
	}
	if (p == NULL) return false;
	else {
		e = p->data;
		return true;
	}
}
bool LocateElem(LinkList L, ElemType e, bool(*compare)(ElemType, ElemType)) {//����L����e����compare��ϵ��Ԫ��λ��
	LinkList p = L->nextnode;

	int count = 0;
	while (p) {
		count++;
		if ((*compare)(p->data, e))return count;
		p = p->nextnode;

	}
	 return false;
	
}
bool compare(ElemType a ,ElemType b) {

	if (a == b) return true;
	else return false;

}
bool PriorElem(LinkList L, ElemType cur_e, ElemType &pre_e) {//��L��Ԫ��cur_e��ǰ��
	ListNode *pCur, *pPre;
	pCur = L->nextnode;
	pPre = L;
	if (pCur->data == cur_e) {   //��һ���ڵ�
		pre_e = NULL;
		return false;
	}
	while (pCur->data != cur_e && pCur != NULL) {
		pCur = pCur->nextnode;
		pPre = pPre->nextnode;
	}
	if (pCur == NULL) {
		pre_e = NULL;
		return false;
	}
	else {
		pre_e = pPre->data;
		return true;
	}
}

void ListTraverse(LinkList L, bool (*visit)(LinkList)) {  //����   
	LinkList p = L->nextnode;
	while (p) {
		visit(p);
		p = p->nextnode;
	}	
	cout << endl;
}
bool visit(LinkList e) {
	if (!e)return false;
	cout << e->data<<" ";
	return true;
}
bool ListInsert(LinkList &L, int i, ElemType e) {//��L�ĵ�i��λ�ò���e
	if (i < 1) { 
		cout << "����λ��С��1��������" << endl;
		return false; 
	}
	ListNode *p = L;//ָ��ͷ�ڵ�
	int count = 0;
	while (p != NULL&&count<i - 1) {
		p = p->nextnode;
		count++;
	}
	if (p == NULL) { 
		cout << "����λ�ò���̫�󣬲�����" << endl;
		return false; 
	}
	ListNode *q = new ListNode;//����һ���½ڵ�
	if (!q)exit(-1);
	q->data = e;
	q->nextnode = p->nextnode;
	p->nextnode = q;
	return true;
}
bool ListDelete(LinkList &L, int i, ElemType &e) {//ɾ��L�ĵ�i��Ԫ��
												  /*�ҵ���i-1���ڵ�*/
	if (i<1)return false;
	ListNode *p = L;//ָ��ͷ�ڵ�
	int count = 0;
	while (p != NULL&&count<i - 1) {
		p = p->nextnode;
		count++;
	}
	if (p == NULL || p->nextnode == NULL) return false;//    !
	ListNode *q = p->nextnode;
	e = q->data;
	p->nextnode = q->nextnode;
	delete q;
	return true;
}

