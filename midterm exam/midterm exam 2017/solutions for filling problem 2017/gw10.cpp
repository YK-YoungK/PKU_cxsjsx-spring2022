
/*题名：回调函数

输入x1 x2 x3 x4 x5 ，输出y = x5^5 + x4^4 + x3^3 + x2^2 + x1^1 + 1的y的值

输入
多组数据。第一行是数据组数 n
每组数据为一行,5个整数，x1 x2 x3 x4 x5。数值不大，不必考虑溢出 

输出
对每组数据，输出一个整数y， y = x5^5 + x4^4 + x3^3 + x2^2 + x1^1 + 1

样例输入
2
2 2 2 2 2
1 1 1 1 1

样例输出

63
6

*/

#include <algorithm>
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <string>
#include <cmath>
#include <map>
#include <set>

using namespace std;
class MyFunc
{
	/*
	补全代码
	*/
//your code starts here
public:
	int parameter;
	MyFunc(int par):parameter(par){}
	int operator() (int num)
	{
		if(num == 0)return 0;
		int res = 1;
		for (int i = 0; i < parameter; ++i)
		{
			res *= num;
		}
		return res;
	}
//your code ends here	

};
int main()
{
	int n;
	cin >> n;
	while(n--) {
		vector<MyFunc> v;
		for (int i = 0; i < 5; ++i)
			v.push_back(MyFunc(i+1));
		int ans = 1;
		for (int i = 0; i < 5; ++i)
		{
			int m;
			cin >> m;
			ans += v[i](m);
		}
		cout << ans <<endl;
	}
}



