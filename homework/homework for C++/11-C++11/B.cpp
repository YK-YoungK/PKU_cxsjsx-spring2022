#include <iostream>
using namespace std;
template<class T1,class T2,class T3>
class combine
{
public:
	T1 t1;
	T2 t2;
	combine(T1 t1_,T2 t2_):t1(t1_),t2(t2_){}
	T3 operator()(T3 x)
	{
		return t1(t1(x)+t2(x));
	}
};
int main()
{
    auto Square = [] (double a) { return a * a; };
    auto Inc = [] (double a) { return a + 1; };
    cout << combine<decltype(Square),decltype(Inc),int>(Square,Inc)(3) << endl;
    cout << combine<decltype(Inc),decltype(Square),double>(Inc,Square)(2.5) << endl;

    return 0;
}