#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
class IntegralImage{
public:
	int h,w;
	int** m;
	int count=0;
	IntegralImage(int x,int y):h(x),w(y) 
	{
		m=new int*[h];
		for (int i=0;i<h;i++)
			m[i]=new int[w];
	}
	void operator()(int* x)
	{
		if (count==0)
		{
			m[0][0]=x[0];
			for (int i=1;i<w;i++)
				m[0][i]=m[0][i-1]+x[i];
		}
		else
		{
			for (int i=0;i<w;i++)
			{
				m[count][i]=m[count-1][i];
				for (int j=0;j<=i;j++)
					m[count][i]+=x[j];
			}
		}
		count++;
	}
	int* operator[](int x)
	{
		return m[x];
	}
};
int main(){
    int H, W;
    cin >> H >> W;
    int ** image = new int*[H];
    for(int i=0;i<H;++i){
        image[i]=new int[W];
    }
    for(int i=0;i<H;++i)
    for(int j=0;j<W;++j)
        cin >> image[i][j];
    IntegralImage it(H,W);
    for_each(image, image+H, it);
    for(int i=0;i<H;++i){
        for(int j=0;j<W;++j)
            cout<<it[i][j]<<" ";
        cout<<endl;
    }
   
}