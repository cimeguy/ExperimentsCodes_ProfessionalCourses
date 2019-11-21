//×îºó°æ±¾
#pragma once
# ifndef STRSAFE_H
#define STRSAFE_H
#include <iostream>

int isUsernameOK(char* name);
int isPasswordOK(char* pwd);
int gets_safe(char* str, rsize_t n);
int strcpy_safe(char* dest, rsize_t destsz, const char* src);
int iMultiply_Safe(int8_t a, int8_t b, int* of); 
#endif // DEBUG

