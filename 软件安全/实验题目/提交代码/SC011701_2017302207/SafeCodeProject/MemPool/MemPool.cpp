//���汾
#include"MemPool.h"
#include<iostream>
using namespace std;
block* mypool;//ָ���ڴ��
int initPool(size_t size ) {
	/*���ܣ������ʼ�ڴ�أ��ڴ�س�ʼ��СĬ��Ϊ 1000 ���飬�� 256 x 1000 �ֽڡ�
	���� size���ڴ�س�ʼ��ʱ������ڴ�������Ĭ��Ϊ 1000 �顣
	����ֵ���ɹ���� 1000 ���ڴ�������򷵻� 0�����򷵻�-1.
	��ʾ����ʹ�� malloc��calloc �Ⱥ�������ڴ��ʼ���� */
	//��ʼ���ڴ��
	mypool = (block*)malloc(sizeof(block));//�ڴ�������ڴ�
	if (!mypool) {
		std::cout << "�ڴ�س�ʼ��ʧ�ܣ�" << endl;
		return -1;//���ɹ�����-1
	}
	mypool->No = size;//��ʼ��ͷ�ڵ㣬No����ڴ����size��mypool->nextΪ��
	mypool->next = NULL;
	for (size_t i = 1; i <=size ; i++) {//����ÿһ�� ����256�ֽ�
		block *b = (block*)malloc(sizeof(block));
		char* p = (char*)malloc(BLOCKSIZE * sizeof(char));
		if ((!b)||(!p)) {//������ʧ��Ӧ�û���ǰ����ڴ�
			block* fb = mypool->next;
			while (fb) {//����ǰ����ڴ��
				char* q = fb->pm;
				block* qb = fb;
				fb = fb->next;
				free(q); q = NULL;
				free(qb); qb = NULL;
			}fb = NULL;
			free(mypool); mypool = NULL;//�����ڴ��
			std::cout << "�����ڴ�ʧ�ܣ�" << endl;
			return -1;
		}
		//����ɹ�
		b->pm = p;
		b->No = (int)(size+1-i);
		b->free = true;//����Ϊ����
		b->next = mypool->next;//����ͷ�ڵ�֮��
		mypool->next = b;
	}
	std::cout << "�ڴ�س�ʼ���ɹ���" << endl;
	return 0;//�ɹ�����0
}


