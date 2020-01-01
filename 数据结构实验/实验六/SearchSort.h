#pragma once
#ifndef SEARCH_H
#define SEARCH_H
const int maxSize = 1000;//预设的存储空间最大容量   最大可存储的元素个数
typedef int SqElemType;  //元素类型
typedef struct {       //结构定义
	SqElemType data[maxSize];//存储空间基址
	int length;        //当前长度
}SeqList;
//顺序查找
int SeqSearch(SeqList &L, SqElemType x);
//折半查找
int BinSearch(SeqList &L, SqElemType x, int &is);
//索引查找
typedef struct {//索引结构定义
	int start;
	int end;
	int key;
	int keypos;
}index;
#define MAXINDEX 20
typedef struct {//索引表
	index *index;
	int length;
}indextable;
SqElemType MaxElem(SeqList L, int start, int end, int &pos);
int BlockSearch(SeqList L, SqElemType x);
//二叉查找树（存储的elem包含了原来数据的位置，以便查找）
typedef struct{
	int data;
	int pos;
} BSTElemType;
typedef struct tnode {
	BSTElemType elem;
	struct tnode *lchild, *rchild;
}BSTnode,*BSTree;
BSTnode *Search(BSTree BT, int x, BSTree  &father, int &pos, int &countcompare);
bool Insert(BSTree &BT, BSTElemType x);
void createBT(BSTree &BT, int a[], int m);
//散列表查找
#define defaultSize 15
enum KindofState {
	Active,Blank,Deleted//元素分类 （已存/空/删除）  //本例中Deleted不需用到
};
typedef struct {
	int data;
	int pos;
} KeyType;
typedef struct {//散列表结构定义

	int divisor;//散列函数的除数
	int n, m;//当前已用地址数及最大地址数
	KeyType *elem;//散列表存储数组
	KindofState *state;//状态数组

}HashTable;
void InitHashTable(HashTable &HT, int d);
void createHashTable(HashTable &HT, int a[], int length);
int FindPos(HashTable &HT, int x, int &i,int &orpos);

void Swap(SeqList &L, int i, int k);
void InsertSort(SeqList &L);
void SelectSort(SeqList &L);
void BubbleSort(SeqList &L);

void ShellSort(SeqList &L, int d[], int m);
void insertSort_gap(SeqList &L, int start, int gap, int &countcompare, int &countmove);
//快速排序
void QuickSort(SeqList &L, int left, int right, int &countcompare, int &countmove);
int Partition(SeqList &L, int low, int high, int &countcompare, int &countmove);
void QuickSortV2(SeqList &L, int left, int right);

//大根堆排序
void siftDown(SeqList &L, int start, int m);
void HeapSort(SeqList&L);

void getLfromA(SeqList &L, int A[], int m);
//int SeqSearch(int a[], int x);
#endif // !SEARCH_H

