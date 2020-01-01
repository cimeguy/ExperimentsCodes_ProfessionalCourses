//#include"polynomial.h"  //多项式
//#include"list.h"        //线性表
#include <iostream>
#include <string>
using namespace std;

int main() {
	

/*--------------单链表--------------*/
	/*cout << "单链表" << endl;
	LinkList A;
	InitList(A);
	ElemType a;
	ListInsert(A, 0, 1);
	ListInsert(A, 1, 1);
	ListInsert(A, 2, 2);
	ListInsert(A, 3, 3);
	ListInsert(A, 7, 1);

	ListDelete(A, 1, a);
	ListTraverse(A, visit);
	cout <<"链表长度 :" <<ListLength(A) << endl;
	DestroyList(A);
	cout <<"被删除元素 :"<< a<<endl;
	*/


/*--------------多项式---------------*/
	cout << endl << "多项式操作:请输入两个多项式（以‘#’表示结束）" << endl;
	Polynomial L1,L2,L3,L4;
	Polynomial L1_d;
	//创建两个多项式
	L1 = CreatPoly();
	L2 = CreatPoly();
	//输出两个多项式
	cout <<endl<<endl<< "L1 = ";
	PrintExpression(L1);
	cout<<endl<< "L2 = ";
	PrintExpression(L2);

	/*加法*/
	InitPoly(L3);
	L3 = AddPoly(L1, L2);
	cout << endl << "L1 + L2 = ";
	PrintExpression(L3);
	PrintTerm(L3);

	/*乘法*/
	L4 = Multiply(L1, L2);
	cout << endl << "L1 * L2 = ";
	PrintExpression(L4);

	/*求导*/
	L1_d = Deriv(L1);
	//PrintTerm(L1_d);
	cout << endl << "(L1) ' = ";
	PrintExpression(L1_d);
	cout << endl;
	/*销毁*/
	DestroyPoly(L1);
	DestroyPoly(L2);
	DestroyPoly(L3);
	DestroyPoly(L4);
	DestroyPoly(L1_d);
	return 0;
}