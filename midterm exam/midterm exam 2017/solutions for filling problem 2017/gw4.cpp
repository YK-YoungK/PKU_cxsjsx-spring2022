/*补充下列代码，使得程序的输出为：
A:3
A:15
B:5
3
15
5

输入
无
输出 
见样例
 
输入样例
无
输出样例
A:3
A:15
B:5
3
15
5
 
*/

#include <iostream>
#using namespace std;
class CMyClassA {
	int val;
public:
	CMyClassA(int);
	void virtual print();
};
CMyClassA::CMyClassA(int arg) {
	val = arg;
	printf("A:%d\n", val);
}
void CMyClassA::print() {
	printf("%d\n", val);
	return;
}
//your code starts here
		class CMyClassB:public CMyClassA {
			int val;
		public:
			CMyClassB(int);
			void virtual print();
		};
		CMyClassB::CMyClassB(int arg):CMyClassA(arg+10) {
			val = arg;
			printf("B:%d\n", arg);
		}
		void CMyClassB::print() {
			printf("%d\n", val);
			return;
		}
//your code ends here
int main(int argc, char** argv) {
	CMyClassA a(3), *ptr;
	CMyClassB b(5);
	ptr = &a; ptr->print();
	a = b;
	a.print();
	ptr = &b; ptr->print();
	return 0;
}


