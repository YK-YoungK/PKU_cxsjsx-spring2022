 /*
�򵥵Ķ���

������գ�ʹ�ó������:

2
1
1
0

����
��
���
2
1
1
0

��������
��
�������
2
1
1
0
 
*/
#include <iostream>
using namespace std;
class A
{
	static int num;
public:
	A(){num+=1;}
	void func()
	{
		cout<< num <<endl;
	}
//your code starts here
	void func() const
	{
		num--;
		cout<< num <<endl;
	}
//your code ends here	
};

int A::num=1;
/////////////////////////////

int main()
{
	A a1;
	const A a2 = a1;
	A & a3 = a1;
	const A & a4 = a1;

	a1.func();
	a2.func();
	a3.func();
	a4.func();

	return 0;
}

