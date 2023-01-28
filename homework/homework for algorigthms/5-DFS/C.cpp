#include <iostream>
using namespace std;
int cost[20][20]={0};
int dp[1<<20][20]={0};
int n=0;
int main()
{
	cin>>n;
	for (int i=0;i<(1<<n);i++)
	{
		for (int j=0;j<n;j++)
			dp[i][j]=1<<30;
	} 
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
			cin>>cost[i][j]; 
	}
	dp[1][0]=0;
	for (int i=1;i<n;i++)
		dp[(1<<i)+1][i]=cost[0][i];
	for (int i=2;i<(1<<n);i++)
	{
		/*if (!(i&1))
			continue;*/
		for (int j=1;j<n;j++)//Rmk.not j=0!
		{
			if (!((i>>j)&1))
				continue;
			for (int k=0;k<n;k++)//Rmk.k=0!
			{
				if (!((i>>k)&1))
					continue;
				dp[i][j]=min(dp[i][j],dp[i-(1<<j)][k]+cost[k][j]);
			}
		}
	}
	cout<<dp[(1<<n)-1][n-1]<<endl;
	return 0; 
}