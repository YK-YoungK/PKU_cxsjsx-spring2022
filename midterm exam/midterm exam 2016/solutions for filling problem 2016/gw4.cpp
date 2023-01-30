#include <iostream>
using namespace std;

class A {
public:
// 在此处补充你的代码
/*
	int v;
	A(int m):v(m) { }
	
	operator int() { return v; }
	A & operator +=(int n) {
		v += n;
		return * this;
	}
	A & operator -=(int n) {
		v -= n;
		return * this;
	}
	int & getValue() { return v; }
*/
};

int main() {
	int t;
	cin >> t;
	while(t-- ) {
		int m,n,k;
		cin >> m >> n >> k;	
	    A a(m);
	    A b = a;
	    cout << b << endl;
	    cout << (a += b -= n) << endl;
	    cout << a.getValue() << endl;
	    a.getValue() = k;
	    cout << a << endl;
	} 
	return 0;
}
