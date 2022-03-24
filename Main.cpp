#include<iostream>

using namespace std;

#include"TList.h"

int main() {
	int e;
	{
		TMonom w(3, 0, 12, -1);
		TMonom r(3, 3, 12, 8);
		TMonom q(9, 3, 12, -3);
		TPolynom p;
		p.addMonom(w);
		p.addMonom(r);
		p.addMonom(q);
		TPolynom o;
		o.addMonom(w);
		o.addMonom(r * (-1));
		o.addMonom(TMonom(3, 4, 1, 2.6));
		o.addMonom(TMonom(3, 4, 0, -3.4));
		o.addMonom(TMonom(0, 4, 1, 0.4));
		cout << "P = " << p << "\n";
		cout << "O = " << o << "\n";
		cout << "P+O = " << o + p << "\n";
		cout << "\n";
	}
	{
		TMonom w(3, 0, 0, -1);
		TMonom r(0, 0, 12, 8);
		TMonom q(9, 0, 0, -3);
		TPolynom p;
		p.addMonom(w);
		p.addMonom(r);
		p.addMonom(q);
		TPolynom o;
		o.addMonom(TMonom(0, 0, 1, 2.6));
		o.addMonom(TMonom(0, 4, 0, -3.4));
		o.addMonom(TMonom(5, 0, 1, 0.4));
		cout << "P = " << p << "\n";
		cout << "O = " << o << "\n";
		cout << "P+O = " << o + p << "\n";
		cout << "\n";
	}
}
