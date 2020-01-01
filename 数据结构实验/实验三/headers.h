#pragma once

#ifndef HEARDERS_H_INCLUDED
#define HEARDERS_H_INCLUDED

/*--------------------------第三次作业-------------------------------*/
/*-----------车---------------*/
#define initstatus -1

#define inPark 1
#define inTempPark -1
#define inDetour 0
#define inOther 2

#define arrive 1
#define leave 0

typedef struct {
	int key;//车牌
	int inhour;//进入的时间 -- 小时
	int inmin;//进入的时间 -- 分钟
	int outhour;//出来的时间 -- 小时
	int outmin;//出来的时间 --分钟
	int status;//到达还是离开  1到达0离开  初始为-1
	int area;        //在哪里?----> 1代表Park停车场； 0代表Detour便道； -1代表TempPark临时停车场；  初始为 2代表其他地方
	int pos;          //车位  初始为0
}car;

/*---------栈---------*/
#define MAXSTACKSIZE 4   停车场大小
//#define MAXSTACKSIZE  15  //实验四钟用到栈 哈夫曼树  哈夫曼编码

typedef car SElemType;
//typedef char SElemType;
typedef struct {
	SElemType * base;//存储空间基址
	int top;         //栈顶指针 ( 当前栈中元素个数 )
	int stacksize;   //允许的最大存储空间 以元素为单位

}SqStack;

/*--------队列--------*/
#define MAXQUEUESIZE 5
typedef car QElemType;
typedef struct {
	QElemType *base; //初始化的动态分配存储空间
	int front;  //头指针，若队列不空，指向头元素前一个
	int rear;   //尾指针，若队列不空，指向队列尾元素
}SqQueue;


#endif // DECLARATION_H_INCLUDED
