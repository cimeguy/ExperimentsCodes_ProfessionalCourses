//  计操第三次作业  分页
//高丽
//2019/11/8
#include <iostream>
#include<vector>
#include <time.h>
#include<algorithm>//使用sort

#define memfree 1//内存块空闲
#define memalloc 0//内存块已分配

#define bitmap_maxsize 500//最大是500*8 = 4000 个块
#define mem_maxsize 1638400//1600*1024
#define block_maxsize 1024//内存块最大大小;
#define maxtime 2000;
using namespace std;

struct Page {
	int page_no;//页号，均从0起始
	int block_no;//内存块号  
	struct Page* next;//指向下一页
};
typedef struct Memory {//内存结构体
	int block_num;//页面数 ==内存块数 pagecnt
	int block_size;//页面大小 ==内存块大小
	int freeblock_num;//空闲块数
	//int bitmap[PAGE_MAX_X + 1][PAGE_MAX_Y];
	char bitmap[bitmap_maxsize];//char[i]从低位到高位编号   块数从0开始编号
	/*位示图,memfree表示空闲，memalloc表示已被分配
	bitmap[]存储空闲块数*/
}Mem;
Mem memory;
typedef struct Process {//进程
	int no;//作业号
	int arrive_time;//到达时间
	int exec_time;//执行时间
	int N;//作业需要的内存块数
	int isalloc;//0未分配内存 1已分配内存
	Page* page_table; //每个进程有一个页表
	//说明：头节点不存储任何东西
}PCB;
vector <Process>processes;//进程列表

bool comp(const Process& a, const Process& b) {//用于进程序列排序
     return a.arrive_time < b.arrive_time;
}
bool free_mem(Process& p);
void pagestr();

//位示图的操作
void setbit_blocki(int i, int v) {//第i块设置为v；i从0开始
	int chari = i/8;//第i块所在的某个char
	int biti = i%8;//第i块所在的位数
	char c = memory.bitmap[chari];
	if (v) {
		c |= (1 << biti);
	}
	else {
		c &= ~(1 << biti);
	}
	memory.bitmap[chari] = c;
	//cout <<"c:" <<int(c)<<endl;
}
int getbit_blocki(int i) {//获得第i块状态
	int chari = i / 8;//第i块所在的某个char
	int biti = i % 8;//第i块所在的位数
	char c = memory.bitmap[chari];
	return (c >> biti) & 1;
}
void print_bitmap() {
	char yn;
	cout << "是否查看位示图?(y or n)";
	while (1) {
		cin >> yn;
		if (yn == 'y'||yn =='Y') {//查看
			cout << "32位系统下：" << endl;
			cout << "这里 1表示空闲，0表示已被分配：" << endl;
			for (int i = 0; i < memory.block_num; i++) {
				cout << getbit_blocki(i)<<" ";
				if ((i + 1) % 32 == 0)cout << endl;//32位输出一行
			}
			cout << endl;
			cout << "空闲块："<<memory.freeblock_num << "个。" << endl;
			return;
		}
		else if(yn =='n'||yn=='N') {
			return;
		}
		else {
			cout << "输入错误，请重新输入：是否查看位示图?(y or n)" << endl;
		}
	}
}
void init_bitmap() {
	cout << "因模拟中间过程，故初始化位示图：部分内存已分配……" << endl;
	srand(time(0));
	for (int i = 0; i < memory.block_num; i++) {//先全部空闲
		setbit_blocki(i, memfree);
	}
	for (int i = 0; i < (memory.block_num)/3; i++) {//有一半已分配
		int rand_num = rand() %(memory.block_num);
		//cout << "randnum:"<<rand_num << " ";
		setbit_blocki(rand_num, memalloc);
	}
	//计算空闲块数
	int freeblock_cnt = 0;
	for (int i = 0; i < memory.block_num; i++) {//第i块
		if (getbit_blocki(i) == memfree)freeblock_cnt++;//如果为1则空闲
	}
	memory.freeblock_num = freeblock_cnt;
	print_bitmap();
}

