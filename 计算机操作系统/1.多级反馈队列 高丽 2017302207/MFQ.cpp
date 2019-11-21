// 计操第一次作业  多级反馈队列
// 高丽


#include <iostream>
#include <queue>
#define Ready 0 /*就绪*/
#define Finished 1/*已完成*/

using namespace std;
struct process {
	int No;//进程号
	int arrive_time;//到达时间
	int require_time;//需要执行的时间
	int timeslice ;//时间片
	int haveran_time;//已经运行的时间
	int status;//进程的状态
	int current_time;//现在的时间
};
struct FBqueue {
	int timeslice ;//时间片
	queue<process>Q;//该级队列
};

bool isarrive(process p,int current_time);//判断是否到达
int run_p(process& p, int currenttime, int levelnum, queue<process>& allprocess, FBqueue FBQ[]);//运行进程
int getarrivetime(process p);
void printme(process p );
int whereisme(process p, int levelnum, FBqueue FBQ[]);//返回在哪一级


int getarrivetime(process p) {
	return p.arrive_time;
}

bool isarrive(process p,int current_time) {
	if (p.arrive_time <= current_time) return true;
	else return false;
}

int whereisme(process p, int levelnum, FBqueue FBQ[]) {
	int sum = 0;
	int i = 0;
	for (i = 0; i < levelnum - 1; i++) {
		sum += FBQ[i].timeslice;
		if (p.haveran_time == 0)return 0;
		else if (p.haveran_time >= sum && p.haveran_time < (sum + FBQ[i+1].timeslice)) {
			return (i + 1);
		}
	}
	return levelnum - 1;

}
int run_p(process &p,int currenttime, int levelnum,queue<process> &allprocess, FBqueue FBQ[]) {//返回运行完后的时间
	cout << "正在运行进程：";
	printme(p);
	p.current_time = currenttime;
	int level = whereisme(p,levelnum,FBQ);//得出在第几级
	cout << "    处于第" << level+1 << "级   " << endl << endl;
	if (p.haveran_time == 0) {//处于最高级
		p.timeslice = FBQ[0].timeslice <p.require_time ? FBQ[0].timeslice : p.require_time;//该次运行的时间片
		for (int i = 0; i <p.timeslice; i++) {//对于运行该进程的每一秒
			p.current_time++;
			while (!allprocess.empty()) {//遍历已经排好序的allprocess
				if(isarrive(allprocess.front(),p.current_time)){//每次到达的进程均进入最高级
					process front = allprocess.front();
					allprocess.pop();
					FBQ[0].Q.push(front);
				}
				else break;
			}

		}
		p.haveran_time += p.timeslice;
		if (p.require_time == p.haveran_time) {//该进程已经完成
			p.status = Finished;
			cout << "第" << p.current_time << "秒:" << "进程[" << p.No << "]已完成。" << endl << endl;
		}
		else {
			p.status = Ready;
			FBQ[1].Q.push(p);
		}
		return p.current_time;
	}
	else {//处于中间几级Q[level]级或最后一级
		int stillreqtime = p.require_time - p.haveran_time;

		p.timeslice = stillreqtime < FBQ[level].timeslice ? stillreqtime : FBQ[level].timeslice;
		bool isNewProArrive = false;
		for (int i = 0; i < p.timeslice; i++) {
			isNewProArrive = false;
			p.current_time++;
			p.haveran_time++;
			while (!allprocess.empty()) {//遍历已经排好序的allprocess
				if(isarrive(allprocess.front(),p.current_time)){
				//每次新到达的进程均进入
					isNewProArrive = true;
					process front = allprocess.front();
					allprocess.pop();
					FBQ[0].Q.push(front);
				}
				else break;
			}
			if (isNewProArrive) {//有优先级更高的队列到来,还在本队列,但处于后面
				p.status = Ready;
				FBQ[level].Q.push(p);
				return p.current_time;
			}
		}
		if (p.haveran_time ==p.require_time) {//完成
			//Q[level].pop();
			p.status = Finished;
			cout << "第" << p.current_time << "秒:" << "进程[" <<p.No << "]已完成。" << endl<<endl;
		}
		else {//进入下一级或者最后一级继续放在最后一级
			p.status = Ready;
			if (level != levelnum - 1) {

				FBQ[level + 1].Q.push(p);//给下一级
			}
			else {
				FBQ[level].Q.push(p);//最后一级继续放在最后一级
			}
		}
		return p.current_time;
	}

}

