#include <bits/stdc++.h>
using namespace std;
void test()
{
	int n,k;
	cin>>n>>k;
	int place[1005]={0};
	int get[1005]={0};
	for (int i=0;i<n;i++)
		cin>>place[i];
	for (int i=0;i<n;i++)
		cin>>get[i];
	long long dp[1005]={0};
	dp[0]=get[0];
	long long mm=get[0];
	for (int i=1;i<n;i++)
	{
		dp[i]=get[i];
		for (int j=0;j<i;j++)
		{
			if (place[i]-place[j]>k)
				dp[i]=max(dp[i],dp[j]+get[i]);	
		} 
		mm=max(mm,dp[i]);
		
	}
	cout<<mm<<endl;
	
}
int main()
{
	int t;
	cin>>t;
	for (int i=0;i<t;i++)
		test(); 
	return 0;
}