#include <iostream> 
#include <cstring> 
#include <cstdlib> 
#include <cstdio> 
using namespace std;
const int MAX = 110; 
class CHugeInt {
public:
	int number[210];
	CHugeInt(char *s)
	{
		int len=strlen(s);
		memset(number,0,sizeof(number));
		for (int i=0;i<len;i++)
			number[209-i]=s[len-1-i]-'0';
	}
	CHugeInt(int n)
	{
		memset(number,0,sizeof(number));
		for (int i=0;i<210;i++)
		{
			number[209-i]=n%10;
			n/=10;
		}
	}
	CHugeInt(const CHugeInt & x)
	{
		for (int i=0;i<210;i++)
			number[i]=x.number[i];
	}
	friend CHugeInt operator+(int x0,const CHugeInt& y)
	{
		CHugeInt x(x0);
		int result[210]={0};
		for (int i=0;i<210;i++)
			result[i]=x.number[i]+y.number[i];
		int tmp=0;
		for (int i=209;i>=0;i--)
		{
			int tmp2=tmp;
			tmp=(result[i]+tmp2)/10;
			result[i]=(result[i]+tmp2)%10;
		}
		CHugeInt final(0);
		for (int i=0;i<210;i++)
			final.number[i]=result[i];
		return final;
	}
	CHugeInt operator+(const CHugeInt& y)
	{
		int result[210]={0};
		for (int i=0;i<210;i++)
			result[i]=number[i]+y.number[i];
		int tmp=0;
		for (int i=209;i>=0;i--)
		{
			int tmp2=tmp;
			tmp=(result[i]+tmp2)/10;
			result[i]=(result[i]+tmp2)%10;
		}
		CHugeInt final(0);
		for (int i=0;i<210;i++)
			final.number[i]=result[i];
		return final;
	}
	CHugeInt operator+(int y0)
	{
		CHugeInt y(y0);
		int result[210]={0};
		for (int i=0;i<210;i++)
			result[i]=number[i]+y.number[i];
		int tmp=0;
		for (int i=209;i>=0;i--)
		{
			int tmp2=tmp;
			tmp=(result[i]+tmp2)/10;
			result[i]=(result[i]+tmp2)%10;
		}
		CHugeInt final(0);
		for (int i=0;i<210;i++)
			final.number[i]=result[i];
		return final;
	}
	CHugeInt& operator +=(const CHugeInt& y)
	{
		for (int i=0;i<210;i++)
			number[i]+=y.number[i];
		int tmp=0;
		for (int i=209;i>=0;i--)
		{
			int tmp2=tmp;
			tmp=(number[i]+tmp2)/10;
			number[i]=(number[i]+tmp2)%10;
		}
		return *this;
	}
	CHugeInt& operator++()
	{
		number[209]++;
		int tmp=0;
		for (int i=209;i>=0;i--)
		{
			int tmp2=tmp;
			tmp=(number[i]+tmp2)/10;
			number[i]=(number[i]+tmp2)%10;
		}
		return *this;
	}
	CHugeInt operator++(int x)
	{
		CHugeInt result(*this);
		number[209]++;
		int tmp=0;
		for (int i=209;i>=0;i--)
		{
			int tmp2=tmp;
			tmp=(number[i]+tmp2)/10;
			number[i]=(number[i]+tmp2)%10;
		}
		return result;
	}
	friend ostream& operator<<(ostream& o,CHugeInt x)
	{
		int start=0;
		for (start=0;start<209;start++)
		{
			if (x.number[start]==0&&x.number[start+1]!=0)
			{
				start++;
				break;
			}
		}
		for (int i=start;i<210;i++)
			o<<x.number[i];
		return o;
	}
};
int  main() 
{ 
	char s[210];
	int n;

	while (cin >> s >> n) {
		CHugeInt a(s);
		CHugeInt b(n);

		cout << a + b << endl;
		cout << n + a << endl;
		cout << a + n << endl;
		b += n;
		cout  << ++ b << endl;
		cout << b++ << endl;
		cout << b << endl;
	}
	return 0;
}