#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include<string>
using namespace std;
int main()
{
	int n=0;
	cin>>n;
	string op;
	int x,y;
	map<int,int> num;
	while (n>0)
	{
		cin>>op;
		if (op=="SELL")
		{
			cin>>x>>y;
			num[y]+=x;
		}
		else
		{
			cin>>x;
			map<int,int>::iterator p=num.begin();
			int k=x;
			int result=0;
			for (;p!=num.end()&&k>0;p++)
			{
				if (k>=p->second)
				{
					k-=p->second;
					result+=p->first*p->second;
					p->second=0;
				}
				else
				{
					result+=k*p->first;
					p->second-=k;
					k=0;
					break;
				}
			}
			result+=k*40;
			cout<<result<<endl;
		}
		n--;
	}
	return 0;
}