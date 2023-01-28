#include <iostream>
using namespace std;
class op
{
public:
	int a,b;
	int op1,op2;
	int last;
	op(int a_,int b_,int c,int d,int e):a(a_),b(b_),op1(c),op2(d),last(e){}
	op(){}
	//op2=-1:fill op2=-2:drop
};
op tt[20000]{};
void print_result(int x)
{
	if (tt[x].op2==-1)
		cout<<"FILL("<<tt[x].op1<<")"<<endl;
	else if (tt[x].op2==-2)
		cout<<"DROP("<<tt[x].op1<<")"<<endl;
	else
		cout<<"POUR("<<tt[x].op1<<","<<tt[x].op2<<")"<<endl;
}
int ss=0,ee=1;
int visited[105][105]={0};
int main()
{
	int x,y,need;
	cin>>x>>y>>need;
	tt[0]=op(0,0,-3,-3,-1);
	visited[0][0]=1;
	int flag=0;
	while (ss<ee)
	{
		int aa=tt[ss].a,bb=tt[ss].b;
		if (aa==need||bb==need)
		{
			flag=1;
			break;
		}
		if (aa<x&&visited[x][bb]==0)//fill 1
		{
			tt[ee]=op(x,bb,1,-1,ss);
			visited[x][bb]=1;
			ee++;
		}
		if (bb<y&&visited[aa][y]==0)//fill 2
		{
			tt[ee]=op(aa,y,2,-1,ss);
			visited[aa][y]=1;
			ee++;
		}
		if (aa>0&&visited[0][bb]==0)//drop 1
		{
			tt[ee]=op(0,bb,1,-2,ss);
			visited[0][bb]=1;
			ee++;
		}
		if (bb>0&&visited[aa][0]==0)//drop 2
		{
			tt[ee]=op(aa,0,2,-2,ss);
			visited[aa][0]=1;
			ee++;
		}
		if (aa>0&&bb<y)//pour 1 to 2
		{
			if (y-bb>=aa&visited[0][bb+aa]==0)
			{
				tt[ee]=op(0,bb+aa,1,2,ss);
				visited[0][bb+aa]=1;
				ee++;
			}
			else if (y-bb<=aa&&visited[aa-y+bb][y]==0)
			{
				tt[ee]=op(aa-(y-bb),y,1,2,ss);
				visited[aa-y+bb][y]=1;
				ee++;
			}
		}
		if (bb>0&&aa<x)//pour 2 to 1
		{
			if (x-aa>=bb&&visited[aa+bb][0]==0)
			{
				tt[ee]=op(aa+bb,0,2,1,ss);
				visited[aa+bb][0]=1;
				ee++;
			}
			else if (x-aa<=bb&&visited[x][bb-x+aa]==0)
			{
				tt[ee]=op(x,bb-x+aa,2,1,ss);
				visited[x][bb-x+aa]=1;
				ee++;
			}
		}
		ss++;
	}
	if (flag==0)
		cout<<"impossible"<<endl;
	else
	{
		int r[20000]={0};
		int cnt=0;
		//cout<<ss<<endl;
		while (tt[ss].last!=-1)
		{
			r[cnt]=ss;
			ss=tt[ss].last;
			cnt++;
		}
		cout<<cnt<<endl;
		for (int i=cnt-1;i>=0;i--)
			print_result(r[i]);
	}
	return 0;
}