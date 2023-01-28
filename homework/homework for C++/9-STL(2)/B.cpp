#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
int main()
{
	multiset<double> result;
	int n=0;
	double m=0;
	cin>>n;
	for (int i=0;i<n;i++) 
	{
		cin>>m;
		result.insert(m);
	}
	
	string a;
	vector<double> tmp;
	while (1)
	{
		//memset(a,'\0',sizeof(a));
		cin>>a;
		if (cin.fail()==1)
			break;
		tmp.push_back(atof(a.c_str()));
		while(1)
		{
			//memset(a,'\0',sizeof(a));
			cin>>a;
			if (a[0]=='=')
			{
				set<double>::iterator p=result.begin();
				result.erase(p);
				result.insert(tmp[0]);
				printf("%e\n",tmp[0]);
				tmp.clear();
				break;
			}
			else if (a=="+")
			{
				vector<double>::iterator p1=tmp.end(),p2=tmp.end();
				p1--;p1--;p2--;
				*p1+=*p2;
				tmp.erase(p2);
			}
			else if (a=="-")
			{
				vector<double>::iterator p1=tmp.end(),p2=tmp.end();
				p1--;p1--;p2--;
				*p1-=*p2;
				tmp.erase(p2);
			}
			else if (a[0]=='*')
			{
				vector<double>::iterator p1=tmp.end(),p2=tmp.end();
				p1--;p1--;p2--;
				*p1*=*p2;
				tmp.erase(p2);
			}
			else if (a=="/")
			{
				vector<double>::iterator p1=tmp.end(),p2=tmp.end();
				p1--;p1--;p2--;
				*p1/=*p2;
				tmp.erase(p2);
			}
			else if (a=="^")
			{
				vector<double>::iterator p1=tmp.end(),p2=tmp.end();
				p1--;p1--;p2--;
				*p1=pow(*p1,*p2);
				tmp.erase(p2);
			}
			else
			{
				double num=0;
				num=atof(a.c_str());
				tmp.push_back(num);
			}
		}
	}
	int c=1;
	cout<<endl;
	set<double>::iterator p=result.begin();
	for (;p!=result.end();p++,c++)
	{
		if (c%10==0)
			printf("%e\n",*p);	
		else
			printf("%e ",*p);	
	}
	if (c%10!=0)
		cout<<endl;
	return 0;
}