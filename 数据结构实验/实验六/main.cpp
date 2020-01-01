#include "SearchSort.h"		//查找排序
#include <iostream>
using namespace std;

int main() {
	/*----------------查找和排序----------------*/
	SeqList L/*排序所用序列*/,Lindex/*索引表查找所用序列*/,LBin/*有序查找*/;
	int a[8] = {49,38,65,97,76,13,27,49};//乱序序列
	int b[8] = { 13,27,38,49,49,65,76,97 };//有序数列  用于折半查找
	int c[8] = { 49,38,27,13,49,97,76,65 };//索引表序列，每sqrt(length(c))个数字为一个块 ，后一块中的最小值应大于前一块的最大值
	getLfromA(L, a, 8);
	getLfromA(Lindex, c, 8);
	getLfromA(LBin, b, 8);
	///*------------查找-------------*/
	cout << "请输入要查找的数字" << endl;
	int x;
	cin >> x;
	cout << "位置" << SeqSearch(L, x) << endl << endl;//1.顺序查找
	int Binis;
	cout << "位置" << BinSearch(LBin, x, Binis) << endl << endl;//2.折半查找
	cout << "位置" << BlockSearch(Lindex, x) << endl << endl;//3.索引表查找
	int Binpos ,countcompare=0;//4.二叉树查找
	BSTree BT,father;
	createBT(BT, a, 8);
	cout << "二叉树查找：" << endl;
	Search(BT, x, father, Binpos,countcompare); cout<<"比较次数："<<countcompare<<endl << "位置" << Binpos << endl << endl;
	HashTable HT;//5.散列表查找
	int i,hashpos;
	InitHashTable(HT, 13);//除数为13
	createHashTable(HT, a, 8);
	FindPos(HT, x, i, hashpos);
	cout << "位置" << hashpos << endl << endl;
	
	/*--------------排序---------------*/
	getLfromA(L, a, 8);
	InsertSort(L);//插入排序 
	getLfromA(L, a, 8);
	int d[3] = { 1,2,3 };
	ShellSort(L, d, 3);//希尔排序
	getLfromA(L, a, 8);
	QuickSortV2(L, 0, L.length - 1);//快速排序
	getLfromA(L, a, 8);
	SelectSort(L);//简单选择排序
	getLfromA(L, a, 8);
	BubbleSort(L);//冒泡排序
	getLfromA(L, a, 8);
	HeapSort(L);//堆排序

	return 0;
}