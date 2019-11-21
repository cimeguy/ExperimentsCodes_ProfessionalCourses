//最后版本
#include"MemPool.h"
#include<iostream>
using namespace std;
block* mypool;//指向内存块
int initPool(size_t size ) {
	/*功能：分配初始内存池，内存池初始大小默认为 1000 个块，即 256 x 1000 字节。
	参数 size：内存池初始化时分配的内存块个数，默认为 1000 块。
	返回值：成功完成 1000 块内存的申请则返回 0，否则返回-1.
	提示：可使用 malloc、calloc 等函数完成内存初始化。 */
	//初始化内存池
	mypool = (block*)malloc(sizeof(block));//内存池申请内存
	if (!mypool) {
		std::cout << "内存池初始化失败！" << endl;
		return -1;//不成功返回-1
	}
	mypool->No = size;//初始化头节点，No存放内存块数size，mypool->next为空
	mypool->next = NULL;
	for (size_t i = 1; i <=size ; i++) {//对于每一块 分配256字节
		block *b = (block*)malloc(sizeof(block));
		char* p = (char*)malloc(BLOCKSIZE * sizeof(char));
		if ((!b)||(!p)) {//若申请失败应该回收前面的内存
			block* fb = mypool->next;
			while (fb) {//回收前面的内存块
				char* q = fb->pm;
				block* qb = fb;
				fb = fb->next;
				free(q); q = NULL;
				free(qb); qb = NULL;
			}fb = NULL;
			free(mypool); mypool = NULL;//回收内存池
			std::cout << "申请内存失败！" << endl;
			return -1;
		}
		//申请成功
		b->pm = p;
		b->No = (int)(size+1-i);
		b->free = true;//设置为空闲
		b->next = mypool->next;//插入头节点之后
		mypool->next = b;
	}
	std::cout << "内存池初始化成功！" << endl;
	return 0;//成功返回0
}


