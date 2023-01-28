
/*
题目：还是Fun和Do
填写代码，使输出结果为
A::Fun
B::Do
C::Fun
C::Do
A::Fun
B::Do
*/
#include <iostream> 
using namespace std;

class A { 
	public: 
		virtual void Fun() { 
			cout << "A::Fun" << endl; 
		}; 
		virtual void Do() { 
			cout << "A::Do" << endl; 
		} 
}; 
//your code starts here
class B:public A { 
	public: 
		virtual void Do() { 
			cout << "B::Do" << endl;
		} 
}; 

class C:public B { 
	public: 
		void Fun() { 
			cout << "C::Fun" << endl; 
		}; 
		void Do() { 
			cout << "C::Do" << endl; 
		} 
}; 

void Call1(B &p) 
//your code ends here
{ 
	p.Fun(); 
	p.Do(); 
} 

void Call2(B p) {
	p.Fun();
	p.Do();
}



int main() { 
	C c;
	B b;
	Call1(b);
	Call1(c); 
	Call2(c);
	return 0;
}
