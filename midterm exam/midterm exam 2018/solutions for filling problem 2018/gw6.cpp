#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;
class C1{
// 在此处补充你的代码
//////////////////
	vector<int> v;
	public:
	C1(int s,const vector<int> & vt):v(vt)  {	}
	int & operator[] (int i) {
		return v[v.size()-i-1]; 
	}
	C1 & operator *=(int n) {
		for(int i = 0;i < v.size(); ++i)
			v[i] *= n;
		return * this;
	}
	vector<int>::iterator operator *() {
		return v.begin();
	}
	
/////////////	

};

int main()
{
    vector<int> v;
    int p;
    int size;
    int k;
    cin >> k;
    while(k--){
        cin >> size;
        v.clear();
        for(int i = 0; i < size; ++i){
            cin >> p;
            v.push_back(p);
        }
        C1 o1 = C1(size,v);
        ostream_iterator<int> it(cout,"---");
        copy(*o1, (*o1)+size, it);
        cout<<endl;
        for(int i = 0; i < size; ++i){
            o1[i]*=2;
            cout<<o1[i]<<"***";
        }
        cout<<endl;
    }
    
}