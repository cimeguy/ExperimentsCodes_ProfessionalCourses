#pragma once
#ifndef SEARCH_H
#define SEARCH_H
const int maxSize = 1000;//Ԥ��Ĵ洢�ռ��������   ���ɴ洢��Ԫ�ظ���
typedef int SqElemType;  //Ԫ������
typedef struct {       //�ṹ����
	SqElemType data[maxSize];//�洢�ռ��ַ
	int length;        //��ǰ����
}SeqList;
//˳�����
int SeqSearch(SeqList &L, SqElemType x);
//�۰����
int BinSearch(SeqList &L, SqElemType x, int &is);
//��������
typedef struct {//�����ṹ����
	int start;
	int end;
	int key;
	int keypos;
}index;
#define MAXINDEX 20
typedef struct {//������
	index *index;
	int length;
}indextable;
SqElemType MaxElem(SeqList L, int start, int end, int &pos);
int BlockSearch(SeqList L, SqElemType x);
//������������洢��elem������ԭ�����ݵ�λ�ã��Ա���ң�
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
//ɢ�б����
#define defaultSize 15
enum KindofState {
	Active,Blank,Deleted//Ԫ�ط��� ���Ѵ�/��/ɾ����  //������Deleted�����õ�
};
typedef struct {
	int data;
	int pos;
} KeyType;
typedef struct {//ɢ�б�ṹ����

	int divisor;//ɢ�к����ĳ���
	int n, m;//��ǰ���õ�ַ��������ַ��
	KeyType *elem;//ɢ�б�洢����
	KindofState *state;//״̬����

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
//��������
void QuickSort(SeqList &L, int left, int right, int &countcompare, int &countmove);
int Partition(SeqList &L, int low, int high, int &countcompare, int &countmove);
void QuickSortV2(SeqList &L, int left, int right);

//���������
void siftDown(SeqList &L, int start, int m);
void HeapSort(SeqList&L);

void getLfromA(SeqList &L, int A[], int m);
//int SeqSearch(int a[], int x);
#endif // !SEARCH_H

