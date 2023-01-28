#include <bits/stdc++.h>
using namespace std;
long long dp[1005][12000]={0};
int n,m;
int p[1005]={0};
int main()
{
	cin>>n>>m;
	for (int i=1;i<=n;i++)
		cin>>p[i];
	dp[0][0]=1;
	dp[1][0]=1;
	dp[1][p[1]]=1;
	for (int i=2;i<=n;i++)
	{
		for (int j=0;j<12000;j++)
		{
			if (j>=p[i])
				dp[i][j]=dp[i-1][j]+dp[i-1][j-p[i]];
			else
				dp[i][j]=dp[i-1][j];
		}
	}
	for (int j=m;;j++)
	{
		if (dp[n][j]!=0)
		{
			cout<<j<<" "<<dp[n][j]<<endl;
			if (dp[n][j]==1)
			{
				int tmp=j;
				stack<int > tt;
				for (int k=n-1;k>=0;k--)
				{
					if (dp[k][tmp]==0)
					{
						tt.push(k+1);
						tmp-=p[k+1];
					}
				}
				while (!tt.empty())
				{
					int kkk=tt.top();
					cout<<kkk<<" ";
					tt.pop(); 
				}
			}
			break;
		}
	}
	return 0;
}