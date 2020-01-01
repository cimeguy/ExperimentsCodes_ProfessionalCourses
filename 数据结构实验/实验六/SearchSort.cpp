#include <iostream>
#include "headers.h"
#include "SearchSort.h"
//countcompare�����Ƚϴ���
//countmove�����ƶ�����

//˳�����
int SeqSearch(SeqList &L, SqElemType x) {//����ʧ�� ����-1
	cout << "˳����ң�" << endl;
	for (int i = 0; i < L.length; i++) {
		if (L.data[i] == x) {
			cout << "�Ƚϴ�����" << i + 1 << endl;
			return i;
		}
	}
	cout << "����ʧ�ܣ�";
	cout << "�Ƚϴ�����" << L.length << endl;
	return -1;
}

//�۰����  (�����) is�������ҵ���Ԫ�ص�ַ�����ҳɹ�����xӦ����ĵ�ַ�����ɹ���
int BinSearch(SeqList &L, SqElemType x, int &is) {
	cout << "�۰���ң�" << endl;
	int left = 0, right = L.length-1,mid,countcom = 0;
	while (left<=right)
	{
		mid = (left + right) / 2;
		is = mid;
		countcom++;
		if (x == L.data[mid]) {
			cout << "�Ƚϴ�����" << countcom << endl;
			return mid;
		}
		else if (x > L.data[mid]) left = mid + 1;
		else right = mid -1;
		
	}
	cout << "����ʧ�ܣ�";
	cout << "�Ƚϴ�����" << countcom << endl;
	is = left; return -1;//����ʧ�� 
}
//��������
SqElemType MaxElem(SeqList L, int start, int end,int &pos) {  //�ҳ�L�� start��end�����ֵ  �������������� ��start end��Ϊ�±�
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
	//����������
	cout << "�������ң�" << endl;
	indextable tableofL;
	int index_length = sqrt(L.length) ; tableofL.length = index_length;//���ݱ��趨��������/����  �����������2
	int lengthofeveryblock = L.length / index_length;//ÿ����Ĵ�С/����  �����������4
	tableofL.index = new index[MAXINDEX];
	int j = 0;
	for (int i = 0; i < tableofL.length;i++ ){//����������
		int pos = 0;
		tableofL.index[i].start = j;
		tableofL.index[i].end = j + lengthofeveryblock-1;
		tableofL.index[i].key = MaxElem(L, tableofL.index[i].start, tableofL.index[i].end,pos);//�ó���������ֵ
		tableofL.index[i].keypos = pos;//�ó��������ֵ��λ��
		j = j + lengthofeveryblock;
		if (j > L.length) j = L.length;
	}
	//��������
	for (int i = 0; i < tableofL.length; i++) {
		if (x == tableofL.index[i].key) {
			cout << "�Ƚϴ�����" << i+1 << endl;
			return tableofL.index[i].keypos;
		}
		else if (x > tableofL.index[i].key)continue;//���������
		else {//С�� ���������
			for (int j = tableofL.index[i].start; j<= tableofL.index[i].end; j++) {
				if (x == L.data[j]) {
					cout<< "�Ƚϴ���Ϊ��" << i + 1+j- tableofL.index[i].start +1<< endl;
					return j;
				}
			}
		}
	}
	cout << "����ʧ�ܣ��Ƚϴ���Ϊ"<< index_length +tableofL.index[index_length-1].end- tableofL.index[index_length - 1].start+1 << endl;
	return -1;
}

//���������
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
	if(p !=NULL)pos = p->elem.pos;//��¼ԭ����λ�� �Ա����
	return p;
}
bool Insert(BSTree &BT, BSTElemType x) {
	int pos/*�Ҹ�Ԫ��ԭ�����±�λ��*/, countcom = 0/*�˺����в���Ҫ*/;
	BSTnode *s, *p, *f; 
	p = Search(BT, x.data, f,pos,countcom);//�ҵ�λ��
	if (p != NULL)return false;//���и�Ԫ��
	s = new BSTnode; if (!s)exit(-1);
	s->elem.data = x.data;
	s->elem.pos = x.pos;
	s->lchild = s->rchild = NULL;
	if (f == NULL)BT = s;//����Ϊ��
	else if (f->elem.data > x.data)f->lchild = s;//�ȸ���С ����Ů
	else f->rchild = s;//�ȸ��״� ����Ů
	return true;
}
void createBT(BSTree &BT, int a[],int m) {//������a���������������mΪa�ĳ���
	BT = NULL;//��ʼ��
	BSTElemType x;
	for (int i = 0; i < m; i++) {
		x.data = a[i];
		x.pos = i;
		Insert(BT, x);
	}
}

