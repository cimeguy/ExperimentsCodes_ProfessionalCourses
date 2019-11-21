// �Ʋٵ�һ����ҵ  �༶��������
// ����


#include <iostream>
#include <queue>
#define Ready 0 /*����*/
#define Finished 1/*�����*/

using namespace std;
struct process {
	int No;//���̺�
	int arrive_time;//����ʱ��
	int require_time;//��Ҫִ�е�ʱ��
	int timeslice ;//ʱ��Ƭ
	int haveran_time;//�Ѿ����е�ʱ��
	int status;//���̵�״̬
	int current_time;//���ڵ�ʱ��
};
struct FBqueue {
	int timeslice ;//ʱ��Ƭ
	queue<process>Q;//�ü�����
};

bool isarrive(process p,int current_time);//�ж��Ƿ񵽴�
int run_p(process& p, int currenttime, int levelnum, queue<process>& allprocess, FBqueue FBQ[]);//���н���
int getarrivetime(process p);
void printme(process p );
int whereisme(process p, int levelnum, FBqueue FBQ[]);//��������һ��


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
int run_p(process &p,int currenttime, int levelnum,queue<process> &allprocess, FBqueue FBQ[]) {//������������ʱ��
	cout << "�������н��̣�";
	printme(p);
	p.current_time = currenttime;
	int level = whereisme(p,levelnum,FBQ);//�ó��ڵڼ���
	cout << "    ���ڵ�" << level+1 << "��   " << endl << endl;
	if (p.haveran_time == 0) {//������߼�
		p.timeslice = FBQ[0].timeslice <p.require_time ? FBQ[0].timeslice : p.require_time;//�ô����е�ʱ��Ƭ
		for (int i = 0; i <p.timeslice; i++) {//�������иý��̵�ÿһ��
			p.current_time++;
			while (!allprocess.empty()) {//�����Ѿ��ź����allprocess
				if(isarrive(allprocess.front(),p.current_time)){//ÿ�ε���Ľ��̾�������߼�
					process front = allprocess.front();
					allprocess.pop();
					FBQ[0].Q.push(front);
				}
				else break;
			}

		}
		p.haveran_time += p.timeslice;
		if (p.require_time == p.haveran_time) {//�ý����Ѿ����
			p.status = Finished;
			cout << "��" << p.current_time << "��:" << "����[" << p.No << "]����ɡ�" << endl << endl;
		}
		else {
			p.status = Ready;
			FBQ[1].Q.push(p);
		}
		return p.current_time;
	}
	else {//�����м伸��Q[level]�������һ��
		int stillreqtime = p.require_time - p.haveran_time;

		p.timeslice = stillreqtime < FBQ[level].timeslice ? stillreqtime : FBQ[level].timeslice;
		bool isNewProArrive = false;
		for (int i = 0; i < p.timeslice; i++) {
			isNewProArrive = false;
			p.current_time++;
			p.haveran_time++;
			while (!allprocess.empty()) {//�����Ѿ��ź����allprocess
				if(isarrive(allprocess.front(),p.current_time)){
				//ÿ���µ���Ľ��̾�����
					isNewProArrive = true;
					process front = allprocess.front();
					allprocess.pop();
					FBQ[0].Q.push(front);
				}
				else break;
			}
			if (isNewProArrive) {//�����ȼ����ߵĶ��е���,���ڱ�����,�����ں���
				p.status = Ready;
				FBQ[level].Q.push(p);
				return p.current_time;
			}
		}
		if (p.haveran_time ==p.require_time) {//���
			//Q[level].pop();
			p.status = Finished;
			cout << "��" << p.current_time << "��:" << "����[" <<p.No << "]����ɡ�" << endl<<endl;
		}
		else {//������һ���������һ�������������һ��
			p.status = Ready;
			if (level != levelnum - 1) {

				FBQ[level + 1].Q.push(p);//����һ��
			}
			else {
				FBQ[level].Q.push(p);//���һ�������������һ��
			}
		}
		return p.current_time;
	}

}

