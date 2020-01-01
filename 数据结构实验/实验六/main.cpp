#include "SearchSort.h"		//��������
#include <iostream>
using namespace std;

int main() {
	/*----------------���Һ�����----------------*/
	SeqList L/*������������*/,Lindex/*�����������������*/,LBin/*�������*/;
	int a[8] = {49,38,65,97,76,13,27,49};//��������
	int b[8] = { 13,27,38,49,49,65,76,97 };//��������  �����۰����
	int c[8] = { 49,38,27,13,49,97,76,65 };//���������У�ÿsqrt(length(c))������Ϊһ���� ����һ���е���СֵӦ����ǰһ������ֵ
	getLfromA(L, a, 8);
	getLfromA(Lindex, c, 8);
	getLfromA(LBin, b, 8);
	///*------------����-------------*/
	cout << "������Ҫ���ҵ�����" << endl;
	int x;
	cin >> x;
	cout << "λ��" << SeqSearch(L, x) << endl << endl;//1.˳�����
	int Binis;
	cout << "λ��" << BinSearch(LBin, x, Binis) << endl << endl;//2.�۰����
	cout << "λ��" << BlockSearch(Lindex, x) << endl << endl;//3.���������
	int Binpos ,countcompare=0;//4.����������
	BSTree BT,father;
	createBT(BT, a, 8);
	cout << "���������ң�" << endl;
	Search(BT, x, father, Binpos,countcompare); cout<<"�Ƚϴ�����"<<countcompare<<endl << "λ��" << Binpos << endl << endl;
	HashTable HT;//5.ɢ�б����
	int i,hashpos;
	InitHashTable(HT, 13);//����Ϊ13
	createHashTable(HT, a, 8);
	FindPos(HT, x, i, hashpos);
	cout << "λ��" << hashpos << endl << endl;
	
	/*--------------����---------------*/
	getLfromA(L, a, 8);
	InsertSort(L);//�������� 
	getLfromA(L, a, 8);
	int d[3] = { 1,2,3 };
	ShellSort(L, d, 3);//ϣ������
	getLfromA(L, a, 8);
	QuickSortV2(L, 0, L.length - 1);//��������
	getLfromA(L, a, 8);
	SelectSort(L);//��ѡ������
	getLfromA(L, a, 8);
	BubbleSort(L);//ð������
	getLfromA(L, a, 8);
	HeapSort(L);//������

	return 0;
}