char* allocBlock() {
	/*功能：从内存池中找到一块空闲内存块进行分配。分配的内存被初始化为 0。如果内存
	池内存已分配完，需对现有内存池进行扩充。 
	返回值：返回分配的内存块首地址，如果出现错误则返回空指针。 
	提示：可使用 malloc、calloc 函数、memset 函数。注意如果使用 realloc 扩充内存，通过
	allocBlock 已经分配出去的内存块地址可能会无效，导致无法回收内存块。 */
	//不适用allocBlock
	if (mypool == NULL) return NULL;
	block* fb = mypool->next;//指向第一块
	block* fpre = mypool;//指向fb前一块
	while (fb) {
		if (fb->free) {//如果空闲
			memset(fb->pm, 0, 256);//初始化为0
			fb->free = false;//表示已分配
			cout << "第" << fb->No << "块分配成功" << endl;
			return fb->pm;//返回分配的内存块首地址
		}
		
		fpre = fb;//便于得到最后一块
		fb = fb->next;
	}
	//若没有空闲块
	block* tmp;
	tmp = (block*)malloc(sizeof(block));//扩充一块
	if (!tmp) {//不成功返回NULL
		cout << "无空闲块且扩充失败！" << endl;
		return NULL;
	}
	//成功
	char *temp_pm = (char*)malloc(BLOCKSIZE);//分配256个字节
	if (temp_pm == NULL) {//不成功则回收前面扩充的一个节点指针，并且返回空
		cout << "无空闲块且扩充失败！" << endl;
		free(tmp);//回收节点
		tmp= NULL;
		return NULL;
	}
	//成功
	tmp->pm = temp_pm;//连接到节点
	mypool->No++;//计数，多一块
	tmp->No = mypool->No;//标号为原始size
	memset(tmp->pm, 0, BLOCKSIZE);//清零
	tmp->free = false;//不为空，已分配
	tmp->next = NULL;//连接到原来的内存池链表
	fpre->next = tmp;
	cout << "原内存池已分配完，故扩充，分配第"<<tmp->No<<"块成功！" << endl;
	return tmp->pm;//返回分配的内存指针
}
int freeBlock(char* buf) {
	/*功能：将 buf 指向的内存块释放，该内存块并不执行堆内存的释放操作，只是放回内存
	池供下次分配使用。释放时，需对 buf 指向的内存区域进行清零操作。 
	参数 buf：指向要放回内存池中的内存块。 
	返回值：执行成功返回 0；buf 指针参数为空返回-1；根据 buf 指针未找到对应的块，即
	buf 指针并不是以前 allocBlock 函数分配的内存块地址，则返回-2. 
	提示：可使用 memset 函数，或者 Windows API SecureZeroMemory 函数清零。 */
	if (buf == NULL) return -1;
	if (mypool == NULL)return -1;
	block* fb = mypool->next;
	//block* fpre = mypool;
	while (fb) {
		if ((fb->pm == buf) && (fb->free == false)) {//找到该内存块且为已分配的
			fb->free = true;
			memset(fb->pm, 0, BLOCKSIZE);//清零
			std::cout << "释放第" << fb->No << "块成功！" << endl;
			return 0;//成功
		}
		fb = fb->next;
	}
	cout << "未找到该块！" << endl;
	return -2;//未找到
}
int freePool() {
	/*功能：将整个内存池的内存全部释放，首先判断是否存在未回收的内存块，如果有则需
	返回-1，如果没有则对内存池所有内存块进行清零，然后执行 free 操作。. 
	返回值：执行成功返回 0，如果存在未回收的内存块，则需返回-1. 
	提示：可使用 free、memset 函数。 */
	if (mypool == NULL) return -1;
	block* fb = mypool->next;
	while (fb) {
		if (!(fb->free)) {//未回收
			cout << "释放内存池失败，有未回收的内存块。" << endl;
			return -1;
		}
		fb = fb->next;
	}
	//没有未回收的内存块
	while (fb) {
		memset(fb->pm, 0, BLOCKSIZE);//已回收的块清零
		block* q = fb;
		fb = fb->next;
		free(q->pm);//释放内存块
		q->pm = NULL;//释放完置空
		free(q);//释放内存块节点
		q = NULL;
	}
	free(mypool);
	mypool = NULL;
	cout << "freePool成功！" << endl;
	return 0;
}
int freePoolForce() {
	/*功能：无论是否存在未回收的内存块，都将整个内存池的内存块进行清零，然后执行 free操作。. 
	返回值：执行成功返回 0，出现错误，则返回-1. 
	提示：可使用 free、memset 函数。 */
	if (mypool == NULL) return -1;
	block* fb = mypool->next;
	while (fb) {
		if (!(fb->free)) {//未回收
			int t = freeBlock(fb->pm);//则回收
			if (t != 0) {//回收不成功
				cout << "freePoolForce回收内存块失败!" << endl;
				return -1;
			}
		}
		fb = fb->next;
	}
	//没有未回收的内存块
	while (fb) {
		memset(fb->pm, 0, BLOCKSIZE);//已回收的块清零
		block* q = fb;
		fb = fb->next;
		free(q->pm);//释放内存块
		q->pm = NULL;//释放完置空
		free(q);//释放内存块节点
		q = NULL;
	}
	free(mypool);//释放内存池 
	mypool = NULL;
	cout << "freePoolForce成功！" << endl;
	return 0;
}
size_t getBlockCount() {
	/*功能：返回内存池中所有的内存块个数。 */
	if (mypool == NULL)return 0;
	return mypool->No;

}
size_t getAvailableBlockCount() {	
	/*功能：返回内存池中空闲可分配的内存块个数。*/
	if (mypool == NULL)return 0;
	block* fb = mypool->next;
	size_t count = 0;
	while (fb) {//循环计算
		if (fb->free)count++;
		fb = fb->next;
	}
	return count;
}