char* allocBlock() {
	/*���ܣ����ڴ�����ҵ�һ������ڴ����з��䡣������ڴ汻��ʼ��Ϊ 0������ڴ�
	���ڴ��ѷ����꣬��������ڴ�ؽ������䡣 
	����ֵ�����ط�����ڴ���׵�ַ��������ִ����򷵻ؿ�ָ�롣 
	��ʾ����ʹ�� malloc��calloc ������memset ������ע�����ʹ�� realloc �����ڴ棬ͨ��
	allocBlock �Ѿ������ȥ���ڴ���ַ���ܻ���Ч�������޷������ڴ�顣 */
	//������allocBlock
	if (mypool == NULL) return NULL;
	block* fb = mypool->next;//ָ���һ��
	block* fpre = mypool;//ָ��fbǰһ��
	while (fb) {
		if (fb->free) {//�������
			memset(fb->pm, 0, 256);//��ʼ��Ϊ0
			fb->free = false;//��ʾ�ѷ���
			cout << "��" << fb->No << "�����ɹ�" << endl;
			return fb->pm;//���ط�����ڴ���׵�ַ
		}
		
		fpre = fb;//���ڵõ����һ��
		fb = fb->next;
	}
	//��û�п��п�
	block* tmp;
	tmp = (block*)malloc(sizeof(block));//����һ��
	if (!tmp) {//���ɹ�����NULL
		cout << "�޿��п�������ʧ�ܣ�" << endl;
		return NULL;
	}
	//�ɹ�
	char *temp_pm = (char*)malloc(BLOCKSIZE);//����256���ֽ�
	if (temp_pm == NULL) {//���ɹ������ǰ�������һ���ڵ�ָ�룬���ҷ��ؿ�
		cout << "�޿��п�������ʧ�ܣ�" << endl;
		free(tmp);//���սڵ�
		tmp= NULL;
		return NULL;
	}
	//�ɹ�
	tmp->pm = temp_pm;//���ӵ��ڵ�
	mypool->No++;//��������һ��
	tmp->No = mypool->No;//���Ϊԭʼsize
	memset(tmp->pm, 0, BLOCKSIZE);//����
	tmp->free = false;//��Ϊ�գ��ѷ���
	tmp->next = NULL;//���ӵ�ԭ�����ڴ������
	fpre->next = tmp;
	cout << "ԭ�ڴ���ѷ����꣬�����䣬�����"<<tmp->No<<"��ɹ���" << endl;
	return tmp->pm;//���ط�����ڴ�ָ��
}
int freeBlock(char* buf) {
	/*���ܣ��� buf ָ����ڴ���ͷţ����ڴ�鲢��ִ�ж��ڴ���ͷŲ�����ֻ�ǷŻ��ڴ�
	�ع��´η���ʹ�á��ͷ�ʱ����� buf ָ����ڴ����������������� 
	���� buf��ָ��Ҫ�Ż��ڴ���е��ڴ�顣 
	����ֵ��ִ�гɹ����� 0��buf ָ�����Ϊ�շ���-1������ buf ָ��δ�ҵ���Ӧ�Ŀ飬��
	buf ָ�벢������ǰ allocBlock ����������ڴ���ַ���򷵻�-2. 
	��ʾ����ʹ�� memset ���������� Windows API SecureZeroMemory �������㡣 */
	if (buf == NULL) return -1;
	if (mypool == NULL)return -1;
	block* fb = mypool->next;
	//block* fpre = mypool;
	while (fb) {
		if ((fb->pm == buf) && (fb->free == false)) {//�ҵ����ڴ����Ϊ�ѷ����
			fb->free = true;
			memset(fb->pm, 0, BLOCKSIZE);//����
			std::cout << "�ͷŵ�" << fb->No << "��ɹ���" << endl;
			return 0;//�ɹ�
		}
		fb = fb->next;
	}
	cout << "δ�ҵ��ÿ飡" << endl;
	return -2;//δ�ҵ�
}
int freePool() {
	/*���ܣ��������ڴ�ص��ڴ�ȫ���ͷţ������ж��Ƿ����δ���յ��ڴ�飬���������
	����-1�����û������ڴ�������ڴ��������㣬Ȼ��ִ�� free ������. 
	����ֵ��ִ�гɹ����� 0���������δ���յ��ڴ�飬���践��-1. 
	��ʾ����ʹ�� free��memset ������ */
	if (mypool == NULL) return -1;
	block* fb = mypool->next;
	while (fb) {
		if (!(fb->free)) {//δ����
			cout << "�ͷ��ڴ��ʧ�ܣ���δ���յ��ڴ�顣" << endl;
			return -1;
		}
		fb = fb->next;
	}
	//û��δ���յ��ڴ��
	while (fb) {
		memset(fb->pm, 0, BLOCKSIZE);//�ѻ��յĿ�����
		block* q = fb;
		fb = fb->next;
		free(q->pm);//�ͷ��ڴ��
		q->pm = NULL;//�ͷ����ÿ�
		free(q);//�ͷ��ڴ��ڵ�
		q = NULL;
	}
	free(mypool);
	mypool = NULL;
	cout << "freePool�ɹ���" << endl;
	return 0;
}
int freePoolForce() {
	/*���ܣ������Ƿ����δ���յ��ڴ�飬���������ڴ�ص��ڴ��������㣬Ȼ��ִ�� free������. 
	����ֵ��ִ�гɹ����� 0�����ִ����򷵻�-1. 
	��ʾ����ʹ�� free��memset ������ */
	if (mypool == NULL) return -1;
	block* fb = mypool->next;
	while (fb) {
		if (!(fb->free)) {//δ����
			int t = freeBlock(fb->pm);//�����
			if (t != 0) {//���ղ��ɹ�
				cout << "freePoolForce�����ڴ��ʧ��!" << endl;
				return -1;
			}
		}
		fb = fb->next;
	}
	//û��δ���յ��ڴ��
	while (fb) {
		memset(fb->pm, 0, BLOCKSIZE);//�ѻ��յĿ�����
		block* q = fb;
		fb = fb->next;
		free(q->pm);//�ͷ��ڴ��
		q->pm = NULL;//�ͷ����ÿ�
		free(q);//�ͷ��ڴ��ڵ�
		q = NULL;
	}
	free(mypool);//�ͷ��ڴ�� 
	mypool = NULL;
	cout << "freePoolForce�ɹ���" << endl;
	return 0;
}
size_t getBlockCount() {
	/*���ܣ������ڴ�������е��ڴ������� */
	if (mypool == NULL)return 0;
	return mypool->No;

}
size_t getAvailableBlockCount() {	
	/*���ܣ������ڴ���п��пɷ�����ڴ�������*/
	if (mypool == NULL)return 0;
	block* fb = mypool->next;
	size_t count = 0;
	while (fb) {//ѭ������
		if (fb->free)count++;
		fb = fb->next;
	}
	return count;
}