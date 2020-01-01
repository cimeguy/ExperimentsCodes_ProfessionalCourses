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
	if ((Q.rear + 1) % MAXQUEUESIZE == Q.front) return false;/*������*/
	Q.rear = (Q.rear + 1) % MAXQUEUESIZE;
	Q.base[Q.rear] = e;
	return true;
}
bool DeSqQueue(SqQueue &Q, QElemType &e) {
	if (Q.front == Q.rear)return false;//����Ϊ��
	Q.front = (Q.front + 1) % MAXQUEUESIZE;
	e = Q.base[Q.front];
	return true;
}
bool SqQueueEmpty(SqQueue Q) {  //���򷵻�true
	return Q.rear == Q.front;
}
bool SqQueueFull(SqQueue Q) {  //������true
	return (Q.rear + 1) % MAXQUEUESIZE==Q.front;
}