#include<iostream>
#include "headers.h"
using namespace std;
typedef int ElemType;
void InitList(LinkList &L) {    //初始化单链表 带头点
	L = new ListNode;
	if (!L) exit(-1);
	L->nextnode = NULL;
}
void DestroyList(LinkList &L) {       //清空单链表 保留头节点
	ListNode *q;
	while (L->nextnode != NULL) {
		q = L->nextnode;
		L->nextnode = q->nextnode;
		delete q;
	}
}
int ListLength(LinkList L) {           //计算表的长度(元素个数)
	ListNode *q = L; //指向头节点
	int count = 0;
	while (q->nextnode != NULL) {
		q = q->nextnode;
		count++;
	}
	return count;
}
bool GetElem(LinkList L, int i, ElemType &e) {//获得L第i个元素值
	if (i<1)return false;
	ListNode *p = L;//指向头节点
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
bool LocateElem(LinkList L, ElemType e, bool(*compare)(ElemType, ElemType)) {//返回L中与e满足compare关系的元素位置
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
bool PriorElem(LinkList L, ElemType cur_e, ElemType &pre_e) {//求L中元素cur_e的前驱
	ListNode *pCur, *pPre;
	pCur = L->nextnode;
	pPre = L;
	if (pCur->data == cur_e) {   //第一个节点
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

void ListTraverse(LinkList L, bool (*visit)(LinkList)) {  //遍历   
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
bool ListInsert(LinkList &L, int i, ElemType e) {//在L的第i个位置插入e
	if (i < 1) { 
		cout << "插入位置小于1，不合理" << endl;
		return false; 
	}
	ListNode *p = L;//指向头节点
	int count = 0;
	while (p != NULL&&count<i - 1) {
		p = p->nextnode;
		count++;
	}
	if (p == NULL) { 
		cout << "插入位置参数太大，不合理" << endl;
		return false; 
	}
	ListNode *q = new ListNode;//创建一个新节点
	if (!q)exit(-1);
	q->data = e;
	q->nextnode = p->nextnode;
	p->nextnode = q;
	return true;
}
bool ListDelete(LinkList &L, int i, ElemType &e) {//删除L的第i个元素
												  /*找到第i-1个节点*/
	if (i<1)return false;
	ListNode *p = L;//指向头节点
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

