/*
�������
�������ݣ�
��һ��������t,����һ��t������. t < 20
��ÿ�����ݣ�
��һ��������n,��ʾ����һ����n�С� 0 < n < 100
�����ÿ�д���һ���ˡ�ÿ����һ����ĸ��ͷ������������������Ȼ�����һ���������������䡣��ĸֻ���� 'A����B' ��������Χ0��100�����ݱ�֤���䶼����ͬ��


������ݣ�
��ÿ���������ݣ�����Щ�˰������С���������ÿ��������������������䡣��ͬ������ˣ������A���ˡ�ÿ�����ݵ�ĩβ��һ�� "****" 

��������

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


������� 
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