//ɢ�б����
void InitHashTable(HashTable &HT, int d) {
	//��ʼ��������Ҫ��d�ǲ�����m����ӽ�m������  ��������Ϊ 13��<15��
	HT.divisor = d;
	cout << "divisor = " << d << endl;
	HT.m = defaultSize;
	HT.n = 0;
	HT.elem = new KeyType;//������洢����
	HT.state = new KindofState;//������״̬����
	for (int i = 0; i < HT.m; i++) {//��ʼ״̬��Ϊ��
		HT.state[i] = Blank;
	}
}
void createHashTable(HashTable &HT, int a[], int length) {//������ϣ��
	int pos;
	for (int i = 0; i < length; i++) {
		pos = a[i] % HT.divisor;
		while (HT.state[pos] == Active) {//�ҵ���һ����λ
			pos = (pos + 1) % HT.divisor;
		}
		HT.elem[pos].data = a[i];//���a[i]
		HT.elem[pos].pos = i;
		HT.state[pos] = Active;
	}
}
int FindPos(HashTable &HT, int x, int &i,int &orpos) {//���ҳɹ�  ����1�����򷵻�0 ����������-1
	cout << "��ϣ����ң�" << endl;
	int countcompare = 1;
	cout << x << endl;
	//������̽�鷨������ɢ�б�HT�йؼ�����xƥ���Ԫ��
	i = x % HT.divisor;
	if (HT.state[i] == Active &&HT.elem[i].data == x) {//�ҵ� ����1
		orpos = HT.elem[i].pos;
		cout << "�Ƚϴ�����" << countcompare<<endl;
		return 1;
	}
	else {
		int  j = i;
		do {
				countcompare++;
				if (HT.state[i] == Active && HT.elem[i].data == x) {
					orpos = HT.elem[i].pos;
					cout << "�Ƚϴ�����" <<countcompare<< endl;
					return 1;
				}
				else if (HT.state[i] != Active) {//��λ���ǿ�λ
					cout << "����ʧ��" << endl;
					orpos = -1;
					return 0;//�ҵ���λ ����0
				}
				i = (i + 1)%HT.m;
			} while (j != i);
		cout << "����ʧ��" << endl;
		orpos = -1;
		return -1;//תһȦ ������ ʧ��
	}
}
//��������
void InsertSort(SeqList &L) {
	SElemType temp;
	cout << "��������:" << endl;
	for (int k = 0; k < L.length; k++)cout << L.data[k] << " "; cout << endl;//��ʼ���
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
				L.data[j + 1] = L.data[j];//������
			}
			L.data[j + 1] = temp;
			//���
			for (int k = 0; k < L.length; k++)cout << L.data[k] << " ";
			cout << endl;
		}
	}
	cout << "�Ƚϴ�����" << countcompare << " ���ƶ�������" << countmove << endl<<endl;
}


