#include <iostream>
#include <map>
#include <cmath>
using namespace std;
int main()
{
	map<int,int> table;//energy,id
	table.insert(make_pair(1000000000,1));
	int n=0;
	cin>>n;
	int id=0,energy=0;
	while (n>0)
	{
		cin>>id>>energy;
		table.insert(make_pair(energy,id));
		map<int,int>::iterator p=table.find(energy),p1,p2;
		if (p==table.begin())
		{
			p2=p;
			p2++;
			cout<<id<<" "<<(*p2).second<<endl;
		}
		else
		{
			p1=p;
			p1--;
			p2=p;
			p2++;
			if (p2==table.end())
				cout<<id<<" "<<(*p1).second<<endl;
			else
			{
				if (p2->first-p->first<p->first-p1->first)
					cout<<id<<" "<<p2->second<<endl;
				else
					cout<<id<<" "<<p1->second<<endl; 
			}
		}
		n--;
	}
	return 0;
}