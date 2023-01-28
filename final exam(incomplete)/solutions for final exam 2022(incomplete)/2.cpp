#include <bits/stdc++.h>
using namespace std;
long long p,q;
int flag=-1;
int d;
long long x,y;
set<long long> visited{};
set<long long> now[2]{};
int main()
{
	cin>>p>>q;
	cin>>x>>y;
	if (p==q)
	{
		cout<<0<<endl;return 0;	
	}
	now[0].insert(q);
	for (d=1;d<=52;d++)
	{
		now[d%2].clear();
		for (auto pp=now[(d-1)%2].begin();pp!=now[(d-1)%2].end();pp++)
		{
			long long tmp=*pp;
			if (visited.find(tmp+x)==visited.end())
			{
				now[d%2].insert(tmp+x);
				visited.insert(tmp+x);	
			} 
			if (tmp%y==0&&visited.find(tmp/y)==visited.end())
			{
				now[d%2].insert(tmp/y);
				visited.insert(tmp/y);
			}
		}
		if (visited.find(p)!=visited.end())
		{
			cout<<d<<endl;return 0;
		}
	}
	cout<<"Failed"<<endl;
	return 0;
}