
/*代码填空，使得程序能够自动统计统计当前各种动物的数量，样例程序输出应为：

0 animals in the zoo, 0 of them are dogs, 0 of them are cats
3 animals in the zoo, 2 of them are dogs, 1 of them are cats
6 animals in the zoo, 3 of them are dogs, 3 of them are cats
3 animals in the zoo, 2 of them are dogs, 1 of them are cats

*/

#include <iostream>
using namespace std;
//your code starts here
class Animal {
public:
	static int number;

	Animal() {
		++number;
	} 
	virtual ~Animal() {}
};

class Dog : public Animal {
public:
	static int number;
	Dog() {
		++number;
	}
	virtual ~Dog() {
		--number;
		--Animal::number;
	}
};

class Cat : public Animal {
public:
	static int number;
	Cat() {
		++number;
	}
	virtual ~Cat() {
		--number;
		--Animal::number;
	}
};

int Animal::number = 0;
int Dog::number = 0;
int Cat::number = 0;
//your code ends here

void print() {
	cout << Animal::number << " animals in the zoo, " << Dog::number << " of them are dogs, " << Cat::number << " of them are cats" << endl;
}

int main() {
	print();
	Dog d1, d2;
	Cat c1;
	print();
	Dog* d3 = new Dog();
	Animal* c2 = new Cat;
	Cat* c3 = new Cat;
	print();
	delete c3;
	delete c2;
	delete d3;
	print();
}

