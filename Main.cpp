#include<iostream>

using namespace std;

#include"TList.h"

int main() {
	int e;
	TMonom w(3,0,12,-1);
	TMonom r(3,3,12,8);
	TMonom q(9,3,12,-3);
	TPolynom p;
	p.addMonom(w);
	p.addMonom(r);
	p.addMonom(q);

	cout << p << "\n";
	TPolynom s;
	s = p*(-1);
	cout << s << "\n";
	cout << p + s << "\n";
}
