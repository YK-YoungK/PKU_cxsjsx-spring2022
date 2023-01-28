#include <bits/stdc++.h> 
using namespace std;
int main()
{
    int n;
    cin>>n;
    int r[300]={0};
    for (int i=0;i<n;i++)
        cin>>r[i];
    for (int i=n;i<2*n;i++)
        r[i]=r[i-n];
    int maxr=0;
    for (int i=0;i<n;i++)
    {
    	for (int j=i+1;j<2*n;j++)
    	{
    		if (r[j]>=r[j-1])
    		{
    			maxr=max(maxr,j-i-1);
				//cout<<j-1<<endl;
				break;
			}
		}
	}
	cout<<maxr<<endl;
    return 0;
}