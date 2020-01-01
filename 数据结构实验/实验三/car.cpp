#include <iostream>
#include <string>
#include "headers.h"
#include "Sqstack.h"	  //˳��ջ
#include "SqQueue.h"	  //˳�����
using namespace std;
bool GetTime(string s ,int &hour,int &min) {
	if (s[2] == ':') {
		hour = int(s[0] - '0') * 10 + int(s[1] - '0');
		min = int(s[3] - '0') * 10 + int(s[4] - '0');

	}
	else if(s[1]==':'){
		hour = int(s[0] - '0');
		min = int(s[2] - '0') * 10 + int(s[3] - '0');
	}
	else {
		cout << "����ʱ����󣺼���Ƿ��������ַ�����������ʽ����" << endl;
		return false;
	}
	if (hour < 0 || hour >= 24||min<0||min>59) {
		cout << "����ʱ�����ʱ�䷶ΧΪ0:00~23:59" << endl;
		return false;
	}
	return true;
}
void visit_car(SElemType e) {  //���ͣ�����ڲ�
	cout << "[" << e.key << "]" << " ";
}
bool InitCar(car &C) {
	C.key = -1;
	C.area = inOther;
	C.inhour = 23;   
	C.inmin = 59;
	C.outhour = 0;
	C.outmin = 0;
	C.status = -1;
	C.pos = 0;
	return true;
}

bool CreatCar(car &C, int key, int s , int area , int pos=0) {
	C.key = key;
	C.status = s;
	C.area = area;
	C.pos = pos;
	return true;
}
bool GetParkingTime(car C, int &hour, int &min, int &sum) {
	int sumout = C.outhour * 60 + C.outmin;
	int summin = C.inhour * 60 + C.inmin;

	if (sumout < summin) {
		cout<<"δͣ���˳�" << endl;
		return false;
	}
	else if (sumout == summin) {
		cout << "��������ʱ����ͬ����ͣ��" << endl;
		return false;
	}
	else {
		sum = sumout - summin;
		
		hour = sum / 60;
		min = sum % 60;
		if (hour == 0) {
			cout << "�ó�ͣ��" << min << "����" << endl;
		}
		else {
			cout << "�ó�ͣ��" << hour << "Сʱ" << min << "����" << endl;
		}
		return true;
	}
}
/*ͣ������Ҫ����*/
void test_main_CarPark() {
	
	int c;  //1������ ���������ִ����뿪
	car CAR;
	int key/*���ƺ�*/;
	int hour, min, sp;
	string s;
	SqStack Park, TempPark;  //Ԫ��Ϊcar��
	SqQueue Detour;
	InitCar(CAR);
	InitSqStack(Park);
	InitSqStack(TempPark);
	InitSqQueue(Detour);
	while (1) {
		cout << "��������or�뿪��������1��ʾ�������0��ʾ�뿪����";
		cin >> c;
		if (c == arrive) {  //����
			cout << endl << "����������복�ƺ�:";
			cin >> key;
			cout << endl << "�����뵽��ʱ�䣨�ԡ�:���ָ��12:00����";
			cin >> s;
			while (!GetTime(s, hour, min)) { //�ж������Ƿ�Ϸ�
				cout << "����������:";
				cin >> s;
				continue;
			}
			//������
			CreatCar(CAR, key, arrive, inOther);
			CAR.inhour = hour;	CAR.inmin = min;

			if (Push(Park, CAR)) {
				cout << "ͣ�ڵ�" << Park.top << "��λ" << endl;
				CAR.area = inPark;
				CAR.pos = Park.top;
				//SqStackTraverse(Park, visit_car);
			}
			else {  //ͣ��������
					//ͣ����
				if (EnSqQueue(Detour, CAR)) {
					cout << "ͣ����������ͣ����ʱ�Ⱥ�����" << Detour.rear << "��λ" << endl;
					CAR.area = inDetour;
					CAR.pos = Detour.rear;
				}
				else {
					cout << "�Բ���ͣ��������������" << endl;
				}
			}
		}
		if (c == leave) {        //��ȥ
			cout << endl << "���뿪�������복�ƺ�:";
			cin >> key;
			cout << endl << "�������뿪ʱ�䣨�ԡ�:���ָ��12:00����";
			cin >> s;
			while (!GetTime(s, hour, min)) { //�ж������Ƿ�Ϸ�
				cout << "����������:";
				cin >> s;
				continue;
			}
			//������
			car k;
			InitCar(k);
			//�Ѻ���ĳ��Ƴ���
			while (Pop(Park, k)) {

				if (k.key == key) {
					break;
				}
				Push(TempPark, k);
			}
			if (k.key != key)cout << "ͣ�������޸ó�" << endl;
			else {
				car &C = k;
				cout << "����Ϊ " << key << " �ĳ��뿪" << endl;
				C.outhour = hour;	C.outmin = min;
				int ParkHour = 0, ParkMin = 0, ParkSumTime;
				if (GetParkingTime(C, ParkHour, ParkMin, ParkSumTime)) {
					C.area = inOther;
					C.pos = 0;
					C.status = leave;
				}

			}
			//�Ѻ���ĳ���װ��ȥ
			while (Pop(TempPark, k)) {
				Push(Park, k);
			}
			if (DeSqQueue(Detour, k)) Push(Park, k);
		}
		cout << "ͣ����:���->";
		SqStackTraverse(Park, visit_car);
		cout << endl;

	}
}