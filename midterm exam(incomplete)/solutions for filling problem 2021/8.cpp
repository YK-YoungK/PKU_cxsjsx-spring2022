#include<iostream>
using namespace std;
unsigned int calc(unsigned int n,unsigned m,int x,int y) {
	int n0=(n>>x)&((1<<(32-y-x))-1);
	int m0=(m>>x)&((1<<(32-y-x))-1);
	return n-(n0<<x)+(m0<<x);
}
int main() {
  int x, y, t;
  unsigned int n, m;
  cin >> t;
  while (t--) { 
    cin >> n >> m >> x >> y;
    cout << calc(n, m, x, y) << endl;
  }
  return 0;
}