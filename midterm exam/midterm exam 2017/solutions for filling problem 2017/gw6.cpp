/* ������գ�ʹ�䰴Ҫ�����(��ʾ������д#include��������Ҫ��ͷ�ļ�) 

����
��һ���Ǹ���������ʾ������������ 
ÿ������һ��,��12������ 

���
��ÿ������, ��12��������С��������ȥ���ظ�Ԫ�غ����


��������
2
34 5 4 6 3 9 8 34 5 3 3 18
31 2 4 6 2 9 8 31 5 3 3 18

�������
3 4 5 6 8 9 18 34 
2 3 4 5 6 8 9 18 31 


(ע�⣺��ĩ����һ���ո� 

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


