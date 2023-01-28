#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class MyString {
	char * p;
public:
	MyString(const char * s) {
		if( s) {
			p = new char[strlen(s) + 1];
			strcpy(p,s);
		}
		else
			p = NULL;

	}
	~MyString() { if(p) delete [] p; }
MyString(const MyString &x)
	{
		if (x.p==NULL)
			p=NULL;
		p=new char[strlen(x.p)+1];
		strcpy(p,x.p);
	}
	MyString& operator =(const MyString & x)
	{
		if (p==x.p)
			return *this;
		if (p)
			delete[] p;
		p=new char[strlen(x.p)+1];
		strcpy(p,x.p);
		return *this;
	}
	MyString& operator =(const char* x)
	{
		if (p)//注意题目中有可能为null 
			delete[] p;
		p=new char[strlen(x)+1];
		strcpy(p,x);
		return *this;
	}
	MyString& Copy(const char* x)
	{
		if (p) 
			delete[] p;
		p=new char[strlen(x)+1];
		strcpy(p,x);
		return *this;
	}
	friend ostream& operator <<(ostream& o,const MyString& c)
	{
		o<<c.p;
		return o;
	} 
};
int main()
{
	char w1[200],w2[100];
	while( cin >> w1 >> w2) {
		MyString s1(w1),s2 = s1;
		MyString s3(NULL);
		s3.Copy(w1);
		cout << s1 << "," << s2 << "," << s3 << endl;

		s2 = w2;
		s3 = s2;
		s1 = s3;
		cout << s1 << "," << s2 << "," << s3 << endl;
		
	}
}