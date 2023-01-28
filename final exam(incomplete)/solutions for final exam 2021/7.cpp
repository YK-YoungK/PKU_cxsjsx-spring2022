#include <bits/stdc++.h>
using namespace std;
int maze[305][305]={0};
int visited[305][305]={0};
int n=0;
int movement[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
bool bfs(int t)
{
	queue<pair<int,int>> qq;
	qq.push(make_pair(0,0));
	if (maze[0][0]>t)
		return false;
	memset(visited,0,sizeof(visited));
	visited[0][0]=1;
	while(!qq.empty())
	{
		pair<int,int> tmp=qq.front();
		qq.pop();
		int xx=tmp.first,yy=tmp.second; 
		if (xx==n-1&&yy==n-1)
			return true;
		for (int i=0;i<4;i++)
		{
			if (xx+movement[i][0]>=0&&xx+movement[i][0]<n&&yy+movement[i][1]>=0&&yy+movement[i][1]<n)
			{
				if (maze[xx+movement[i][0]][yy+movement[i][1]]<=t&&visited[xx+movement[i][0]][yy+movement[i][1]]==0)
				{
					qq.push(make_pair(xx+movement[i][0],yy+movement[i][1]));
					visited[xx+movement[i][0]][yy+movement[i][1]]=1;
				}
			}
		} 
	}
	return false;
}
int main()
{
	cin>>n;
	int l=0,r=10000000;
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			cin>>maze[i][j]; 
		}
	}
	int best=10000001;
	while (l<=r)
	{
		int mid=(l+r)/2;
		if (bfs(mid))
		{
			best=min(best,mid);
			r=mid-1;
		}
		else
			l=mid+1;
	}
	cout<<best<<endl;
	return 0;
	
}