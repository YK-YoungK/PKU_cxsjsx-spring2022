#include <iostream>
using namespace std;
class Complex
{
	public :
		int r,i;
		
		Complex(int n = 0):r(n),i(0) { };
		Complex(const char * s) {
			r = s[0] - '0';
			i = s[2] - '0';
			
		}
		Complex(int rr,int ii):r(rr),i(ii) { }
		
		friend ostream & operator <<(ostream & o,const Complex & c ) {
			if( c.i && c.r )
				o << c.r << "+" << c.i << "i";	
			else if( c.r == 0 && c.i == 0)
				cout << 0 ;
			else if( c.r == 0)
				o <<  c.i << "i";	
			else
				o << c.r ;
			return o;
		}
		Complex operator +(const Complex & c) {
			return Complex(r+c.r,i+c.i);
		}
		Complex operator -(const Complex & c) {
			return Complex(r-c.r,i-c.i);
		}
		Complex operator *(const Complex & c) {
			return Complex(r * c.r - i * c.i, r * c.i + c.r * i);
		}
		Complex & operator *= (const Complex & c) {
			int tmpr  = r * c.r - i * c.i;
			
			i = r * c.i + c.r * i;
			r = tmpr;
			return * this;
		}
		Complex & operator += (const Complex & c) {
			r += c.r;
			i += c.i;
			return * this;
		}
		Complex & operator -= (const Complex & c) {
			r -= c.r;
			i -= c.i;
			return * this;
		}
		
		
};

int main() {
	Complex c1;
	Complex c2("3+2i"); // 用字符串初始化时，只需考虑"a+bi"的形式，其中a和b都是1位数字
	Complex c3(c2);
	Complex c4(-15);
	cout << c2 << endl;
	cout << c3 << endl;
	cout << c4 << endl;
	cout << c2 + c4 << endl;
	cout << c2 - c3 << endl;
	cout << c2 * c3 << endl;
	c2 += c4;
	cout << c2 << endl;
	c2 -= -12;
	cout << c2 << endl;
	c3 *= c3;
	cout << c3 << endl;
	return 0;
}
