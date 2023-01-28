#include <iostream>
#include <string>
using namespace std;
template<class T, int num>
class A {
public:
	T* p = NULL;
	A(T* a) {
		p = new T[num];
		for (int i = 0; i < num; ++i) *(p + i) = a[i];
	}
	~A() {
		if (p) {
			delete[] p;
			p = NULL;
		}
	}
friend ostream& operator<<(ostream& o,const A& x)
	{
		for (int i=0;i<num;i++)
			cout<<x.p[i]<<" ";
		return o;
	}
	friend void print_sum(const A& x)
	{
		T result{};
		for (int i=0;i<num;i++)
			result+=x.p[i];
		cout<<result<<endl;
	}
	T sum()
	{
		T result{};
		for (int i=0;i<num;i++)
			result+=p[i];
		return result;
	}
};
int main() {

	int t;
	cin >> t;
	while (t--) {
		int b1[10];
		for (int i = 0; i < 10; ++i)
			cin >> b1[i];

		A<int, 10> a1 = b1;
		cout << a1 << endl;

		double b2[5];
		for (int i = 0; i < 5; ++i)
			cin >> b2[i];

		A<double, 5> a2 = b2;
		print_sum(a2);
		cout << a2.sum() << endl;

		string b3[4];
		for (int i = 0; i < 4; ++i)
			cin >> b3[i];
		A<string, 4> a3 = b3;
		print_sum(a3);
		cout << a3.sum() << endl;
	}
	return 0;
}