#include <iostream>
#include "headers.h"
using namespace std;
bool InitSqQueue(SqQueue& Q) {
	Q.base = new QElemType[MAXQUEUESIZE];
	if (!Q.base)
		exit(OVERFLOW);
	Q.front = Q.rear = 0;
	return true;
}
int SqQueueLength(SqQueue &Q) {
	return (Q.rear + MAXQUEUESIZE - Q.front) % MAXQUEUESIZE;
}
bool EnSqQueue(SqQueue &Q,QElemType e) {
	if ((Q.rear + 1) % MAXQUEUESIZE == Q.front) return false;/*队列满*/
	Q.rear = (Q.rear + 1) % MAXQUEUESIZE;
	Q.base[Q.rear] = e;
	return true;
}
bool DeSqQueue(SqQueue &Q, QElemType &e) {
	if (Q.front == Q.rear)return false;//队列为空
	Q.front = (Q.front + 1) % MAXQUEUESIZE;
	e = Q.base[Q.front];
	return true;
}
bool SqQueueEmpty(SqQueue Q) {  //空则返回true
	return Q.rear == Q.front;
}
bool SqQueueFull(SqQueue Q) {  //队满则true
	return (Q.rear + 1) % MAXQUEUESIZE==Q.front;
}