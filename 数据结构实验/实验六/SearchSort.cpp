#include <iostream>
#include "headers.h"
#include "SearchSort.h"
//countcompare计数比较次数
//countmove计数移动次数

//顺序查找
int SeqSearch(SeqList &L, SqElemType x) {//查找失败 返回-1
	cout << "顺序查找：" << endl;
	for (int i = 0; i < L.length; i++) {
		if (L.data[i] == x) {
			cout << "比较次数：" << i + 1 << endl;
			return i;
		}
	}
	cout << "查找失败，";
	cout << "比较次数：" << L.length << endl;
	return -1;
}

//折半查找  (有序表) is给出查找到的元素地址（查找成功）或x应插入的地址（不成功）
int BinSearch(SeqList &L, SqElemType x, int &is) {
	cout << "折半查找：" << endl;
	int left = 0, right = L.length-1,mid,countcom = 0;
	while (left<=right)
	{
		mid = (left + right) / 2;
		is = mid;
		countcom++;
		if (x == L.data[mid]) {
			cout << "比较次数：" << countcom << endl;
			return mid;
		}
		else if (x > L.data[mid]) left = mid + 1;
		else right = mid -1;
		
	}
	cout << "查找失败，";
	cout << "比较次数：" << countcom << endl;
	is = left; return -1;//查找失败 
}
//索引查找
SqElemType MaxElem(SeqList L, int start, int end,int &pos) {  //找出L中 start到end的最大值  服务于索引查找 ，start end均为下标
	SqElemType maxelem = L.data[start]; pos = start;
	for (int i = start + 1; i <= end; i++) {
		if (L.data[i] > maxelem) {
			maxelem = L.data[i];
			pos = i;
		}
	}
	return maxelem;
}

int BlockSearch(SeqList L, SqElemType x) {
	//创建索引表
	cout << "索引查找：" << endl;
	indextable tableofL;
	int index_length = sqrt(L.length) ; tableofL.length = index_length;//根据表长设定索引表长度/块数  这个例子中是2
	int lengthofeveryblock = L.length / index_length;//每个块的大小/长度  这个例子中是4
	tableofL.index = new index[MAXINDEX];
	int j = 0;
	for (int i = 0; i < tableofL.length;i++ ){//建立索引表
		int pos = 0;
		tableofL.index[i].start = j;
		tableofL.index[i].end = j + lengthofeveryblock-1;
		tableofL.index[i].key = MaxElem(L, tableofL.index[i].start, tableofL.index[i].end,pos);//得出块中最大的值
		tableofL.index[i].keypos = pos;//得出块中最大值的位置
		j = j + lengthofeveryblock;
		if (j > L.length) j = L.length;
	}
	//索引查找
	for (int i = 0; i < tableofL.length; i++) {
		if (x == tableofL.index[i].key) {
			cout << "比较次数：" << i+1 << endl;
			return tableofL.index[i].keypos;
		}
		else if (x > tableofL.index[i].key)continue;//不在这个块
		else {//小于 在这个块里
			for (int j = tableofL.index[i].start; j<= tableofL.index[i].end; j++) {
				if (x == L.data[j]) {
					cout<< "比较次数为：" << i + 1+j- tableofL.index[i].start +1<< endl;
					return j;
				}
			}
		}
	}
	cout << "查找失败，比较次数为"<< index_length +tableofL.index[index_length-1].end- tableofL.index[index_length - 1].start+1 << endl;
	return -1;
}

//二叉查找树
BSTnode *Search(BSTree BT,int x,BSTree  &father,int &pos,int &countcompare) {
	//int countcompare = 0;
	countcompare = 1;
	BSTnode *p = BT; father = NULL;
	while (p != NULL&&p->elem.data != x){
		countcompare++;
		father = p;
		if (x< p->elem.data)p = p->lchild;
		else p = p->rchild;
	}
	if(p !=NULL)pos = p->elem.pos;//记录原来的位置 以便查找
	return p;
}
bool Insert(BSTree &BT, BSTElemType x) {
	int pos/*找该元素原本的下标位置*/, countcom = 0/*此函数中不需要*/;
	BSTnode *s, *p, *f; 
	p = Search(BT, x.data, f,pos,countcom);//找到位置
	if (p != NULL)return false;//已有该元素
	s = new BSTnode; if (!s)exit(-1);
	s->elem.data = x.data;
	s->elem.pos = x.pos;
	s->lchild = s->rchild = NULL;
	if (f == NULL)BT = s;//父亲为空
	else if (f->elem.data > x.data)f->lchild = s;//比父亲小 左子女
	else f->rchild = s;//比父亲大 右子女
	return true;
}
void createBT(BSTree &BT, int a[],int m) {//从数组a建立二叉查找树，m为a的长度
	BT = NULL;//初始化
	BSTElemType x;
	for (int i = 0; i < m; i++) {
		x.data = a[i];
		x.pos = i;
		Insert(BT, x);
	}
}

