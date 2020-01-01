#include "MGraph.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int main() {
	//*-------------图---------------*/



	//邻接矩阵测试
	MGraph G;
	CreatMGraph(G);
	if (hasEdge(G, 'A', 'B'))cout << "存在AB" << endl;;
	if (hasEdge(G, 'A', 'C'))cout << "存在AC" << endl;
	if (!hasEdge(G, 'A', 'D'))cout << "不存在AD" << endl;
	addVertex(G, 'M');
	int pos = -1;
	pos=getVertexPos(G, 'M');
	cout << pos << endl;
	cout << "顶点个数： " << getNumVertices(G);
	removeEdge(G, 'A', 'B');
	cout << "边个数： " << getNumEdges(G);
	if (!hasEdge(G, 'A', 'B'))cout << "不存在AB" << endl;
	else cout << "存在AB" << endl;
	addEdge(G, 'A', 'M', 20, 80);
	//cout << "hello" << endl;
	if (hasEdge(G, 'A', 'M'))cout << "存在AM" << endl;
	cout << "边个数： " << getNumEdges(G);


	/*------旅客代价咨询操作------*/
	MGraph G;
	CreatMGraph(G);
	menu(G);
	

	
	return 0;
}