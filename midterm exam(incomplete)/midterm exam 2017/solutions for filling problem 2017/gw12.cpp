/* 
完成以下程序，使得输入的整数n，以及若干正整数，将
大于n的正整数输出；然后输入若干字符串，将字符串长度大于n的字符串输出

输入
第一行是整数t，表示一共t组数据

每组数据有三行 
第一行是整数x 和整数 n 
第二行是n个整数 
第三行是n个不带空格的字符串

输出
对每组数据
先按原序输出第一行中大于 x的正整数(数据保证会有输出） 
再按原序输出第二行中长度大于x的字符串 (数据保证会有输出）
 
输入样例
3
5 6
1 3 59 30 2 40
this is hello please me ha
1 1
4
this

输出样例
59,30,40,
please,
4,
this,

 

*/
#include<iostream>
#include<algorithm>
#include<vector>
#include<bitset>

using namespace std;


class Printer{
//your code starts here	
	public:
	int n;
	Printer(int _n):n(_n){}
	void operator () (int i){
		if (i>n)
			cout<<i<<',';
	}
	void operator () (string i){
		if (i.size()>n)
			cout<<i<<',';
	}

};
//your code ends here

int main(){

	int t;
	cin >> t;
	while(t--) {
		int n,x;
		cin>>x>>n;
		
		vector<int> intVec;
		for(int i = 0;i < n; ++i) {
			int y;
			cin >> y;
			intVec.push_back(y);
		}
		for_each(intVec.begin(), intVec.end(), Printer(x));
		cout<<endl;
		
		vector<string> strVec;
		for(int i = 0;i < n; ++i) {
			string str;
			cin >> str;
			strVec.push_back(str);
		}
		for_each(strVec.begin(), strVec.end(), Printer(x));
		cout<<endl;
	}
	return 0;
}

