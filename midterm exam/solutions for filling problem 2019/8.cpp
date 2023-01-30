#include <iostream>
using namespace std;
int main()
{
	int a=0,b=0,i=0,j=0;
	cin>>a>>b>>i>>j;
	if (j<i)
	{
		int tmp=j;
		j=i;
		i=tmp;
	}
	if (j-i==31)
	{
		cout<<~a<<endl;
		return 0;
	}
	int x=(~((b>>i)&((1<<(j-i+1))-1)))&((1<<(j-i+1))-1) ;
	a=(a&((-1)-((1<<(j+1))-1)+((1<<i)-1)));
	a+=(x<<i);
	cout<<a<<endl;
	return 0;
}