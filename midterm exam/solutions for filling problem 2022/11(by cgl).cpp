#include <iomanip>
#include <iostream>
using namespace std;

class TNone {};
TNone None;
template<class T>
class Option{
public:
	T * x;
	Option(){
		
		x=NULL;
	}
	Option(TNone y){
		
		x=NULL;
	}
	Option(T y){
		
		x=new T(y);
	}
	void operator =(Option<T> y){
		if(y.x==NULL)x=NULL;
		else{
			x=new T;
			*x=*(y.x);
		}
	}
	T & operator *(){
		return *x;
	}
	const T & operator *()const{
		return *x;
	}
	void operator =(TNone y){
		x=NULL;
	}
	bool has_value()const{
		return x!=NULL;
	}
	T value(){
		return *x;
	}
	operator bool()const{
		return has_value();
	}
};
int main() {
	cout << boolalpha;
	
	Option<int> a(0), b, c(1);
	cout << a.has_value() << endl;
	cout << b.has_value() << endl;
	b = a;
	*b += 10;
	cout << a.value() << endl;
	cout << b.value() << endl;
	c = None;
	cout << c.has_value() << endl;
	
	Option< Option<int> > x = None;
	const Option< Option<int> > y = a;
	Option< Option<int> > z = c;
	if (x)
		cout << "x has value" << endl;
	if (y)
		cout << "y has value" << endl;
	if (z)
		cout << "z has value" << endl;
	x = y;
	x = x;
	*x = b;
	**x = 20;
	cout << x.value().value() + **y << endl;
	return 0;
}
