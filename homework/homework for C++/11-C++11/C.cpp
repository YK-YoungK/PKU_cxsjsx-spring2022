#include <iostream>
#include <cstring>
using namespace std;
template <int bitNum>
struct MyBitset 
{
	char a[bitNum/8+1];
	MyBitset() { memset(a,0,sizeof(a));};
	void Set(int i,int v) {
		char & c = a[i/8];
		int bp = i % 8;
		if( v ) 
			c |= (1 << bp);
		else 
			c &= ~(1 << bp);
	}
class bit;
	friend class bit;
	class bit
	{
	public:
		int place;
		bool num;
		MyBitset& out;
		bit(int x,bool n,MyBitset& y):place(x),num(n),out(y){}
		bit& operator=(const bit& x)
		{
			num=x.num;
			out.Set(place,num);
			return *this;
		}
		bit& operator=(int x)
		{
			num=x;
			out.Set(place,num);
			return *this;
		}
		friend ostream& operator<<(ostream& o,const bit& b)
		{
			o<<b.num;
			return o;
		}
	};
	bit operator[](int x)
	{
		return bit(x,(a[x/8]>>(x%8))&1,*this);
	}
void Print() {
		for(int i = 0;i < bitNum; ++i) 
			cout << (*this) [i];
		cout << endl;
	}

};

int main()
{
	int n;
	int i,j,k,v;
	while( cin >>  n) {
		MyBitset<20> bs;
		for(int i = 0;i < n; ++i) {
			int t;
			cin >> t;
			bs.Set(t,1);
		}
		bs.Print();
		cin >> i >> j >> k >> v;
		bs[k] = v;
		bs[i] = bs[j] = bs[k];
		bs.Print();
		cin >> i >> j >> k >> v;
		bs[k] = v;
		(bs[i] = bs[j]) = bs[k];
		bs.Print();
	}
	return 0;
}