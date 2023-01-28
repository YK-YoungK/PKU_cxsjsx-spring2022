#include <bits/stdc++.h>
using namespace std;
int n,m;
int k=-1,q=0;
char maze[105][105]={};
int xj[105][105]={0};
int visited[105][105][1<<7][11]={0};
int sx,sy,ex,ey;
class point
{
public:
	int x,y,step,xian,key;
	point(int a,int b,int c,int d,int e):x(a),y(b),step(c),xian(d),key(e){}
	friend bool operator<(const point&a,const point& b)
	{
		return a.step>b.step;
	}
};
priority_queue<point> pp;
int mo[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
bool inmaze(int x,int y,int f,int b=1)
{
	if (x+mo[f][0]>=0&&x+mo[f][0]<n&&y+mo[f][1]>=0&&y+mo[f][1]<m)
		return true;
	return false;
}
int test(int c)
{
	memset(xj,-1,sizeof(xj));
	cin>>n>>m;
	for (int i=0;i<n;i++)
	{
		cin>>maze[i];
		for (int j=0;j<m;j++)
		{
			if (maze[i][j]=='S')
			{
				sx=i;sy=j;
			}
			if (maze[i][j]=='T')
			{
				ex=i;ey=j;
			}
			if (maze[i][j]=='G')
			{
				xj[i][j]=q;q++;
			}
			if (maze[i][j]>='1'&&maze[i][j]<='9')
			{
				k=max(k,maze[i][j]-'0');
			}
		}
	}
	pp.push(point(sx,sy,0,0,0));
	visited[sx][sy][0][0]=1;
	//cout<<q<<endl;
	while (!pp.empty())
	{
		point tmp=pp.top();
		pp.pop();
		int xx=tmp.x,yy=tmp.y,ss=tmp.step,xxj=tmp.xian,kk=tmp.key;
		//cout<<xx<<" "<<yy<<" "<<ss<<endl;
		if (xx==ex&&yy==ey&&kk==k)
		{
			cout<<ss<<endl;return 1;
		}
		for (int i=0;i<4;i++)
		{
			if (inmaze(xx,yy,i)&&visited[xx+mo[i][0]][yy+mo[i][1]][xxj][kk]==0&&maze[xx+mo[i][0]][yy+mo[i][1]]!='X')
			{
				visited[xx+mo[i][0]][yy+mo[i][1]][xxj][kk]=1;
				if (maze[xx+mo[i][0]][yy+mo[i][1]]=='G'&&((xxj>>xj[xx+mo[i][0]][yy+mo[i][1]])&1)==0)
				{
					pp.push(point(xx+mo[i][0],yy+mo[i][1],ss+2,xxj+(1<<xj[xx+mo[i][0]][yy+mo[i][1]]),kk));
				}
				else if (maze[xx+mo[i][0]][yy+mo[i][1]]>='1'&&maze[xx+mo[i][0]][yy+mo[i][1]]<='9'&&kk==maze[xx+mo[i][0]][yy+mo[i][1]]-'0'-1)
				{
					pp.push(point(xx+mo[i][0],yy+mo[i][1],ss+1,xxj,kk+1));
				}
				else
					pp.push(point(xx+mo[i][0],yy+mo[i][1],ss+1,xxj,kk));
			}
		}
	}
	return 1;
}
int main()
{
	int t=1;
	//cin>>t;
	for (int i=1;i<=t;i++)
	{
		if (test(i)==0)
			break;
	}
	return 0;
}