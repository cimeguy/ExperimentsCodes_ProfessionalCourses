#pragma once

#ifndef SQSTACK_H_INCLUDED
#define SQSTACK_H_INCLUDED
#include"headers.h"

void InitSqStack(SqStack &S);
void DestroySqStack(SqStack &S);  //����ջ
void ClearSqStack(SqStack &S);    //��S��Ϊ��ջ
bool SqStackEmpty(SqStack S);     //��SΪ��ջ���򷵻�TRUE�����򷵻�FALSE
int  SqStackLength(SqStack S);    //����S��Ԫ�ظ���  ջ�ĳ���
bool GetTop(SqStack S, SElemType &e);  //����ջ��Ԫ��
bool Push(SqStack &S, SElemType e);    //
bool Pop(SqStack &S, SElemType &e);	 //ɾ��ջ��Ԫ��
void SqStackTraverse(SqStack S, void(*visit)(SElemType));
void visit(SElemType e);

#endif // DECLARATION_H_INCLUDED