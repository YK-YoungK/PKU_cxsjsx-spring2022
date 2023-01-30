#include <iostream>
using namespace std;
// 在此处补充你的代码
//your code starts here
class CType {
	int v;
	public:
		void setvalue(int i) { v = i; }
		operator int() { return v * v; }
		int operator ++(int )  {
			return v;
		}
		
};
//your code ends here 
int main(int argc, char* argv[]) {
	CType obj;
	int   n;		
	cin>>n;
	while ( n ) {
		obj.setvalue(n);
		cout<<obj++<<" "<<obj<<endl;
		cin>>n;
	}
	return 0;
}
