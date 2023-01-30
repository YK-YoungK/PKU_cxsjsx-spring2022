#include <iostream>
#include <string>
#include <numeric>
#include <algorithm>
using namespace std;
// 在此处补充你的代码

template <class T>
//参考accumulate的源代码 
struct Print {
	int total; //用来记录一共 + 多少次以后就要换行
	int printTimes;
	Print(int t):total(t),printTimes(0) { }
	Print<T> operator +(T & t) {
		cout << t ;		
		++printTimes;
		if( printTimes == total )
			cout << endl;
		return * this;
			
	}
};

/////////////////////
int main(){
	string s[20];
	int num[20];
	int m,n;
	
	while(cin >> m >> n){
		for(int i=0; i<m; i++){
			cin >> s[i];
		}
		accumulate(s, s+m, Print<string>(m));
		for(int i=0; i<n; i++){
			cin >> num[i];
		}
		accumulate(num, num+n, Print<int>(n));
	}
}
