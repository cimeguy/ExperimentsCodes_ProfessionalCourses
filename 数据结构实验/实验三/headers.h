#pragma once

#ifndef HEARDERS_H_INCLUDED
#define HEARDERS_H_INCLUDED

/*--------------------------��������ҵ-------------------------------*/
/*-----------��---------------*/
#define initstatus -1

#define inPark 1
#define inTempPark -1
#define inDetour 0
#define inOther 2

#define arrive 1
#define leave 0

typedef struct {
	int key;//����
	int inhour;//�����ʱ�� -- Сʱ
	int inmin;//�����ʱ�� -- ����
	int outhour;//������ʱ�� -- Сʱ
	int outmin;//������ʱ�� --����
	int status;//���ﻹ���뿪  1����0�뿪  ��ʼΪ-1
	int area;        //������?----> 1����Parkͣ������ 0����Detour����� -1����TempPark��ʱͣ������  ��ʼΪ 2���������ط�
	int pos;          //��λ  ��ʼΪ0
}car;

/*---------ջ---------*/
#define MAXSTACKSIZE 4   ͣ������С
//#define MAXSTACKSIZE  15  //ʵ�������õ�ջ ��������  ����������

typedef car SElemType;
//typedef char SElemType;
typedef struct {
	SElemType * base;//�洢�ռ��ַ
	int top;         //ջ��ָ�� ( ��ǰջ��Ԫ�ظ��� )
	int stacksize;   //��������洢�ռ� ��Ԫ��Ϊ��λ

}SqStack;

/*--------����--------*/
#define MAXQUEUESIZE 5
typedef car QElemType;
typedef struct {
	QElemType *base; //��ʼ���Ķ�̬����洢�ռ�
	int front;  //ͷָ�룬�����в��գ�ָ��ͷԪ��ǰһ��
	int rear;   //βָ�룬�����в��գ�ָ�����βԪ��
}SqQueue;


#endif // DECLARATION_H_INCLUDED
