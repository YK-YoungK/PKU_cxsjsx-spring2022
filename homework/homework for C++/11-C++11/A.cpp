#include <iostream>
using namespace std;
template<class T1,class T2>
class f
{
public:
	T1 t;
	f(T1 t_):t(t_){}
	T2 operator()(T2 x)
	{
		T2 y;
		y=t;
		return x+y;
	}
};
int main()
{
   cout << f<int,int>(7)(9) << endl;   //16
   cout << f<string,string> (" hello!")("world")  <<endl; // world hello!
   cout << f<char,string> ('!')("world") << endl;
   
   
   return 0;    //world!
}