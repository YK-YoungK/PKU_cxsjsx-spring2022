//二分答案 
#include <bits/stdc++.h>
using namespace std;
int n;
long long m;
long long a[100005]={0};
long long b[100005]={0};  
long long tmpleft[100005]={0};
long long tmpright[100005]={0};
long long best=-1;
void search(long long l,long long r)
{
	long long mid=(l+r)/2;
	if (l>r)
		return;
	//cout<<l<<" "<<r<<endl; 
	vector<int> qleft{},qright{};
	long long maxr=0,minr=0;
	int cntleft=0,cntright=0;
	for (int i=0;i<n;i++)
	{
		if (mid>b[i])
		{
			cntleft++;
			minr+=a[i];
		}
		else if (mid<a[i])
		{
			cntright++;
			maxr+=b[i];
		}
		else
		{
			qleft.push_back(a[i]);
			qright.push_back(b[i]);
		}
	}
	if (cntright>n/2)//answer too small
	{
		l=mid+1;
		search(l,r);
		return;
	}
	if (cntleft>n/2)//answer too big
	{
		r=mid-1;
		search(l,r);
		return;
	}
	sort(qleft.begin(),qleft.end());
	sort(qright.begin(),qright.end(),greater<int>());
	for (int i=0;i<n/2-cntleft;i++)
		minr+=qleft[i];
	for (int i=0;i<n/2-cntright;i++)
		maxr+=qright[i];
	minr+=(n+1)/2*mid;
	maxr+=(n+1)/2*mid;
	if (maxr>=m&&minr<=m)
	{
		//cout<<mid<<endl;
		best=max(best,mid);
		l=mid+1;
		search(l,r);
	}
	else if (minr>m)//answer too big
	{
		search(l,mid-1);
		//search(mid+1,r);
	}
	else
	{
		search(mid+1,r);
	}
}
int main()
{
	cin>>n>>m;
	//r=m;
	for (int i=0;i<n;i++)
		cin>>a[i]>>b[i];
	search(0,m);
	cout<<best<<endl;
	return 0;
}