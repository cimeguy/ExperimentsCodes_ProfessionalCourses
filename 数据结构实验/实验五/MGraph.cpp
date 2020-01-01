#include<iostream>
#include "headers.h"
#include<sstream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
int getVertexPos (MGraph G, Gtype u ){  //获得u的位置,查找失败即不存在返回-1
	for (int i = 0; i < G.NumVertices; i++)
		if (G.Vertices[i] == u)return i;
	return -1;
}
int getNumVertices(MGraph G) {
	return G.NumVertices;
}//获得顶点个数
int getNumEdges(MGraph G) {
	return G.NumEdges;
}//获得边的个数
bool hasEdge(MGraph G, Gtype u, Gtype v) {
	int pos1 = getVertexPos(G, u);
	int pos2 = getVertexPos(G, v);
	if (pos1 != -1 && pos2 != -1) {
		return (G.Edges[pos1][pos2].time == MaxWeight) ? false : true;//maxWeight 为无穷 即没有边
	}
	return false;
}
bool addVertex(MGraph &G, Gtype u) {//增加顶点
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
bool  addEdge(MGraph &G, Gtype u, Gtype v, int time, int money) {//增加边
	if (!hasEdge(G, u, v)) {//没有边
		int pos1 = getVertexPos(G, u);
		int pos2 = getVertexPos(G, v);
		if (pos1 != -1 && pos2 != -1) {//有点
			G.Edges[pos1][pos2].time = time;
			G.Edges[pos1][pos2].money = money;
			G.NumEdges++;
			return true;
		}
		else return false;//没有点
	}
	return false;

}
bool removeEdge(MGraph &G, Gtype u, Gtype v) {//删除边

	if (!hasEdge(G, u, v)) return false;
	int pos1 = getVertexPos(G, u);
	int pos2 = getVertexPos(G, v);
	if (pos1 != -1 && pos2 != -1) {//有点
		G.Edges[pos1][pos2].time = MaxWeight;
		G.Edges[pos1][pos2].money = MaxWeight;
		G.NumEdges--;
		return true;
	}
	else return false;
}
void CreatMGraph(MGraph &G/*,int MaxVertices*/) {  //有向图  //输入格式参考test_graph.txt  顶点是单个字符，以‘#’结束，边以‘；’隔开，以‘#’结束
	char cintype;
	cout << "从终端输入(z)或者从文件读取(t)：" << endl;
	cin >> cintype;
	G.NumEdges=G.NumVertices = 0;//初始化
	if (cintype == 't' || cintype == 'T') {//文件读取 
		cout << "从test_graph.txt文件读取" << endl;
		string s, inputresult;
		vector<string> vec_s;
		ifstream fin("../图输入文件集/test_graph.txt");
		if (!fin)exit(-1);
		while (getline(fin, s)) {
			stringstream input(s);
			while (input >> inputresult) {
				vec_s.push_back(inputresult);
			}
		}
		for (unsigned i = 0; i < vec_s.size(); i++) {  //顶点
			if (vec_s[i][0] == '#')break;
			if (vec_s[i][0] == ';')continue;
			if (vec_s[i][0] >= 'A'&&vec_s[i][0] <= 'Z') {
				G.Vertices[i] = vec_s[i][0];
				G.NumVertices++;
			}
		}
		for(int i = 0; i < G.NumVertices; i++){
			for (int j = 0; j < G.NumVertices; j++) {
				G.Edges[i][j].time = (i == j) ? 0 : MaxWeight;//对角线为0，否则为无穷大，即MaxWeight
				G.Edges[i][j].money = (i == j) ? 0 : MaxWeight;
			}
		}//初始化边
		
		for (unsigned i = G.NumVertices; i < vec_s.size(); i++) {
			if (vec_s[i][0] >= 'A'&&vec_s[i][0] <= 'Z'&&vec_s[i + 1][0]>'A'&&vec_s[i + 1][0]<'Z') {
				char u = vec_s[i][0], v= vec_s[i + 1][0];
				int pos1 =getVertexPos(G, u), pos2 = getVertexPos(G, v);
				if (pos1!=-1 &&pos2 !=-1) {//存在u和v
					G.Edges[pos1][pos2].time = atoi(vec_s[i + 2].c_str());
					G.Edges[pos1][pos2].money = atoi(vec_s[i + 3].c_str());
					G.NumEdges++;
				}
				else {
					cout << "顶点错误" << endl;
				}
			}
		}
	}
	else { //终端输入
		cout << "请输入顶点序列：（顶点为单个字符，以'#'结束）" << endl;
		Gtype u;//顶点名字data
		int countv = 0;//计算顶点个数
		while (cin >> u) {//循环输入 
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
		}//初始化边
		for (int i = 0; i < G.NumVertices; i++)cout << G.Vertices[i];//查看已存在的顶点
		cout << "请输入边序列（包括代价）：格式为A B 20 30 ; A C 30 40 ; # (以‘#’结束，第一个字为时间代价 ，第二个数字为旅费代价)" << endl;
		while (1) {
			Gtype u, v;
			cin >> u;// cout << node1;
			if (u == '#') break; if (u == ';')continue;
			//cout << "输入终点" << endl;
			cin >> v;// cout << node2 << endl;
			int pos1 = getVertexPos(G, u), pos2 = getVertexPos(G, v);
			if ( pos1!=-1&&pos2!=-1 ) {
				int time, money;
				cin >> time >> money;
				G.Edges[pos1][pos2].time = time;
				G.Edges[pos1][pos2].money = money;
				G.NumEdges++;
			}
			else cout << "顶点错误" << endl;
		}
	}
}
void Floyd(MGraph &G, Weight a[][MaxVertices], int timepath[][MaxVertices],int moneypath[][MaxVertices]) {
	for (int i = 0; i < G.NumVertices; i++) {//初始化
		for (int j = 0; j < G.NumVertices; j++) {
			a[i][j] = G.Edges[i][j];
			if (i != j &&a[i][j].time < MaxWeight)timepath[i][j] = moneypath[i][j]=i;
			else timepath[i][j]= moneypath[i][j] = -1;
		}
	}
	for (int k = 0;k<G.NumVertices ;k++)
		for (int i = 0; i < G.NumVertices; i++) {
			for (int j = 0; j < G.NumVertices; j++) {
				if (a[i][k].time + a[k][j].time < a[i][j].time) {//最短时间
					a[i][j].time = a[i][k].time + a[k][j].time;
					timepath[i][j] = timepath[k][j];
				}
				if (a[i][k].money + a[k][j].money < a[i][j].money) {//最少费用
					a[i][j].money = a[i][k].money + a[k][j].money;
					moneypath[i][j] = moneypath[k][j];
				}
			}
		}
}
void miniTransfer(MGraph G, int a[][MaxVertices], int path[][MaxVertices]) {//得到中转次数最少的路径
	//两种思路：1.广搜 2.将所有权值看成1，计算最短路径  这里是第二种
	for (int i = 0; i < G.NumVertices; i++) {//初始化
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
				if (a[i][k] + a[k][j] < a[i][j]) {//中转次数最少
					a[i][j] = a[i][k] + a[k][j];
					path[i][j] = path[k][j];
				}
				
			}
		}
}
void printPath(MGraph &G, int u, int v, Weight a[][MaxVertices], int timepath[][MaxVertices], int moneypath[][MaxVertices], int transferpath[][MaxVertices]) {
	Gtype x = G.Vertices[u], y = G.Vertices[v];
	if (moneypath[u][v] == -1 || timepath[u][v] == -1) {
		cout << x << "到" << y << "无路径" << endl;
		return;
	}
	cout << "从" << x << "到" << y << "时间最快的路径为:";
	int S1[MaxVertices]/*存储路径*/, pre_ver1 = timepath[u][v]/*前一个路径*/, k1 = 0/*S标记*/;
	while (pre_ver1 != u) {
		S1[k1++] = pre_ver1;
		pre_ver1 = timepath[u][pre_ver1];
	}
	S1[k1++] = u;
	while (k1 > 0) {
		cout << G.Vertices[S1[--k1]] << "->";
	}cout << y << endl << "最短消耗时间为:" << a[u][v].time << endl << endl;

	cout << "从" << x << "到" << y << "费用最少的路径为:";
	int S2[MaxVertices]/*存储路径*/, pre_ver2 = moneypath[u][v]/*前一个路径*/, k2 = 0/*S标记*/;
	while (pre_ver2 != u) {
		S2[k2++] = pre_ver2;
		pre_ver2 = moneypath[u][pre_ver2];
	}
	S2[k2++] = u;
	while (k2 > 0) {
		cout << G.Vertices[S2[--k2]] << "->";
	}cout << y << endl << "最少费用为:" << a[u][v].money << endl << endl;

	cout << "从" << x << "到" << y << "中转次数最少的路径为:";
	int S3[MaxVertices]/*存储路径*/, pre_ver3 = transferpath[u][v]/*前一个路径*/, k3 = 0/*S标记*/;
	while (pre_ver3 != u) {
		S3[k3++] = pre_ver3;
		pre_ver3 = transferpath[u][pre_ver3];
	}
	S3[k3++] = u;
	int numtransfer = k3;
	while (k3 > 0) {
		cout << G.Vertices[S3[--k3]] << "->";
	}cout << y << endl << "最少中转次数为：" << numtransfer - 1 << endl;
	cout << "----------------" << endl << endl;

}
void menu(MGraph G){
	while (1) {
		cout << "请输入起点和终点：（如 A B ）" << endl;
		char x, y;
		cin >> x >> y;
		int u, v;
		u = getVertexPos(G, x);
		v = getVertexPos(G, y);
		if (u == -1) { cout << "起点不存在" << endl; continue; }
		if (v == -1) { cout << "终点不存在"<<endl; continue; }
		Weight a[MaxVertices][MaxVertices]; int  b[MaxVertices][MaxVertices];
		int timepath[MaxVertices][MaxVertices], moneypath[MaxVertices][MaxVertices], transferpath[MaxVertices][MaxVertices];
		Floyd(G, a, timepath, moneypath);
		miniTransfer(G, b, transferpath);
		printPath(G, u, v, a, timepath, moneypath, transferpath);

	}
}