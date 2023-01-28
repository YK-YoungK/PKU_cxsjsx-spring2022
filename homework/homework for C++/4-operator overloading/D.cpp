#include <iostream>
#include <cstring>
using namespace std;

class Array2 {
private:
	int** ptr;
	int m,n;
public:
	Array2()
	{
		ptr=NULL;
		m=0;
		n=0;
	}
	Array2(int x,int y):m(x),n(y)
	{
		ptr=new int*[x];
		for (int i=0;i<x;i++)
			ptr[i]=new int[y]; 
	}
	~Array2()
	{
		if (ptr)
		{
			for (int i=0;i<m;i++)
				delete[] ptr[i];
			delete[] ptr;
		}
	}
	int* operator[] (int x)
	{
		return ptr[x];
	}
	int operator() (int x,int y)
	{
		return ptr[x][y];
	}
	Array2& operator =(const Array2& x)
	{
		if (ptr)
		{
			for (int i=0;i<m;i++)
				delete[] ptr[i];
			delete[] ptr;
		}
		m=x.m;
		n=x.n;
		ptr=new int*[m];
		for (int i=0;i<m;i++)
		{
			ptr[i]=new int[n];
			for (int j=0;j<n;j++)
			{
				ptr[i][j]=x.ptr[i][j];
			}
		}
		return *this;
	}
};

int main() {
    Array2 a(3,4);
    int i,j;
    for(  i = 0;i < 3; ++i )
        for(  j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;     b = a;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}