#include<iostream>
using namespace std;
struct  student
{
	int stuID;
	char stuName[10];
	int dsScore;

};
/*用于结构体变量输入*/
void Input(student &s, int ID, char name[], int score) {
	s.stuID = ID;
	strcpy(s.stuName, name);
	s.dsScore = score;
}

/*使用动态分配方法向系统申请一块大小为sizeof（student）的存储空间
并将该存储空间的 指针pStu通过函数参数返回*/
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
/*打印结构体变量的成员值*/
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