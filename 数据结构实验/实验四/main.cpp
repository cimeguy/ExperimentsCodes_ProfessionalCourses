#include "Sqstack.h"	  //顺序栈
#include "SqQueue.h"	  //顺序队列
#include"Huffman.h"		  //哈夫曼树
#include "bintree.h"       //二叉树
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int main() {
	
//*-------------二叉树---------------*//
	cout << "测试二叉树:" << endl;
	int n = 0;
	TElemType ch[] = "ABC##D#E###;";//测试样例
	//cout << "测试样例为" << ch << endl;
	BinTree BT;
	InitBiTree(BT);//初始化
	CreatBiTree(BT, ch, n );//创建二叉树  ，n返回输入统计
	cout << "高度为"<<BiTreeEmpty(BT) << endl;//深度/高度
	InsertChild(BT, BT->lchild->lchild, 0, 'M');//在C插入左孩子，M
	PreOrder(BT);//非递归  先序遍历
	DestoryBiTree(BT);//销毁
	cout << endl;
///*------------哈夫曼树-------------*/

	Huffman_operate();      //哈夫曼系统 在Huffman.cpp中 ;栈中元素typedef char SElemType;
	return 0;
//

}