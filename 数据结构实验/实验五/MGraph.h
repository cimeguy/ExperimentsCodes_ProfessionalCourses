#pragma once
#ifndef MGRAPH_H
#define MGRAPH_H
#include "headers.h"
int getVertexPos(MGraph G, Gtype u);
int getNumVertices(MGraph G);
int getNumEdges(MGraph G);
bool hasEdge(MGraph G, Gtype u, Gtype v);
bool addVertex(MGraph &G, Gtype u);
bool  addEdge(MGraph &G, Gtype u, Gtype v, int time, int money);
bool removeEdge(MGraph &G, Gtype u, Gtype v);
void CreatMGraph(MGraph &G/*,int MaxVertices*/);
void Floyd(MGraph &G, Weight a[][MaxVertices], int timepath[][MaxVertices], int moneypath[][MaxVertices]);
void printPath(MGraph &G, int u, int v, Weight a[][MaxVertices], int timepath[][MaxVertices], int moneypath[][MaxVertices], int transferpath[][MaxVertices]);
void miniTransfer(MGraph G, int a[][MaxVertices], int path[][MaxVertices]);
void menu(MGraph G);
#endif // !1
