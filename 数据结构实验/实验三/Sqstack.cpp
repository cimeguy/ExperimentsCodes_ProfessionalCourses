#include<iostream>
#include "headers.h"
using namespace std;


void InitSqStack(SqStack &S){//��ʼʱΪ0
	S.base = new SElemType[MAXSTACKSIZE];
	if (!S.base)exit(-1);
	S.stacksize = MAXSTACKSIZE;
	S.top = 0;
}
void DestroySqStack(SqStack &S) {
	S.top = 0;
	delete S.base;

}
void ClearSqStack(SqStack &S) {
	S.top = 0;
}
bool SqStackEmpty(SqStack S) {
	return S.top == 0;
}
int  SqStackLength(SqStack S) {
	return S.top;
}
bool GetTop(SqStack S, SElemType &e) {
	if (S.top == 0)return false;
	else {
		e = *(S.base + S.top - 1);
		return true;
	}
}
bool Push(SqStack &S, SElemType e) {
	if ( S.top == S.stacksize )return false;  //ջ����
	*(S.base + S.top) = e;
	++S.top;
	return true;
}
bool Pop(SqStack &S, SElemType &e) {
	if (S.top == 0) return false;  //��ջ
	e = *(S.base + S.top - 1);		//ջ��Ԫ��
	--S.top;
	return true;
}
void SqStackTraverse(SqStack S, void(*visit)(SElemType)) {
	int count = 0;
	SElemType e;
	if (S.top == 0) cout << "None!" << endl;
	while (S.top !=0) {
		Pop(S, e);
		visit(e);
	}
	cout << endl;
}
void visit(SElemType e) {
	//cout << e.key<<" ";
	cout << e << " ";
}
