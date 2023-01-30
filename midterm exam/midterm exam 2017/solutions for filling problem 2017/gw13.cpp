/*
��Ŀ������
���꣬���ڵ��Ӿ�������Խ��Խ��Ĺ�ע���е���ǿ�����Ա���ݶ��������ڣ����硶��������ʮ���һ�����Life After Life��Blooms Over Blooms�����е�����ʱ���ľ��������ϲ�������硶��������塷��In the Name of People�����е����Ծ�տ���ݼ�����Ϊ���̣����硶����������1566����Ming Dynasty: 1566����
��������Ǹ��ݵ��Ӿ�Ĳ�ͬ���ԣ���Ա���ݡ�������ݼ����Ե��Ӿ�������С�


���룺
������������n��������Ӿ�ĸ�����������������ÿ�����Ӿ����������룺��һ��һ���ַ��������ܺ��пո񣬶��ţ�ð�ŵȱ����ţ���Ϊ���Ӿ�����֣��ڶ��а��������������ֱ�Ϊ��Ա���ݡ�������ݼ������֡�
�����
����������У��ֱ�Ϊ���Ӿ簴��Ա���ݡ�������ݼ������а������ɸߵ��ͣ������Ӿ�����֮���ԷֺŸ���

�������룺
3
In the Name of People
98 97 99
Life After Life, Blooms Over Blooms
99 82 73
Ming Dynasty: 1566
97 100 100

���������
Life After Life, Blooms Over Blooms; In the Name of People; Ming Dynasty: 1566;
Ming Dynasty: 1566; In the Name of People; Life After Life, Blooms Over Blooms;
Ming Dynasty: 1566; In the Name of People; Life After Life, Blooms Over Blooms;
*/ 

#include<iostream>
#include<cstring>
#include<list>
#include<algorithm>
using namespace std;

class TV_Drama{
	public:
	char name[100];
	int actor;
	int story;
	int acting_skill;

	TV_Drama(char* _name, int _actor, int _story, int _acting_skill):actor(_actor), story(_story), acting_skill(_acting_skill){
	strcpy(name, _name);
}
	
//your code starts here
	bool operator < (const TV_Drama a){
		return actor<a.actor;
	}
	
	friend ostream & operator << (ostream & o, const TV_Drama drama){
		o<<drama.name<<' ';
		return o;
	}
};

void Printer(TV_Drama drama){
	cout<<drama<<';';
}

bool comparator_1(const TV_Drama a, const TV_Drama b){
	return a.story<b.story;
}

class comparator_2{
	public:
	int operator () (const TV_Drama a, const TV_Drama b){
		return a.acting_skill<b.acting_skill;
	}
};

//your code ends here

int main(){
	list<TV_Drama> lst;
	int n;
	
	cin>>n;
	char _name[100];
	int _actor, _story, _acting_skill;
	for (int i=0; i<n; i++){
		cin.ignore();
		
		cin.getline(_name, 100);
		cin>>_actor>>_story>>_acting_skill;
		lst.push_back(TV_Drama(_name, _actor, _story, _acting_skill));
	}

	lst.sort();
	for_each(lst.begin(), lst.end(), Printer);	
	cout<<endl;

	lst.sort(comparator_1);
	for_each(lst.begin(), lst.end(), Printer);	
	cout<<endl;

	lst.sort(comparator_2());
	for_each(lst.begin(), lst.end(), Printer);	
	cout<<endl;

	return 0;
}