//����
void Swap(SeqList &L, int i, int k) {
	SElemType temp = L.data[i];
	L.data[i] = L.data[k];
	L.data[k] = temp;
	//ÿ�ν������
	for (int m = 0; m < L.length; m++) {
		if (m == i || m == k)
			cout << L.data[m] << " ";
		else cout << "   ";
	}cout << endl;
}
void SelectSort(SeqList &L) {
	cout << "ѡ������" << endl;
	for (int k = 0; k < L.length; k++)cout << L.data[k] << " "; cout << endl;
	int  j, k; int countmove = 0, countcompare = 0;
	for (int i = 0; i < L.length - 1; i++) {
		k = i;
		for (j = i + 1; j < L.length; j++) {
			countcompare++;
			if (L.data[j] < L.data[k])k = j;//����СԪ��
		}
		if (i!=k) {
			Swap(L, i, k);//����
			countmove++;
		}
	}
	for (int k = 0; k < L.length; k++)cout << L.data[k] << " "; cout << endl;//��������
	cout << "�Ƚϴ�����" << countcompare << " ���ƶ�������" << countmove << endl << endl;
}
void BubbleSort(SeqList &L) {
	cout << "ð������" << endl;
	for (int k = 0; k < L.length; k++)cout << L.data[k] << " "; cout << endl;
	int exchange;
	int j, countmove = 0, countcompare = 0;
	for (int i = 0; i < L.length - 1; i++) {
		exchange = 0;
		for (j = L.length - 1; j >= i + 1; j--) {
			countcompare++;
			if (L.data[j - 1] > L.data[j]) {//���򽻻�Ԫ��
				Swap(L, j - 1, j);
				countmove++;
				exchange = 1;
			}
		}
		if (!exchange) {
			for (int k = 0; k < L.length; k++)cout << L.data[k] << " "; cout << endl;//��������
			cout << "�Ƚϴ�����" << countcompare << " ���ƶ�������" << countmove << endl << endl;
			return;//������������ֹͣ
		}
	}for (int k = 0; k < L.length; k++)cout << L.data[k] << " "; cout << endl;//��������
	cout << "�Ƚϴ�����" << countcompare << " ���ƶ�������" << countmove << endl << endl;
}
//ϣ������
void insertSort_gap(SeqList &L, int start, int gap,int &countcompare ,int &countmove) {
	SqElemType temp;
	int i, j;
	cout << "gap:" << gap << endl;//���ÿ�ε� gap
	for (i = start + gap; i <= L.length - 1; i = i + gap) {
		countcompare++;
		if (L.data[i - gap] > L.data[i]) {//����
			countmove++;
			temp = L.data[i]; j = i;
			do {
				L.data[j] = L.data[j - gap];
				j = j - gap;
			} while (j - gap > 0 && L.data[j - gap] > temp);
			L.data[j] = temp;
			//���
			for (int k = 0; k < L.length; k++)cout << L.data[k] << " ";
			cout << endl;
		}
	}
}
void ShellSort(SeqList &L, int d[], int m) {
	cout << "ϣ������" << endl;
	for (int k = 0; k < L.length; k++)cout << L.data[k] << " "; cout << endl;//��ʼ���
	//d[m]����������У�d[0]=1
	int i, start, gap; int countmove = 0, countcompare = 0;
	for (i = m - 1; i >= 0; i--) {//gap�ɺ���ǰ
		gap = d[i];
		for (start = 0; start < gap; start++) {//ֱ��d[0]=1ֹͣ����
			insertSort_gap(L, start, gap,countcompare,countmove);
		}
	}
	cout << "�Ƚϴ�����" << countcompare << " ���ƶ�������" << countmove << endl << endl;
	//for (int k = 0; k < L.length; k++)cout << L.data[k] << " "; cout << endl;//��������
}
//��������
int Partition(SeqList &L, int low, int high,int &countcompare ,int &countmove ) {
	int i, k = low; SqElemType pivot = L.data[low];//��׼Ԫ��
	for (i = low + 1; i <= high; i++) {//ɨ���������н��л���
		countcompare++;
		if (L.data[i] < pivot) {//С��pivot
			k++;
			if (k != i) {
				Swap(L, i, k);//����
				countmove++;
			}
		}
	}
	//countmove++;
	L.data[low] = L.data[k];//����׼Ԫ�ش��
	L.data[k] = pivot;
	return k;//���ػ�׼Ԫ��λ��
}
void QuickSort(SeqList &L, int left, int right,int &countcompare, int &countmove) {//���� QuickSort(L,0,L.length-1)
//��left��right����
	
	if (left < right) {
		int pivotpos = Partition(L, left, right,countcompare,countmove);//pivopos�ǻ���
		QuickSort(L, left, pivotpos - 1 , countcompare, countmove);
		QuickSort(L, pivotpos + 1, right, countcompare, countmove);
	}

}
void QuickSortV2(SeqList &L, int left, int right) {//Ϊ���������
	cout << "��������" << endl;
	int countcompare=0, countmove=0;
	for (int k = 0; k < L.length; k++)cout << L.data[k] << " "; cout << endl;//��ʼ���
	QuickSort(L, 0, L.length - 1, countcompare, countmove);
	for (int k = 0; k < L.length; k++)cout << L.data[k] << " "; cout << endl;//��������
	cout << "�Ƚϴ�����" << countcompare << " ���ƶ�������" << countmove << endl << endl;
}
void siftDown(SeqList &L,int start, int m, int &countcompare, int &countmove) {
	int i = start; 
	int j = i * 2 + 1;//j��i������Ů
	SqElemType temp = L.data[i];
	while (j <= m/*�����Ů�ڵ���Ƿ����λ��*/) {
		countcompare++;
		if (j < m&&L.data[j] < L.data[j + 1]) {//��jָ������Ů�нϴ�� �Ǹ�
			j++;
		}
		if (temp >= L.data[j]) {
			break;//����Ƚ� temp��������򲻵���
		}
		else {
			countmove++;
			L.data[i] = L.data[j];//��Ů�д�������
			i = j;//i�½�������Ůjλ��
			j = 2 * j + 1;
			
		}
	}
	//ÿ�ν������
	for (int m = 0; m < L.length; m++) {
		cout << L.data[m] << " ";
	}cout << endl;
	L.data[i] = temp;//temp�ݴ�Ԫ�طŵ�����λ��

}
void HeapSort(SeqList&L) {
	cout << "������" << endl;
	int countcompare = 0, countmove = 0;
	for (int k = 0; k < L.length; k++)cout << L.data[k] << " "; cout << endl;//��ʼ���
	int i;
	for (i = (L.length - 2) / 2; i >= 0; i--) {
		siftDown(L, i, L.length - 1,countcompare,countmove);
	}//����תΪ�����
	for (i = L.length - 1; i > 0; i--) {//�Դ��������
		SqElemType temp = L.data[0];
		L.data[0] = L.data[i];
		L.data[i] = temp;
		siftDown(L, 0, i - 1, countcompare, countmove);//���� �ؽ������
	}
	for (int k = 0; k < L.length; k++)cout << L.data[k] << " "; cout << endl;//��������
	cout << "�Ƚϴ�����" << countcompare << " ���ƶ�������" << countmove << endl << endl;
}
void getLfromA(SeqList &L, int A[], int m) {//������A�õ�˳���L
	for (int i = 0; i < m; i++) {
		L.data[i] = A[i];
	}
	L.length = m;
}