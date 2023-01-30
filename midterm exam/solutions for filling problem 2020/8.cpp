#include <iostream>
using namespace std;
class A
{
public:
	int t;
	A(int t0):t(t0){}
	int& get_value()
	{
		return t;
	}
	A operator+(A* x)
	{
		return A(t+x->t);
	}
	A* operator->()
	{
		return this;
	}
};
class B:public A
{
public:
	B(int t0):A(t0){}
};
class C:public A
{
public:
	C(int t0):A(t0){}
};
int main() {
    int t;
    cin >> t;
    while (t --){
        int aa, bb, cc;
        cin >> aa >> bb >> cc;
        A a(aa);
        B b(bb);
        C c(cc);
        A* x = &a;
        A* y = &b;
        A* z = &c;
        cout << (x->get_value() + y->get_value() + z->get_value()) << " ";
        cout << ((*x) + y + z)->get_value() << endl;
    }
    return 0;
}