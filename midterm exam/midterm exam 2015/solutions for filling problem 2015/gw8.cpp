/*

输入整数 n ( 0 <=n<= 2^30) , 以及整数i,j(0 <= i,j <31,i < j-1), 输出整数k(按十六进制输出结果 )，k的第i位和n相同，第j位和n不同，i,j之间的位是1, 其他位都是0。这里提到的所有的位，指的都是二进制位，最右边算第0位  


输入数据
第一行是整数 t，表示数据组数

每组输入数据是一行，三个整数 n,i和j 

输出数据
对每组输入数据，按十六进制输出结果 

输入样例：
2
23 3 5 
7 0 2

输出样例：
30
3 
*/

#include <iostream>
using namespace std;

using namespace std;
int main()
{
	int t;
	cin >> t;
	while( t--) {
		int n,i,j;
		cin >> n >> i >> j;
		int m = ( 1 << j )^n;
		int k = ((1 << i) & n ) | ((1 << j) & m);
		int tmp1 = 0xffffffff << (i+1);
		int tmp2 = ~ (0xffffffff << j);
		
		cout << hex << ( k | (tmp1 & tmp2)) << endl; 
	}
	return 0;
}

