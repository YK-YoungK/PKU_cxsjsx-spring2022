/*
5.补充代码，使程序按要求输出 

输入

有若干组数据
每组数据三行
第一行是一个浮点数f和一个整数 n
第二行是两个浮点数 x 和 y
第三行是两个整数  p 和q

输出

对每组数据
先输出 x + y - f
再输出 p + q - n

输入样例：
2.2 3
1.0 2.0
10 20
4.5 30
4.8 9.2
100 200


输出样例

0.8
27
9.5
270

*/

#include <iostream>
using namespace std;
template <class T>
class Add{
public:
	//your code starts here
	T val;
	Add(T i) :val(i){}
	T operator()(T a, T b){
		return a + b - val;
	}
	//your code ends here
};

int main(){
	double f;
	int n;
	while( cin >> f >> n) {
		
		Add<double> a1(f);
		Add<int> a2(n);
		double x,y;
		int p,q;
		cin >> x >> y >> p >> q;
		cout << a1(x, y) << endl;
		cout << a2(p, q) << endl;
	}
	return 0;
}



