/*
��������������ǣ�


2
3
B::destructor
A::destructor
3
4
B::destructor
A::destructor
3
B::destructor
A::destructor
A::destructor
A::destructor


�����

��ʾ��

int A::count = 0; ���������������¼һ���ж��ٸ���A����A��������Ķ���ġ�
*/


#include <iostream>
#include <map>
using namespace std;
//your code starts here
class A {
	
	public :
		int v;
		int static count;
		A(int i):v(i) { ++count ; }
		A():v(0) { ++count ; }
		virtual ~A() { 
			-- count; 
			cout << "A::destructor" << endl; 
		}
		A(const A & a):v(a.v) {
			++ count; 
		} 
		
};

class B :public A {
	public:
		B(int k):A(k) { }
		B(const B & b):A(b.v) {
			
		}
		~B() {
			cout << "B::destructor" << endl;
		}
};

//you code ends here
int A::count = 0;
void func(B b) {  }
int main()
{
	A a1(5),a2;
	cout << A::count << endl;
	B b1(4);
	cout << A::count << endl;
	func(b1);
	cout << A::count << endl;
	A * pa = new B(4);
	cout << A::count << endl;
	delete pa;
	cout << A::count << endl;
	return 0;
}

