#include<iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include<string> 
using namespace std;
int main()
{
	int n=0,m=0;
	cin>>n>>m;
	long long result=0;
	map<string,pair<int,int> > name;
	//map<string,int> ordered;
	string s;
	int x,y;
	for (int i=0;i<m;i++)
	{
		cin>>s>>x>>y;
		name.insert(make_pair(s,make_pair(x,y)));
	}
	for (int i=0;i<3*n;i++)
	{
		cin>>s; 
		map<string,pair<int,int> >::iterator p=name.find(s);
		if (p->second.second>0)
		{
			result+=p->second.first;
			p->second.second--;
			//cout<<s<<" "<<p->second.first<<" "<<p->second.second<<endl;
		}
	}
	cout<<result<<endl;
	return 0;
}