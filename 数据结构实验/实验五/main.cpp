#include "MGraph.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int main() {
	//*-------------ͼ---------------*/



	//�ڽӾ������
	MGraph G;
	CreatMGraph(G);
	if (hasEdge(G, 'A', 'B'))cout << "����AB" << endl;;
	if (hasEdge(G, 'A', 'C'))cout << "����AC" << endl;
	if (!hasEdge(G, 'A', 'D'))cout << "������AD" << endl;
	addVertex(G, 'M');
	int pos = -1;
	pos=getVertexPos(G, 'M');
	cout << pos << endl;
	cout << "��������� " << getNumVertices(G);
	removeEdge(G, 'A', 'B');
	cout << "�߸����� " << getNumEdges(G);
	if (!hasEdge(G, 'A', 'B'))cout << "������AB" << endl;
	else cout << "����AB" << endl;
	addEdge(G, 'A', 'M', 20, 80);
	//cout << "hello" << endl;
	if (hasEdge(G, 'A', 'M'))cout << "����AM" << endl;
	cout << "�߸����� " << getNumEdges(G);


	/*------�ÿʹ�����ѯ����------*/
	MGraph G;
	CreatMGraph(G);
	menu(G);
	

	
	return 0;
}