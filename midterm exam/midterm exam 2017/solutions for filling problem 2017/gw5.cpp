
/*

�������д��룬ʹ�ó����ܹ���Ҫ�����

����
��һ��������t��ʾ�������� 
ÿ������������ 
��һ�п�ͷ������m��Ȼ�������m������(5 < m < 30)
�ڶ�����һ��û�пո���ַ��������Ȳ�����50 

���
��ÿ������ �����m�������еĵ�5����Ȼ������ַ����еĵ�7���ַ���
"��i��"�е� i �Ǵ�0��ʼ��ġ� 

��������
1
6 1 3 5 5095 8 8
helloworld

�������
8 r

 
*/
#include <iostream>
#include <cstring> 
#include <vector>
#include <cstdio> 
using namespace std;
//your code starts here
		template <class T>
		class CMyClass {
			T* val;
		public:
			CMyClass(const T*, int);
			T& operator [] (int);
		};
		template <class T>
		CMyClass<T>::CMyClass(const T* ptr, int len) {
			val = new T[len];
			for(int i=0; i<len; i++)
				val[i] = ptr[i];
		}
		template <class T>
		T& CMyClass<T>::operator [] (int arg) {
			return val[arg];
		}
//your code ends here
int  a[40];
int main(int argc, char** argv) {
	int t;
	scanf("%d",&t);
	while ( t -- ) {
		int m;
		scanf("%d",&m);
		for (int i = 0;i < m; ++i) 
			scanf("%d",a+i);
		char s[100];
		scanf("%s",s);
		CMyClass<int> b(a, m);
		CMyClass<char> c(s, strlen(s));
		printf("%d %c\n", b[5], c[7]);
	}
	return 0;
}

