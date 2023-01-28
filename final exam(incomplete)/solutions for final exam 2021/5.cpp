#include <bits/stdc++.h>
using namespace std;
int n;
long long cnt[20][3]={0};
long long dp[20][3]={0};
int main()
{
	cin>>n;
	for (int j=0;j<n;j++)
	{
		int k;
		cin>>k;
		int tmp;
		for (int i=0;i<k;i++)
		{
			cin>>tmp;
			cnt[j][tmp%3]++; 
		}
	}
	dp[0][0]=cnt[0][0];
	dp[0][1]=cnt[0][1];
	dp[0][2]=cnt[0][2];
	for (int i=1;i<n;i++)
	{
		dp[i][0]=dp[i-1][0]*cnt[i][0]+dp[i-1][1]*cnt[i][2]+dp[i-1][2]*cnt[i][1];
		dp[i][1]=dp[i-1][0]*cnt[i][1]+dp[i-1][1]*cnt[i][0]+dp[i-1][2]*cnt[i][2];
		dp[i][2]=dp[i-1][0]*cnt[i][2]+dp[i-1][1]*cnt[i][1]+dp[i-1][2]*cnt[i][0];
	}
	cout<<dp[n-1][0]<<endl; 
	return 0;
}