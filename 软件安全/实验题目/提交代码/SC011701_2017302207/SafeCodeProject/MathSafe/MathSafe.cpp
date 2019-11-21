//最后版本
#include "MathSafe.h"
#include<iostream>
typedef unsigned int UINT;
using namespace std;
int8_t my_atoi8(char* str, int* of) {
	/*功能：将 str 指向的整数字符串转换为一个整数类型。本函数只针对[-128, 127]范围内的
		整数执行转换。
		参数 str：C 字符串。
		参数 of：整数指针，返回转换中的错误情况。Str 合规且转换成功，(*of) = 0；str 不指
		向数字或者为空，(*of) = -1；str 指向的数字不合法，(*of) = -2.
		返回值：返回转换后的整数，如果参数 str 不正确或者指向的数字越界，则返回 0.
		提示：p164 例程改造。*/
	if (str == NULL) {//str 为空，(*of) = -1
		*of = -1;
		return 0;
	}
	bool neg;
	int8_t val=0;
	while (*str == ' ') {//去掉多余空格
		str++;
	}
	if (neg = *str == '-') {//负数
		++str;
		while (*str == ' ') {//去掉多余空格
			str++;
		}
		if (*str == '0') {//“-0xxx”参数不合法
			*of = -2;
			return 0;
		}
		while (*str) {
			if (isdigit(*str)) {

				if (val > INT8_MAX / 10) {//数字越界
					(*of) = -2;
					return 0;
				}
				val *= 10;//小于等于
				int8_t i = *str - '0';
				if (i > INT8_MAX + 1 - val) {
					(*of) = -2;
					return 0;
				}
				val += i;
				str++;
			}
			else if (*str == ' ') {
				str++;
				continue;
			}
			else {//否则str不指向数字
				(*of) = -1;
				return 0;
			}
		}
		*of = 0;
		return -val;
	}
	else if(isdigit(*str)){//正数
		while (*str == ' ') {//去掉多余空格
			str++;
		}
		if (*str == '0') {//判断0
			str++;
			while (*str) {
				if (*str == '0') {//"  0xxx0x"或“ 00xxxx”不合法
					*of = -2;
					return 0;
				}
			}
		}
		while (*str) {
			if (isdigit(*str)) {
				if (val > INT8_MAX / 10) {//数字越界
					*of = -2;
					return 0;
				}
				val *= 10;//小于等于
				int8_t i = *str - '0';
				if (i > INT8_MAX - val) {
					*of = -2;
					return 0;
				}
				val += i;
				str++;
			}
			else if (*str == ' ') {
				str++;
				continue;
			}
			else {//否则str不指向数字
				*of = -1;
				return 0;
			}
		}
		//当*str不是数字
		//如果是结束符
			*of= 0;
			return val;
	
		
	}
	else {//str 不指向数字
		*of = -1;
		return 0;
	}
}
/*功能：分别实现有符号数 int8_t 的加减乘除运算。 
参数 of：整数指针，返回计算中的错误情况。(*of) = 0 计算成功；(*of) = -1 表示除零错；
(*of) = -2 表示溢出错。 
返回值：计算成功返回计算结果，否则返回 0. */
int iAdd_Safe(int8_t a, int8_t b, int* of){// 功能：a + b
	cout << int(a) << "+" << int(b) << " = ";//输出查看
	if (a > INT8_MAX - b || a < INT8_MIN - b) {
		cout << "溢出错误！";
		*of = -2;
		return 0;
	}
	else {
		*of = 0;
		cout << int(a + b);
		return a + b;
	}
}
int iSubtract_Safe(int8_t a, int8_t b, int* of) {//功能：a - b即a+(-b)
	cout << int(a) << "-" << int(b) << " = ";//输出查看
	if (a > INT8_MAX + b || a < INT8_MIN + b) {
		cout << "溢出错误！";
		*of = -2;
		return 0;
	}
	else {
		*of = 0;
		cout << int(a - b);
		return a -b;
	}
}
int iMultiply_Safe(int8_t a, int8_t b, int* of) {//功能：a* b
	
	cout << int(a) << "*" << int(b) << " = ";//输出查看
	if (a > 0) {
		if (b > 0) {
			if (a > INT8_MAX / b) {
				*of = -2;
				cout << "溢出错误！";
				return 0;
			}
		}
		else {//b<0
			if (b < INT8_MIN / a) {
				*of = -2;
				cout << "溢出错误！";
				return 0;
			}
		}
	}
	else {//a<0
		if (b > 0) {
			if (a < INT8_MIN / b) {
				*of = -2;
				cout << "溢出错误！";
				return 0;
			}
		}
		else {
			if ((a != 0) && (b < (INT8_MAX / a))) {
				*of = -2;
				cout << "溢出错误！";
				return 0;
			}
		}
	}
	*of = 0;
	cout << int(a * b);
	return a * b;
}
int iDivide_Safe(int8_t a, int8_t b, int* of) { //功能：a / b
	cout << int(a) << "/" << int(b) << " = ";//输出查看
	if (b == 0) {//除零错误
		*of = -1;
		cout << "除零错误！";
		return 0;
	}
	if (a == INT8_MIN && b == -1) {
		*of = -2;
		cout << "溢出错误！";
		return 0;
	}
	else {
		*of = 0;
		cout << int(a / b);
		return a / b;
	}

}
UINT Add_Safe(uint8_t a, uint8_t b, int* of){// 功能：a + b
	cout << UINT(a) << "+" << UINT(b) << " = ";//仅输出查看
	if (UINT8_MAX-a <b) {
		cout << "回绕错误！";
		*of = -2;
		return 0;
	}
	else {
		*of = 0;
		cout << UINT(a + b);
		return a+b;
	}
}

UINT Subtract_Safe(uint8_t a, uint8_t b, int* of) {//功能：a - b
	cout << UINT(a) << "-" << UINT(b) << " = ";//仅输出查看
	if (a<b) {
		cout << "回绕错误！";
		*of = -2;
		return 0;
	}
	else {
		*of = 0;
		cout << UINT(a - b);
		return a-b;
	}

}
UINT Multiply_Safe(uint8_t a, uint8_t b, int* of) {// 功能：a* b
	int c;
	cout << UINT(a) << "*" << UINT(b) << " = ";//输出查看
	c = a * b;
	if (a>UINT8_MAX/b) {
		cout << "回绕错误！";
		*of = -2;
		return 0;

	}
	else {
		*of = 0;
		cout << UINT(a * b);
		return a *b;
	}


}
UINT Divide_Safe(uint8_t a, uint8_t b, int* of) {//功能：a / b
	cout << UINT(a) << "/" << UINT(b) << " = ";//输出查看
	if (b == 0) {//除零错误
		*of = -1;
		cout << "除零错误！";
		return 0;
	}
	else {

		*of = 0;
		cout << UINT(a / b);
		return a / b;
	}
}

