#include <set>
#include <iostream>
using namespace std;
template <class T>
class MySet: public set<T> {
public:
void insert(T x)
    {
        if (set<T>::find(x)!=set<T>::end())
            cout<<"Error insert "<<x<<endl;
        else
            set<T>::insert(x);
    }
    void erase(T x)
    {
        if (set<T>::find(x)==set<T>::end())
            cout<<"Error erase "<<x<<endl;
        else
            set<T>::erase(x);
    }
};
int main(){
	int n; scanf("%d",&n);
	MySet<int> S;
	for (int i=1;i<=n;i++){
		cout<<"Operation #"<<i<<":"<<endl;
		string type; int w;
		cin>>type>>w;
		if (type=="insert") S.insert(w);
		else if (type=="erase") S.erase(w);
	}
	cout<<endl;
	MySet<string> S2;
	for (int i=1;i<=n;i++){
		cout<<"Operation #"<<i<<":"<<endl;
		string type; string w;
		cin>>type>>w;
		if (type=="insert") S2.insert(w);
		else if (type=="erase") S2.erase(w);
	}
}