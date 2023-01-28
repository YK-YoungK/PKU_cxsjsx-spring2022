#include <bits/stdc++.h>
using namespace std;
string s,p;
int lens,lenp;
bool check(int a,int b)
{
	//c//out<<a<<b<<endl;
	if (a==lens||b==lenp)
	{
		if (a==lens&&b==lenp)	return true;
		if (a==lens)
		{
			for (int i=b;i<lenp;i++)
			{
				if (p[i]!='*')	return false;
			}
			return true;
		}
		return false;
	}
	if (p[b]=='?')
		return check(a+1,b+1);
	if (p[b]=='*')
	{
		bool tt=false;
		for (int i=a;i<=lens;i++)
		{
			if (check(i,b+1))
				return true;
		}
		return false;
	}
	if (s[a]!=p[b])
	{
		return false;
	}
	else
		return check(a+1,b+1);
}
int test(int cases)
{
	cin>>s>>p;
	lens=s.length();
	lenp=p.length();
	if (check(0,0))
		cout<<"yes"<<endl;
	else
		cout<<"no"<<endl;
    return 1;
}
int main()
{
    int t;
    cin>>t;
    for (int i=0;i<t;i++)
    	test(i);
    return 0;
}