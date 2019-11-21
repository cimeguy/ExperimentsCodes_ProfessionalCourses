//���汾
#include"LogSafe.h"
#include <iostream>
#include <fstream>
#include <mutex>
#include<thread>
#include<time.h>
#include  <io.h>
#include <direct.h>
#include <Windows.h>
//#include <io.h>
//#include<direct.h>
using namespace std;
char* PATH = NULL;
char NEWPATH[] = "C:\temp\log2.txt";
mutex m;
int initLog(char* path) {
	/*���ܣ���ʼ����־ģ�飬������־�ļ���ŵ�·����
	���� path��ָ��һ���ļ�·���� C �ַ�����
	����ֵ����־�ļ������ɹ����� 0�����򷵻� - 1������� path �ɱ�����ģ���ڲ���ȫ��
	������logStr �������ֱ���������·��ָ����ļ��С�
	��ʾ����ʹ�� C �������ļ� IO ������
	*/
	if (path == NULL)return -1;
	string spath = path;
	string folderPath = "C:\\temp";//����Ƿ���ڸ��ļ���  Ĭ��ΪC:\\temp
	std::string::size_type nPos = std::string::npos;
	nPos = spath.find_last_of("log.txt");
	if (nPos != -1) {//�ҳ��ļ�·��
		folderPath = spath.substr(0, nPos - 7);
	}
	else return -1;
	//cout << folderPath << endl;
	string command;
	if (access(folderPath.c_str(), 0) == -1) {//�����ڴ����ļ���
		command = "mkdir -p " + folderPath;
		system(command.c_str());
	}
	ofstream fout;//��path·�������ļ�
	fout.open(path, std::ios::out | std::ios::app);
	PATH = path;
	if (fout.is_open()){//����ļ������ʾ�����ɹ����ر��ļ�������0
		cout << "��ʼ����־ģ��ɹ�����" << endl;
		fout << "�����߳���־�ļ�" << endl;
		fout.close();
		return 0;
	}
	else{//���򴴽�ʧ�ܣ�����-1
		cout << "��ʼ����־ģ��ʧ�ܡ���" << endl;
		return -1;
	}
}
int logStr(char* level, char* str) {
	/*���ܣ����ַ��� str �������־�ļ��У����� level �ַ��������������־��Ϣ����־��
	ʽ��Level || �߳� id || ʱ���� || str �ַ�����Ҫ��ʵ���̰߳�ȫ��ȷ�����߳�ʹ��ʱ�������
	�������ضϵȡ�����־�ļ����� 1MB ʱ����ִ�б��ݲ����� 
	���� level��C �ַ��������ܵ� level ������Normal��Warning��Alert��Error �ȡ� 
	���� str��C �ַ������û���Ҫ�������־��Ϣ�� 
	����ֵ������Ҫ�󷵻� 0�����򷵻�-1. 
	��ʾ��ʹ�ñ�׼�߳̿⣬��ʹ�û�������֤�̰߳�ȫ������ RAII �÷��� */
	//if (level == NULL || str == NULL)return -1;
	if (PATH == NULL)return -1;
	time_t currentTime;
	time(&currentTime);
	struct tm* p;
	p = localtime(&currentTime);//���ڻ��ʱ����
	lock_guard<mutex> LockGuard(m);//�����ƿ��� RAII
	ofstream fout;
	time_t timep;//���ʱ��
	time(&timep);
	fout.open(PATH, std::ios::out | std::ios::app);
	//���
	fout << level << " || " << std::this_thread::get_id() << " || " 
		<<p->tm_hour<<":"<<p->tm_min<<":"<<p->tm_sec << " || " << str << endl;
	//cout << fout.tellp()/1024<<endl;
	if (fout.tellp()> 1024* 1024){//�����ļ�
		LPCTSTR P1 =(LPCTSTR) PATH;
		LPCTSTR P2 = (LPCTSTR)NEWPATH;
		CopyFile(P1, P2, FALSE);
	}
	fout.close();
	return 0;

}

//void ThreadFun() {
//	char c1[] = "Normal", c2[] = "Start Normal Testing ...";
//	logStr(c1,c2 );
//	char c3[] = "Warning",c4[] = "Start Warning Testing ...";
//	logStr(c3,c4);
//	//logStr("Alert", "Start Alert Testing ...");
//	//logStr("Error", "Start Error Testing ...");
//}