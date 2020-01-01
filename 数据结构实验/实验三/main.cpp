#include "Sqstack.h"	  //顺序栈
#include "SqQueue.h"	  //顺序队列
#include "car.h"		  //停车场操作
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int main() {
	
/*---------停车场的操作-----------*/
	test_main_CarPark();  //函数在car.cpp中 注意：  headers 中typedef car SElemType;

	return 0;
}