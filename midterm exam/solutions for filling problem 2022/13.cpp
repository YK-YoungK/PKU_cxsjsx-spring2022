#include<iostream>
using namespace std;
void print(unsigned int x) {
int result[32]={0};
	for (int i=0;i<32;i++)
		result[i]=(x>>i)&1;
	int count=0;
	for (int i=0;i<32;i++)
		count+=result[i];
	int place[10]={0};
	int tmp=0;
	for (int i=0;i<32;i++)
	{
		if (result[i])
		{
			place[tmp]=i;
			tmp++; 
		}
	}
	for (int i=0;i<(1<<count);i++)
	{
		unsigned int r=0;
		for (int j=0;j<count;j++)
		{
			if ((i>>j)&1)
				r+=(1<<place[j]);
				
		}
		cout<<r<<endl;
	}
}
int main() {
	int T; cin >> T;
	while (T--) {
		unsigned x; cin >> x;
		print(x);
	}
	return 0;
}