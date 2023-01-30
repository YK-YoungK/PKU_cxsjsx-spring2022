#include <iostream>
#include <set>
using namespace std;
// 在此处补充你的代码
/*
struct Rectangle
{
	int a,b;
	Rectangle(int a_,int b_):a(a_),b(b_) { }
	int ar() const { return a * b; }
	int p() const {  return (a + b) * 2; }
	bool operator <(const Rectangle & r) const {
		if (ar() == r.ar())
			return p() > r.p();
		return ar() > r.ar();
	}
	
};
struct Comp
{
	bool operator ()(const Rectangle & r1, const Rectangle & r2)
	{
		if (r1.p() == r2.p()) 
			return r1.ar() < r2.ar();
		return r1.p() < r2.p();
	}
};
ostream & operator << (ostream & o,const Rectangle & r) {
	o << r.ar() << " " << r.p() ;
	return o;
}
*/

int main() {
    multiset<Rectangle> m1;
    multiset<Rectangle, Comp> m2;
    int n, a, b;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        m1.insert(Rectangle(a, b));
        m2.insert(Rectangle(a, b));
    }
    for (multiset<Rectangle>::iterator it = m1.begin(); it != m1.end(); it++) {
        cout << *it << endl;
    }
    cout << endl;
    for (multiset<Rectangle>::iterator it = m2.begin(); it != m2.end(); it++) {
        cout << *it << endl;
    }
	return 0;
}
