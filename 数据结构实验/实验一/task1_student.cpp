#include<iostream>
using namespace std;
struct  student
{
	int stuID;
	char stuName[10];
	int dsScore;

};
/*���ڽṹ���������*/
void Input(student &s, int ID, char name[], int score) {
	s.stuID = ID;
	strcpy(s.stuName, name);
	s.dsScore = score;
}

/*ʹ�ö�̬���䷽����ϵͳ����һ���СΪsizeof��student���Ĵ洢�ռ�
�����ô洢�ռ�� ָ��pStuͨ��������������*/
student* creat(student *pStu) {
	pStu = new student;
	if (!pStu) exit(-1);
	return pStu;

}

void setData(student *s,int stuID,char stuName[],int dsScore) {
	s->stuID = stuID;
	strcpy(s->stuName, stuName);
	s->dsScore = dsScore;
}
/*��ӡ�ṹ������ĳ�Աֵ*/
void print(student s) {
	cout << s.stuID << " "<<s.stuName <<" "<< s.dsScore << endl;
}
int main() {
	student student1,student2;
	Input(student1, 1, "Alice", 90);
	student* pstu;
	pstu = creat(&student2);
	setData(pstu, student1.stuID, student1.stuName, student1.dsScore);
	print(student1);
	print(*pstu);
	return 0;
}