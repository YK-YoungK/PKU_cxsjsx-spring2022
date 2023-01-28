#include <iostream>
using namespace std;
int gcd(int a, int b) { // 计算两个数的最大公约数
    return (!b) ? a : gcd(b, a % b);
}
class Fraction {
    int p, q;
public:
	Fraction(int p0=1,int q0=1):p(p0),q(q0)
	{
		int t=gcd(p,q);
		p/=t;
		q/=t;
	}
	Fraction operator* (const Fraction& x)
	{
		return Fraction(p*x.p,q*x.q);
	}
	friend ostream& operator<<(ostream& o,Fraction x)
	{
		if (x.q==1)
			o<<x.p;
		else
			o<<x.p<<"/"<<x.q;
		return o; 
	}
	friend istream& operator>>(istream& i,Fraction& x)
	{
		i>>x.p>>x.q;
		int t=gcd(x.p,x.q);
		x.p/=t;
		x.q/=t;
		return i;
	}
};

int main(){
    int testcases;
    cin >> testcases;
    while (testcases --) {
        Fraction a, b, two(2);
        cin >> a >> b;
        cout << a << " * " << b << " = " << a * b << endl;
        cout << "2 * " << a << " = " << two * a << endl;
        cout << b << " * 3 = " << b * 3 << endl;
    }
    return 0;
}