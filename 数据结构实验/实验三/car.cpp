#include <iostream>
#include <string>
#include "headers.h"
#include "Sqstack.h"	  //顺序栈
#include "SqQueue.h"	  //顺序队列
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
		cout << "输入时间错误：检查是否是中文字符或者其他格式问题" << endl;
		return false;
	}
	if (hour < 0 || hour >= 24||min<0||min>59) {
		cout << "输入时间错误：时间范围为0:00~23:59" << endl;
		return false;
	}
	return true;
}
void visit_car(SElemType e) {  //输出停车场内部
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
		cout<<"未停过此车" << endl;
		return false;
	}
	else if (sumout == summin) {
		cout << "入库与出库时间相同，不停车" << endl;
		return false;
	}
	else {
		sum = sumout - summin;
		
		hour = sum / 60;
		min = sum % 60;
		if (hour == 0) {
			cout << "该车停了" << min << "分钟" << endl;
		}
		else {
			cout << "该车停了" << hour << "小时" << min << "分钟" << endl;
		}
		return true;
	}
}
/*停车的主要操作*/
void test_main_CarPark() {
	
	int c;  //1代表到达 ，其他数字代表离开
	car CAR;
	int key/*车牌号*/;
	int hour, min, sp;
	string s;
	SqStack Park, TempPark;  //元素为car型
	SqQueue Detour;
	InitCar(CAR);
	InitSqStack(Park);
	InitSqStack(TempPark);
	InitSqQueue(Detour);
	while (1) {
		cout << "汽车到达or离开？（输入1表示到达，输入0表示离开）：";
		cin >> c;
		if (c == arrive) {  //到达
			cout << endl << "（到达）请输入车牌号:";
			cin >> key;
			cout << endl << "请输入到达时间（以‘:’分割，如12:00）：";
			cin >> s;
			while (!GetTime(s, hour, min)) { //判断输入是否合法
				cout << "请重新输入:";
				cin >> s;
				continue;
			}
			//创建车
			CreatCar(CAR, key, arrive, inOther);
			CAR.inhour = hour;	CAR.inmin = min;

			if (Push(Park, CAR)) {
				cout << "停在第" << Park.top << "车位" << endl;
				CAR.area = inPark;
				CAR.pos = Park.top;
				//SqStackTraverse(Park, visit_car);
			}
			else {  //停车场已满
					//停入便道
				if (EnSqQueue(Detour, CAR)) {
					cout << "停车场已满，停在临时等候便道第" << Detour.rear << "车位" << endl;
					CAR.area = inDetour;
					CAR.pos = Detour.rear;
				}
				else {
					cout << "对不起，停车场与便道均已满" << endl;
				}
			}
		}
		if (c == leave) {        //离去
			cout << endl << "（离开）请输入车牌号:";
			cin >> key;
			cout << endl << "请输入离开时间（以‘:’分割，如12:00）：";
			cin >> s;
			while (!GetTime(s, hour, min)) { //判断输入是否合法
				cout << "请重新输入:";
				cin >> s;
				continue;
			}
			//创建车
			car k;
			InitCar(k);
			//把后面的车移出来
			while (Pop(Park, k)) {

				if (k.key == key) {
					break;
				}
				Push(TempPark, k);
			}
			if (k.key != key)cout << "停车场内无该车" << endl;
			else {
				car &C = k;
				cout << "车牌为 " << key << " 的车离开" << endl;
				C.outhour = hour;	C.outmin = min;
				int ParkHour = 0, ParkMin = 0, ParkSumTime;
				if (GetParkingTime(C, ParkHour, ParkMin, ParkSumTime)) {
					C.area = inOther;
					C.pos = 0;
					C.status = leave;
				}

			}
			//把后面的车再装进去
			while (Pop(TempPark, k)) {
				Push(Park, k);
			}
			if (DeSqQueue(Detour, k)) Push(Park, k);
		}
		cout << "停车场:入口->";
		SqStackTraverse(Park, visit_car);
		cout << endl;

	}
}