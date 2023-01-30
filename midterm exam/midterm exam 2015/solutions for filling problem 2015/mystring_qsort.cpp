/*
��д�� MyString�࣬ʹ�����������������ǣ�


1. abcd-efgh-abcd-
2. abcd-
3. 
4. abcd-efgh-
5. efgh-
6. c
7. abcd-
8. ijAl-
9. ijAl-mnop
10. qrst-abcd-
11. abcd-qrst-abcd- uvw xyz
about
big
me
take
abcd
qrst-abcd-


����
��

���
��������

��������
��

�������
��������

*/

#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;
// �ڴ˴�������Ĵ���
#include <algorithm> 

class MyString : public string{
	public:
	MyString():string() {};
	MyString( const char * s):string(s){};
	MyString( const string & s ): string(s){};
	MyString operator() ( int s, int l)
	{	
		return this->substr(s,l);
	};
};
typedef int (* COMPTR ) ( const void * e1, const void * e2);

struct Comp {
	COMPTR fptr;
	Comp(COMPTR ptr):fptr(ptr) { }
	bool operator()(const MyString & ms1, const MyString & ms2) {
		return fptr(&ms1,&ms2) < 0;
	}
};
template<class T>
void Qsort(T * a,int n,int width,COMPTR comp)
{
	T * p = (T*) a;
	sort(p,p+n,Comp(comp));
}
#define qsort Qsort   //�±�������qsort���ܶ�string���� ������Ҫ�滻֮ 


/////////////////////////
int CompareString( const void * e1, const void * e2)
{
	MyString * s1 = (MyString * ) e1;
	MyString * s2 = (MyString * ) e2;
	if( * s1 < *s2 )
		return -1;
	else if( *s1 == *s2)
		return 0;
	else if( *s1 > *s2 )
		return 1;
}
int main()
{
	//cout << qsort << endl;
	MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
	MyString SArray[4] = {"big","me","about","take"};
	cout << "1. " << s1 << s2 << s3<< s4<< endl;
	s4 = s3;
	s3 = s1 + s3;
	cout << "2. " << s1 << endl;
	cout << "3. " << s2 << endl;
	cout << "4. " << s3 << endl;
	cout << "5. " << s4 << endl;
	cout << "6. " << s1[2] << endl;
	s2 = s1;
	s1 = "ijkl-";
	s1[2] = 'A' ;
	cout << "7. " << s2 << endl;
	cout << "8. " << s1 << endl;
	s1 += "mnop";
	cout << "9. " << s1 << endl;
	s4 = "qrst-" + s2;
	cout << "10. " << s4 << endl;
	s1 = s2 + s4 + " uvw " + "xyz";
	cout << "11. " << s1 << endl;
	qsort(SArray,4,sizeof(MyString),CompareString);
	for( int i = 0;i < 4;i ++ )
	cout << SArray[i] << endl;
	//s1�Ĵ��±�0��ʼ����Ϊ4���Ӵ�
	cout << s1(0,4) << endl;
	//s1�Ĵ��±�5��ʼ����Ϊ10���Ӵ�
	cout << s1(5,10) << endl;
	return 0;
}