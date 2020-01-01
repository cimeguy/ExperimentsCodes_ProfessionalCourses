#include <iostream>
#include "Huffman.h"
#include "headers.h"
#include "Sqstack.h"
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include<string>
#include<vector>
using namespace std;
#define maxWeight 32767

void menu() {//�˵�����
	cout << endl;
	cout << "������������������ ����������ϵͳ������������������" << endl;
	cout<<  "��           I����ʼ��           ��"<<endl;
	cout << "��           E������             ��" << endl;
	cout << "��           D������             ��" << endl;
	cout << "��      P����ӡ�������ļ�      ��" << endl;
	cout << "��        T����ӡHuffman��       ��" << endl;
	cout << "��           Q���˳�             ��" << endl;
	cout << "������������������������������������������������������������������" << endl;
	cout << endl;
}
void Huffman_operate() {
	char input;
	HFTree HT;
	while (1) {//����ѭ��
		menu();
		cin >> input; 
		bool quit = false;
		switch (input) {//�����ִ�Сд
			case 'I':
			case 'i':
				Init(HT); break;
			case 'E':
			case 'e':
				Encoding(HT); break;
			case'D':
			case'd':
				Decoding(HT); break;
			case'P':
			case'p':
				Print(); break;
			case'T':
			case't':
				TreePrinting(HT); break;
			case'Q':
			case'q':
				quit = true; break;
			default:break;
		}
		if (quit)break;
	}
}
void creatHFTree(HFTree & HT,HuElemType value []/*����value[n]*/,int fr[]/*��ӦȨֵfr[n]*/,int n){
	int i, k, s1/*��Сֵ��*/, s2/*��Сֵ��*/;
	int min1/*��Сֵ*/, min2/*��Сֵ*/;
	
	for (i = 0; i < n; i++) { //�������㸳ֵ
		HT.elem[i].data = value[i];
		HT.elem[i].weight = fr[i];
	}
	for (i = 0; i < totalnumber; i++) { //����ָ���ÿ�  //�������ж��ÿ�
		HT.elem[i].parent = HT.elem[i].lchild = HT.elem[i].rchild = -1;
	}
	for (i = n; i < 2 * n - 1; i++) {//������������Ĺ���
		min1 = min2 = maxWeight;
		s1 = s2 = 0;
		for (k = 0; k < i; k++) {
			if (HT.elem[k].parent == -1) {//δ���������������
				if (HT.elem[k].weight <= min1) {//��С��ɴ�С
					min2 = min1; min1 = HT.elem[k].weight;
					s2 = s1; s1 = k;
				}
				else if (HT.elem[k].weight <= min2) {//�´�С
					min2 = HT.elem[k].weight;
					s2 = k;
				}
			}
		}
		HT.elem[s1].parent = HT.elem[s2].parent = i;//��������
		HT.elem[i].lchild = s1;
		HT.elem[i].rchild = s2;
		HT.elem[i].weight = HT.elem[s1].weight + HT.elem[s2].weight;
	}
	HT.num = n; HT.root = 2 * n - 2;
	for (i = n; i < 2 * n - 1; i++) {   //���û��data�͸�ֵ��#��
		HT.elem[i].data = '#';
	}
}
void Init(HFTree &HT) {
	string line_info, input_result,path/*�ļ�·��*/;
	vector<string> vec_s;
	vector<int> w;
	vector<char>c;
	char value[100];
	int fr[100];
	int n, a;
	cout << "��ѡ����ĸ������ļ���test1.txt ���� test2.txt : ";
	cin >> a; 

	if (a == 1) path ="../�������������ļ���/test1.txt";
	else if(a==2) path = "../�������������ļ���/test2.txt";
	else {
		cout << "�����ڸ��ļ�" << endl;
	}

	ifstream fin(path);
	if (!fin)exit(1);
	else {
		while (getline(fin, line_info)) {//��ȡһ��
			stringstream input(line_info);
			while (input >> input_result)
				vec_s.push_back(input_result);//vec_s���ո�ֿ�
		}
	}
	for (unsigned int j = 0; j< vec_s.size(); j++) {
		if (vec_s[j][0] >= 'A' && vec_s[j][0] <= 'Z') {
			c.push_back(vec_s[j][0]);
		}
		else {
			int tempi;
			double tempf;
			tempf = atof(vec_s[j].c_str());
			if (tempf >= 1) {//����1 ���ʾȨֵ
				tempi = atoi(vec_s[j].c_str());
			}
			else {//������1��Ƶ�� Ȩֵ����Ƶ��*100
				tempi = int(tempf * 100);
			}
			w.push_back(tempi);
		}
	}
	if (c.size() == 0) {//��data��value
		for (unsigned int i = 0; i < w.size(); i++)value[i] = '#';
	}
	else if(c.size() ==w.size()-1) {  //�����ո�
		value[0] = ' ';
		for (unsigned int i = 1; i < c.size()+1; i++) {
			value[i] = c[i-1];
		}
	}
	else {//�޿ո�
		for (unsigned int i = 0; i < c.size(); i++) {
			value[i] = c[i ];
		}
	}
	for (unsigned int i = 0; i < w.size(); i++) {
		fr[i] = w[i];
	//cout << value[i ] << " " << fr[i] << endl;
	}
	/*for (int i = 0;i<c.size(); i++) {//�鿴����
		cout << value[i] << " " << fr[i] << endl;
	}*/
	std::cout << "���ļ��е������ݳɹ���" ;
	n = w.size();
	creatHFTree(HT, value, fr, n);//������������
	ofstream fout("../������������ļ���/HuffTree.txt");
	fout <<"num:" <<HT.num <<" root:"<< HT.root << endl;
	fout << "�±�" << " data weight parent lchild rchild" << endl;
	for (int i = 0; i <=HT.root; i++) {
		fout <<i<<"     "<< HT.elem[i].data << "         " << HT.elem[i].weight <<"     "<< HT.elem[i].parent<<"     " << HT.elem[i].lchild <<"      "<< HT.elem[i].rchild << endl;
		//cout << i << " " << HT.elem[i].weight << " " << HT.elem[i].parent << " " << HT.elem[i].lchild << " " << HT.elem[i].rchild << endl;
	}
	fin.close();
	fout.close();
	cout << " Huffman ���Ա����ʽ�����ļ� HuffTree.txt�� " << endl;
}
void Huffcode(HFTree HT, vector<string>&code,vector<string>&Data) {//����������
	//-------------����������-------------//
	code.clear();
	Data.clear();
	char e;
	for (int i = 0; i < HT.root+1; i++) {//��ÿһ��Ҷ�ڵ�  ;���ֻ��Ҷ�ӽڵ������ i<HT.num
		int j = i;
		string temp = "";
		SqStack S;
		InitSqStack(S);
		while (j != HT.root) {
			int parent = HT.elem[j].parent;
			if (HT.elem[parent].lchild == j) Push(S, '0');
			if (HT.elem[parent].rchild == j) Push(S, '1');
			j = parent;
		}
		while (!SqStackEmpty(S)) {
			Pop(S, e);
			temp += e;
		}
		code.push_back(temp);
		//cout << HT.elem[i].data<<' '<<temp<<endl;//����鿴������ĸ�ı���
		string data = "";
		data += HT.elem[i].data;
		Data.push_back(data);
	}
}
void Encoding(HFTree HT) {
	vector<string>code;
	vector<string>Data;
	Huffcode(HT,code,Data);//����
	ifstream fincode("../�������������ļ���/ToBeTran.txt");
	string line_info,input_result;
	vector<string>vec_s;
	if (!fincode)exit(1);
	else {
		while (getline(fincode, line_info)) {//��ȡһ��
			stringstream input(line_info);
			while (input >> input_result)
				vec_s.push_back(input_result);//vec_s���ո�ֿ�
		}
	}
	cout << "�� ToBeTran.txt �ж�ȡ���ݣ����б���" << endl;
	vector<string>codefi;
	ofstream foutcode("../������������ļ���/CodedFile.txt");
	for (unsigned int i = 0; i < vec_s.size(); i++) {
		for (unsigned int j = 0; j < vec_s[i].size(); j++) {
			string s = "";
			s += vec_s[i][j];
			for (int k =0; k < HT.num;k++) {
				if (s == Data[k]) {
					foutcode << code[k];
				}
			}
		}
		foutcode << code[0];
	}
	fincode.close();
	foutcode.close();
	cout << "������������������ CodedFile.txt ��" << endl;

}
void Decoding(HFTree HT) {
	ifstream findecode("../������������ļ���/CodedFile.txt");
	string line_info, input_result;
	vector<string>vec_s;
	if (!findecode)exit(1);
	else {
		while (getline(findecode, line_info)) {//��ȡһ��
			stringstream input(line_info);
			while (input >> input_result)
				vec_s.push_back(input_result);//vec_s���ո�ֿ�
		}
	}
	cout << "�� CodedFile.txt �ж�ȡ���� ����������" << endl;
	ofstream fout("../������������ļ���/PlainFile.txt");
	for (unsigned int i = 0; i < vec_s.size(); i++) {
		int key = HT.root;
		for (unsigned int j = 0; j < vec_s[i].size(); j++) {
			if (vec_s[i][j] =='0') 
				key = HT.elem[key].lchild;
			else if(vec_s[i][j] == '1')
				key = HT.elem[key].rchild;
			if (key < HT.num) {
				fout << HT.elem[key].data;
				key = HT.root;
			}
		}
		//fout << " ";
	}
	fout.close();
	cout << "������������������浽 PlainFile.txt" << endl;
}
void Print(){
	ifstream fin("../������������ļ���/CodedFile.txt");
	string line_info, input_result;
	vector<string>vec_s;
	if (!fin)exit(1);
	else {
		while (getline(fin, line_info)) {//��ȡһ��
			stringstream input(line_info);
			while (input >> input_result) {
				vec_s.push_back(input_result);//vec_s���ո�ֿ�
			}
		}
	}cout << "�� CodedFile.txt �ж�ȡ���� ����ӡ���ݣ�" << endl;
	ofstream fout("../������������ļ���/CodedPrint.txt");
	int count = 0;
	for (unsigned int i = 0; i < vec_s.size(); i++) {
		for (unsigned int j = 0; j < vec_s[i].size(); j++) {
			cout << vec_s[i][j];
			fout << vec_s[i][j];
			count++;
			if (count == 50) {
				count = 0;
				cout << endl;
				fout << endl;
			}
		}
	}cout << endl;

	cout<< "�����ļ��Ѵ���CodedPrint.txt�ļ���" <<endl;
}
void TreePrinting(HFTree HT) {//�������ȸ�����������ÿ���ڵ��ַ��Ĺ������������������������ 0��λ�������ߩ���1��λ���ǿո񣻻���Ҳ����ֱ���ȸ�����ʱ��������´���Ϊ��һ�ַ���
	cout << endl;
	int key;
	vector<string>Code;
	vector<string>Data;
	Huffcode(HT, Code, Data);//����
	key = HT.root;
	int top = -1;
	int count = -1;
	HTNode S[20];
	ofstream fout("../������������ļ���/TreePrint.txt");
	//int SK[20];

	do {
		while (key != -1) {
			string s2 = "";
			if (key == HT.elem[HT.elem[key].parent].lchild) 
				s2 = "������ ";
			else  
				s2 = "������ ";
			for (unsigned int i=0; i < Code[key].size()&& Code[key].size() - 1 != i; i++) {//����ֱ��дi<Code[key].size()-1�ᱨ��
				if (Code[key].size()==1)break;
				if (Code[key][i] == '1') {
					cout << "    "; 
					fout<< "    ";
				}
				else if (Code[key][i] == '0') {
					cout << "��   ";
					fout<< "��   ";
				}
			}
			if (key == HT.root) cout <<"root(" << HT.elem[key].weight << ")" << endl;
			else {
				cout << s2 << HT.elem[key].data << "(" << HT.elem[key].weight << ")" << endl;
				fout << s2 << HT.elem[key].data << "(" << HT.elem[key].weight << ")" << endl;
			}
			S[++top] = HT.elem[key];
			key = HT.elem[key].lchild;
		}
		if (top > -1) {
			key = S[top--].rchild;
		}
	} while (key!=-1|| top > -1);
	fout.close();
}




