#include <iostream>
using namespace std;
class B { 
	private: 
		int nBVal; 
	public: 
		void Print() 
		{ cout << "nBVal="<< nBVal << endl; } 
		void Fun() 
		{cout << "B::Fun" << endl; } 
		B ( int n ) { nBVal = n;} 
};
class D:public B
{
public:
	int ndval;
	D(int n):B(3*n),ndval(n){}
	void Fun()
	{
		cout<<"D::Fun"<<endl;
	}
	void Print()
	{
		B::Print();
		cout<<"nDVal="<<ndval<<endl;
	}
}; 
int main() { 
	B * pb; D * pd; 
	D d(4); d.Fun(); 
	pb = new B(2); pd = new D(8); 
	pb -> Fun(); pd->Fun(); 
	pb->Print (); pd->Print (); 
	pb = & d; pb->Fun(); 
	pb->Print(); 
	return 0;
}