/* 要做数据 
题名：前K大的偶数

输入n个整数，输出整数数列中大小排名前k的偶数

输入
有多组数据
第一行是数据组数 t
对每组数据： 
第一行为整数n (n>=3)和k
接下来的一行为n个整数，保证这些整数中至少有k个偶数。

输出
对每组数据，输出k个整数，降序排列，表示选出来的大小排名前k的偶数

样例输入
2
9 4
1 2 4 3 6 6 7 8 9
3 2
18 16 14

样例输出
8 6 6 4
18 16
*/

#include <algorithm>
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <string>
#include <map>
#include <set>

using namespace std;
class MyQueue
{
//your code starts here
public:
	int k;
	priority_queue<int> pq;
	MyQueue(int _k):k(_k){}
	void insert(int n)
	{
		pq.push(n);
	}
	friend istream & operator >> (istream &in, MyQueue &q)
	{
		int tmp;
		in>>tmp;
		if (tmp %2 == 0) q.insert(tmp);
		return in;
	}
	friend ostream & operator<<(ostream &out, MyQueue &q)
	{
		for (int i = 0; i < q.k; ++i)
		{
			out<<q.pq.top()<<" ";
			q.pq.pop();
		}
		return out;
	}
//your code ends here
};
int main()
{
	int t;
	cin >> t;
	while(t--) {
		int n, k;
		cin >> n >> k;
		MyQueue q(k);
		for (int i = 0; i < n; ++i)
			cin >> q;
		cout<<q;
		cout << endl;
	}
	return 0; 
}



