#include <bits/stdc++.h>
using namespace std;
long long n,k;
double tmplen[10005]={0};
long long len[10005]={0}; 
long long l=1,r=0;
int main()
{
	cin>>n>>k;
	long long cnt=0;
	for (int i=0;i<n;i++)
	{
		cin>>tmplen[i];
		len[i]=tmplen[i]*100;
		r=max(len[i],r);
		cnt+=len[i];
	}
	if (cnt<k)
	{
		cout<<"0.00"<<endl;
		return 0;
	}
	long long best=1;
	while (l<=r)
	{
		long long mid=(l+r)/2;
		long long tmpcnt=0;
		for (int i=0;i<n;i++) 
			tmpcnt+=len[i]/mid;
		if (tmpcnt>=k)
		{
			best=max(best,mid);
			l=mid+1;
		}
		else
			r=mid-1;
	}
	//cout<<best<<endl;
	cout<<fixed<<setprecision(2)<<(double)best/100<<endl; 
	return 0;
}