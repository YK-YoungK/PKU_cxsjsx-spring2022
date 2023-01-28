#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	cin>>n;
	int t[1005][2]={0};
	for (int i=0;i<n;i++)
		cin>>t[i][0]>>t[i][1];
	int m=0;
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			if (j==i)
				continue;
			if (t[i][1]<t[j][0]||t[i][0]>t[j][1])
				continue;
			if (t[i][0]>=t[j][0]&&t[i][1]<=t[j][1])
				m=max(m,t[i][1]-t[i][0]+1);
			else if (t[j][0]>=t[i][0]&&t[j][1]<=t[i][1])
				m=max(m,t[j][1]-t[j][0]+1);
			else
				m=max(m,min(abs(t[i][1]-t[j][0])+1,abs(t[i][0]-t[j][1])+1));
		}
	 } 
	cout<<m<<endl;
	return 0;
}