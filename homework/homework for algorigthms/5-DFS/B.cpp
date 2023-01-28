#include <iostream>
using namespace std;
char maze[10][10]={};
int n=0,k=0;
int visited[10]={0};
int result=0;
int cnt=0;
void dfs(int row)
{
	if (cnt==k)
	{
		result++;
		return;
	}
	if (row==n)
		return;
	for (int i=0;i<n;i++)
	{
		if (visited[i]==1||maze[row][i]=='.')
			continue;
		visited[i]=1;
		cnt++; 
		dfs(row+1);
		cnt--;
		visited[i]=0;
	}
	dfs(row+1);
} 
int main()
{
	while (true)
	{
		cin>>n>>k;
		result=0;
		if (n==-1&&k==-1)
			break;
		for (int i=0;i<n;i++)
		{
			for (int j=0;j<n;j++)
				cin>>maze[i][j]; 
		}
		dfs(0);
		cout<<result<<endl;
	}
	return 0;
}