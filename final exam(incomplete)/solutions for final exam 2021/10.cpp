#include <bits/stdc++.h>
using namespace std;
int dp[105][1<<15]={0};
int tmpbegin[15][105]={0};
int bb[105]={0};
int n,m; 
inline int getlight(int x)
{
	int r=0;
	for (int i=0;i<n;i++)
		r+=(x>>i)&1;
	return r;
}
void test()
{
	memset(dp,0,sizeof(dp));
	memset(bb,0,sizeof(bb));
	cin>>n>>m;
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<m;j++)
		{
			cin>>tmpbegin[i][j];
			bb[j]+=tmpbegin[i][j]*(1<<i);
		} 
	}
	for (int j=0;j<(1<<n);j++)
	{
		dp[0][j]=max(getlight(bb[0]^j),n-getlight(bb[0]^j));	
	}
	for (int i=1;i<m;i++)
	{
		for (int j=0;j<(1<<n);j++)
		{
			dp[i][j]=dp[i-1][j]+max(getlight(bb[i]^j),n-getlight(bb[i]^j));
		}
	}
	int maxr=0;
	for (int i=0;i<(1<<n);i++)
		maxr=max(maxr,dp[m-1][i]);
	cout<<maxr<<endl;
}
int main()
{
	int t;
	cin>>t;
	for (int i=0;i<t;i++)
		test();
	return 0;
}