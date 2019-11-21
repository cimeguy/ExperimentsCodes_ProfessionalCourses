//最后版本
#include <iostream>
#include <safeint.h>
#include "MemPool/MemPool.h"
#include "MathSafe/MathSafe.h"
#include "StrSafe/StrSafe.h"
#include"MySafeIntException/MySafeInt.h"
#include "LogSafe/LogSafe.h"
#include <thread>

using namespace msl::utilities;
using namespace std;

int main()
{
	
	
	//----------------------------[实验一]----------------------------//
	/*char s1[] = "a12345678";
	char s2[] = "a123";
	char s3[] = "a123bcdefg4567890";
	char s4[] = "";
	char *s5 = 0;
	char s6[] = "123456789";
	char s7[] = "abcdefghjik";
	cout << s1<<": "<<isUsernameOK(s1)<<endl;
	cout << s2 << ": " << isUsernameOK(s2) << endl;
	cout << s3 << ": " << isUsernameOK(s3) << endl;
	cout << s4 << ": " << isUsernameOK(s4) << endl;
	cout<< "isUsernameOK(0): " << isUsernameOK(s5) << endl;
	cout << s6 << ": " << isUsernameOK(s6) << endl;
	cout << s7 << ": " << isUsernameOK(s7) << endl;
	cout << endl << endl;
	char t1[] = "1234A5678";
	char t2[] = "a123";
	char t3[] = "a123Bcdefg4567890";
	char t4[] = "";
	char* t5 = 0;
	char t6[] = "123456789";
	char t7[] = "abcdefghjik";
	char t8[] = "1234abcde8";
	cout << t1 << ": " << isPasswordOK(t1) << endl;
	cout << t2 << ": " << isPasswordOK(t2) << endl;
	cout << t3 << ": " << isPasswordOK(t3) << endl;
	cout << t4 << ": " << isPasswordOK(t4) << endl;
	cout << " isPasswordOK(0): " << isPasswordOK(t5) << endl;
	cout << t6 << ": " << isPasswordOK(t6) << endl;
	cout << t7 << ": " << isPasswordOK(t7) << endl;
	cout << t8 << ": " << isPasswordOK(t8) << endl;*/
	
	//----------------------------[实验二]----------------------------//
	
	/*for (int i = 0; i < 4; i++) {
		char buf1[8];
		cout << gets_safe(buf1, sizeof(buf1)) << endl;
	}*/
	//2
	//char* buf2 = 0;
	//cout<<gets_safe(buf2, sizeof(buf2))<<endl;
	////3
	//char buf3[8];
	//cout<<gets_safe(buf3, 0)<<endl;

	// //strcpy_safe
	////1
	//char dest1[8];
	//char src1[] = "12345";
	//cout << strcpy_safe(dest1, sizeof(dest1), src1) << endl;
	////2
	//char dest2[8];
	//char src2[] = "1234567";
	//cout << strcpy_safe(dest2, sizeof(dest2), src2) << endl;
	////3
	//char dest3[8];
	//char *src3 = (char *)"12345678";
	//cout << strcpy_safe(dest3, sizeof(dest3), src3) << endl;
	////4
	//cout << strcpy_safe(0, 8, src2)<<endl;
	////5
	//char dest5[8];
	//cout<<strcpy_safe(dest5, sizeof(dest5), 0)<<endl;
	////6
	//cout << strcpy_safe(dest5, 0, src3) << endl;

	//----------------------------[实验三]----------------------------//
	//initPool(8);
	//allocBlock(); 
	//char* buf = allocBlock();
	//bool isnull = true;
	//for (int i = 0; i < 256; i++) {
	//	if (buf[i] != 0) {
	//		isnull = false;
	//		break;
	//	}
	//}
	//if (isnull)cout << "buf[0] + buf[1] + ... +buf[255] = 0 " << endl;
	////cout << endl;
	//cout<<getBlockCount()<<endl; 
	//cout << getAvailableBlockCount()<<endl;
	//allocBlock(); allocBlock();
	//cout<<getAvailableBlockCount()<<endl;
	//freeBlock(buf);
	//cout<<getBlockCount()<<endl;
	//cout << getAvailableBlockCount() << endl;
	//freeBlock(buf);
	//for (int i = 0; i < 256; i++) {
	//	if (buf[i] != 0) {
	//		isnull = false;
	//		break;
	//	}
	//}
	//if (isnull)cout << "buf[0] + buf[1] + ... +buf[255] = 0" << endl; 
	//cout << "freePool()=="<<freePool() << endl;
	//cout << "freePoolForce()==" << freePoolForce() << endl;
	//cout << getBlockCount() << endl;
	//cout << getAvailableBlockCount() << endl;

	//----------------------------[实验四]----------------------------//
	/*int x = 0;
	int* of = &x;
	
	cout << "第一组：" << endl;
	char str11[] = "-128";
	my_atoi8(str11, of);
	cout <<"(*of)=="<< *of << endl;
	char str12[] = "127";
	my_atoi8(str12, of);
	cout << "(*of)==" << *of << endl;
	char str13[] = "0";
	my_atoi8(str13, of);
	cout << "(*of)==" << *of << endl;
	char str14[] = "-1";
	my_atoi8(str14, of);
	cout << "(*of)==" << *of << endl;

	cout << "第二组：" << endl;
	char str21[] = "1285";
	my_atoi8(str21, of);
	cout << "(*of)==" << *of << endl;
	char str22[] = "-129";
	my_atoi8(str22, of);
	cout << "(*of)==" << *of << endl;
	char str23[] = "130";
	my_atoi8(str23, of);
	cout << "(*of)==" <<*of << endl;

	cout << "第三组：" << endl;
	char str31[] = "";
	my_atoi8(str31, of);
	cout << "(*of)==" << *of << endl;
	my_atoi8(0, of);
	cout << "(*of)==" << *of << endl;
	char str33[] = "abc";
	my_atoi8(str33, of);
	cout << "(*of)==" << *of << endl;
	char str34[] = "12a";
	my_atoi8(str34, of);
	cout << "(*of)==" << *of << endl;

	cout << "第四组：" << endl;
	char str41[] = "123a";
	my_atoi8(str41, of);
	cout << "(*of)==" << *of << endl;
	char str42[] = "12a";
	my_atoi8(str42, of);
	cout << "(*of)==" << *of << endl;
	char str43[] = "-12a";
	my_atoi8(str43, of);
	cout << "(*of)==" << *of << endl;

	cout << "第五组：" << endl;
	char str51[] = "00123";
	my_atoi8(str51, of);
	cout << "(*of)==" << *of << endl;
	char str52[] = "-00123";
	my_atoi8(str52, of);
	cout << "(*of)==" << *of << endl;

	cout << "第六组：" << endl;
	char str61[] = "  123  ";
	my_atoi8(str61, of);
	cout << "(*of)==" << *of << endl;
	char str62[] = " - 23   ";
	my_atoi8(str62, of);
	cout << "(*of)==" << *of << endl;
	char str63[] = " - 2 3   ";
	my_atoi8(str63, of);
	cout << "(*of)==" << *of << endl;*/
	///////有符号整数加减乘除 
	int x = 0;
	int* of = &x;
	/////加法
	//cout << "有符号整数加减乘除 " << endl;
	//cout << "加法第一组：" << endl;
	//iAdd_Safe(12, 13,of); cout << "    (*of)==" << *of << endl; 
	//iAdd_Safe(127, 0, of); cout << "    (*of)==" << *of << endl;
	//iAdd_Safe(-12, -13,of); cout << "    (*of)==" << *of << endl;
	//iAdd_Safe(-127, 13, of); cout << "    (*of)==" << *of << endl;
	//cout << "第二组：" << endl;
	//iAdd_Safe(127, 3,of); cout << "    (*of)==" << *of << endl;
	//iAdd_Safe(-126, -13, of); cout << "    (*of)==" << *of << endl;

	///////减法
	//cout << "减法第一组：" << endl; 
	//iSubtract_Safe(12, 13, of); cout << "    (*of)==" << *of << endl;
	//iSubtract_Safe(127, 0, of); cout << "    (*of)==" << *of << endl;
	//iSubtract_Safe(-12, -13, of); cout << "    (*of)==" << *of << endl;
	//iSubtract_Safe(-127, 1, of); cout << "    (*of)==" << *of << endl;
	//cout << "第二组：" << endl;
	//iSubtract_Safe(127, -1, of); cout << "    (*of)==" << *of << endl;
	//iSubtract_Safe(-126, 13, of) ; cout << "    (*of)==" << *of << endl;

	//cout << "乘法第一组：" << endl;
	//iMultiply_Safe(2, 30, of); cout << "    (*of)==" << *of << endl;
	//iMultiply_Safe(127, 1, of); cout << "    (*of)==" << *of << endl;
	//iMultiply_Safe(-2, 30, of); cout << "    (*of)==" << *of << endl;
	//iMultiply_Safe(-12, -3, of); cout << "    (*of)==" << *of << endl;
	//iMultiply_Safe(-128, 1, of); cout << "    (*of)==" << *of << endl;
	//cout << "第二组：" << endl;
	//iMultiply_Safe(127, 3, of); cout << "    (*of)==" << *of << endl;
	//iMultiply_Safe(-28, 6, of); cout << "    (*of)==" << *of << endl;
	//iMultiply_Safe(-128, -1, of); cout << "    (*of)==" << *of << endl;
	//cout << "除法第一组：" << endl;
	//iDivide_Safe(127, 3, of); cout << "    (*of)==" << *of << endl;
	//iDivide_Safe(-28, 7, of); cout << "    (*of)==" << *of << endl;
	////iDivide_Safe(-128, -1, of); cout << "    (*of)==" << *of << endl;
	//cout << "第二组：" << endl;
	//iDivide_Safe(-128, -1, of); cout << "    (*of)==" << *of << endl;
	//cout << "第三组：" << endl;
	//iDivide_Safe(127, 0, of); cout << "    (*of)==" << *of << endl;
	//iDivide_Safe(-28, 0, of); cout << "    (*of)==" << *of << endl;
	//iDivide_Safe(-128, 0, of); cout << "    (*of)==" << *of << endl;
	//cout << "无符号整数加减乘除 " << endl;
	//
	//cout << "无符号加法第一组：" << endl;
	//Add_Safe(12, 13, of); cout << "    (*of)==" << *of << endl;
	//Add_Safe(255, 0, of); cout << "    (*of)==" << *of << endl;
	//Add_Safe(132, 13, of); cout << "    (*of)==" << *of << endl;
	//cout << "第二组:" << endl;
	//Add_Safe(255, 1, of); cout << "    (*of)==" << *of << endl;
	//Add_Safe(124, 123, of); cout << "    (*of)==" << *of << endl;

	//cout << "无符号减法第一组：" << endl;
	//Subtract_Safe(17, 13, of); cout << "    (*of)==" << *of << endl;
	//Subtract_Safe(127, 0, of); cout << "    (*of)==" << *of << endl;
	//Subtract_Safe(232, 13, of); cout << "    (*of)==" << *of << endl;
	//cout << "第二组:" << endl;
	//Subtract_Safe(127, 128, of); cout << "    (*of)==" << *of << endl;
	//Subtract_Safe(2, 255, of); cout << "    (*of)==" << *of << endl;

	//cout << "无符号乘法第一组：" << endl;
	//Multiply_Safe(2, 30, of); cout << "    (*of)==" << *of << endl;
	//Multiply_Safe(127, 1, of); cout << "    (*of)==" << *of << endl;
	//Multiply_Safe(122, 2, of); cout << "    (*of)==" << *of << endl;
	//cout << "第二组:" << endl;
	//Multiply_Safe(127, 3, of); cout << "    (*of)==" << *of << endl;
	//Multiply_Safe(28, 26, of); cout << "    (*of)==" << *of << endl;
	//cout << "无符号除法第一组：" << endl;
	//Divide_Safe(234, 3, of); cout << "    (*of)==" << *of << endl;
	//Divide_Safe(228, 7, of); cout << "    (*of)==" << *of << endl;
	//cout << "第二组:" << endl;
	//iDivide_Safe(127, 0, of); cout << "    (*of)==" << *of << endl;
	//iDivide_Safe(0, 0, of); cout << "    (*of)==" << *of << endl;

//----------------------------[实验五]----------------------------//
	//bool b1, b2;
	////1
	//cout << "uint64_t + uint64_t:" << endl;
	////int8_t i1 = 126, res/*结果*/; int16_t i2 = 1, i3 = 2; 
	//uint64_t a1 = 0x000000007ffffffe, a2 = 0x0000000000000000,res;
	//b1 = SafeAdd(a1, a2, res); cout <<  endl<<"用例(1): " << b1 << "  ";
	//SafeInt<uint64_t, MySafeIntException> su64_1(a1);
	//SafeInt<uint64_t, MySafeIntException> su64_2(a2);
	//SafeInt<uint64_t, MySafeIntException> sres_u64 = su64_1 + su64_2;
	//
	//uint64_t a3 = 0xffffffffffffffff, a4 = 0x0000000000000001;
	//b2 = SafeAdd(a3, a4, res); cout << endl << "用例(2): " << b2 << "  ";
	//su64_1 = a3; su64_2 = a4; sres_u64 = su64_1 + su64_2;

	//a1 = 0x000000007ffffffe, a2 = 0x000000007fffffff; 
	//b1 = SafeAdd(a1, a2, res); cout << endl << "用例(3): "<< b1 << "  ";
	//su64_1 = a1; su64_2 = a2; sres_u64 = su64_1 + su64_2;

	//a3 = 0x7fffffffffffffff, a4 = 0x8000000000000001;
	//b1 = SafeAdd(a3, a4, res); cout << endl << "用例(4): " << b1 << "  ";
	//su64_1 = a3; su64_2 = a4; sres_u64 = su64_1 + su64_2;
	////2
	//cout <<endl<< "uint64_t+uint16_t:" << endl;
	//uint64_t z21 = 0x7fffffffffffffff; uint16_t z22 = 0x7ffe;
	//b1 = SafeAdd(z21, z22, res); cout << endl << "用例(1): " << b1 << "  ";
	//su64_1 = z21; SafeInt<uint16_t, MySafeIntException>su16(z22); sres_u64 = su64_1 + (uint16_t)su16;
	//z21 = 0x8000000000000001; z22 = 0x8001;
	//b1 = SafeAdd(z21, z22, res); cout << endl << "用例(2): " << b1 << "  ";
	//su64_1 = z21; su16 =z22; sres_u64 = su64_1 + (uint16_t)su16;
	//z21 = 0xfffffffffffffffe; z22 = 0x8001;
	//b1 = SafeAdd(z21, z22, res); cout << endl << "用例(3): " << b1 << "  ";
	//su64_1 = z21; su16 = z22; sres_u64 = su64_1 + (uint16_t)su16;
	//z21 = 0xfffffffffffffffe; z22 = 0xffff;
	//b1 = SafeAdd(z21, z22, res); cout << endl << "用例(4): " << b1 << "  ";
	//su64_1 = z21; su16 = z22; sres_u64 = su64_1 + (uint16_t)su16;
	////3  
	//cout << endl << "uint64_t+int32_t:" << endl;
	//uint64_t z31 = 0x000000007ffffffe; int32_t z32 = 0x7ffffffe;
	//b1 = SafeAdd(z31, z32, res); cout << endl << "用例(1): " << b1 << "  ";
	//su64_1 = z31; SafeInt<int32_t, MySafeIntException> si32(z32); sres_u64 = su64_1 + (int32_t)si32;
	//z31 = 0xfffffffffffffffe; z32 = 0x7ffffffe;
	//b1 = SafeAdd(z31, z32, res); cout << endl << "用例(2): " << b1 << "  ";
	//su64_1 = z31; si32=z32; sres_u64 = su64_1 + (int32_t)si32;
	//z31 = 0x0000000000000001; z32 = 0xffffffff;
	//b1 = SafeAdd(z31, z32, res); cout << endl << "用例(3): " << b1 << "  ";
	//su64_1 = z31; si32 = z32; sres_u64 = su64_1 + (int32_t)si32;
	//z31 = 0x0000000000000000; z32 = 0xffffffff;
	//b1 = SafeAdd(z31, z32, res); cout << endl << "用例(4): " << b1 << "  ";
	//su64_1 = z31; si32 = z32; sres_u64 = su64_1 + (int32_t)si32;
	////4
	//cout << endl << "int64_t + uint32_t:" << endl;
	//int64_t z41 = 0x000000007ffffffe,res2;uint32_t z42 = 0x00000001;
	//b1 = SafeAdd(z41, z42, res2); cout << endl << "用例(1): " << b1 << "  ";
	//SafeInt<int64_t, MySafeIntException> si64(z41); SafeInt<uint32_t, MySafeIntException> su32(z42);
	//SafeInt<int64_t, MySafeIntException> sresi64 = si64 + (uint32_t)su32;
	//z41 = 0x7ffffffffffffffe; 
	//b1 = SafeAdd(z41, z42, res2); cout << endl << "用例(2): " << b1 << "  ";
	//si64 = z41; su32 = z42; sresi64 = si64 + (uint32_t)su32;
	//z41 = 0x7fffffffffffffff; 
	//b1 = SafeAdd(z41, z42, res2); cout << endl << "用例(3): " << b1 << "  ";
	//si64 = z41; su32 = z42; sresi64 = si64 + (uint32_t)su32;
	//z41 = 0x8000000000000000; 
	//b1 = SafeAdd(z41, z42, res2); cout << endl << "用例(4): " << b1 << "  ";
	//si64 = z41; su32 = z42; sresi64 = si64 + (uint32_t)su32;
	////5
	//cout << endl << "uint64_t - int32_t:" << endl;
	//z31 = 0x0000000000000000; z32 = 0x00000001;
	//b1 = SafeSubtract(z31, z32, res); cout << endl << "用例(1): " << b1 << "  ";
	//su64_1 = z31; si32 = z32; sres_u64 = su64_1 - (int32_t)si32;
	//z31 = 0x0000000000000000; z32 = 0x80000000;
	//b1 = SafeSubtract(z31, z32, res); cout << endl << "用例(2): " << b1 << "  ";
	//su64_1 = z31; si32 = z32; sres_u64 = su64_1 - (int32_t)si32;
	//z31 = 0xfffffffffffffffe; z32 =0x80000000;
	//b1 = SafeSubtract(z31, z32, res); cout << endl << "用例(3): " << b1 << "  ";
	//su64_1 = z31; si32 = z32; sres_u64 = su64_1 - (int32_t)si32;
	//z31 = 0xfffffffffffffffe; z32 =0xffffffff;
	//b1 = SafeSubtract(z31, z32, res); cout << endl << "用例(4): " << b1 << "  ";
	//su64_1 = z31; si32 = z32; sres_u64 = su64_1 - (int32_t)si32;
	////6
	//cout << endl << "uint32_t* int64_t:" << endl;
	//uint32_t resu32; 
	//z42 = 0x7fffffff; z41 = 2;
	//b1 = SafeMultiply(z42, z41, resu32);  cout << endl << "用例(1): " << b1 << "  ";
	//su32 = z42; si64 = z41; SafeInt<uint32_t, MySafeIntException> sres_u32 = su32 * (int64_t)si64;
	//z42 = 0x80000000; z41 = 2;
	//b1 = SafeMultiply(z42, z41, resu32); cout << endl << "用例(2): " << b1 << "  ";
	//su32 = z42; si64 = z41; sres_u32 = su32 * (int64_t)si64;
	//z42 = 0x7fffffff; z41 = 0x7fffffff;
	//b1 = SafeMultiply(z42, z41, resu32);  cout << endl << "用例(3): " << b1 << "  ";
	//su32 = z42; si64 = z41; sres_u32 = su32 *(int64_t)si64;
	//z42 = 1; z41 = 0x7fffffffffffffff;
	//b1 = SafeMultiply(z42, z41, resu32); cout << endl << "用例(4): " << b1 << "  ";
	//su32 = z42; si64 = z41; sres_u32 = su32 *(int64_t)si64;
	////7
	//cout << endl << "uint64_t / int32_t:" << endl;
	//uint64_t u64 = 0x7fffffff,resu; int32_t i32 = 0;
	//b1 = SafeDivide(u64, i32, resu); cout << endl << "用例(1): " << b1 << "  ";
	//su64_1 = u64; si32 = i32; sres_u64 = su64_1 /(int32_t) si32;
	//u64 = 0x80000000; i32 = 0x7fffffff;
	//b1 = SafeDivide(u64, i32, resu);  cout << endl << "用例(2): " << b1 << "  ";
	//su64_1 = u64; si32 = i32; sres_u64 = su64_1 / (int32_t)si32;
	//u64 = 0x80000000; i32 = 0x80000000;
	//b1 = SafeDivide(u64, i32, resu);  cout << endl << "用例(3): " << b1 << "  ";
	//su64_1 = u64; si32 = i32; sres_u64 = su64_1 / (int32_t)si32;
	//u64 = 1; i32 = 0xffffffff;
	//b1 = SafeDivide(u64, i32, resu);  cout << endl << "用例(4): " << b1 << "  ";
	//su64_1 = u64; si32 = i32; sres_u64 = su64_1 / (int32_t)si32;
	//----------------------------[实验七]----------------------------//
	//char pa[]="C:\\temp\\log.txt";
	//initLog(pa);
	////Create thread1, CreateThread2, CreateThread3;
	//for (int i = 0; i < 1000; i++) {
	//	char c1[] = "Normal", c2[] = "Start Normal testing...";
	//	thread th1(logStr, c1, c2); th1.join();//th1.detach();
	//调用detach()函数使子线程独立于主线程并发执行，主线程后续代码段无需等待
	//	char c3[] = "Warning", c4[] = "Start Warning testing...";
	//	thread th2(logStr, c3, c4); th2.join();//th2.detach();
	//	char c5[] = "Alert", c6[] = "Start Alert Testing ... ";
	//	thread th3(logStr, c5, c6); th3.join();//th3.detach();
	//	char c7[] = "Error", c8[] = "Start Error Testing ... ";
	//	thread th4(logStr, c7, c8); th4.join();//th4.detach();
	//}

	return 0;
}

