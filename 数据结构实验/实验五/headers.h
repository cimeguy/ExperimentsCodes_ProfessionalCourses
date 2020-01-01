#pragma once

#ifndef HEARDERS_H_INCLUDED
#define HEARDERS_H_INCLUDED
#include <vector>
using namespace std;//using std::vector;

/*-------------------------第五次作业  图-------------------------------*/

//邻接矩阵法
#define MaxVertices 30//最大顶点数
#define MaxWeight 30000//最大权值
#define MaxEdges 900//最大边数
typedef char Gtype;
typedef struct 
{
	int time;//时间代价
	int money;//费用代价
}Weight;
typedef struct {
	int NumVertices, NumEdges;
	Gtype Vertices[MaxVertices];//顶点表
	Weight Edges[MaxVertices][MaxVertices];//邻接矩阵
}MGraph;

#endif // DECLARATION_H_INCLUDED
