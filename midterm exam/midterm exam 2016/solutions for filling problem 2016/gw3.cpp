#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
// 在此处补充你的代码

/*
struct Pred
{
	int n;
	Pred(int n_):n(n_) {	}
	bool operator()(int x) {
		return (x >> n ) & 1;
	}
};
*/
int main(int argc, char** argv) {	
	int n, x;
	vector<int> intVec;
	cin>>n>>x; 
	while(x) {
		intVec.push_back(x);
		cin>>x;
	}
	cout<<count_if(intVec.begin(), intVec.end(), Pred(n))<<endl;
	return 0;
}
