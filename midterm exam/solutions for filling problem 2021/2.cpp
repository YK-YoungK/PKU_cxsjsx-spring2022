#include <cstdio>
#include <iostream>
using namespace std;

class f {
public:
	int x;
	f(int x0):x(x0){}
	f(int m,int n):x(m*n){}
	int operator()(int y)
	{
		x=y-x;
		return x;
	}
	operator int()
	{
		return x;
	}
};

int main() {
  cout << f(3)(5) << endl;
  cout << f(4)(10) << endl;
  cout << f(114)(514) << endl;
  cout << f(9,7) << endl;
  cout << f(2,3) << endl;
  cout << f(2,5) << endl;
}