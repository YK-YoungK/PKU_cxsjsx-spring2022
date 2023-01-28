#include <bits/stdc++.h>
using namespace std;
char tmp[25]={};
void dfs(int rl,int rr,int now)
{
	if (rl==0&&rr==0)
	{
		cout<<tmp<<endl;
		return;
	} 
	if (rl<0||rr<0)
		return;
	if (rl>rr)
		return;
	tmp[now]='(';
	dfs(rl-1,rr,now+1);
	tmp[now]=')';
	dfs(rl,rr-1,now+1); 
	tmp[now]='\0';
	return; 
}
int main()
{
	int n;
	cin>>n;
	dfs(n,n,0); 
	return 0;
}