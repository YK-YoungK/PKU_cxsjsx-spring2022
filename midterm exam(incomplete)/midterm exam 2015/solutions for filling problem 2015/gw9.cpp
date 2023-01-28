/*
程序填空
输入数据：
第一行是整数t,表明一共t组数据. t < 20
对每组数据：
第一行是整数n,表示下面一共有n行。 0 < n < 100
下面的每行代表一个人。每行以一个字母开头，代表该人所属的类别，然后跟着一个整数，代表年龄。字母只会是 'A‘或‘B' 。整数范围0到100。数据保证年龄都不相同。


输出数据：
对每组输入数据，将这些人按年龄从小到大输出。每个人先输出类别，再输出年龄。相同年龄的人，先输出A类人。每组数据的末尾加一行 "****" 

输入样例

2
4
A 3
B 4
A 5
B 6
3
A 4
A 3
A 2


输出样例 
A 3
B 4
A 5
B 6
****
A 2
A 3
A 4
****
 
*/


#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
using namespace std;

//your code starts here
class A {
	public:
		int x;
	public:
		virtual void Print() 
		{
			cout << "A " << x << endl;
		}
		A(int i):x(i) { }
};


class B:public A
{
	public:
	virtual void Print() {
		cout << "B " << x << endl;
	}
	B(int i):A(i) { }
};

class Comp {
	public:
	bool operator() ( A * p1, A * p2)
	{
		return p1->x < p2->x; 
	}
};


void Print( A * p) {
	p->Print();
}

// your code ends here

int main()
{

	int t;
	cin >> t;
	set<A*,Comp> ct;
	while( t -- ) {
		int n;
		cin >> n;
		ct.clear();
		for( int i = 0;i < n; ++i)	{
			char c; int k;
			cin >> c >> k;
			
			if( c == 'A')
				ct.insert(new A(k));
			else
				ct.insert(new B(k));
		}	
		for_each(ct.begin(),ct.end(),Print);
		cout << "****" << endl;
	}
}