void printme(process p ) {
	cout << "���̺ţ�" << p.No << "    ";
	cout << "����ʱ�䣺" << p.arrive_time << "    ";
	cout << "��Ҫʱ�䣺" << p.require_time << "    ";
	cout << "������ʱ�䣺" << p.haveran_time << "    ";
	cout << "��ǰ״̬��" << p.status << "    ";

}
#include<vector>
using namespace std;
bool cmp(process p1, process p2) {
	return p1.arrive_time < p2.arrive_time;
}
void Init(int levelnum,FBqueue FBQ[] ,queue<process>& allprocess) {
	int pronum = 0;
	int intimeslice;
	vector<process>vpro;//�洢��������Ľ��̣�����ѡ��������Ϊ�˷�������
	cout << "������༶���е�ʱ��Ƭ���ӵ͵��ߣ���" << endl;
	for (int i = levelnum - 1; i >= 0; i--) {
		cin >> intimeslice;
		FBQ[i].timeslice = intimeslice;
	}

	while (1) {
		cout << "�������������";
		cin >> pronum;
		if (pronum > 0) {
			cout << "���������н���:�������¸�ʽ��ʱ��Ϊ���ڵ���0��������" << endl;
			cout << "���̺� ����ʱ�� ��Ҫִ�е�ʱ�� " << endl;
			break;
		}
		else {
			cout << "�����������" << endl;
		}
	}
	int No, arrivetime, requiretime;
	for (int i = 0; i < pronum; i++) {//���������Ϣ
		cin >> No >> arrivetime >> requiretime;
		process A;
		A.No = No;
		A.require_time = requiretime;
		A.arrive_time = arrivetime;
		A.haveran_time = 0;
		A.current_time = 0;
		A.status = Ready;
		A.timeslice = 0;
	
		vpro.push_back(A);//��������vpro��
	}
	sort(vpro.begin(), vpro.end(), cmp);//������ʱ�����򣬲��������allprocess��
	for (vector<process>::iterator it = vpro.begin(); it != vpro.end(); it++) {
		allprocess.push(*it);
		printme(*it);
		cout << endl;
	}
	cout << "------------------------------------------------------------------------" << endl << endl;
}



void MFQ(int levelnum, queue<process> &allprocess, FBqueue FBQ[]) {
	int time = 0;//��ʼʱ��Ϊ0
	while (true)//����ÿ��ʱ��
	{
		cout << "��" << time << "��:" << endl;

		bool allfinished = true;
		for (int i = 0; i < levelnum; i++) {//�����һ��Ϊ�գ���û��ȫ�����
			if (!(FBQ[i].Q.empty())) allfinished = false;
		}
		if (allfinished && allprocess.empty()) {
			cout << "����..." << endl;
			break;
		}//������̳�ʼ���кͶ༶����ȫ��Ϊ�գ����˳�ѭ��

		while (1) {  //����allprocess
			if (!allprocess.empty() && isarrive(allprocess.front(),time))//�����ʼ����δ���Ҷ��е�һ�����̵���
			{
				process temp = allprocess.front();
				allprocess.pop();
				FBQ[0].Q.push(temp);//���µ���Ľ��̷������ȼ���ߵĶ�����
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
				time = run_p(temp, time, levelnum, allprocess, FBQ);//���иý��̣��������������ʱ��
				break;//ÿ����һ��������鿴ǰ�漶�Ķ���
			}
		}
		if (j == levelnum)time++;//û�����н��̣�time++

	}
	cout << "ϵͳ���ȣ��༶�������У����������ķ�ʱ��Ϊ:" << time << endl;
	cout << endl;
}


int main()
{
	int levelnum = 0;
	FBqueue FBQ[20];//���20��,0Ϊ��߼�
	queue<process> allprocess;//��ʼ���н��̶���
	cout << "*****�༶��������*****" << endl;
	cout << "�������������" << endl;
	while (1) {
		cin >> levelnum;
		if (levelnum > 20)cout << "�������󣬲��ó���20��,���������룺" << endl;
		else break;
	}
	Init(levelnum,FBQ,allprocess);
	MFQ(levelnum,allprocess,FBQ);
	return 0;
}

