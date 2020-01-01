#include<iostream>
#include "headers.h"
using namespace std;


void InitSqStack(SqStack &S){//初始时为0
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
	if ( S.top == S.stacksize )return false;  //栈已满
	*(S.base + S.top) = e;
	++S.top;
	return true;
}
bool Pop(SqStack &S, SElemType &e) {
	if (S.top == 0) return false;  //空栈
	e = *(S.base + S.top - 1);		//栈顶元素
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
