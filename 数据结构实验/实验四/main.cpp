#include "Sqstack.h"	  //˳��ջ
#include "SqQueue.h"	  //˳�����
#include"Huffman.h"		  //��������
#include "bintree.h"       //������
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int main() {
	
//*-------------������---------------*//
	cout << "���Զ�����:" << endl;
	int n = 0;
	TElemType ch[] = "ABC##D#E###;";//��������
	//cout << "��������Ϊ" << ch << endl;
	BinTree BT;
	InitBiTree(BT);//��ʼ��
	CreatBiTree(BT, ch, n );//����������  ��n��������ͳ��
	cout << "�߶�Ϊ"<<BiTreeEmpty(BT) << endl;//���/�߶�
	InsertChild(BT, BT->lchild->lchild, 0, 'M');//��C�������ӣ�M
	PreOrder(BT);//�ǵݹ�  �������
	DestoryBiTree(BT);//����
	cout << endl;
///*------------��������-------------*/

	Huffman_operate();      //������ϵͳ ��Huffman.cpp�� ;ջ��Ԫ��typedef char SElemType;
	return 0;
//

}