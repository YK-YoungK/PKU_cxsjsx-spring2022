/* 程序填空，使其按要求输出(提示：可以写#include语句包含需要的头文件) 

输入
第一行是个整数，表示输入数据组数 
每组数据一行,有12个整数 

输出
对每组数据, 将12个整数从小到大排序并去除重复元素后输出


输入样例
2
34 5 4 6 3 9 8 34 5 3 3 18
31 2 4 6 2 9 8 31 5 3 3 18

输出样例
3 4 5 6 8 9 18 34 
2 3 4 5 6 8 9 18 31 


(注意：行末都有一个空格） 

*/


#include <iterator>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <stack>
#include <iostream>
#include <set>
using namespace std;

int main() {
	int t;
	int  a[100];
	cin >> t;
	while(t--) {
		for(int i = 0;i < 12; ++i)
			cin >> a[i];
	//your code starts here
		set<int> b(a, a+12);
		ostream_iterator<int> c(cout, " ");
	//end of your code 
		std::copy(b.begin(), b.end(), c);
		cout << endl;

	}
	return 0;
}


