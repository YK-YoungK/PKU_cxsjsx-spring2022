/* Ҫ������ 
������ǰK���ż��

����n��������������������д�С����ǰk��ż��

����
�ж�������
��һ������������ t
��ÿ�����ݣ� 
��һ��Ϊ����n (n>=3)��k
��������һ��Ϊn����������֤��Щ������������k��ż����

���
��ÿ�����ݣ����k���������������У���ʾѡ�����Ĵ�С����ǰk��ż��

��������
2
9 4
1 2 4 3 6 6 7 8 9
3 2
18 16 14

�������
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



