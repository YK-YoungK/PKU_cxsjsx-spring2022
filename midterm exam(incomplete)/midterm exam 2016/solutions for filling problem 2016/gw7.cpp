#include <iostream>
#include <string>
#include <map>
#include <list>
using namespace std;
// 在此处补充你的代码
/*
ostream & operator <<(ostream &o, const pair<int,list<int> > &p){
	o << p.first << ": ";
	list <int>::const_iterator it;
	for (it = p.second.begin(); it != p.second.end(); it++)
		o << *it <<' ';
	o << endl;
	return o;
}
template <class T>
void QueryResult(T first, T last){
	for (; first != last; first++){
		cout << *first;
	}
}
*/
int main(int argc, char* argv[])
{
	map<int, list<int> > Attendance;
	map<int, list<int> >::iterator it;
	string cmd;
	int date, id, date_lower, date_upper;
	while (cin >> cmd){
		if (cmd == "add"){
			cin >> date >> id;
			it = Attendance.find(date);
			if (it != Attendance.end()){
				it->second.push_back(id);
			}
			else{
				list<int> lst_id;
				lst_id.push_back(id);
				Attendance.insert(make_pair(date,lst_id));
			}
		}
		else if (cmd == "query"){
			cin >> date_lower>>date_upper;
			QueryResult(Attendance.lower_bound(date_lower), Attendance.upper_bound(date_upper));
		}
		else if (cmd == "exit")
			return 0;
	}
	return 0;
}
