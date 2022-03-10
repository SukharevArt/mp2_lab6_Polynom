#pragma once
#include<iostream>


struct TMonom {
	double coeff;
	int x, y, z;

	TMonom(int _x=0, int _y=0, int _z=0,double _c = 0) {
		coeff = _c;
		x = _x;
		y = _y;
		z = _z;
	}
	TMonom(const TMonom& a) {
		coeff = a.coeff;
		x = a.x;
		y = a.y;
		z = a.z;
	}
	TMonom& operator = (const TMonom& a){
		coeff = a.coeff;
		x = a.x;
		y = a.y;
		z = a.z;
		return *this;
	}

	bool operator==(const TMonom& a) const {
		return a.x == x && a.y == y && a.z == z;
	}
	bool operator!=(const TMonom& a) const {
		return a.x != x || a.y != y || a.z != z;
	}
	bool operator<(const TMonom& a) const {
		if (a.x == x) {
			if (a.y == y) {
				return z < a.z;
			}
			else
				return y < a.y;
		}
		else
			return x < a.x;
	}
	bool operator>(const TMonom& a) const {
		return !(*this < a || *this == a);
	}
	friend std::ostream& operator<<(std::ostream& sout, const TMonom& a) {	
		sout << a.coeff;
		if (a.x != 0)
			sout << "x^" << a.x;
		if (a.y != 0)
			sout << "y^" << a.y;
		if (a.z != 0)
			sout << "z^" << a.z;
		return sout;
	}
	TMonom operator+(const TMonom& a) {
		if (*this != a)
			throw "Not_equal_monoms";
		TMonom nw(*this);
		nw.coeff += a.coeff;
		return nw;
	}
	TMonom operator-(const TMonom& a) {
		if (*this != a)
			throw "Not_equal_monoms";
		TMonom nw(*this);
		nw.coeff -= a.coeff;
		return nw;
	}
	TMonom operator*(const TMonom& a) {
		TMonom nw(a.x+x,a.y+y,a.z+z, a.coeff * coeff);
		return nw;
	}
	TMonom operator*(const int a) {
		TMonom nw(x,y,z, a * coeff);
		return nw;
	}
	TMonom operator*(const double a) {
		TMonom nw(x,y,z, a * coeff);
		return nw;
	}
	TMonom operator/(const TMonom& a) {
		TMonom nw(-a.x+x,-a.y+y,-a.z+z, coeff / a.coeff);
		return nw;
	}
	
};