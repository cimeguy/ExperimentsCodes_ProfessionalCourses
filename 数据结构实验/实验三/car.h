#pragma once
#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED
#include <string>
#include "headers.h"
using namespace std;

bool GetTime(string s, int &hour, int &min);
void visit_car(SElemType e);
bool InitCar(car &C); 
//bool SetCar(car &C, int key, int hour, int min, CarStatus s = -1, int area = 2, int pos = 0);
bool CreatCar(car &C, int key, int s = initstatus, int area = inOther, int pos = 0);
bool GetParkingTime(car C, int &hour, int &min, int &sum);
void test_main_CarPark();
#endif // !CAR_H

