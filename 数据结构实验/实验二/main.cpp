//#include"polynomial.h"  //����ʽ
//#include"list.h"        //���Ա�
#include <iostream>
#include <string>
using namespace std;

int main() {
	

/*--------------������--------------*/
	/*cout << "������" << endl;
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
	cout <<"������ :" <<ListLength(A) << endl;
	DestroyList(A);
	cout <<"��ɾ��Ԫ�� :"<< a<<endl;
	*/


/*--------------����ʽ---------------*/
	cout << endl << "����ʽ����:��������������ʽ���ԡ�#����ʾ������" << endl;
	Polynomial L1,L2,L3,L4;
	Polynomial L1_d;
	//������������ʽ
	L1 = CreatPoly();
	L2 = CreatPoly();
	//�����������ʽ
	cout <<endl<<endl<< "L1 = ";
	PrintExpression(L1);
	cout<<endl<< "L2 = ";
	PrintExpression(L2);

	/*�ӷ�*/
	InitPoly(L3);
	L3 = AddPoly(L1, L2);
	cout << endl << "L1 + L2 = ";
	PrintExpression(L3);
	PrintTerm(L3);

	/*�˷�*/
	L4 = Multiply(L1, L2);
	cout << endl << "L1 * L2 = ";
	PrintExpression(L4);

	/*��*/
	L1_d = Deriv(L1);
	//PrintTerm(L1_d);
	cout << endl << "(L1) ' = ";
	PrintExpression(L1_d);
	cout << endl;
	/*����*/
	DestroyPoly(L1);
	DestroyPoly(L2);
	DestroyPoly(L3);
	DestroyPoly(L4);
	DestroyPoly(L1_d);
	return 0;
}