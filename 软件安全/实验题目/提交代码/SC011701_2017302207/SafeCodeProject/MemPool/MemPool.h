//最后版本
#ifndef  MEMPOOL_H
#define MEMPOOL_H

#include<iostream>
const int BLOCKSIZE = 256;
typedef struct Mem_Block {//内存块节点  
	int No;//编号，内存池链带头结点， 对于头节点，存放总节点个数  
	char *pm;//内存块
	Mem_Block* next;//指向下一个节点
	bool free ;//true表示空闲
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
