#pragma once

#ifndef HEARDERS_H_INCLUDED
#define HEARDERS_H_INCLUDED
#include <vector>
using namespace std;//using std::vector;

/*-------------------------�������ҵ  ͼ-------------------------------*/

//�ڽӾ���
#define MaxVertices 30//��󶥵���
#define MaxWeight 30000//���Ȩֵ
#define MaxEdges 900//������
typedef char Gtype;
typedef struct 
{
	int time;//ʱ�����
	int money;//���ô���
}Weight;
typedef struct {
	int NumVertices, NumEdges;
	Gtype Vertices[MaxVertices];//�����
	Weight Edges[MaxVertices][MaxVertices];//�ڽӾ���
}MGraph;

#endif // DECLARATION_H_INCLUDED
