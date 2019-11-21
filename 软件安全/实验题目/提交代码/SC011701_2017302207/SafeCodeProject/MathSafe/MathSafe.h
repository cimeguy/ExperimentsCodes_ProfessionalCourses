//最后版本
#pragma once

#ifndef  MATHSAFE_H
#define  MATHSAFE_H
#include <cstdint>
typedef unsigned int UINT;
int8_t my_atoi8(char* str, int* of);

int iAdd_Safe(int8_t a, int8_t b, int* of);
int iSubtract_Safe(int8_t a, int8_t b, int* of); 
int iMultiply_Safe(int8_t a, int8_t b, int* of);
int iDivide_Safe(int8_t a, int8_t b, int* of); 

UINT Add_Safe(uint8_t a, uint8_t b, int* of); // 功能：a + b
UINT Subtract_Safe(uint8_t a, uint8_t b, int* of); //功能：a - b
UINT Multiply_Safe(uint8_t a, uint8_t b, int* of);// 功能：a* b
UINT Divide_Safe(uint8_t a, uint8_t b, int* of); //功能：a / b
#endif // ! MATHSAFE_H

