/*

�������� n ( 0 <=n<= 2^30) , �Լ�����i,j(0 <= i,j <31,i < j-1), �������k(��ʮ������������ )��k�ĵ�iλ��n��ͬ����jλ��n��ͬ��i,j֮���λ��1, ����λ����0�������ᵽ�����е�λ��ָ�Ķ��Ƕ�����λ�����ұ����0λ  


��������
��һ�������� t����ʾ��������

ÿ������������һ�У��������� n,i��j 

�������
��ÿ���������ݣ���ʮ������������ 

����������
2
23 3 5 
7 0 2

���������
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

