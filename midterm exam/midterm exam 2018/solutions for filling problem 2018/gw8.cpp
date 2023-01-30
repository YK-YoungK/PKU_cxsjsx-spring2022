#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
// 在此处补充你的代码
struct A {
	A() { cout << "New A" << endl; }
	virtual ~A() { cout << "Delete A" << endl; }
};
struct B:public A
{
	B() { cout << "New B" << endl; }
	virtual ~B() { cout << "Delete B" << endl; }
	
};
	
////////////
int main(){
	int n;
	cin >> n;
	for (int i = 1; i<=n; i++) {
		int x;
		cin >> x;
		if (x == 0) {
			A *a = new A();
			delete a;
		}else {
			A *a = new B();
			delete a;
		}
	}
	return 0;	
}

