#include <iostream>
#include <set>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;
#include<iostream>
using namespace std;
class Number {
public:
    int num;
    Number(int n=0): num(n) {}
//your code starts here
	int operator*(const Number & nb)
	{
		return num * nb.num;
	}
	operator int() {
		return num;
	}
	

//your code ends here


};

int main() {
    Number n1(10), n2(20);
    Number n3;
    n3 = n1*n2;
    cout << int(n3) << endl;
    return 0;
}