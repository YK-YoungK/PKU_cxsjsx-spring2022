

/*下列程序的输出为"10 13 18 15 17 12 16 19",  请补充代码

输入
无
输出
10 13 18 15 17 12 16 19
输入样例
无
输出样例
10 13 18 15 17 12 16 19 
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
int  a[10] = {0, 6, 7, 3, 9, 5, 8, 6, 4, 9};
int  b[10] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
int main(int argc, char** argv) {
//start of your code
	map< int, int >  c;
	map< int, int >::iterator it;
//end of your code 
	for(int i=0; i<10; i++) 
		c[a[i]] = b[i];
	for(it=c.begin(); it!=c.end(); it++) 
		cout<<it->second<<" ";
	return 0;
}