void init_Mem(){//初始化内存
	cout << "初始化内存信息——请分别输入计算机的内存大小和内存块的大小（以KB为单位）：";
	int memsize = 0;
	int block_size = 0;
	while (true) {
		cin >> memsize;
		if (memsize <= mem_maxsize) break;
		cout << "内存过大!请重新输入：";
	}
	while (true){
		cin >> block_size;
		if (block_size <= block_maxsize)break;
		cout << "内存块过大!请重新输入：";
	}
	//cout << "模拟中间过程……" << endl;
	memory.block_num = memsize / block_size;//计算可用内存块数时向下取整，最后的碎片遗弃
	cout << "共有" << memory.block_num << "个内存块" << endl;
	memory.block_size = block_size;
	init_bitmap();
}

bool creat_PCB(Process &p){
	int needmemsize = 0;
	while (true) {//输入进程需要的内存空间大小
		cin >> p.no >> needmemsize >> p.arrive_time >> p.exec_time;//输入进程号
		if (needmemsize > (memory.block_num * memory.block_size))cout << "需要内存太大！重新输入进程信息：";
		else if (needmemsize <= 0)cout << "需要内存为0，错误！" << endl;
		else if (p.arrive_time < 0 || p.exec_time <= 0)cout << "时间错误！" << endl;
		else break;
	}
	p.isalloc = 0;//初始化时还未分配内存
	//初始化页表
	p.N = (needmemsize - 1) / memory.block_size + 1;//获得作业需要的内存块数  向上取整
	if (p.N > memory.freeblock_num) {//一开始就大于初始空闲数量
		cout << "进程[" << p.no << "]创建失败，不符合要求。" << endl;
		return false;
	}
	//cout << "需" << p.N << "页。" << endl;
	p.page_table = new Page;//初始化头节点
	if (p.page_table == NULL) {
		cout << "初始化页表失败！" << endl;
		cout << "进程[" << p.no << "]创建失败，不符合要求。" << endl;
		return false;
	}
	p.page_table->next = NULL;//下一个节点置空
	return true;
}
void print_pagetable(Process p) {

	if (p.isalloc == 0) {//未分配
		cout << "       进程[" << p.no << "]未分配内存，无页表信息。" << endl;
		return;
	}
	if (p.N >= 10) {
		char yn;
		cout << "       页表信息较长，是否打印？（y/n）：";
		while (cin >> yn) {
			if (yn == 'Y' || yn == 'y') {
				cout << "       进程[" << p.no << "]的页表信息如下：";
				cout << "(" << p.N << "页)" << endl;
				Page* pag = p.page_table->next;//指向第0页
				while (pag) {
					cout << "       页号 " << pag->page_no << "  ---块号  " << pag->block_no << endl;
					pag = pag->next;
				}
				cout << endl;
				break;
			}
			else if (yn == 'n' || yn == 'N') {//不打印
				cout << endl;
				break;
			}
			else {
				cout << "输入错误，是否打印页表信息？（y/n）：";
			}
		}
	}
	else {//信息较短时直接输出
		cout << "       进程[" << p.no << "]的页表信息如下：";
		cout << "(" << p.N << "页)" << endl;
		Page* pag = p.page_table->next;//指向第0页
		while (pag) {
			cout << "       页号 " << pag->page_no << "  ---块号  " << pag->block_no << endl;
			pag = pag->next;
		}
		cout << endl;

	}
	
}
bool alloc_mem(Process& p) {
	if (p.N > memory.freeblock_num) {//所需内存块数大于空闲块数
		//cout << "进程[" << p.no << "]所需内存块数大于空闲块数" << memory.freeblock_num << "，无法分配。进程等待。" << endl;
		//p.isalloc = -1;//表示在等待
		return false;
	}
	int cntpage = 0;
	Page* first = p.page_table;
	for (int i = 0; i < memory.block_num; i++) {
		if (cntpage == p.N)break;
		if (getbit_blocki(i) == memfree) {//第i块空闲
			Page* pag = new Page;
			if (!pag) {
				cout << "申请页面不成功！" << endl;
				return false;
			}
			pag->block_no = i;//更改页面和页表
			pag->page_no = cntpage;
			cntpage++;
			pag->next = first->next;//插在尾部
			first->next = pag;
			first = first->next;
			setbit_blocki(i, memalloc);//更改位示图
			memory.freeblock_num--;//空闲块数减一
		}
	}
	//分配完毕
	p.isalloc = 1;
	//cout << "进程[" << p.no << "]分配完毕！" << endl;
	//print_pagetable(p);
	return true;
}
bool free_mem(Process &p) {
	if (!(p.isalloc )) {
		cout << "进程[" << p.no << "]未分配过内存!" << endl;
		return false;
	}
	Page* pag = p.page_table->next;//指向第0页
	while (pag) {//删除页表并更改位示图
		int blockno = pag->block_no;
		setbit_blocki(blockno,memfree);//更改位示图
		memory.freeblock_num++;//空闲块数加一
		Page* q = pag;
		pag = pag->next;
		delete q;
		q = NULL;
	}
	p.page_table->next = NULL;
	p.isalloc = 0;
	return true;
}
void pagestr() {
	sort(processes.begin(), processes.end(), comp);//按到达时间排序
	for (int time = 0; /*time < 2000*/; time++){//最大为2000s
		cout << "第" << time << "秒：" << endl;
		bool isoperate = false;//表示是否有操作
		if (processes.empty()) {
			cout<<"       结束。" << endl;
			break;
		}
		for (vector<Process>::iterator it = processes.begin(); it != processes.end();) {//先释放内存
			if ((it->exec_time + it->arrive_time == time) && (it->isalloc == 1)) {//有进程完成
				if (free_mem(*it)) {//如果释放成功
					isoperate = true;
					cout << "       进程[" << it->no << "]完成。释放内存块" << it->N << "个。" << endl;
					it = processes.erase(it);//容器删除进程 返回指向下一个元素的迭代器
				}
				else {
					it++;
				}
			}
			else it++;
		}
		for (vector<Process>::iterator it = processes.begin(); it != processes.end();it++){//分配内存
			if (it->isalloc == 1) {
				isoperate = true;
				cout << "       进程[" << it->no << "]占用内存中。" << endl;
			}
			if (it->arrive_time == time&&it->isalloc ==0) {//如果有进程到达并且未分配
				isoperate = true;
				if (!alloc_mem(*it)) {//如果分配失败，对于该进程arrivetime加一
					cout << "       进程[" << it->no << "]等待。" << endl;
					/*for (vector<Process>::iterator temp = it; temp != processes.end(); temp++) {
						temp->arrive_time++;
					}*/
					it->arrive_time++;
				}
				else {
					cout << "       进程[" << it->no << "]分配内存块" << it->N << "个。";
					print_pagetable(*it);
					//cout << "       目前共有空闲块" << memory.freeblock_num << "个。 " << endl;
					
				}
			}
		}
		if (!isoperate)cout << "       无操作" << endl << endl;
		cout << "       目前共有空闲块" << memory.freeblock_num << "个。 " << endl << endl;
	}
}

int main()
{
	cout << "********************分页存储管理********************" << endl;
	init_Mem();//初始化内存及位示图
	cout << "请输入进程数：" << endl;
	int pn;
	cin >> pn;
	cout << "创建进程：请分别输入进程号、需要的内存空间、到达时间、执行时间" << endl;
	for (int i = 0; i < pn;i++) {
		Process pro;
		if(creat_PCB(pro))processes.push_back(pro);
	}
	cout << endl << "开始模拟：" << endl << endl;
	pagestr();

	return 0;
}
