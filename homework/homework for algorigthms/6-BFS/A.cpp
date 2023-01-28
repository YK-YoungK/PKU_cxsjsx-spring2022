#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
int snake[6][2]={0};
class p
{
public:
	int x;
	int y;
	int t;
	int kill;
	int nowkey; 
	p(int x_,int y_,int t_,int k,int n=0):x(x_),y(y_),t(t_),kill(k),nowkey(n){}
	friend bool operator<(const p&x,const p& y)
	{
		return x.t>y.t;
	}
};
priority_queue<p> ff;
char maze[105][105]={};
int snakenum[105][105]={0};
int n,m;
int cnt;
int startx,starty,endx,endy;
int visited[105][105][32]={0};
int main()
{
	while (true)
	{
		cin>>n>>m;
		if (n==0&&m==0)
			break;
		memset(maze,'\0',sizeof(maze));
		memset(snake,0,sizeof(snake));
		memset(snakenum,-1,sizeof(snakenum));
		memset(visited,0,sizeof(visited));
		priority_queue<p> ff{};
		cnt=0;
		for (int i=0;i<n;i++)
		{
			for (int j=0;j<n;j++)
			{
				cin>>maze[i][j];
				if (maze[i][j]=='K')
				{
					startx=i;
					starty=j;
				} 
				else if (maze[i][j]=='T')
				{
					endx=i;
					endy=j;
				}
				else if (maze[i][j]=='S')
				{
					snake[cnt][0]=i;
					snake[cnt][1]=j;
					snakenum[i][j]=cnt;
					cnt++;
				}
			}
		}
		int flag=0;
		//bfs
		ff.push(p(startx,starty,0,0,0));
		visited[startx][starty][0]=1;
		while (!ff.empty())
		{
			p tmp=ff.top();
			ff.pop();
			int xx=tmp.x;
			int yy=tmp.y;
			int tt=tmp.t;
			int kk=tmp.kill;
			int nn=tmp.nowkey;
			if (xx==endx&&yy==endy&&nn==m)
			{
				cout<<tt<<endl;
				flag=1;
				break;
			}
			if (xx>0&&maze[xx-1][yy]!='#'&&visited[xx-1][yy][nn]==0)
			{
				if (maze[xx-1][yy]=='S')
				{
					if ((kk>>snakenum[xx-1][yy])&1)//killed
						ff.push(p(xx-1,yy,tt+1,kk,nn));
					else
						ff.push(p(xx-1,yy,tt+2,kk+(1<<snakenum[xx-1][yy]),nn));
				}
				else if (maze[xx-1][yy]>='1'&&maze[xx-1][yy]<=m+'0')
				{
					if (maze[xx-1][yy]-'0'-1==nn)
						ff.push(p(xx-1,yy,tt+1,kk,nn+1));
					else
						ff.push(p(xx-1,yy,tt+1,kk,nn));
				}
				else
					ff.push(p(xx-1,yy,tt+1,kk,nn));
				visited[xx-1][yy][nn]=1;
			}
			if (xx<n-1&&maze[xx+1][yy]!='#'&&visited[xx+1][yy][nn]==0)
			{
				if (maze[xx+1][yy]=='S')
				{
					if ((kk>>snakenum[xx+1][yy])&1)//killed
						ff.push(p(xx+1,yy,tt+1,kk,nn));
					else
						ff.push(p(xx+1,yy,tt+2,kk+(1<<snakenum[xx+1][yy]),nn));
				}
				else if (maze[xx+1][yy]>='1'&&maze[xx+1][yy]<=m+'0')
				{
					if (maze[xx+1][yy]-'0'-1==nn)
						ff.push(p(xx+1,yy,tt+1,kk,nn+1));
					else
						ff.push(p(xx+1,yy,tt+1,kk,nn));
				}
				else
					ff.push(p(xx+1,yy,tt+1,kk,nn));
				visited[xx+1][yy][nn]=1;
			}
			if (yy>0&&maze[xx][yy-1]!='#'&&visited[xx][yy-1][nn]==0)
			{
				if (maze[xx][yy-1]=='S')
				{
					if ((kk>>snakenum[xx][yy-1])&1)//killed
						ff.push(p(xx,yy-1,tt+1,kk,nn));
					else
						ff.push(p(xx,yy-1,tt+2,kk+(1<<snakenum[xx][yy-1]),nn));
				}
				else if (maze[xx][yy-1]>='1'&&maze[xx][yy-1]<=m+'0')
				{
					if (maze[xx][yy-1]-'0'-1==nn)
						ff.push(p(xx,yy-1,tt+1,kk,nn+1));
					else
						ff.push(p(xx,yy-1,tt+1,kk,nn));
				}
				else
					ff.push(p(xx,yy-1,tt+1,kk,nn));
				visited[xx][yy-1][nn]=1;
			}
			if (yy<n-1&&maze[xx][yy+1]!='#'&&visited[xx][yy+1][nn]==0)
			{
				if (maze[xx][yy+1]=='S')
				{
					if ((kk>>snakenum[xx][yy+1])&1)//killed
						ff.push(p(xx,yy+1,tt+1,kk,nn));
					else
						ff.push(p(xx,yy+1,tt+2,kk+(1<<snakenum[xx][yy+1]),nn));
				}
				else if (maze[xx][yy+1]>='1'&&maze[xx][yy+1]<=m+'0')
				{
					if (maze[xx][yy+1]-'0'-1==nn)
						ff.push(p(xx,yy+1,tt+1,kk,nn+1));
					else
						ff.push(p(xx,yy+1,tt+1,kk,nn));
				}
				else
					ff.push(p(xx,yy+1,tt+1,kk,nn));
				visited[xx][yy+1][nn]=1;
			}
		}
		if (flag==0)
			cout<<"impossible"<<endl; 
	}
	return 0;
} 