#include <bits/stdc++.h>
using namespace std;
int maze[10][10]={0};
int eachl[10][10]={0};
int eachc[10][10]={0};
int eachp[3][3][10]={0};
int tmp[10][10]={0};
int flag=0;
void dfs(int x,int y)
{
	if (x==9)
	{
		flag=1;
		for (int i=0;i<9;i++)
		{
			for (int j=0;j<9;j++)
				cout<<tmp[i][j];
			cout<<endl;
		}
		return;
	}
	if (flag==1)
		return;
	if (maze[x][y]!=0) 
	{
		if (y!=8)
			dfs(x,y+1);
		else
			dfs(x+1,0);	
		return;
	}
	for (int i=1;i<=9;i++)
	{
		if (eachl[x][i]==0&&eachc[y][i]==0&eachp[x/3][y/3][i]==0)
		{
			eachl[x][i]=1;eachc[y][i]=1;eachp[x/3][y/3][i]=1;
			tmp[x][y]=i;
			if (y!=8)
				dfs(x,y+1);
			else
				dfs(x+1,0);
			if (flag==1)
				return;
			eachl[x][i]=0;eachc[y][i]=0;eachp[x/3][y/3][i]=0;
		}
	}
	//tmp[x][y]=0;
}
void test()
{
	memset(maze,0,sizeof(maze));
	memset(eachl,0,sizeof(eachl));
	memset(eachc,0,sizeof(eachc));
	memset(eachp,0,sizeof(eachp));
	flag=0;
	char c;
	for (int i=0;i<9;i++)
	{
		for (int j=0;j<9;j++)
		{
			cin>>c;
			maze[i][j]=c-'0';
			tmp[i][j]=maze[i][j];
			eachl[i][maze[i][j]]=1;
			eachc[j][maze[i][j]]=1;
			eachp[i/3][j/3][maze[i][j]]=1; 
		}
	}
	dfs(0,0);
}
int main()
{
	int t;
	cin>>t;
	for (int i=0;i<t;i++)
		test(); 
	return 0;
}