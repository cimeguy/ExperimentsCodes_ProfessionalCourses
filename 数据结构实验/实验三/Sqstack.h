#pragma once

#ifndef SQSTACK_H_INCLUDED
#define SQSTACK_H_INCLUDED
#include"headers.h"

void InitSqStack(SqStack &S);
void DestroySqStack(SqStack &S);  //销毁栈
void ClearSqStack(SqStack &S);    //将S置为空栈
bool SqStackEmpty(SqStack S);     //若S为空栈，则返回TRUE，否则返回FALSE
int  SqStackLength(SqStack S);    //返回S的元素个数  栈的长度
bool GetTop(SqStack S, SElemType &e);  //返回栈顶元素
bool Push(SqStack &S, SElemType e);    //
bool Pop(SqStack &S, SElemType &e);	 //删除栈顶元素
void SqStackTraverse(SqStack S, void(*visit)(SElemType));
void visit(SElemType e);

#endif // DECLARATION_H_INCLUDED