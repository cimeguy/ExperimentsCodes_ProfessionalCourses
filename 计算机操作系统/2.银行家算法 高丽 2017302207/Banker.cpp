// 计操第二次作业  银行家
// 高丽

#include<iostream>
#include<queue>

#define MAX_PROCESSES 20
#define MAX_RESOURCES 15
using namespace std;
bool SafetyCheck(int m/*资源数*/, int n/*进程数*/, int Allocation[MAX_PROCESSES][MAX_RESOURCES],
	int Need[MAX_PROCESSES][MAX_RESOURCES], int Available[], int Safetyqueue[]/*返回安全序列*/,
	int workandallocation[][MAX_RESOURCES]/*便于后续输出*/) {
	int p, r;
	int count = 0;//计算Finish的个数
	int Work[MAX_RESOURCES];
	
	bool Finish[MAX_PROCESSES];
	for (r = 0; r < m; r++)//初始等于Available[]
		Work[r] = Available[r];
	for (p = 0; p < n; p++)
		Finish[p] = false;
	bool found = false;

	while (1) {//
		int count_unfi_p = 0;//注意该语句位置！！之前放在while外面出错
		found = false;
		for (p = 0; p < n; p++) {//从进程集合中寻找
			if (!Finish[p]) {
				int countr = 0;
				for (r = 0; r < m; r++) {//对于p进程
					if (Need[p][r] <= Work[r]) countr++;
				}
				if (countr == m) {
					found = true;//找到执行第三步
					break;
				}
			}
			count_unfi_p++;//不符合的进程数+1
		}
		if (count_unfi_p == n) //没有找到满足条件的进程
			break;
		if (found) {//第三步
			for (r = 0; r < m; r++) {//对于p进程
				Work[r] = Work[r] + Allocation[p][r];
				workandallocation[p][r] = Work[r];
			}
			Finish[p] = true;
			
			Safetyqueue[count] = p;
			count++;
		}
	}
	//第四步  如果所有进程Finish[p]为true 则安全
	if (count != n) return false;
	else return true;
}
void PrintSafety(int Safetyqueue[], int m/*资源数*/, int n/*进程数*/,int Max[][MAX_RESOURCES],
	int Allocation[][MAX_RESOURCES],int Need[][MAX_RESOURCES], int Available[],
	int workandallocation[][MAX_RESOURCES]/*便于后续输出*/) {
	//仅在安全时输出
	int r = 0;
	cout << "-----------------------安全检查--------------------------" << endl;
	cout << "输出分别为Max矩阵、Need矩阵、Allocation矩阵、Work+Allocation、Finish：" << endl;
	for(int i = 0;i<n;i++){
		int temp = Safetyqueue[i];
		
		cout << "进程 [" << temp << "]:  |  ";
		for (r = 0; r < m; r++) {
			cout << Max[temp][r] << "  ";
		}cout << "|  ";
		for (r = 0; r < m; r++) {
			cout << Need[temp][r] << "  ";
		}cout << "|  ";
		for (r = 0; r < m; r++) {
			cout << Allocation[temp][r] << "  ";
		}cout << "|  ";
		for (r = 0; r < m; r++) {
			cout << workandallocation[temp][r] << "  ";
		}cout << "|  ";
		cout <<"true"<< endl;

	}
	cout <<endl<< "安全序列：";
	for (int i = 0; i < n; i++) {
		cout << Safetyqueue[i] << "  ";
	}
	cout << endl<<endl;
}
void Init(int m/*资源数*/,int n/*进程数*/,int Max[][MAX_RESOURCES],
	int Allocation[][MAX_RESOURCES],int Need[][MAX_RESOURCES] ,int Available[]) {
	while (1) {
		int p, r;
		cout << "请输入各进程最大需求矩阵Max[P][R]：" << endl;
		for (p = 0; p < n; p++)
			for (r = 0; r < m; r++)
				cin >> Max[p][r];
		cout << endl << "请输入分配矩阵Allocation[P][R]：" << endl;
		for (p = 0; p < n; p++)
			for (r = 0; r < m; r++)
				cin >> Allocation[p][r];
		cout << endl << "则需求矩阵（还需要的资源数）Need[P][R]为：" << endl;
		for (p = 0; p < n; p++) {
			for (r = 0; r < m; r++) {
				Need[p][r] = Max[p][r] - Allocation[p][r];
				cout << Need[p][r] << " ";
			}
			cout << endl;
		}
		cout << endl << "请输入可利用资源Available[R]：" << endl;
		for (r = 0; r < m; r++)
			cin >> Available[r];
		cout << endl;
		int Safetyqueue[MAX_PROCESSES];
		int workandallocation[MAX_PROCESSES][MAX_RESOURCES];
		if (SafetyCheck(m, n, Allocation, Need, Available, Safetyqueue,workandallocation)) {//先安全性检查
			PrintSafety(Safetyqueue,m,n,Max,Allocation,Need,Available,workandallocation);
			break;
		}
		else {//不安全
			cout << "初始化：不安全！请重新输入：" << endl;
			continue;
		}
	}
}

