#include <iostream>
using namespace std;

//your code starts here
template <class T,class Pred>
T sum(T * a,int n,Pred op)
{
	T tmp = op(a[0]);
	for(int i = 1;i < n; ++i) 
		tmp += op(a[i]);
	return tmp;
}

//your code ends here
int sqr(int n) {
    return n * n;
}
int main() {
    int t, n, a[0x100];
    cin >> t;
    for (int c = 0; c < t; ++c) {
        cin >> n;
        for (int i = 0; i < n; ++i) cin >> a[i];
        cout << sum(a, n, sqr) << endl;
    }
    return 0;
}