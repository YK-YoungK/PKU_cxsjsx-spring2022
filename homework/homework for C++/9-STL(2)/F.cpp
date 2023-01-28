#include <iostream>
#include <map>
#include <cmath>
using namespace std;
int main()
{
	typedef multimap<int,int> mmii;
	mmii record;
	record.insert(make_pair(1000000000,1));
	int n=0;
	cin>>n;
	int id=0,e=0;
	while (n>0)
	{
		cin>>id>>e;
		record.insert(make_pair(e,id));
		int num=record.count(e);
		if (num>1)
		{
			mmii::iterator p1=record.lower_bound(e),p2=record.upper_bound(e);
			int minium=p1->second; 
			for (;p1!=p2;p1++)
			{
				if (p1->second==id)
					continue;
				minium=min(p1->second,minium);	
			}
			cout<<id<<" "<<minium<<endl; 
		}
		else
		{
			mmii::iterator p=record.find(e);
			if (p==record.begin())
			{
				p++;
				mmii::iterator p1=record.lower_bound(p->first),p2=record.upper_bound(p->first);
				int minium=p1->second;
				for (;p1!=p2;p1++)
					minium=min(p1->second,minium);
				cout<<id<<" "<<minium<<endl; 
			}
			else
			{
				mmii::iterator q1=p,q2=p;
				q1--;
				q2++;
				if (q2==record.end())
				{
					mmii::iterator p1=record.lower_bound(q1->first),p2=record.upper_bound(q1->first);
					int minium=p1->second;
					for (;p1!=p2;p1++)
						minium=min(p1->second,minium);
					cout<<id<<" "<<minium<<endl; 
				}
				else
				{
					int r1=e-q1->first,r2=q2->first-e;
					if (r1<r2)
					{
						mmii::iterator p1=record.lower_bound(q1->first),p2=record.upper_bound(q1->first);
						int minium=p1->second;
						for (;p1!=p2;p1++)
							minium=min(p1->second,minium);
						cout<<id<<" "<<minium<<endl; 
					}
					else if (r2<r1)
					{
						mmii::iterator p1=record.lower_bound(q2->first),p2=record.upper_bound(q2->first);
						int minium=p1->second;
						for (;p1!=p2;p1++)
							minium=min(p1->second,minium);
						cout<<id<<" "<<minium<<endl; 
					}
					else
					{
						mmii::iterator p1=record.lower_bound(q1->first),p2=record.upper_bound(q1->first);
						int minium=p1->second;
						for (;p1!=p2;p1++)
							minium=min(p1->second,minium);
						p1=record.lower_bound(q2->first);
						p2=record.upper_bound(q2->first);
						for (;p1!=p2;p1++)
							minium=min(p1->second,minium);
						cout<<id<<" "<<minium<<endl; 
					}
				}
			}
		}
		n--;
	}
	return 0;
}