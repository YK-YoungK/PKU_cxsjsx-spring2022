#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Mat{
	int h,w;
public:
	Mat(int height,int width):h(height),w(width)
// 在此处补充你的代码
	{
		p = new int[h*w];
		ct = count;
		++ count;
	}
	Mat() { //无参 构造函数写了保险，以免有对象用此初始化，p没有new,析构却被delete 
		p = new int[1];
	}
	
	Mat (const Mat & m) {
		h = m.h;
		w = m.w;
		p = new int[m.w * m.h];
		for(int i = 0;i < h; ++i)
			for(int j = 0; j < w; ++j)
				p[i*w+j] = m.p[i*w+j];
		ct = count;
		++ count;
	}
	int * p ;
	int ct; //创建序号 
	static int count;
	int sum() const {
		int s = 0;
		for(int i = 0;i < h; ++i)
			for(int j = 0; j < w; ++j)
				s += p[i*w+j];
		return s;
	}
	bool operator <(const Mat & m) const {
		if( h * w == m.h * m.w)
			return m.ct < ct;
		else
			return 	h * w < m.h * m.w;
	}
	Mat & operator=(const Mat & m )  {
		if( this == & m)
			return * this;
		delete [] p;
		p = new int[m.h*m.w];
		h = m.h;
		w = m.w;
		ct = ct;
		for(int i = 0;i < h*w; ++i)
			p[i] = m.p[i];
		return * this;
	}
	
	~Mat() { delete [] p ;};
	friend istream & operator>>(istream & in, Mat & m);
	friend ostream & operator<<(ostream & out, const Mat & m);
	friend bool comparator_1(const Mat & m1, const Mat & m2);
	friend struct  comparator_2;

};
int Mat::count = 0;
istream & operator>>(istream & in, Mat & m)
{
	for(int i = 0;i < m.h; ++i)
		for(int j = 0;j < m.w; ++j)
			in >> m.p[i * m.w + j ];
	return in;
}
ostream & operator<<(ostream & out, const Mat & m)
{
	for(int i = 0;i < m.h; ++i) {
		for(int j = 0;j < m.w; ++j)
			out <<  m.p[i * m.w + j ] << " ";
		out << endl;
	}
	return out;
}

bool comparator_1(const Mat & m1, const Mat & m2)
{
	int s1 = m1.sum();
	int s2 = m2.sum();
	if( s1 == s2 ) 
		return m2.ct < m1.ct;
	else
		return s1 < s2;
}
struct  comparator_2
{
	bool operator()(const Mat & m1, const Mat & m2)
	{
		return m1.ct < m2.ct;
	}
};

///////////////////
int main()
{
	vector<Mat> m;
	m.push_back(Mat(2,2));
	m.push_back(Mat(3,4));
	m.push_back(Mat(2,2));
	cin >> m[0] >> m[1] >> m[2];
	sort(m.begin(),m.end());
	cout<< m[0] << endl << m[1] << endl << m[2] <<endl;
	cout<<"*************"<<endl;
	sort(m.begin(),m.end(),comparator_1);
	cout<< m[0] << endl << m[1] << endl << m[2] <<endl;
	cout<<"*************"<<endl;
	sort(m.begin(),m.end(),comparator_2());
	cout<< m[0] << endl << m[1] << endl << m[2] <<endl;
	return 0;
}