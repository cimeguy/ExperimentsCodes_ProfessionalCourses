//���汾
#include "MathSafe.h"
#include<iostream>
typedef unsigned int UINT;
using namespace std;
int8_t my_atoi8(char* str, int* of) {
	/*���ܣ��� str ָ��������ַ���ת��Ϊһ���������͡�������ֻ���[-128, 127]��Χ�ڵ�
		����ִ��ת����
		���� str��C �ַ�����
		���� of������ָ�룬����ת���еĴ��������Str �Ϲ���ת���ɹ���(*of) = 0��str ��ָ
		�����ֻ���Ϊ�գ�(*of) = -1��str ָ������ֲ��Ϸ���(*of) = -2.
		����ֵ������ת������������������ str ����ȷ����ָ�������Խ�磬�򷵻� 0.
		��ʾ��p164 ���̸��졣*/
	if (str == NULL) {//str Ϊ�գ�(*of) = -1
		*of = -1;
		return 0;
	}
	bool neg;
	int8_t val=0;
	while (*str == ' ') {//ȥ������ո�
		str++;
	}
	if (neg = *str == '-') {//����
		++str;
		while (*str == ' ') {//ȥ������ո�
			str++;
		}
		if (*str == '0') {//��-0xxx���������Ϸ�
			*of = -2;
			return 0;
		}
		while (*str) {
			if (isdigit(*str)) {

				if (val > INT8_MAX / 10) {//����Խ��
					(*of) = -2;
					return 0;
				}
				val *= 10;//С�ڵ���
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
			else {//����str��ָ������
				(*of) = -1;
				return 0;
			}
		}
		*of = 0;
		return -val;
	}
	else if(isdigit(*str)){//����
		while (*str == ' ') {//ȥ������ո�
			str++;
		}
		if (*str == '0') {//�ж�0
			str++;
			while (*str) {
				if (*str == '0') {//"  0xxx0x"�� 00xxxx�����Ϸ�
					*of = -2;
					return 0;
				}
			}
		}
		while (*str) {
			if (isdigit(*str)) {
				if (val > INT8_MAX / 10) {//����Խ��
					*of = -2;
					return 0;
				}
				val *= 10;//С�ڵ���
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
			else {//����str��ָ������
				*of = -1;
				return 0;
			}
		}
		//��*str��������
		//����ǽ�����
			*of= 0;
			return val;
	
		
	}
	else {//str ��ָ������
		*of = -1;
		return 0;
	}
}
/*���ܣ��ֱ�ʵ���з����� int8_t �ļӼ��˳����㡣 
���� of������ָ�룬���ؼ����еĴ��������(*of) = 0 ����ɹ���(*of) = -1 ��ʾ�����
(*of) = -2 ��ʾ����� 
����ֵ������ɹ����ؼ����������򷵻� 0. */
int iAdd_Safe(int8_t a, int8_t b, int* of){// ���ܣ�a + b
	cout << int(a) << "+" << int(b) << " = ";//����鿴
	if (a > INT8_MAX - b || a < INT8_MIN - b) {
		cout << "�������";
		*of = -2;
		return 0;
	}
	else {
		*of = 0;
		cout << int(a + b);
		return a + b;
	}
}
int iSubtract_Safe(int8_t a, int8_t b, int* of) {//���ܣ�a - b��a+(-b)
	cout << int(a) << "-" << int(b) << " = ";//����鿴
	if (a > INT8_MAX + b || a < INT8_MIN + b) {
		cout << "�������";
		*of = -2;
		return 0;
	}
	else {
		*of = 0;
		cout << int(a - b);
		return a -b;
	}
}
int iMultiply_Safe(int8_t a, int8_t b, int* of) {//���ܣ�a* b
	
	cout << int(a) << "*" << int(b) << " = ";//����鿴
	if (a > 0) {
		if (b > 0) {
			if (a > INT8_MAX / b) {
				*of = -2;
				cout << "�������";
				return 0;
			}
		}
		else {//b<0
			if (b < INT8_MIN / a) {
				*of = -2;
				cout << "�������";
				return 0;
			}
		}
	}
	else {//a<0
		if (b > 0) {
			if (a < INT8_MIN / b) {
				*of = -2;
				cout << "�������";
				return 0;
			}
		}
		else {
			if ((a != 0) && (b < (INT8_MAX / a))) {
				*of = -2;
				cout << "�������";
				return 0;
			}
		}
	}
	*of = 0;
	cout << int(a * b);
	return a * b;
}
int iDivide_Safe(int8_t a, int8_t b, int* of) { //���ܣ�a / b
	cout << int(a) << "/" << int(b) << " = ";//����鿴
	if (b == 0) {//�������
		*of = -1;
		cout << "�������";
		return 0;
	}
	if (a == INT8_MIN && b == -1) {
		*of = -2;
		cout << "�������";
		return 0;
	}
	else {
		*of = 0;
		cout << int(a / b);
		return a / b;
	}

}
UINT Add_Safe(uint8_t a, uint8_t b, int* of){// ���ܣ�a + b
	cout << UINT(a) << "+" << UINT(b) << " = ";//������鿴
	if (UINT8_MAX-a <b) {
		cout << "���ƴ���";
		*of = -2;
		return 0;
	}
	else {
		*of = 0;
		cout << UINT(a + b);
		return a+b;
	}
}

UINT Subtract_Safe(uint8_t a, uint8_t b, int* of) {//���ܣ�a - b
	cout << UINT(a) << "-" << UINT(b) << " = ";//������鿴
	if (a<b) {
		cout << "���ƴ���";
		*of = -2;
		return 0;
	}
	else {
		*of = 0;
		cout << UINT(a - b);
		return a-b;
	}

}
UINT Multiply_Safe(uint8_t a, uint8_t b, int* of) {// ���ܣ�a* b
	int c;
	cout << UINT(a) << "*" << UINT(b) << " = ";//����鿴
	c = a * b;
	if (a>UINT8_MAX/b) {
		cout << "���ƴ���";
		*of = -2;
		return 0;

	}
	else {
		*of = 0;
		cout << UINT(a * b);
		return a *b;
	}


}
UINT Divide_Safe(uint8_t a, uint8_t b, int* of) {//���ܣ�a / b
	cout << UINT(a) << "/" << UINT(b) << " = ";//����鿴
	if (b == 0) {//�������
		*of = -1;
		cout << "�������";
		return 0;
	}
	else {

		*of = 0;
		cout << UINT(a / b);
		return a / b;
	}
}

