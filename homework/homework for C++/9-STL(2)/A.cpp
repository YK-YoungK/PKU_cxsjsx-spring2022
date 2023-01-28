#include <iostream>
#include <list>
#include <cstring>
using namespace std;
int main()
{
	list<int> a[10000];
	int t=0;
	cin>>t;
	string s;
	int b1=0,b2=0;
	while(t>0)
	{
		cin>>s;
		if (s[0]=='n')
			cin>>b1;
		else if (s[0]=='a')
		{
			cin>>b1>>b2;
			a[b1].push_back(b2);
		}
		else if (s[0]=='m')
		{
			cin>>b1>>b2;
			a[b1].merge(a[b2]);
		}
		else if (s[0]=='u')
		{
			cin>>b1;
			a[b1].sort();//去掉所有重复元素需要先排序！ 
			a[b1].unique();
		}
		else if (s[0]=='o')
		{
			cin>>b1;
			a[b1].sort();
			list<int>::iterator p=a[b1].begin();
			/*if (p==a[b1].end())
			{
				t--;
				continue;
			}
			cout<<*p;
			p++;*/
			for (;p!=a[b1].end();p++)
				cout<<*p<<" ";
			cout<<endl;
		}
		t--;
	}
	return 0;
} 