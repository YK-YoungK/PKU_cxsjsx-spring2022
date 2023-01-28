#include <bits/stdc++.h>
using namespace std;
int n,m;
int di[15]={0};
int tmp[15]={};
int start[15]={0};
void dfs(int depth)
{
	if (depth==n)
	{
		for (int i=0;i<n;i++)
			cout<<tmp[i];
		cout<<endl;
		return;
	}
	for (int i=0;i<m;i++)
	{
		tmp[depth]=(start[depth]+i)%m;
		dfs(depth+1);
	}
	start[depth]=(start[depth]+(m-1))%m;
}

int main()
{
ios::sync_with_stdio(false);
cin.tie(0);
cout.tie(0);
	cin>>n>>m;
	di[n-1]=1;
	for (int i=n-2;i>=0;i--)
		di[i]=di[i+1]*m;
	dfs(0);
	return 0;
}