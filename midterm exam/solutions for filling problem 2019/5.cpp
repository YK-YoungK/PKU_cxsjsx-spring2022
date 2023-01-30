#include <iostream>
#include <string>
using namespace std;
template <class T> 
class container{
public:
	T t;
	container(T e):t(e){}
	T operator+(const container& x)
	{
		T r=t+x.t+x.t;
		return r;
	}
	T operator+(const T& x)
	{
		t=t+x;
		return t;
	}
};
int main(){
	int n,m;
	cin >> n >> m;
	string s1,s2;
	cin >> s1 >> s2;
    container <int> a = n;
    container <int> b = m;
    cout<<a+b<<endl;
    cout<<a+m<<endl;
    container <string> sa = string(s1);
    container <string> sb = string(s2);
    cout<<sa+sb<<endl;
    cout<< sa + s2<<endl;
}