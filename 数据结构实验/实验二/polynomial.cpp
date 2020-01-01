#include "polynomial.h"
#include "headers.h"
#include <iostream>
#include<string>
using namespace std;

void InitPoly(Polynomial &L) {    //初始化单链表 带头点
	L = new ListTerm;
	if (!L) exit(-1);
	L->coef = 0.0;
	L->next = NULL;
}
void DestroyPoly(Polynomial &L) {       //清空单链表 保留头节点
	ListTerm *q;
	while (L->next != NULL) {
		q = L->next;
		L->next = q->next;
		delete q;
	}
}
bool PolyInsert(Polynomial &L, double coef, int exp) {
	if (coef == 0)return false;

	ListTerm *p = L->next;//指向第一个节点
	ListTerm *prep = L;

	while (p != NULL&& p->exp < exp) {  //prep比exp小 ；p>=exp
		prep = p;
		p = p->next;
	}
	//插在最后
	if (p == NULL) {
		ListTerm *pnew = new ListTerm;
		pnew->coef = coef;
		pnew->exp = exp;
		pnew->next = NULL;
		prep->next = pnew;
		L->coef++;
		return true;
	}
	/*p->exp = exp  或者p->exp >exp */
	if (p->exp == exp) {  //下一个为exp(有exp)
		p->coef += coef;
		if (p->coef == 0.0)
		{
			L->coef--;
			prep->next = p->next;
			delete p;
		}
		return true;
	}

	ListTerm *q = new ListTerm;//创建一个新节点
	if (!q)exit(-1);
	q->coef = coef;
	q->exp = exp;
	q->next = p;
	prep->next = q;
	L->coef++;
	return true;
}
ListTerm* CreatPoly() {//从输入创造多项式
	string scoef;
	string sexp;

	Polynomial L;/*初始化*/
	InitPoly(L);
	double count = 0;
	while (1) {
		//输入#结束
		cin >> scoef;
		if (scoef == "#")break;
		cin >> sexp;
		if (sexp == "#") break;
		//转换类型
		double coef = atof(scoef.c_str());
		int exp = atoi(sexp.c_str());
		//插入
		PolyInsert(L, coef, exp);
	}
	/*计算个数*/
	ListTerm *p = L->next;//指向第一个节点
	while (p) {
		p = p->next;
		count++;
	}
	L->coef = count;//头节点存储个数
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
void PrintExpression(Polynomial L) {/*按照书写习惯输出多项式*/
	Polynomial p = L->next;/*第一个节点*/
	if (L->coef == 0) {
		cout << 0 << endl; return;
	}
	if (p->coef == 0.0) {/*系数为0*/
		p = p->next;
	}
	else {/*系数不为0*/
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
			if (p->exp != 0)  /*指数不为0*/
				cout << "x^" << p->exp;
		}
	}
	p = p->next;/*第二个结点*/
	if (!p) {
		cout << endl;
		return;
	}
	if (p->coef == 0.0) {/*系数为0*/
		p = p->next;
	}
	else {/*系数不为0*/
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
ListTerm *AddPoly(Polynomial L1, Polynomial L2)  /*多项式加法*/
{
	Polynomial L3;
	InitPoly(L3);
	ListTerm * p1 = L1->next;
	ListTerm * p2 = L2->next;
	ListTerm * p3 = L3;
	ListTerm *p;
	double tempcoef;
	while (p1 != NULL && p2 != NULL) {
		if (p1->exp == p2->exp) {  //指数相同 ，系数相加
			tempcoef = p1->coef + p2->coef;
			/*系数为0*/
			if (tempcoef == 0.0) {
				p1 = p1->next;
				p2 = p2->next;
			}
			/*系数不为0*/
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
	if (p1) {  //剩余部分
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
ListTerm * Deriv(Polynomial L) {            /*求导*/

	Polynomial L_deriv;
	InitPoly(L_deriv);
	Polynomial p = L->next;
	Polynomial pd = L_deriv;
	double count = 0.0;
	if (L->coef == 0) {//系数为0
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
		s->exp = (p->exp) - 1;//求导
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
ListTerm* Multiply(Polynomial L1, Polynomial L2) {   //乘法
	Polynomial p1, p2, p3, pr;//pr记录前一个
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
	while (p1) {//对于每个p1

		p2 = L2->next;
		while (p2) {   //遍历p2
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
				if (p3->coef == 0.0) {//系数为0时
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
