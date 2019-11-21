//最后版本
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
	/*功能：初始化日志模块，设置日志文件存放的路径。
	参数 path：指向一个文件路径的 C 字符串。
	返回值：日志文件创建成功返回 0，否则返回 - 1。传入的 path 可保存在模块内部的全局
	变量，logStr 函数则可直接输出到该路径指向的文件中。
	提示：可使用 C 语言中文件 IO 操作。
	*/
	if (path == NULL)return -1;
	string spath = path;
	string folderPath = "C:\\temp";//检测是否存在该文件夹  默认为C:\\temp
	std::string::size_type nPos = std::string::npos;
	nPos = spath.find_last_of("log.txt");
	if (nPos != -1) {//找出文件路径
		folderPath = spath.substr(0, nPos - 7);
	}
	else return -1;
	//cout << folderPath << endl;
	string command;
	if (access(folderPath.c_str(), 0) == -1) {//不存在创建文件夹
		command = "mkdir -p " + folderPath;
		system(command.c_str());
	}
	ofstream fout;//在path路径创建文件
	fout.open(path, std::ios::out | std::ios::app);
	PATH = path;
	if (fout.is_open()){//如果文件打开则表示创建成功，关闭文件，返回0
		cout << "初始化日志模块成功……" << endl;
		fout << "这是线程日志文件" << endl;
		fout.close();
		return 0;
	}
	else{//否则创建失败，返回-1
		cout << "初始化日志模块失败……" << endl;
		return -1;
	}
}
int logStr(char* level, char* str) {
	/*功能：将字符串 str 输出到日志文件中，根据 level 字符串设置输出的日志信息。日志格
	式：Level || 线程 id || 时分秒 || str 字符串。要求实现线程安全，确保多线程使用时输出不产
	生乱序或截断等。当日志文件大于 1MB 时，需执行备份操作。 
	参数 level：C 字符串，可能的 level 包括：Normal，Warning，Alert，Error 等。 
	参数 str：C 字符串，用户需要输出的日志信息。 
	返回值：符合要求返回 0，否则返回-1. 
	提示：使用标准线程库，可使用互斥量保证线程安全，尝试 RAII 用法。 */
	//if (level == NULL || str == NULL)return -1;
	if (PATH == NULL)return -1;
	time_t currentTime;
	time(&currentTime);
	struct tm* p;
	p = localtime(&currentTime);//便于获得时分秒
	lock_guard<mutex> LockGuard(m);//锁机制看管 RAII
	ofstream fout;
	time_t timep;//获得时间
	time(&timep);
	fout.open(PATH, std::ios::out | std::ios::app);
	//输出
	fout << level << " || " << std::this_thread::get_id() << " || " 
		<<p->tm_hour<<":"<<p->tm_min<<":"<<p->tm_sec << " || " << str << endl;
	//cout << fout.tellp()/1024<<endl;
	if (fout.tellp()> 1024* 1024){//备份文件
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