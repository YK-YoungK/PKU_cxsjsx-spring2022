#include <iostream>
using namespace std;
int maze[5][5]={0};
int result[30][2]={0};
int minstep=100;
int nowstep=0;
int now[30][2]={0};
int visited[5][5]={0};
void dfs(int x,int y)
{
	if (visited[x][y]==1||maze[x][y]==1)
		return;
	visited[x][y]=1;
	now[nowstep][0]=x;
	now[nowstep][1]=y;
	nowstep++;
	if (x==4&&y==4)
	{
		if (nowstep<minstep)
		{
			minstep=nowstep;
			for (int i=0;i<minstep;i++)
			{
				result[i][0]=now[i][0];
				result[i][1]=now[i][1];
			}
		}
	}
	if (x<4)
		dfs(x+1,y);
	if (y<4)
		dfs(x,y+1);
	if (x>0)
		dfs(x-1,y);
	if (y>0)
		dfs(x,y-1);
	nowstep--;
	visited[x][y]=0;
}
int main()
{
	for (int i=0;i<5;i++)
	{
		for (int j=0;j<5;j++)
			cin>>maze[i][j];
	}
	dfs(0,0);
	for (int i=0;i<minstep;i++)
		cout<<"("<<result[i][0]<<", "<<result[i][1]<<")"<<endl;
	return 0; 
} 