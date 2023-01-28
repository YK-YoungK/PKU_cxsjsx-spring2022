#include <iostream>
#include <queue>
#include <cmath>
using namespace std;
int isprime[10000000]={0};
int result[10000000]={0}; 
int prime(int x)
{
	if (x==1)
		return 0;
	if (x==2||x==3)
		return 1;
	for (int i=2;i*i<=x;i++)
	{
		if (x%i==0)
			return 0;
	}
	return 1;
}
int p_num(int x)
{
	if (x<=3)
		return 0;
	int count=0;
	for (int i=2;i<x;i++)
	{
		if ((isprime[i]==1)&&(x%i==0))
			count++;
	}	
	return count;
}
class f
{
public:
	bool operator()(int x,int y)
	{
		if (result[x]>result[y])
			return true;
		else if (result[x]<result[y])
			return false;
		else
		{
			if (x>y)
				return true;
			else
				return false;
		}
	}
};
class g
{
public:
	bool operator()(int x,int y)
	{
		if (result[x]>result[y])
			return false;
		else if (result[x]<result[y])
			return true;
		else
		{
			if (x>y)
				return false;
			else
				return true;
		}
	}
};
int main()
{
	//数据预处理 
	for (int i=2;i<10000000;i++)
		isprime[i]=1;
	for (int i=2;i<10000000;i++)
		result[i]=-1;
	for (int i=2;i*2<10000000;i++)
	{
		if (isprime[i]==0)
			continue;
		for (int j=2;i*j<10000000;j++)
			isprime[i*j]=0;
	}
	/*for (int i=1;i<100000;i++)
		result[i]=p_num(i);*/
	typedef priority_queue<int,vector<int>,f> pqif;
	typedef priority_queue<int,vector<int>,g> pqig;
	pqif l;
	pqig r;
	int n=0;
	cin>>n;
	int a=0;
	while (n>0)
	{
		for (int i=0;i<10;i++)
		{
			cin>>a;
			if (result[a]==-1)
				result[a]=p_num(a);
			l.push(a);
			r.push(a);
		}
		cout<<r.top()<<" "<<l.top()<<endl;
		l.pop();
		r.pop();
		n--;
	}
	return 0;
}