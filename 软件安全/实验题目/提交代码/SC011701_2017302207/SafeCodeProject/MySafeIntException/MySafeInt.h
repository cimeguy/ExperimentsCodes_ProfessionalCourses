//���汾
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
		cout << "SafeInt Arithmetic Overflow!" << endl;//�������
	}
	static void SafeIntOnDivZero(){
		cout << " SafeInt Divide By Zero!" << endl;//�������
	}
};

#endif // !MYSAFEINT_H

#pragma once
