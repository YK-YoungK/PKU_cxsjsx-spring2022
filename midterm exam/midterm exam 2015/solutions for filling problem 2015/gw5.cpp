#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// 在此处补充你的代码
//your code starts here
class CMy_add {
	int & mySum;
public:	
	CMy_add(int & ms):mySum(ms) { }
	void operator ()(int & n ) {
		mySum += n & 0x7; 
	}
};

//your code ends here
int main(int argc, char* argv[]) {
	int  v, my_sum=0;
	vector<int> vec;		
	cin>>v;
	while ( v ) {
		vec.push_back(v);
		cin>>v;
	}
	for_each(vec.begin(), vec.end(), CMy_add(my_sum));
	cout<<my_sum<<endl;	
	return 0;
}
