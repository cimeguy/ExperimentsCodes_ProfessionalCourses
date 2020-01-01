#pragma once
#ifndef POLYNOMIAL_H_INCLUDED
#define POLYNOMIAL_H_INCLUDED

/*****����ʽ����*****/
typedef struct term ListTerm;
typedef ListTerm * Polynomial;
void InitPoly(Polynomial &L);							//��ʼ��
void DestroyPoly(Polynomial &L);						//����
bool PolyInsert(Polynomial &L, double coef, int exp);   //���������
ListTerm* CreatPoly();									//�����봴������ʽ ��#����
void PrintTerm(Polynomial L);							//���ÿ��
void PrintExpression(Polynomial L);                     //������дϰ�����
ListTerm *AddPoly(Polynomial L1, Polynomial L2);        //�ӷ�
ListTerm * Deriv(Polynomial L);                         //��
ListTerm* Multiply(Polynomial L1, Polynomial L2);       //�˷�
/********************/

#endif // DECLARATION_H_INCLUDED