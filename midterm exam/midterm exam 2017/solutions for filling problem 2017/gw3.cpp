/*
5.������룬ʹ����Ҫ����� 

����

������������
ÿ����������
��һ����һ��������f��һ������ n
�ڶ��������������� x �� y
����������������  p ��q

���

��ÿ������
����� x + y - f
����� p + q - n

����������
2.2 3
1.0 2.0
10 20
4.5 30
4.8 9.2
100 200


�������

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



