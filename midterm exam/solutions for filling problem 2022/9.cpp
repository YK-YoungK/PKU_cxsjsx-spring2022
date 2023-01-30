#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;
template <class T>
class CArray3D
{
public:
    int x;
    int y;
    int z;
    T* p;
   
    CArray3D(int xx, int yy, int zz) {
        x = xx;
        y = yy;
        z = zz;
        p = new T[x * y * z];
    }
    ~CArray3D() {
        delete[]p;
    }
class d
    {
    public:
		T* ptr;
		int w,l;
		d(T* pp,int w0,int l0):ptr(pp),w(w0),l(l0){}
		T* operator[](int t)
		{
			return ptr+t*l;
		}
	};
	d operator[](int t)
    {
    	return d(p+t*y*z,y,z);
	}
	CArray3D& operator +(const CArray3D& t)
	{
		for (int i=0;i<x*y*z;i++)
			p[i]+=t.p[i];
		return *this;
	}
	operator T*()
	{
		return p;
	 } 
};
CArray3D<int> a(3, 4, 5);
CArray3D<int>aa(3, 4, 5);
void PrintA()
{
    for (int i = 0; i < 3; ++i) {
        cout << "layer " << i << ":" << endl;
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 5; ++k)
                cout << a[i][j][k] << ",";
            cout << endl;
        }
    }
}
void PrintAA()
{
    for (int i = 0; i < 3; ++i) {
        cout << "layer " << i << ":" << endl;
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 5; ++k)
                cout << aa[i][j][k] << ",";
            cout << endl;
        }
    }
}
int main()
{
    int No = 0;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 4; ++j)
            for (int k = 0; k < 5; ++k)
            {
                a[i][j][k] = No++;
                aa[i][j][k] = a[i][j][k]+a[i][j][0];
            }
    PrintA();
    PrintAA();
    a + aa;//计算内部每个元素对应求和,更新a
    PrintA();

    memset(a, -1, 60 * sizeof(int));        //注意这里
    memset(a[1][1], 0, 5 * sizeof(int));
    PrintA();

    return 0;
}