//dp+滚动 
//dp[j]:前i门伤心j次,mingpa
#include <bits/stdc++.h>
using namespace std;
int n;
double gpa[4005][2]={0};
double dp[4005]={0};
int main()
{
	cin>>n;
	for (int i=0;i<n;i++)
		cin>>gpa[i][0]>>gpa[i][1];
	for (int i=0;i<4005;i++)
		dp[i]=-1;
	dp[0]=min(gpa[0][0],gpa[0][1]); 
	for (int i=1;i<n;i++)
	{
		for (int j=i;j>=0;j--)
		{
			double tmp=1000;
			if (dp[j]!=-1&&gpa[i][0]>=dp[j])
				tmp=min(tmp,(dp[j]*i+gpa[i][0])/(i+1));
			if (dp[j]!=-1&&gpa[i][1]>=dp[j])
				tmp=min(tmp,(dp[j]*i+gpa[i][1])/(i+1));
			if (j>=1)
			{
				if (gpa[i][0]<dp[j-1])
					tmp=min(tmp,(dp[j-1]*i+gpa[i][0])/(i+1));
				if (gpa[i][1]<dp[j-1])
					tmp=min(tmp,(dp[j-1]*i+gpa[i][1])/(i+1));
			}
			if (tmp==1000)
				dp[j]=-1;//no solution
			else
				dp[j]=tmp;
		}
	}
	for (int i=0;i<n;i++)
	{
		if (dp[i]!=-1)
		{
			cout<<i<<endl;
			break; 
		}
	}
	return 0;
}