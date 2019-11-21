//×îºó°æ±¾
#ifndef MYSAFEINT_H
#define MYSAFEINT_H
//#include "stdafx.h"
#include <safeint.h>
#include <iostream>

using namespace std;
using namespace msl::utilities;

class MySafeIntException : public SafeIntException{
public:
	static void SafeIntOnOverflow(){
		cout << "SafeInt Arithmetic Overflow!" << endl;//Òç³ö´íÎó
	}
	static void SafeIntOnDivZero(){
		cout << " SafeInt Divide By Zero!" << endl;//³ýÁã´íÎó
	}
};

#endif // !MYSAFEINT_H

#pragma once
