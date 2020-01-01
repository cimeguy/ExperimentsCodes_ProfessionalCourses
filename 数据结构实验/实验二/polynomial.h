#pragma once
#ifndef POLYNOMIAL_H_INCLUDED
#define POLYNOMIAL_H_INCLUDED

/*****多项式操作*****/
typedef struct term ListTerm;
typedef ListTerm * Polynomial;
void InitPoly(Polynomial &L);							//初始化
void DestroyPoly(Polynomial &L);						//销毁
bool PolyInsert(Polynomial &L, double coef, int exp);   //插入多相似
ListTerm* CreatPoly();									//从输入创建多项式 以#结束
void PrintTerm(Polynomial L);							//输出每项
void PrintExpression(Polynomial L);                     //按照书写习惯输出
ListTerm *AddPoly(Polynomial L1, Polynomial L2);        //加法
ListTerm * Deriv(Polynomial L);                         //求导
ListTerm* Multiply(Polynomial L1, Polynomial L2);       //乘法
/********************/

#endif // DECLARATION_H_INCLUDED