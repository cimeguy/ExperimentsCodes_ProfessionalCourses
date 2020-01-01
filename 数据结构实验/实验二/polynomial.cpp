#include "polynomial.h"
#include "headers.h"
#include <iostream>
#include<string>
using namespace std;

void InitPoly(Polynomial &L) {    //��ʼ�������� ��ͷ��
	L = new ListTerm;
	if (!L) exit(-1);
	L->coef = 0.0;
	L->next = NULL;
}
void DestroyPoly(Polynomial &L) {       //��յ����� ����ͷ�ڵ�
	ListTerm *q;
	while (L->next != NULL) {
		q = L->next;
		L->next = q->next;
		delete q;
	}
}
bool PolyInsert(Polynomial &L, double coef, int exp) {
	if (coef == 0)return false;

	ListTerm *p = L->next;//ָ���һ���ڵ�
	ListTerm *prep = L;

	while (p != NULL&& p->exp < exp) {  //prep��expС ��p>=exp
		prep = p;
		p = p->next;
	}
	//�������
	if (p == NULL) {
		ListTerm *pnew = new ListTerm;
		pnew->coef = coef;
		pnew->exp = exp;
		pnew->next = NULL;
		prep->next = pnew;
		L->coef++;
		return true;
	}
	/*p->exp = exp  ����p->exp >exp */
	if (p->exp == exp) {  //��һ��Ϊexp(��exp)
		p->coef += coef;
		if (p->coef == 0.0)
		{
			L->coef--;
			prep->next = p->next;
			delete p;
		}
		return true;
	}

	ListTerm *q = new ListTerm;//����һ���½ڵ�
	if (!q)exit(-1);
	q->coef = coef;
	q->exp = exp;
	q->next = p;
	prep->next = q;
	L->coef++;
	return true;
}
ListTerm* CreatPoly() {//�����봴�����ʽ
	string scoef;
	string sexp;

	Polynomial L;/*��ʼ��*/
	InitPoly(L);
	double count = 0;
	while (1) {
		//����#����
		cin >> scoef;
		if (scoef == "#")break;
		cin >> sexp;
		if (sexp == "#") break;
		//ת������
		double coef = atof(scoef.c_str());
		int exp = atoi(sexp.c_str());
		//����
		PolyInsert(L, coef, exp);
	}
	/*�������*/
	ListTerm *p = L->next;//ָ���һ���ڵ�
	while (p) {
		p = p->next;
		count++;
	}
	L->coef = count;//ͷ�ڵ�洢����
	return L;
}
void PrintTerm(Polynomial L) {
	Polynomial p = L;
	cout << p->coef << ' ';
	p = p->next;
	while (p) {
		cout << p->coef << ' ' << p->exp << ' ';
		p = p->next;
	}
	cout << endl;
}
void PrintExpression(Polynomial L) {/*������дϰ���������ʽ*/
	Polynomial p = L->next;/*��һ���ڵ�*/
	if (L->coef == 0) {
		cout << 0 << endl; return;
	}
	if (p->coef == 0.0) {/*ϵ��Ϊ0*/
		p = p->next;
	}
	else {/*ϵ����Ϊ0*/
		if (p->coef == -1) {
			cout << "-";
		}
		else if (p->coef == 1.0) {
			if (p->exp == 0)cout << 1;
		}
		else {
			cout << p->coef;
		}
		if (p->exp == 1)
			cout << "x";
		else {
			if (p->exp != 0)  /*ָ����Ϊ0*/
				cout << "x^" << p->exp;
		}
	}
	p = p->next;/*�ڶ������*/
	if (!p) {
		cout << endl;
		return;
	}
	if (p->coef == 0.0) {/*ϵ��Ϊ0*/
		p = p->next;
	}
	else {/*ϵ����Ϊ0*/
		if (p->coef == -1) {

			cout << "-";
			cout << "x";
		}
		else if (p->coef == 1.0) {
			cout << "+";
			cout << "x";
		}
		else {

			if (p->coef > 0)cout << "+";

			cout << p->coef;
			cout << "x";


		}
		if (p->exp != 1)cout << "^" << p->exp;
		p = p->next;
	}
	while (p != NULL) {

		if (p->coef == 0.0) {
			p = p->next;
			continue;
		}
		else if (p->coef > 0.0) {
			if (p->coef == 1) {
				cout << "+" << "x^" << p->exp;
			}
			else {
				cout << "+" << p->coef << "x^" << p->exp;
			}
			p = p->next;
			continue;

		}
		else {
			if (p->coef == -1) {
				cout << "-x^" << p->exp;
			}
			else {
				cout << p->coef << "x^" << p->exp;
			}
			p = p->next;
			continue;
		}
	}
	cout << endl;
}
ListTerm *AddPoly(Polynomial L1, Polynomial L2)  /*����ʽ�ӷ�*/
{
	Polynomial L3;
	InitPoly(L3);
	ListTerm * p1 = L1->next;
	ListTerm * p2 = L2->next;
	ListTerm * p3 = L3;
	ListTerm *p;
	double tempcoef;
	while (p1 != NULL && p2 != NULL) {
		if (p1->exp == p2->exp) {  //ָ����ͬ ��ϵ�����
			tempcoef = p1->coef + p2->coef;
			/*ϵ��Ϊ0*/
			if (tempcoef == 0.0) {
				p1 = p1->next;
				p2 = p2->next;
			}
			/*ϵ����Ϊ0*/
			else {
				Polynomial s = new ListTerm;
				s->exp = p1->exp;
				s->coef = tempcoef;
				s->next = p3->next;
				p3->next = s;

				p1 = p1->next;
				p2 = p2->next;
				p3 = p3->next;
			}
		}
		else {
			Polynomial s = new ListTerm;
			if (p1->exp > p2->exp) {
				s->exp = p2->exp;
				s->coef = p2->coef;
				s->next = p3->next;
				p3->next = s;
				p2 = p2->next;
				p3 = p3->next;
			}
			else {
				s->exp = p1->exp;
				s->coef = p1->coef;
				s->next = p3->next;
				p3->next = s;
				p1 = p1->next;
				p3 = p3->next;
			}
		}
	}
	Polynomial s = new ListTerm;
	if (p1) {  //ʣ�ಿ��
		p = p1;
	}
	else {
		p = p2;
	}

	while (p) {
		Polynomial s = new ListTerm;
		s->coef = p->coef;
		s->exp = p->exp;
		s->next = p3->next;
		p3->next = s;
		p3 = p3->next;
		p = p->next;
	}
	p3->next = NULL;

	ListTerm * pcount = L3->next;
	double count = 0.0;
	while (pcount) {
		pcount = pcount->next;
		count++;
	}
	L3->coef = count;
	return L3;

}
ListTerm * Deriv(Polynomial L) {            /*��*/

	Polynomial L_deriv;
	InitPoly(L_deriv);
	Polynomial p = L->next;
	Polynomial pd = L_deriv;
	double count = 0.0;
	if (L->coef == 0) {//ϵ��Ϊ0
		L_deriv->coef = 0.0;
		L_deriv->next = NULL;
		return L_deriv;
	}
	while (p) {
		if (p->exp == 0) {
			p = p->next;
			continue;
		}
		Polynomial s = new ListTerm;
		s->exp = (p->exp) - 1;//��
		s->coef = (p->coef)*(p->exp);
		s->next = pd->next;
		pd->next = s;
		pd = pd->next;
		p = p->next;
		count++;
	}
	L_deriv->coef = count;
	return L_deriv;

}
ListTerm* Multiply(Polynomial L1, Polynomial L2) {   //�˷�
	Polynomial p1, p2, p3, pr;//pr��¼ǰһ��
	Polynomial L3;
	int tempexp;
	double tempcoef;
	InitPoly(L3);
	p1 = L1->next;
	double count = 0.0;
	if (L1->coef == 0.0 || L2->coef == 0.0) {
		L3->coef = 0.0;
		L3->next = NULL;
		return L3;
	}
	while (p1) {//����ÿ��p1

		p2 = L2->next;
		while (p2) {   //����p2
			pr = L3;
			p3 = L3->next;
			tempcoef = p1->coef * p2->coef;
			tempexp = p1->exp + p2->exp;
			while (p3&&p3->exp < tempexp) {

				pr = pr->next;
				p3 = p3->next;

			}

			if (p3 == NULL || p3->exp>tempexp) {
				Polynomial s = new ListTerm;
				s->coef = tempcoef;
				s->exp = tempexp;
				s->next = p3;
				pr->next = s;
				count++;
			}
			else {
				p3->coef += tempcoef;
				if (p3->coef == 0.0) {//ϵ��Ϊ0ʱ
					Polynomial q = p3;
					pr->next = q->next;
					p3 = p3->next;
					delete q;
					count--;
				}
			}
			p2 = p2->next;
		}
		p1 = p1->next;
	}
	L3->coef = count;
	return L3;
}
