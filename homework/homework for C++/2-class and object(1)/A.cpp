#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cstdlib>
using namespace std;

class Student {
private:
	char name[30];
	int age;
	long long id;
	int score[5];
	double average;
public:
	void input()
	{
		for (int i=0;i<30;i++)
		{
			cin.get(name[i]);
			if (name[i]==',')
			break; 
		}
		char ch;
		cin>>age>>ch>>id>>ch;
		cin>>score[0]>>ch>>score[1]>>ch>>score[2]>>ch>>score[3]; 
	}
	void calculate()
	{
		average=((double)(score[0]+score[1]+score[2]+score[3]))/4;
	}
	void output()
	{
		cout<<name<<age<<","<<id<<","<<average<<endl;
	}
};

int main() {
	Student student;        // 定义类的对象
	student.input();        // 输入数据
	student.calculate();    // 计算平均成绩
	student.output();       // 输出数据
}