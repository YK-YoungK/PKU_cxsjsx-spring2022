/*
�����
���������
����һ��int��ʾ��Χ�ڵ�������x�����������Ʊ�ʾ��һ��Ҫ���31λ�����㴦Ҫ��0��

����

��һ��������n(n<15)����ʾ��n��������Ҫ����
�ڶ�����n�������� 

���
��ÿ�������������������������Ʊ�ʾ������31λ����0���뵽31λ

��������
3
1 2 3

���������
 
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

