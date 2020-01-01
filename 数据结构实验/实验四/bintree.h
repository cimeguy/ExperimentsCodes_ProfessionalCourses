#pragma once
#ifndef BINTREE_H
#define BINTREE_H
#include "headers.h"



void InitBiTree(BinTree &T);
void PreOrder(BinTree BT);
int BiTreeEmpty(BinTree T);
void DestoryBiTree(BinTree &T);
void CreatBiTree(BinTree &T, TElemType definition[], int &n);
bool InsertChild(BinTree &T, BinTree &p, int LR, TElemType c);
#endif // ! TREE_H
