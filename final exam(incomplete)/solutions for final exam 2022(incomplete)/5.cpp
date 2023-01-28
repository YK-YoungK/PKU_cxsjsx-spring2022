#include <bits/stdc++.h>
using namespace std;
int getbit(int x,int w)
{
	return (x>>w)&1;
}
char maze[5][5]={};
char maze2[5][5]={};
int visited[1<<16]={0};
int s=0,e=0;
queue<pair<int,int > > qq{};
int mo[4]={-4,4,-1,1};
int main()
{
	for (int i=0;i<4;i++)
	{
		cin>>maze[i];
		for (int j=0;j<4;j++)
		{
			//cout<<(1<<(4*i+j))*(maze[i][j]-'0')<<endl;
			s+=(1<<(4*i+j))*(maze[i][j]-'0');
		}
	}
	//cout<<s<<endl;
	for (int i=0;i<4;i++)
	{
		cin>>maze2[i];
		for (int j=0;j<4;j++)
		{
			//cout<<(1<<(4*i+j))*(maze2[i][j]-'0')<<endl;
			e+=(1<<(4*i+j))*(maze2[i][j]-'0');
		}
	}
	//cout<<e<<endl;
	visited[s]=1;//visited[e]=1;
	qq.push(make_pair(s,0));
	while(!qq.empty())
	{
		pair<int, int>  tmp=qq.front();
		qq.pop();
		int xx=tmp.first,yy=tmp.second;
		//cout<<xx<<endl;
		if (xx==e)
		{
			cout<<yy<<endl;return 0;
		}
		for (int i=0;i<16;i++)
		{
			if (getbit(xx,i))
			{
				for (int j=0;j<4;j++)
				{
					if (i+mo[j]>=0&&i+mo[j]<16)
					{
						if (i%4==0&&j==2)
							continue;
						if (i%4==3&&j==3)
							continue;
						if (i/4==3&&j==1)
							continue;
						if (i/4==0&&j==0)
							continue;
						if (getbit(xx,i+mo[j])==0)
						{
							int xxx=xx-(1<<i)+(1<<(i+mo[j]));
							if (visited[xxx]==0)
							{
								visited[xxx]=1;
								qq.push(make_pair(xxx,yy+1));
							}
						}
					}
				}
			}
		}
	}
	return 0;
}