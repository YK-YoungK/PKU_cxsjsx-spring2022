/*
周昊宇
二进制输出
给出一个int表示范围内的正整数x，输出其二进制表示。一共要输出31位，不足处要补0。

输入

第一行是整数n(n<15)，表示有n个正整数要处理
第二行是n个正整数 

输出
对每个给出的正整数，输出其二进制表示。不足31位则用0补齐到31位

输入样例
3
1 2 3

输出样例：
 
0000000000000000000000000000001
0000000000000000000000000000010
0000000000000000000000000000011

*/ 

#include <iostream>
#include <string>
using namespace std;
string dec2bin(int x){
	//your code starts here
 	string tmp;
	for (int i = 0; i < 31; i++)
	{
		tmp = char('0' + !!(x & (1 << i))) + tmp;
	}
	return tmp;
 	//your code ends here
}
int main(){
	int n;
	cin >> n;
	while(n--) {
		int x;
		cin >> x;
		cout << dec2bin(x) << endl;
	}
	return 0;
}

