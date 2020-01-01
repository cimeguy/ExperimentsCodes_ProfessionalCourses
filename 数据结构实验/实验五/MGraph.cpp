#include<iostream>
#include "headers.h"
#include<sstream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
int getVertexPos (MGraph G, Gtype u ){  //���u��λ��,����ʧ�ܼ������ڷ���-1
	for (int i = 0; i < G.NumVertices; i++)
		if (G.Vertices[i] == u)return i;
	return -1;
}
int getNumVertices(MGraph G) {
	return G.NumVertices;
}//��ö������
int getNumEdges(MGraph G) {
	return G.NumEdges;
}//��ñߵĸ���
bool hasEdge(MGraph G, Gtype u, Gtype v) {
	int pos1 = getVertexPos(G, u);
	int pos2 = getVertexPos(G, v);
	if (pos1 != -1 && pos2 != -1) {
		return (G.Edges[pos1][pos2].time == MaxWeight) ? false : true;//maxWeight Ϊ���� ��û�б�
	}
	return false;
}
bool addVertex(MGraph &G, Gtype u) {//���Ӷ���
	int pos = getVertexPos(G, u);
	if (pos = -1) {
		G.Vertices[G.NumVertices] = u;
		G.NumVertices++;
		for (int j = 0; j < G.NumVertices-1; j++) {
			G.Edges[j][G.NumVertices - 1].time = G.Edges[j][G.NumVertices - 1].money =  MaxWeight;
			G.Edges[G.NumVertices - 1][j].time = G.Edges[G.NumVertices - 1][j].money = MaxWeight;
		}
	
		return true;
	}
	return false;
}
bool  addEdge(MGraph &G, Gtype u, Gtype v, int time, int money) {//���ӱ�
	if (!hasEdge(G, u, v)) {//û�б�
		int pos1 = getVertexPos(G, u);
		int pos2 = getVertexPos(G, v);
		if (pos1 != -1 && pos2 != -1) {//�е�
			G.Edges[pos1][pos2].time = time;
			G.Edges[pos1][pos2].money = money;
			G.NumEdges++;
			return true;
		}
		else return false;//û�е�
	}
	return false;

}
bool removeEdge(MGraph &G, Gtype u, Gtype v) {//ɾ����

	if (!hasEdge(G, u, v)) return false;
	int pos1 = getVertexPos(G, u);
	int pos2 = getVertexPos(G, v);
	if (pos1 != -1 && pos2 != -1) {//�е�
		G.Edges[pos1][pos2].time = MaxWeight;
		G.Edges[pos1][pos2].money = MaxWeight;
		G.NumEdges--;
		return true;
	}
	else return false;
}
void CreatMGraph(MGraph &G/*,int MaxVertices*/) {  //����ͼ  //�����ʽ�ο�test_graph.txt  �����ǵ����ַ����ԡ�#�����������ԡ������������ԡ�#������
	char cintype;
	cout << "���ն�����(z)���ߴ��ļ���ȡ(t)��" << endl;
	cin >> cintype;
	G.NumEdges=G.NumVertices = 0;//��ʼ��
	if (cintype == 't' || cintype == 'T') {//�ļ���ȡ 
		cout << "��test_graph.txt�ļ���ȡ" << endl;
		string s, inputresult;
		vector<string> vec_s;
		ifstream fin("../ͼ�����ļ���/test_graph.txt");
		if (!fin)exit(-1);
		while (getline(fin, s)) {
			stringstream input(s);
			while (input >> inputresult) {
				vec_s.push_back(inputresult);
			}
		}
		for (unsigned i = 0; i < vec_s.size(); i++) {  //����
			if (vec_s[i][0] == '#')break;
			if (vec_s[i][0] == ';')continue;
			if (vec_s[i][0] >= 'A'&&vec_s[i][0] <= 'Z') {
				G.Vertices[i] = vec_s[i][0];
				G.NumVertices++;
			}
		}
		for(int i = 0; i < G.NumVertices; i++){
			for (int j = 0; j < G.NumVertices; j++) {
				G.Edges[i][j].time = (i == j) ? 0 : MaxWeight;//�Խ���Ϊ0������Ϊ����󣬼�MaxWeight
				G.Edges[i][j].money = (i == j) ? 0 : MaxWeight;
			}
		}//��ʼ����
		
		for (unsigned i = G.NumVertices; i < vec_s.size(); i++) {
			if (vec_s[i][0] >= 'A'&&vec_s[i][0] <= 'Z'&&vec_s[i + 1][0]>'A'&&vec_s[i + 1][0]<'Z') {
				char u = vec_s[i][0], v= vec_s[i + 1][0];
				int pos1 =getVertexPos(G, u), pos2 = getVertexPos(G, v);
				if (pos1!=-1 &&pos2 !=-1) {//����u��v
					G.Edges[pos1][pos2].time = atoi(vec_s[i + 2].c_str());
					G.Edges[pos1][pos2].money = atoi(vec_s[i + 3].c_str());
					G.NumEdges++;
				}
				else {
					cout << "�������" << endl;
				}
			}
		}
	}
	else { //�ն�����
		cout << "�����붥�����У�������Ϊ�����ַ�����'#'������" << endl;
		Gtype u;//��������data
		int countv = 0;//���㶥�����
		while (cin >> u) {//ѭ������ 
			if (u == '#')break;
			else {
				G.Vertices[countv++] =u;
				G.NumVertices++;
			}
		}
		for (int i = 0; i < G.NumVertices; i++) {
			for (int j = 0; j < G.NumVertices; j++) {
				G.Edges[i][j].time = (i == j) ? 0 : MaxWeight;
				G.Edges[i][j].money = (i == j) ? 0 : MaxWeight;
			}
		}//��ʼ����
		for (int i = 0; i < G.NumVertices; i++)cout << G.Vertices[i];//�鿴�Ѵ��ڵĶ���
		cout << "����������У��������ۣ�����ʽΪA B 20 30 ; A C 30 40 ; # (�ԡ�#����������һ����Ϊʱ����� ���ڶ�������Ϊ�÷Ѵ���)" << endl;
		while (1) {
			Gtype u, v;
			cin >> u;// cout << node1;
			if (u == '#') break; if (u == ';')continue;
			//cout << "�����յ�" << endl;
			cin >> v;// cout << node2 << endl;
			int pos1 = getVertexPos(G, u), pos2 = getVertexPos(G, v);
			if ( pos1!=-1&&pos2!=-1 ) {
				int time, money;
				cin >> time >> money;
				G.Edges[pos1][pos2].time = time;
				G.Edges[pos1][pos2].money = money;
				G.NumEdges++;
			}
			else cout << "�������" << endl;
		}
	}
}
void Floyd(MGraph &G, Weight a[][MaxVertices], int timepath[][MaxVertices],int moneypath[][MaxVertices]) {
	for (int i = 0; i < G.NumVertices; i++) {//��ʼ��
		for (int j = 0; j < G.NumVertices; j++) {
			a[i][j] = G.Edges[i][j];
			if (i != j &&a[i][j].time < MaxWeight)timepath[i][j] = moneypath[i][j]=i;
			else timepath[i][j]= moneypath[i][j] = -1;
		}
	}
	for (int k = 0;k<G.NumVertices ;k++)
		for (int i = 0; i < G.NumVertices; i++) {
			for (int j = 0; j < G.NumVertices; j++) {
				if (a[i][k].time + a[k][j].time < a[i][j].time) {//���ʱ��
					a[i][j].time = a[i][k].time + a[k][j].time;
					timepath[i][j] = timepath[k][j];
				}
				if (a[i][k].money + a[k][j].money < a[i][j].money) {//���ٷ���
					a[i][j].money = a[i][k].money + a[k][j].money;
					moneypath[i][j] = moneypath[k][j];
				}
			}
		}
}
void miniTransfer(MGraph G, int a[][MaxVertices], int path[][MaxVertices]) {//�õ���ת�������ٵ�·��
	//����˼·��1.���� 2.������Ȩֵ����1���������·��  �����ǵڶ���
	for (int i = 0; i < G.NumVertices; i++) {//��ʼ��
		for (int j = 0; j < G.NumVertices; j++) {
			if (G.Edges[i][j].time == 0)a[i][j] = 0;
			else if (G.Edges[i][j].time == MaxWeight)a[i][j] = MaxWeight;
			else a[i][j] = 1;
			if (i != j && G.Edges[i][j].time < MaxWeight)path[i][j] = i;
			else path[i][j] = -1;
		}
	}
	for (int k = 0; k<G.NumVertices; k++)
		for (int i = 0; i < G.NumVertices; i++) {
			for (int j = 0; j < G.NumVertices; j++) {
				if (a[i][k] + a[k][j] < a[i][j]) {//��ת��������
					a[i][j] = a[i][k] + a[k][j];
					path[i][j] = path[k][j];
				}
				
			}
		}
}
void printPath(MGraph &G, int u, int v, Weight a[][MaxVertices], int timepath[][MaxVertices], int moneypath[][MaxVertices], int transferpath[][MaxVertices]) {
	Gtype x = G.Vertices[u], y = G.Vertices[v];
	if (moneypath[u][v] == -1 || timepath[u][v] == -1) {
		cout << x << "��" << y << "��·��" << endl;
		return;
	}
	cout << "��" << x << "��" << y << "ʱ������·��Ϊ:";
	int S1[MaxVertices]/*�洢·��*/, pre_ver1 = timepath[u][v]/*ǰһ��·��*/, k1 = 0/*S���*/;
	while (pre_ver1 != u) {
		S1[k1++] = pre_ver1;
		pre_ver1 = timepath[u][pre_ver1];
	}
	S1[k1++] = u;
	while (k1 > 0) {
		cout << G.Vertices[S1[--k1]] << "->";
	}cout << y << endl << "�������ʱ��Ϊ:" << a[u][v].time << endl << endl;

	cout << "��" << x << "��" << y << "�������ٵ�·��Ϊ:";
	int S2[MaxVertices]/*�洢·��*/, pre_ver2 = moneypath[u][v]/*ǰһ��·��*/, k2 = 0/*S���*/;
	while (pre_ver2 != u) {
		S2[k2++] = pre_ver2;
		pre_ver2 = moneypath[u][pre_ver2];
	}
	S2[k2++] = u;
	while (k2 > 0) {
		cout << G.Vertices[S2[--k2]] << "->";
	}cout << y << endl << "���ٷ���Ϊ:" << a[u][v].money << endl << endl;

	cout << "��" << x << "��" << y << "��ת�������ٵ�·��Ϊ:";
	int S3[MaxVertices]/*�洢·��*/, pre_ver3 = transferpath[u][v]/*ǰһ��·��*/, k3 = 0/*S���*/;
	while (pre_ver3 != u) {
		S3[k3++] = pre_ver3;
		pre_ver3 = transferpath[u][pre_ver3];
	}
	S3[k3++] = u;
	int numtransfer = k3;
	while (k3 > 0) {
		cout << G.Vertices[S3[--k3]] << "->";
	}cout << y << endl << "������ת����Ϊ��" << numtransfer - 1 << endl;
	cout << "----------------" << endl << endl;

}
void menu(MGraph G){
	while (1) {
		cout << "�����������յ㣺���� A B ��" << endl;
		char x, y;
		cin >> x >> y;
		int u, v;
		u = getVertexPos(G, x);
		v = getVertexPos(G, y);
		if (u == -1) { cout << "��㲻����" << endl; continue; }
		if (v == -1) { cout << "�յ㲻����"<<endl; continue; }
		Weight a[MaxVertices][MaxVertices]; int  b[MaxVertices][MaxVertices];
		int timepath[MaxVertices][MaxVertices], moneypath[MaxVertices][MaxVertices], transferpath[MaxVertices][MaxVertices];
		Floyd(G, a, timepath, moneypath);
		miniTransfer(G, b, transferpath);
		printPath(G, u, v, a, timepath, moneypath, transferpath);

	}
}