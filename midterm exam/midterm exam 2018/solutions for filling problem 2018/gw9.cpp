#include <iostream>
using namespace std;
int gcd(int x, int y){
	return x%y==0?y:gcd(y,x%y);
}
class Fraction
{
    int num, den;
public:
// 在此处补充你的代码
	Fraction(int n,int d = 1):num(n),den(d) { }
	Fraction & operator *= (const Fraction & g) {
		num *= g.num;
		den *= g.den;
		int Gcd = gcd(num,den);
		num /= Gcd;
		den /= Gcd;
		return * this;
	}
	Fraction & operator /= (const Fraction & g) {
		num *= g.den;
		den *= g.num;
		int Gcd = gcd(num,den);
		num /= Gcd;
		den /= Gcd;
		return * this;
	}
	Fraction operator / (const Fraction & g) {
		Fraction tmp(*this);
		tmp /= g;
		return tmp;
	}
	Fraction operator * (const Fraction & g) {
		Fraction tmp(*this);
		tmp *= g;
		return tmp;
	}

	operator float() {
		return double(num)/den;
	}
	friend ostream & operator << (ostream & o,const Fraction & f) {
		o << f.num << "/" << f.den;
		return o;
	}
///////////////////////////
};
 
int main() {
	int a,b,c;
	cin >> a >> b >> c;
    Fraction f(a, b), g(c);
	f *= g;
	cout << f << endl;
	f /= g;
	cout << f << endl;
	f = f * f;
	cout << f << endl;
	f = f / g;
	cout << f << endl;
	cout << (float) f << endl;
    return 0;
}
