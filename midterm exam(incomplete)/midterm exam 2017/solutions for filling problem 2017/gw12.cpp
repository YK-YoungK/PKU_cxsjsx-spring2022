/* 
������³���ʹ�����������n���Լ���������������
����n�������������Ȼ�����������ַ��������ַ������ȴ���n���ַ������

����
��һ��������t����ʾһ��t������

ÿ������������ 
��һ��������x ������ n 
�ڶ�����n������ 
��������n�������ո���ַ���

���
��ÿ������
�Ȱ�ԭ�������һ���д��� x��������(���ݱ�֤��������� 
�ٰ�ԭ������ڶ����г��ȴ���x���ַ��� (���ݱ�֤���������
 
��������
3
5 6
1 3 59 30 2 40
this is hello please me ha
1 1
4
this

�������
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

