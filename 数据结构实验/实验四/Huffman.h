#pragma once
#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "headers.h"

void menu();
void Huffman_operate();
void creatHFTree(HFTree & HT, HuElemType value[]/*数据value[n]*/, int fr[]/*相应权值fr[n]*/, int n);
void Init(HFTree &HT);
//void Encoding(char path[]);
void Huffcode(HFTree HT, vector<string>&code, vector<string>&Data);
void Encoding(HFTree HT);
void Decoding(HFTree HT);
void Print();
void TreePrinting(HFTree HT);
/*
void HuffmanCoding(HuffmanTree&HT, HuffmanCode &HC, int *w, int n, char *ch);
void select(HuffmanTree HT, int j, int &s1, int &s2);
void Encoding();
void Tree_printing();

void Decoding();
void Delete();*/
#endif // ! TREE_H