//散列表查找
void InitHashTable(HashTable &HT, int d) {
	//初始化函数，要求d是不大于m但最接近m的素数  这里设置为 13（<15）
	HT.divisor = d;
	cout << "divisor = " << d << endl;
	HT.m = defaultSize;
	HT.n = 0;
	HT.elem = new KeyType;//创建表存储数组
	HT.state = new KindofState;//创建表状态数组
	for (int i = 0; i < HT.m; i++) {//初始状态均为空
		HT.state[i] = Blank;
	}
}
void createHashTable(HashTable &HT, int a[], int length) {//创建哈希表
	int pos;
	for (int i = 0; i < length; i++) {
		pos = a[i] % HT.divisor;
		while (HT.state[pos] == Active) {//找到第一个空位
			pos = (pos + 1) % HT.divisor;
		}
		HT.elem[pos].data = a[i];//存放a[i]
		HT.elem[pos].pos = i;
		HT.state[pos] = Active;
	}
}
int FindPos(HashTable &HT, int x, int &i,int &orpos) {//查找成功  返回1，否则返回0 ，表满返回-1
	cout << "哈希表查找：" << endl;
	int countcompare = 1;
	cout << x << endl;
	//用线性探查法查找在散列表HT中关键码与x匹配的元素
	i = x % HT.divisor;
	if (HT.state[i] == Active &&HT.elem[i].data == x) {//找到 返回1
		orpos = HT.elem[i].pos;
		cout << "比较次数：" << countcompare<<endl;
		return 1;
	}
	else {
		int  j = i;
		do {
				countcompare++;
				if (HT.state[i] == Active && HT.elem[i].data == x) {
					orpos = HT.elem[i].pos;
					cout << "比较次数：" <<countcompare<< endl;
					return 1;
				}
				else if (HT.state[i] != Active) {//该位置是空位
					cout << "查找失败" << endl;
					orpos = -1;
					return 0;//找到空位 返回0
				}
				i = (i + 1)%HT.m;
			} while (j != i);
		cout << "查找失败" << endl;
		orpos = -1;
		return -1;//转一圈 表已满 失败
	}
}
//插入排序
void InsertSort(SeqList &L) {
	SElemType temp;
	cout << "插入排序:" << endl;
	for (int k = 0; k < L.length; k++)cout << L.data[k] << " "; cout << endl;//起始输出
	int i, j;
	int countmove=0, countcompare=0;
	for (i = 1; i < L.length; i++) {
		countcompare++;
		if (L.data[i] < L.data[i - 1]) {
			countmove++; 
			temp = L.data[i];
			for (j = i - 1; j >= 0 && temp < L.data[j]; j--)
			{
				countcompare++;
				L.data[j + 1] = L.data[j];//往后移
			}
			L.data[j + 1] = temp;
			//输出
			for (int k = 0; k < L.length; k++)cout << L.data[k] << " ";
			cout << endl;
		}
	}
	cout << "比较次数：" << countcompare << " ；移动次数：" << countmove << endl<<endl;
}


