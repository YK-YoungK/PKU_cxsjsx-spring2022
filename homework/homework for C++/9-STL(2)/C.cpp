#include <iostream>
#include <set>
using namespace std;
int main()
{
	multiset<int> result;
	set<int> tmp;
	string s;
	int n=0;
	cin>>n;
	int m=0;
	while (n>0)
	{
		cin>>s;
		if (s[1]=='d')
		{
			cin>>m;
			result.insert(m);
			tmp.insert(m);
			cout<<result.count(m)<<endl;
		}
		else if (s[0]=='d')
		{
			cin>>m;
			cout<<result.count(m)<<endl;
			result.erase(result.lower_bound(m),result.upper_bound(m));
		}
		else if (s[1]=='s')
		{
			cin>>m;
			if (tmp.find(m)==tmp.end())
				cout<<"0 ";
			else
				cout<<"1 ";
			cout<<result.count(m)<<endl;
		}
		n--;
	}
	return 0;
}