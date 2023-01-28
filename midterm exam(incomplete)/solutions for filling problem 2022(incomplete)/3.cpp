#include<iostream>
using namespace std;
int count(unsigned int x) {
int r=0;
    for (int i=0;i<32;i++) 
    {
        r+=(x>>i)&1;
    }
    return r;
}
int main() {
	int T; cin >> T;
	while (T--) {
		unsigned x; cin >> x;
		cout << count(x) << endl;
	}
	return 0;
}