#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;
class CMean {
public:
	int sum;
	int count;
	int* average;
	CMean(int& x)
	{
		average=&x;
		count=0;
		sum=0;
	}
	void operator()(int y)
	{
		sum+=y;
		count++;
		*average=sum/count;
	}
	
};

int main(int argc, char* argv[]) {
	int  v;
	int t;
	cin >> t;
	while ( t -- ) {
		cin >> v;
		vector<int> vec;
		while (v) {
			vec.push_back(v);
			cin >> v;
		}
		int myAver = 0;
		for_each(vec.begin(), vec.end(), CMean(myAver));
		cout << myAver << endl;
	}
	return 0;
}