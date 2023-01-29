#include<bits/stdc++.h>
using namespace std;
int dp[501][501],n,a[510];//dp[i][j][k] 前i个改j最后为k得到的lis
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		for(int j=n;j>=0;j--){
			for(int k=n;k>=0;k--){
				if(k<a[i])dp[j][a[i]]=max(dp[j][a[i]],dp[j][k]+1);
				if(j&&k)dp[j][k]=max(dp[j][k],dp[j-1][k-1]+1);
			}
		}
	}
	for(int i=0;i<=n;i++){
		int mx=0;
		for(int k=0;k<=n;k++)mx=max(mx,dp[i][k]);
		cout<<mx<<' ';
	}
}
