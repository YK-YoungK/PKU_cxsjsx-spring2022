#include <bits/stdc++.h>
using namespace std;
void test()
{
	int n,k;
	cin>>n>>k;
	int m[100005]={0};
	for (int i=0;i<n;i++)
		cin>>m[i];
	sort(m,m+n);
	int l=m[0],r=300000;
	int best=1;
	int now=-1;
	for (int q=l;q<=r;q++)
	{
		while (now<n-1&&q>=m[now+1])
			now++;
		int tmp=k;
		int cnt=0;
		for (int j=now;j>=0;j--)
		{
			if (tmp>=q-m[j])
			{
				tmp-=(q-m[j]);cnt++;
			}
			else
			{
				break;
			}
		}
		/*if (cnt>best)
			cout<<q<<now<<endl;*/
		best=max(cnt,best);
		//cout<<i<<endl;
		/*if (cnt>=best)
		{
			l=mid+1;
			best=cnt;
		}
		else
			r=mid-1;*/
	}
	cout<<best<<endl; 
} 
int main()
{
	int t;
	cin>>t;
	for (int i=0;i<t;i++)
		test();
	return 0;
}