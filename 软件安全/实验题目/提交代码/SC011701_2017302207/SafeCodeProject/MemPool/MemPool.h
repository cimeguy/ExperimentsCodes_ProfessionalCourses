//���汾
#ifndef  MEMPOOL_H
#define MEMPOOL_H

#include<iostream>
const int BLOCKSIZE = 256;
typedef struct Mem_Block {//�ڴ��ڵ�  
	int No;//��ţ��ڴ������ͷ��㣬 ����ͷ�ڵ㣬����ܽڵ����  
	char *pm;//�ڴ��
	Mem_Block* next;//ָ����һ���ڵ�
	bool free ;//true��ʾ����
}block;
int initPool(size_t size=1000);
char* allocBlock();
int freeBlock(char* buf);
int freePool();
int freePoolForce();
size_t getBlockCount();
size_t getAvailableBlockCount();
#endif // ! MEMPOOL_H

#pragma once