//交换
void Swap(SeqList &L, int i, int k) {
	SElemType temp = L.data[i];
	L.data[i] = L.data[k];
	L.data[k] = temp;
	//每次交换输出
	for (int m = 0; m < L.length; m++) {
		if (m == i || m == k)
			cout << L.data[m] << " ";
		else cout << "   ";
	}cout << endl;
}
void SelectSort(SeqList &L) {
	cout << "选择排序：" << endl;
	for (int k = 0; k < L.length; k++)cout << L.data[k] << " "; cout << endl;
	int  j, k; int countmove = 0, countcompare = 0;
	for (int i = 0; i < L.length - 1; i++) {
		k = i;
		for (j = i + 1; j < L.length; j++) {
			countcompare++;
			if (L.data[j] < L.data[k])k = j;//找最小元素
		}
		if (i!=k) {
			Swap(L, i, k);//交换
			countmove++;
		}
	}
	for (int k = 0; k < L.length; k++)cout << L.data[k] << " "; cout << endl;//最后结果输出
	cout << "比较次数：" << countcompare << " ；移动次数：" << countmove << endl << endl;
}
void BubbleSort(SeqList &L) {
	cout << "冒泡排序：" << endl;
	for (int k = 0; k < L.length; k++)cout << L.data[k] << " "; cout << endl;
	int exchange;
	int j, countmove = 0, countcompare = 0;
	for (int i = 0; i < L.length - 1; i++) {
		exchange = 0;
		for (j = L.length - 1; j >= i + 1; j--) {
			countcompare++;
			if (L.data[j - 1] > L.data[j]) {//逆序交换元素
				Swap(L, j - 1, j);
				countmove++;
				exchange = 1;
			}
		}
		if (!exchange) {
			for (int k = 0; k < L.length; k++)cout << L.data[k] << " "; cout << endl;//最后结果输出
			cout << "比较次数：" << countcompare << " ；移动次数：" << countmove << endl << endl;
			return;//本趟无逆序则停止
		}
	}for (int k = 0; k < L.length; k++)cout << L.data[k] << " "; cout << endl;//最后结果输出
	cout << "比较次数：" << countcompare << " ；移动次数：" << countmove << endl << endl;
}
//希尔排序
void insertSort_gap(SeqList &L, int start, int gap,int &countcompare ,int &countmove) {
	SqElemType temp;
	int i, j;
	cout << "gap:" << gap << endl;//输出每次的 gap
	for (i = start + gap; i <= L.length - 1; i = i + gap) {
		countcompare++;
		if (L.data[i - gap] > L.data[i]) {//逆序
			countmove++;
			temp = L.data[i]; j = i;
			do {
				L.data[j] = L.data[j - gap];
				j = j - gap;
			} while (j - gap > 0 && L.data[j - gap] > temp);
			L.data[j] = temp;
			//输出
			for (int k = 0; k < L.length; k++)cout << L.data[k] << " ";
			cout << endl;
		}
	}
}
void ShellSort(SeqList &L, int d[], int m) {
	cout << "希尔排序：" << endl;
	for (int k = 0; k < L.length; k++)cout << L.data[k] << " "; cout << endl;//起始输出
	//d[m]存放增量序列，d[0]=1
	int i, start, gap; int countmove = 0, countcompare = 0;
	for (i = m - 1; i >= 0; i--) {//gap由后往前
		gap = d[i];
		for (start = 0; start < gap; start++) {//直到d[0]=1停止迭代
			insertSort_gap(L, start, gap,countcompare,countmove);
		}
	}
	cout << "比较次数：" << countcompare << " ；移动次数：" << countmove << endl << endl;
	//for (int k = 0; k < L.length; k++)cout << L.data[k] << " "; cout << endl;//最后结果输出
}
//快速排序
int Partition(SeqList &L, int low, int high,int &countcompare ,int &countmove ) {
	int i, k = low; SqElemType pivot = L.data[low];//基准元素
	for (i = low + 1; i <= high; i++) {//扫描整个序列进行划分
		countcompare++;
		if (L.data[i] < pivot) {//小于pivot
			k++;
			if (k != i) {
				Swap(L, i, k);//交换
				countmove++;
			}
		}
	}
	//countmove++;
	L.data[low] = L.data[k];//将基准元素存放
	L.data[k] = pivot;
	return k;//返回基准元素位置
}
void QuickSort(SeqList &L, int left, int right,int &countcompare, int &countmove) {//调用 QuickSort(L,0,L.length-1)
//从left到right排序
	
	if (left < right) {
		int pivotpos = Partition(L, left, right,countcompare,countmove);//pivopos是划分
		QuickSort(L, left, pivotpos - 1 , countcompare, countmove);
		QuickSort(L, pivotpos + 1, right, countcompare, countmove);
	}

}
void QuickSortV2(SeqList &L, int left, int right) {//为了体现输出
	cout << "快速排序：" << endl;
	int countcompare=0, countmove=0;
	for (int k = 0; k < L.length; k++)cout << L.data[k] << " "; cout << endl;//起始输出
	QuickSort(L, 0, L.length - 1, countcompare, countmove);
	for (int k = 0; k < L.length; k++)cout << L.data[k] << " "; cout << endl;//最后结果输出
	cout << "比较次数：" << countcompare << " ；移动次数：" << countmove << endl << endl;
}
void siftDown(SeqList &L,int start, int m, int &countcompare, int &countmove) {
	int i = start; 
	int j = i * 2 + 1;//j是i的左子女
	SqElemType temp = L.data[i];
	while (j <= m/*检查子女节点号是否到最后位置*/) {
		countcompare++;
		if (j < m&&L.data[j] < L.data[j + 1]) {//让j指向两子女中较大的 那个
			j++;
		}
		if (temp >= L.data[j]) {
			break;//纵向比较 temp排序码大则不调整
		}
		else {
			countmove++;
			L.data[i] = L.data[j];//子女中大者上移
			i = j;//i下降到大子女j位置
			j = 2 * j + 1;
			
		}
	}
	//每次交换输出
	for (int m = 0; m < L.length; m++) {
		cout << L.data[m] << " ";
	}cout << endl;
	L.data[i] = temp;//temp暂存元素放到合适位置

}
void HeapSort(SeqList&L) {
	cout << "堆排序：" << endl;
	int countcompare = 0, countmove = 0;
	for (int k = 0; k < L.length; k++)cout << L.data[k] << " "; cout << endl;//起始输出
	int i;
	for (i = (L.length - 2) / 2; i >= 0; i--) {
		siftDown(L, i, L.length - 1,countcompare,countmove);
	}//将表转为大根堆
	for (i = L.length - 1; i > 0; i--) {//对大根堆排序
		SqElemType temp = L.data[0];
		L.data[0] = L.data[i];
		L.data[i] = temp;
		siftDown(L, 0, i - 1, countcompare, countmove);//交换 重建大根堆
	}
	for (int k = 0; k < L.length; k++)cout << L.data[k] << " "; cout << endl;//最后结果输出
	cout << "比较次数：" << countcompare << " ；移动次数：" << countmove << endl << endl;
}
void getLfromA(SeqList &L, int A[], int m) {//从数组A得到顺序表L
	for (int i = 0; i < m; i++) {
		L.data[i] = A[i];
	}
	L.length = m;
}