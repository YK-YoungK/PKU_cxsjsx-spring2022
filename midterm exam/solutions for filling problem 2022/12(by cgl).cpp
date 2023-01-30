#include <algorithm>
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <string>
#include <map>
#include <set>

using namespace std;
typedef pair<string, int> PAIR;
class MyMap:public map<string, int>
{
public:
	struct comp{
		bool operator ()(const PAIR & a,const PAIR & b)const{
			if(a.second!=b.second)return a.second>b.second;
			if(a.first.length()!=b.first.length())return a.first.length()<b.first.length();
			return a.first<b.first;
		}
	};
	vector<PAIR> st;
	friend istream & operator >>(istream & is,MyMap & y){
		string a;int b;
		cin>>a>>b;
		if(y.count(a))return is;
		y.st.push_back(make_pair(a,b));
		y.insert(make_pair(a,b));
		return is;
	}
	friend ostream& operator <<(ostream & os,MyMap & y){
		sort(y.st.begin(),y.st.end(),comp());
		for(auto i=y.st.begin();i!=y.st.end();i++)cout<<i->first<<' '<<i->second<<'\n';
		return os;
	}
};
int main()
{
	int t;
	cin >> t;
	while(t--) {
		int n;
		cin >> n;
		MyMap mm;
		for (int i = 0; i < n; ++i)
			cin >> mm;
		cout<<mm;
		
	}
	return 0; 
}
