#include "bintree.h"
#include <iostream>
#include<vector>
using namespace std;
void InitBiTree(BinTree &T) {//��ʼ��
	T = NULL;
}
void DestoryBiTree(BinTree &T) {//���ٶ�����
	if (T != NULL) {
		DestoryBiTree(T->lchild);
		DestoryBiTree(T->rchild);
		delete T;
		T = NULL;
	}
}
void CreatBiTree(BinTree &T,TElemType definition[],int &n) {//���ݶ������������й���������  ,����������õ���ʽΪ int n=0;creatBiTree(root,pre,n);
	//�Եݹ鷽ʽ������������pre[]���������У��ԡ������������ս��ı�־��'#'
	//n��ʼ���ø�ֵ0���˳���n������ͳ��
	TElemType ch = ' ';
		ch = definition[n++];
		//cout << ch<<endl;
	if (ch == ';')return;
	if (ch != '#') {
		T = new BiTnode;
		if (!T) exit(-1);
		T->lchild = NULL;
		T->rchild = NULL;
		T->data = ch;
		CreatBiTree(T->lchild, definition, n);
		CreatBiTree(T->rchild, definition, n);
	}
	else T = NULL;
	
}
int BiTreeEmpty(BinTree T) {//��������߶�or���
	if (T == NULL) return 0; 
	else {
		int i = BiTreeEmpty(T->lchild);
		int j = BiTreeEmpty(T->rchild);
		return (i < j) ? j + 1 : i + 1;
	}
}
bool InsertChild(BinTree &T, BinTree &p, int LR, TElemType c) {//����
	if (LR== 0) {//���
		if (p->lchild!= NULL)return false;
		BinTree L = new BiTnode;
		if (!L)exit(-1);
		L->data = c;
		L->lchild = L->rchild = NULL;
	//	L->parent = p;
		p->lchild = L;
		cout << "�ɹ�����Ԫ�� " << c << endl;
		return true;
	}
	else if (LR == 1) {
		if (p->rchild != NULL)return false;
		BinTree R= new BiTnode;
		if (!R)exit(-1);
		R->data = c;
		R->lchild = R->rchild = NULL;
	//	R->parent = p;
		p->lchild = R;
		return true;
	}
	else {
		cout << "LR��������" << endl;
		return false;
	}
}

#define StactSize 20
void PreOrder(BinTree BT) {
	BiTnode* S[StactSize];
	int top = -1;
	BiTnode *p = BT;
	do {
		while(p !=NULL){
			cout << p->data << " ";
			S[++top] = p;
			p = p->lchild;
		}
		if (top > -1) {
			p = S[top--];
			//cout << p->data<<" ";����
			p = p->rchild;
		}
	} while (p != NULL || top > -1);
}