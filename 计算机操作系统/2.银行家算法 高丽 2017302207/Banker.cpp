// �Ʋٵڶ�����ҵ  ���м�
// ����

#include<iostream>
#include<queue>

#define MAX_PROCESSES 20
#define MAX_RESOURCES 15
using namespace std;
bool SafetyCheck(int m/*��Դ��*/, int n/*������*/, int Allocation[MAX_PROCESSES][MAX_RESOURCES],
	int Need[MAX_PROCESSES][MAX_RESOURCES], int Available[], int Safetyqueue[]/*���ذ�ȫ����*/,
	int workandallocation[][MAX_RESOURCES]/*���ں������*/) {
	int p, r;
	int count = 0;//����Finish�ĸ���
	int Work[MAX_RESOURCES];
	
	bool Finish[MAX_PROCESSES];
	for (r = 0; r < m; r++)//��ʼ����Available[]
		Work[r] = Available[r];
	for (p = 0; p < n; p++)
		Finish[p] = false;
	bool found = false;

	while (1) {//
		int count_unfi_p = 0;//ע������λ�ã���֮ǰ����while�������
		found = false;
		for (p = 0; p < n; p++) {//�ӽ��̼�����Ѱ��
			if (!Finish[p]) {
				int countr = 0;
				for (r = 0; r < m; r++) {//����p����
					if (Need[p][r] <= Work[r]) countr++;
				}
				if (countr == m) {
					found = true;//�ҵ�ִ�е�����
					break;
				}
			}
			count_unfi_p++;//�����ϵĽ�����+1
		}
		if (count_unfi_p == n) //û���ҵ����������Ľ���
			break;
		if (found) {//������
			for (r = 0; r < m; r++) {//����p����
				Work[r] = Work[r] + Allocation[p][r];
				workandallocation[p][r] = Work[r];
			}
			Finish[p] = true;
			
			Safetyqueue[count] = p;
			count++;
		}
	}
	//���Ĳ�  ������н���Finish[p]Ϊtrue ��ȫ
	if (count != n) return false;
	else return true;
}
void PrintSafety(int Safetyqueue[], int m/*��Դ��*/, int n/*������*/,int Max[][MAX_RESOURCES],
	int Allocation[][MAX_RESOURCES],int Need[][MAX_RESOURCES], int Available[],
	int workandallocation[][MAX_RESOURCES]/*���ں������*/) {
	//���ڰ�ȫʱ���
	int r = 0;
	cout << "-----------------------��ȫ���--------------------------" << endl;
	cout << "����ֱ�ΪMax����Need����Allocation����Work+Allocation��Finish��" << endl;
	for(int i = 0;i<n;i++){
		int temp = Safetyqueue[i];
		
		cout << "���� [" << temp << "]:  |  ";
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
	cout <<endl<< "��ȫ���У�";
	for (int i = 0; i < n; i++) {
		cout << Safetyqueue[i] << "  ";
	}
	cout << endl<<endl;
}
void Init(int m/*��Դ��*/,int n/*������*/,int Max[][MAX_RESOURCES],
	int Allocation[][MAX_RESOURCES],int Need[][MAX_RESOURCES] ,int Available[]) {
	while (1) {
		int p, r;
		cout << "���������������������Max[P][R]��" << endl;
		for (p = 0; p < n; p++)
			for (r = 0; r < m; r++)
				cin >> Max[p][r];
		cout << endl << "������������Allocation[P][R]��" << endl;
		for (p = 0; p < n; p++)
			for (r = 0; r < m; r++)
				cin >> Allocation[p][r];
		cout << endl << "��������󣨻���Ҫ����Դ����Need[P][R]Ϊ��" << endl;
		for (p = 0; p < n; p++) {
			for (r = 0; r < m; r++) {
				Need[p][r] = Max[p][r] - Allocation[p][r];
				cout << Need[p][r] << " ";
			}
			cout << endl;
		}
		cout << endl << "�������������ԴAvailable[R]��" << endl;
		for (r = 0; r < m; r++)
			cin >> Available[r];
		cout << endl;
		int Safetyqueue[MAX_PROCESSES];
		int workandallocation[MAX_PROCESSES][MAX_RESOURCES];
		if (SafetyCheck(m, n, Allocation, Need, Available, Safetyqueue,workandallocation)) {//�Ȱ�ȫ�Լ��
			PrintSafety(Safetyqueue,m,n,Max,Allocation,Need,Available,workandallocation);
			break;
		}
		else {//����ȫ
			cout << "��ʼ��������ȫ�����������룺" << endl;
			continue;
		}
	}
}

void PRequest(int m/*��Դ��*/, int n/*������*/,int &p,int Request[MAX_PROCESSES][MAX_RESOURCES]) {
	cout << "-------������Դ---------:" << endl;
	int  r;
	while (true)
	{
		cout << "����������Դ�Ľ��̣���������-1�����ʾ�������룩";
		cin >> p;
		cout << endl;
		if (p == -1) {
			return;
		}
		if (p<0 || p>n - 1) {
			cout << "�������󣬽��̺Ų���С��0�������" << n << endl;
			continue;
		}
		cout << "����������Դ������" << endl;
		for (r = 0; r < m; r++) {
			cin>>Request[p][r];
		}
		break;
	}
}
void Banker(int m/*��Դ��*/, int n/*������*/,int p/*������Դ�Ľ���*/, int Max[][MAX_RESOURCES],
	int Allocation[][MAX_RESOURCES],int Need[][MAX_RESOURCES],int Available[],int Request[][MAX_RESOURCES]) {
	int r;
	int Safetyqueue[MAX_PROCESSES];/*��ȫ����*/

	for (r = 0; r < m; r++) {
		if (Request[p][r] > Need[p][r]) {
			std::cout << "������Դ������Ҫ�����ֵ��" << endl;
			return;
		}
		if (Request[p][r] > Available[r]) {
			cout << "�����㹻��Դ������������" << endl;
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
		cout << "����ȫ�ķ���! ������̽�������ϡ�" << endl;
		for (r = 0; r < m; r++) {
			Available[r] += Request[p][r];
			Allocation[p][r] -= Request[p][r];
			Need[p][r] += Request[p][r];
		}
	}
	cout << "-------------------������Դ�������---------------------" << endl;
	cout << "����ֱ�ΪMax����Need����Allocation����Available����" << endl;
	for (int i = 0; i < n; i++) {
		cout << "���� [" << i << "]:  | ";
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
	int m , n ;//mΪ��Դ�������ΪMAX_RESOURCES����nΪ�����������ΪMAX_PROCESSES��
	int Available[MAX_RESOURCES];//��������Դ����
	int Max[MAX_PROCESSES][MAX_RESOURCES];//����������
	int Allocation[MAX_PROCESSES][MAX_RESOURCES];//��������ѷ��䣩
	int Need[MAX_PROCESSES][MAX_RESOURCES];//������󣬣�����Ҫ��
	int Request[MAX_PROCESSES][MAX_RESOURCES];

	cout << "*****���м��㷨*****" << endl;
	while (1) {//����m,n������С
		cout << "�����������������Դ������";
		cin >>n>>m;
		if (m <= MAX_RESOURCES && n <= MAX_PROCESSES)break;
		else if (m > MAX_RESOURCES)cout << "��������m���ô���MAX_RESOURCES" << endl;
		else cout << "��������n���ô��� MAX_PROCESSES" << endl;
	}
	Init(m, n, Max, Allocation, Need, Available);//�����ʼ����
	int p = 0;
	while (1) {
		PRequest(m, n, p, Request);
		if (p == -1)break;//��������
		Banker(m, n, p, Max, Allocation, Need, Available, Request);
	}
	cout << "����ģ�⡣" << endl;
	return 0;
}