void PRequest(int m/*资源数*/, int n/*进程数*/,int &p,int Request[MAX_PROCESSES][MAX_RESOURCES]) {
	cout << "-------请求资源---------:" << endl;
	int  r;
	while (true)
	{
		cout << "输入请求资源的进程：（若输入-1，则表示结束申请）";
		cin >> p;
		cout << endl;
		if (p == -1) {
			return;
		}
		if (p<0 || p>n - 1) {
			cout << "参数错误，进程号不得小于0，或大于" << n << endl;
			continue;
		}
		cout << "输入请求资源数量：" << endl;
		for (r = 0; r < m; r++) {
			cin>>Request[p][r];
		}
		break;
	}
}
void Banker(int m/*资源数*/, int n/*进程数*/,int p/*申请资源的进程*/, int Max[][MAX_RESOURCES],
	int Allocation[][MAX_RESOURCES],int Need[][MAX_RESOURCES],int Available[],int Request[][MAX_RESOURCES]) {
	int r;
	int Safetyqueue[MAX_PROCESSES];/*安全序列*/

	for (r = 0; r < m; r++) {
		if (Request[p][r] > Need[p][r]) {
			std::cout << "申请资源超过需要的最大值。" << endl;
			return;
		}
		if (Request[p][r] > Available[r]) {
			cout << "尚无足够资源，进程阻塞。" << endl;
			return;
		}
	}
	for (r = 0; r < m; r++) {
		Available[r] -= Request[p][r];
		Allocation [p][r]+= Request[p][r];
		Need[p][r] -= Request[p][r];
	}
	int workandallocation[MAX_PROCESSES][MAX_RESOURCES];
	if (SafetyCheck(m, n, Allocation, Need, Available, Safetyqueue,workandallocation)) {
		PrintSafety(Safetyqueue, m, n, Max, Allocation, Need, Available, workandallocation);
	}
	else {
		cout << "不安全的分配! 本次试探分配作废。" << endl;
		for (r = 0; r < m; r++) {
			Available[r] += Request[p][r];
			Allocation[p][r] -= Request[p][r];
			Need[p][r] += Request[p][r];
		}
	}
	cout << "-------------------现在资源分配情况---------------------" << endl;
	cout << "输出分别为Max矩阵、Need矩阵、Allocation矩阵、Available矩阵：" << endl;
	for (int i = 0; i < n; i++) {
		cout << "进程 [" << i << "]:  | ";
		for (r = 0; r < m; r++) {
			cout << Max[i][r] << "  ";
		}cout << "|  ";
		for (r = 0; r < m; r++) {
			cout << Need[i][r] << "  ";
		}cout << "|  "; 
		for (r = 0; r < m; r++) {
			cout << Allocation[i][r] << "  ";
		}cout << "|";
		if (i == 0) {
			for (r = 0; r < m; r++) {
				cout << Available[r] << "  ";
			}cout << "|";
		}
		cout << endl;
	}
	cout << endl;
}
int main() {
	int m , n ;//m为资源数（最大为MAX_RESOURCES），n为进程数（最大为MAX_PROCESSES）
	int Available[MAX_RESOURCES];//可利用资源向量
	int Max[MAX_PROCESSES][MAX_RESOURCES];//最大需求矩阵
	int Allocation[MAX_PROCESSES][MAX_RESOURCES];//分配矩阵（已分配）
	int Need[MAX_PROCESSES][MAX_RESOURCES];//需求矩阵，（还需要）
	int Request[MAX_PROCESSES][MAX_RESOURCES];

	cout << "*****银行家算法*****" << endl;
	while (1) {//输入m,n并检查大小
		cout << "请输入进程数量和资源数量：";
		cin >>n>>m;
		if (m <= MAX_RESOURCES && n <= MAX_PROCESSES)break;
		else if (m > MAX_RESOURCES)cout << "参数错误，m不得大于MAX_RESOURCES" << endl;
		else cout << "参数错误，n不得大于 MAX_PROCESSES" << endl;
	}
	Init(m, n, Max, Allocation, Need, Available);//输入初始数据
	int p = 0;
	while (1) {
		PRequest(m, n, p, Request);
		if (p == -1)break;//结束程序
		Banker(m, n, p, Max, Allocation, Need, Available, Request);
	}
	cout << "结束模拟。" << endl;
	return 0;
}