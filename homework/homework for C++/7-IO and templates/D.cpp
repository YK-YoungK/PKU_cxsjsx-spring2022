#include <iostream>
using namespace std;
class MyCin
{
public:
	bool stop;
	MyCin():stop(false){}
	MyCin& operator>>(int& x)
	{
		cin>>x;
		if (x==-1)
			stop=true;
		return *this;
	}
	operator bool()
	{
		return !stop;
	}
};
int main()
{
    MyCin m;
    int n1,n2;
    while( m >> n1 >> n2) 
        cout  << n1 << " " << n2 << endl;
    return 0;
}