#include <bits/stdc++.h>
using namespace std;
int maze[1005][1005]={0};
int visited[1005]={0};
int dp[1005]={0};
int n,m;
int flag=0;
int dfs(int x)
{
	if (dp[x]!=-1)
		return dp[x];
	visited[x]=1;
	dp[x]=0;
	for (int i=1;i<=n;i++)
	{
		if (maze[x][i]>0)
		{
			if (dfs(i)==1000000000)
			{
				dp[x]=1000000000;visited[x]=0;return dp[x];
			}
			else if (visited[i]==1)
			{
				dp[x]=1000000000;visited[x]=0;return dp[x];
			}
			else
				dp[x]=max(dp[x],dp[i]+maze[x][i]);
		}
	}
	visited[x]=0;
	return dp[x];
}
int test(int cases)
{
	cin>>n>>m;
	int x,y,z;
	memset(dp,-1,sizeof(dp));
	for (int i=0;i<m;i++)
	{
		cin>>x>>y>>z;
		maze[x][y]=max(maze[x][y],z);
	}
	cout<<dfs(1)<<endl;
	return 1;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t=1;
	//cin>>t;
	for (int i=1;i<=t;i++)
	{
		if (test(i)==0)
			break;
	}
	return 0;
}