void printme(process p ) {
	cout << "进程号：" << p.No << "    ";
	cout << "到达时间：" << p.arrive_time << "    ";
	cout << "需要时间：" << p.require_time << "    ";
	cout << "已运行时间：" << p.haveran_time << "    ";
	cout << "当前状态：" << p.status << "    ";

}
#include<vector>
using namespace std;
bool cmp(process p1, process p2) {
	return p1.arrive_time < p2.arrive_time;
}
void Init(int levelnum,FBqueue FBQ[] ,queue<process>& allprocess) {
	int pronum = 0;
	int intimeslice;
	vector<process>vpro;//存储所有输入的进程，这里选择容器是为了方便排序
	cout << "请输入多级队列的时间片（从低到高）：" << endl;
	for (int i = levelnum - 1; i >= 0; i--) {
		cin >> intimeslice;
		FBQ[i].timeslice = intimeslice;
	}

	while (1) {
		cout << "请输入进程数：";
		cin >> pronum;
		if (pronum > 0) {
			cout << "请输入所有进程:（按以下格式，时间为大于等于0的整数）" << endl;
			cout << "进程号 到达时间 需要执行的时间 " << endl;
			break;
		}
		else {
			cout << "输入参数错误" << endl;
		}
	}
	int No, arrivetime, requiretime;
	for (int i = 0; i < pronum; i++) {//输入进程信息
		cin >> No >> arrivetime >> requiretime;
		process A;
		A.No = No;
		A.require_time = requiretime;
		A.arrive_time = arrivetime;
		A.haveran_time = 0;
		A.current_time = 0;
		A.status = Ready;
		A.timeslice = 0;
	
		vpro.push_back(A);//加入容器vpro中
	}
	sort(vpro.begin(), vpro.end(), cmp);//按到达时间排序，并放入队列allprocess中
	for (vector<process>::iterator it = vpro.begin(); it != vpro.end(); it++) {
		allprocess.push(*it);
		printme(*it);
		cout << endl;
	}
	cout << "------------------------------------------------------------------------" << endl << endl;
}



void MFQ(int levelnum, queue<process> &allprocess, FBqueue FBQ[]) {
	int time = 0;//初始时间为0
	while (true)//遍历每个时间
	{
		cout << "第" << time << "秒:" << endl;

		bool allfinished = true;
		for (int i = 0; i < levelnum; i++) {//如果有一级为空，则并没有全部完成
			if (!(FBQ[i].Q.empty())) allfinished = false;
		}
		if (allfinished && allprocess.empty()) {
			cout << "结束..." << endl;
			break;
		}//如果进程初始队列和多级队列全部为空，则退出循环

		while (1) {  //遍历allprocess
			if (!allprocess.empty() && isarrive(allprocess.front(),time))//如果初始队列未空且队列第一个进程到达
			{
				process temp = allprocess.front();
				allprocess.pop();
				FBQ[0].Q.push(temp);//有新到达的进程放入优先级最高的队列中
			}
			else
			{
				break;
			}
		}
		int j = 0;
		for (j = 0; j < levelnum; j++) {
			if (!FBQ[j].Q.empty()) {
				process temp = FBQ[j].Q.front();
				FBQ[j].Q.pop();
				time = run_p(temp, time, levelnum, allprocess, FBQ);//运行该进程，并返回运行完的时间
				break;//每运行一个程序都需查看前面级的队列
			}
		}
		if (j == levelnum)time++;//没有运行进程，time++

	}
	cout << "系统调度（多级反馈队列）结束——耗费时间为:" << time << endl;
	cout << endl;
}


int main()
{
	int levelnum = 0;
	FBqueue FBQ[20];//最大20级,0为最高级
	queue<process> allprocess;//初始所有进程队列
	cout << "*****多级反馈队列*****" << endl;
	cout << "请输入队列数：" << endl;
	while (1) {
		cin >> levelnum;
		if (levelnum > 20)cout << "参数错误，不得超过20级,请重新输入：" << endl;
		else break;
	}
	Init(levelnum,FBQ,allprocess);
	MFQ(levelnum,allprocess,FBQ);
	return 0;
}

