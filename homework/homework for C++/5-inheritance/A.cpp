#include <cstdlib>
#include <iostream>
using namespace std;
int strlen(const char * s) 
{	int i = 0;
	for(; s[i]; ++i);
	return i;
}
void strcpy(char * d,const char * s)
{
	int i = 0;
	for( i = 0; s[i]; ++i)
		d[i] = s[i];
	d[i] = 0;
		
}
int strcmp(const char * s1,const char * s2)
{
	for(int i = 0; s1[i] && s2[i] ; ++i) {
		if( s1[i] < s2[i] )
			return -1;
		else if( s1[i] > s2[i])
			return 1;
	}
	return 0;
}
void strcat(char * d,const char * s)
{
	int len = strlen(d);
	strcpy(d+len,s);
}
class MyString
{
public:
	char ch[30];
	MyString()
	{
		for (int i=0;i<30;i++)
			ch[i]='\0';
	}
	MyString(const char * s)
	{
		int len=strlen(s);
		for (int i=0;i<30;i++)
			ch[i]='\0';
		for (int i=0;i<len;i++)
			ch[i]=s[i];
	}
	MyString(const MyString& s)//记得加const！ 
	{
		for (int i=0;i<30;i++)
			ch[i]=s.ch[i];
	}
	friend ostream& operator<<(ostream& o,const MyString& x)
	{
		o<<x.ch;
		return o; 
	}
	MyString& operator=(const MyString& x)
	{
		for (int i=0;i<30;i++)
			ch[i]=x.ch[i];
		return *this;
	}
	MyString operator+(const MyString& x)
	{
		int len1=strlen(ch),len2=strlen(x.ch);
		MyString result(*this);
		for (int i=len1;i<len1+len2;i++)
			result.ch[i]=x.ch[i-len1];
		return result;
	}
	friend MyString operator+(const char* x,const MyString& y)
	{
		int len1=strlen(x),len2=strlen(y.ch);
		MyString result(x);
		for (int i=len1;i<len1+len2;i++)
			result.ch[i]=y.ch[i-len1];
		return result;
	} 
	char& operator[](int x)
	{
		return ch[x]; 
	}
	MyString& operator+=(const char* x)
	{
		int len1=strlen(ch),len2=strlen(x);
		for (int i=len1;i<len1+len2;i++)
			ch[i]=x[i-len1];
		return *this;
	}
	friend bool operator<(MyString& x,MyString& y)
	{
		for (int i=0;i<30;i++)
		{
			if (x.ch[i]<y.ch[i])
				return true;
			if (x.ch[i]>y.ch[i])
				return false;
		} 
		return false; 
	}
	friend bool operator==(MyString& x,MyString& y)
	{
		for (int i=0;i<30;i++)
		{
			if (x.ch[i]!=y.ch[i])
				return false; 
		}
		return true;
	}
	friend bool operator>(MyString& x,MyString& y)
	{
		for (int i=0;i<30;i++)
		{
			if (x.ch[i]<y.ch[i])
				return false;
			if (x.ch[i]>y.ch[i])
				return true;
		} 
		return false; 
	}
	MyString operator()(int x,int y)
	{
		MyString result;
		for (int i=0;i<y;i++)
			result.ch[i]=ch[i+x];
		return result;
	}
};


int CompareString( const void * e1, const void * e2)
{
	MyString * s1 = (MyString * ) e1;
	MyString * s2 = (MyString * ) e2;
	if( * s1 < *s2 )
	return -1;
	else if( *s1 == *s2)
	return 0;
	else if( *s1 > *s2 )
	return 1;
}
int main()
{
	MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
	MyString SArray[4] = {"big","me","about","take"};
	cout << "1. " << s1 << s2 << s3<< s4<< endl;
	s4 = s3;
	s3 = s1 + s3;
	cout << "2. " << s1 << endl;
	cout << "3. " << s2 << endl;
	cout << "4. " << s3 << endl;
	cout << "5. " << s4 << endl;
	cout << "6. " << s1[2] << endl;
	s2 = s1;
	s1 = "ijkl-";
	s1[2] = 'A' ;
	cout << "7. " << s2 << endl;
	cout << "8. " << s1 << endl;
	s1 += "mnop";
	cout << "9. " << s1 << endl;
	s4 = "qrst-" + s2;
	cout << "10. " << s4 << endl;
	s1 = s2 + s4 + " uvw " + "xyz";
	cout << "11. " << s1 << endl;
	qsort(SArray,4,sizeof(MyString),CompareString);
	for( int i = 0;i < 4;i ++ )
	cout << SArray[i] << endl;
	//s1的从下标0开始长度为4的子串
	cout << s1(0,4) << endl;
	//s1的从下标5开始长度为10的子串
	cout << s1(5,10) << endl;
	return 0;
}