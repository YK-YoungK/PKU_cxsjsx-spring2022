#include <cstdio>
#include <iostream>
using namespace std;

class f {
public:
    int r;
    f(int x):r(x){}
    f(int x,int y):r(x*y){}
    f operator()(int x)
    {
        return f(x+r);
    }
    friend ostream& operator<<(ostream& o,const f& x)
    {
        o<<x.r;
        return o;
    }
};

int main() {
  cout << f(4)(5) << endl;
  cout << f(64)(36) << endl;
  cout << f(3)(5)(7) << endl;
  cout << f(3,8) << endl;
  cout << f(15,3) << endl;
  cout << f(7,10) << endl;
}