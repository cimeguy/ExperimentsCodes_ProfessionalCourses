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

void menu() {//菜单界面
	cout << endl;
	cout << "┌──────── 哈夫曼编译系统────────┐" << endl;
	cout<<  "│           I：初始化           │"<<endl;
	cout << "│           E：编码             │" << endl;
	cout << "│           D：译码             │" << endl;
	cout << "│      P：打印编码后的文件      │" << endl;
	cout << "│        T：打印Huffman树       │" << endl;
	cout << "│           Q：退出             │" << endl;
	cout << "└───────────────────────────────┘" << endl;
	cout << endl;
}
void Huffman_operate() {
	char input;
	HFTree HT;
	while (1) {//不断循环
		menu();
		cin >> input; 
		bool quit = false;
		switch (input) {//不区分大小写
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
void creatHFTree(HFTree & HT,HuElemType value []/*数据value[n]*/,int fr[]/*相应权值fr[n]*/,int n){
	int i, k, s1/*最小值点*/, s2/*次小值点*/;
	int min1/*最小值*/, min2/*次小值*/;
	
	for (i = 0; i < n; i++) { //所有外结点赋值
		HT.elem[i].data = value[i];
		HT.elem[i].weight = fr[i];
	}
	for (i = 0; i < totalnumber; i++) { //所有指针置空  //！！所有都置空
		HT.elem[i].parent = HT.elem[i].lchild = HT.elem[i].rchild = -1;
	}
	for (i = n; i < 2 * n - 1; i++) {//构造哈夫曼树的过程
		min1 = min2 = maxWeight;
		s1 = s2 = 0;
		for (k = 0; k < i; k++) {
			if (HT.elem[k].parent == -1) {//未变成其他树的子树
				if (HT.elem[k].weight <= min1) {//最小变成次小
					min2 = min1; min1 = HT.elem[k].weight;
					s2 = s1; s1 = k;
				}
				else if (HT.elem[k].weight <= min2) {//新次小
					min2 = HT.elem[k].weight;
					s2 = k;
				}
			}
		}
		HT.elem[s1].parent = HT.elem[s2].parent = i;//构造子树
		HT.elem[i].lchild = s1;
		HT.elem[i].rchild = s2;
		HT.elem[i].weight = HT.elem[s1].weight + HT.elem[s2].weight;
	}
	HT.num = n; HT.root = 2 * n - 2;
	for (i = n; i < 2 * n - 1; i++) {   //如果没有data就赋值‘#’
		HT.elem[i].data = '#';
	}
}
void Init(HFTree &HT) {
	string line_info, input_result,path/*文件路径*/;
	vector<string> vec_s;
	vector<int> w;
	vector<char>c;
	char value[100];
	int fr[100];
	int n, a;
	cout << "请选择打开哪个测试文件，test1.txt 或者 test2.txt : ";
	cin >> a; 

	if (a == 1) path ="../哈夫曼树调用文件集/test1.txt";
	else if(a==2) path = "../哈夫曼树调用文件集/test2.txt";
	else {
		cout << "不存在该文件" << endl;
	}

	ifstream fin(path);
	if (!fin)exit(1);
	else {
		while (getline(fin, line_info)) {//读取一行
			stringstream input(line_info);
			while (input >> input_result)
				vec_s.push_back(input_result);//vec_s按空格分开
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
			if (tempf >= 1) {//大于1 则表示权值
				tempi = atoi(vec_s[j].c_str());
			}
			else {//不大于1，频率 权值等于频率*100
				tempi = int(tempf * 100);
			}
			w.push_back(tempi);
		}
	}
	if (c.size() == 0) {//无data即value
		for (unsigned int i = 0; i < w.size(); i++)value[i] = '#';
	}
	else if(c.size() ==w.size()-1) {  //包含空格
		value[0] = ' ';
		for (unsigned int i = 1; i < c.size()+1; i++) {
			value[i] = c[i-1];
		}
	}
	else {//无空格
		for (unsigned int i = 0; i < c.size(); i++) {
			value[i] = c[i ];
		}
	}
	for (unsigned int i = 0; i < w.size(); i++) {
		fr[i] = w[i];
	//cout << value[i ] << " " << fr[i] << endl;
	}
	/*for (int i = 0;i<c.size(); i++) {//查看数据
		cout << value[i] << " " << fr[i] << endl;
	}*/
	std::cout << "从文件中导入数据成功。" ;
	n = w.size();
	creatHFTree(HT, value, fr, n);//创建哈夫曼树
	ofstream fout("../哈夫曼树输出文件集/HuffTree.txt");
	fout <<"num:" <<HT.num <<" root:"<< HT.root << endl;
	fout << "下标" << " data weight parent lchild rchild" << endl;
	for (int i = 0; i <=HT.root; i++) {
		fout <<i<<"     "<< HT.elem[i].data << "         " << HT.elem[i].weight <<"     "<< HT.elem[i].parent<<"     " << HT.elem[i].lchild <<"      "<< HT.elem[i].rchild << endl;
		//cout << i << " " << HT.elem[i].weight << " " << HT.elem[i].parent << " " << HT.elem[i].lchild << " " << HT.elem[i].rchild << endl;
	}
	fin.close();
	fout.close();
	cout << " Huffman 树以表格形式存于文件 HuffTree.txt中 " << endl;
}
void Huffcode(HFTree HT, vector<string>&code,vector<string>&Data) {//哈夫曼编码
	//-------------哈夫曼编码-------------//
	code.clear();
	Data.clear();
	char e;
	for (int i = 0; i < HT.root+1; i++) {//对每一个叶节点  ;如果只对叶子节点编码则 i<HT.num
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
		//cout << HT.elem[i].data<<' '<<temp<<endl;//输出查看各个字母的编码
		string data = "";
		data += HT.elem[i].data;
		Data.push_back(data);
	}
}
void Encoding(HFTree HT) {
	vector<string>code;
	vector<string>Data;
	Huffcode(HT,code,Data);//编码
	ifstream fincode("../哈夫曼树调用文件集/ToBeTran.txt");
	string line_info,input_result;
	vector<string>vec_s;
	if (!fincode)exit(1);
	else {
		while (getline(fincode, line_info)) {//读取一行
			stringstream input(line_info);
			while (input >> input_result)
				vec_s.push_back(input_result);//vec_s按空格分开
		}
	}
	cout << "从 ToBeTran.txt 中读取数据，进行编码" << endl;
	vector<string>codefi;
	ofstream foutcode("../哈夫曼树输出文件集/CodedFile.txt");
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
	cout << "编码结束，结果保存在 CodedFile.txt 中" << endl;

}
void Decoding(HFTree HT) {
	ifstream findecode("../哈夫曼树输出文件集/CodedFile.txt");
	string line_info, input_result;
	vector<string>vec_s;
	if (!findecode)exit(1);
	else {
		while (getline(findecode, line_info)) {//读取一行
			stringstream input(line_info);
			while (input >> input_result)
				vec_s.push_back(input_result);//vec_s按空格分开
		}
	}
	cout << "从 CodedFile.txt 中读取数据 ，进行译码" << endl;
	ofstream fout("../哈夫曼树输出文件集/PlainFile.txt");
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
	cout << "译码结束，译码结果保存到 PlainFile.txt" << endl;
}
void Print(){
	ifstream fin("../哈夫曼树输出文件集/CodedFile.txt");
	string line_info, input_result;
	vector<string>vec_s;
	if (!fin)exit(1);
	else {
		while (getline(fin, line_info)) {//读取一行
			stringstream input(line_info);
			while (input >> input_result) {
				vec_s.push_back(input_result);//vec_s按空格分开
			}
		}
	}cout << "从 CodedFile.txt 中读取数据 ，打印数据：" << endl;
	ofstream fout("../哈夫曼树输出文件集/CodedPrint.txt");
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

	cout<< "代码文件已存入CodedPrint.txt文件中" <<endl;
}
void TreePrinting(HFTree HT) {//类似于先根遍历，根据每个节点字符的哈夫曼编码来输出，横向来看 0的位置有竖线│，1的位置是空格；或者也可以直接先根遍历时输出，以下代码为第一种方法
	cout << endl;
	int key;
	vector<string>Code;
	vector<string>Data;
	Huffcode(HT, Code, Data);//编码
	key = HT.root;
	int top = -1;
	int count = -1;
	HTNode S[20];
	ofstream fout("../哈夫曼树输出文件集/TreePrint.txt");
	//int SK[20];

	do {
		while (key != -1) {
			string s2 = "";
			if (key == HT.elem[HT.elem[key].parent].lchild) 
				s2 = "├── ";
			else  
				s2 = "└── ";
			for (unsigned int i=0; i < Code[key].size()&& Code[key].size() - 1 != i; i++) {//不能直接写i<Code[key].size()-1会报错
				if (Code[key].size()==1)break;
				if (Code[key][i] == '1') {
					cout << "    "; 
					fout<< "    ";
				}
				else if (Code[key][i] == '0') {
					cout << "│   ";
					fout<< "│   ";
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




