#include <iostream>
#include <iterator>
using namespace std;

template<class T1, class T2>
void Copy(T1 s, T1 e, T2 x) {
    for(; s != e; ++s, ++x)
        *x = *s;
}
class Fib
{
public:
	int now;
	int last;
	int n;
	Fib(int x):n(x),now(0),last(1){}
	bool operator!=(const Fib& x)
	{
		return n!=x.n;
	}
	int operator*()
	{
		int tmp=last;
		last=now;
		now+=tmp;
		return now;
	}
	Fib& operator++()
	{
		n++;
		return *this;
	}
};
int main() {
	while(true) {
		int n;
		cin >> n;
		if(n == 0)
			break;
		
	    Fib f1(1), f2(n);
	    ostream_iterator<int> it(cout, " ");
	    Copy(f1, f2, it);
	    cout << endl;
	}
	return 0;
}