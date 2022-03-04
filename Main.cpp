#include<iostream>

using namespace std;

#include"TList.h"

int main() {
	int e;
	TMonom w(3,0,12,3);
	TMonom r(3,3,12,3);
	TMonom q(9,3,12,3);
	TPolinom p;
	for (int i = 0; i < 10; i++) {
		p.addMonom(TMonom(rand() % 3, rand() % 3, rand() % 3, -rand() % 10+rand()%10));
	}

	cout << p << "\n";
	p = p + p;
	cout << p << "\n";
}
