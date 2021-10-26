#pragma once
#define ONED 1
#define TWOD 2
#define THRD 3
#define FOUD 4

#include <math.h>
#include "../tool/list.h"



class measure //²â¶È
{
private:
	double var;
public:
	measure() { var = 0; };
	measure(int mea) { var = mea; };
	measure(float mea) { var = mea; };
	measure(double mea) { var = mea; };

	measure operator= (const int mea) { var = mea; return *this; };
	measure operator= (const float mea) { var = mea; return *this; };
	measure operator= (const double mea) { var = mea; return *this; };
	measure operator= (const measure mea) { var = mea.var; return *this; };

	measure operator+ () { var = +var; return *this; };
	measure operator- () { var = -var; return *this; };

	bool operator > (const measure mea) { return var > mea.var; };
	bool operator < (const measure mea) { return var < mea.var; };
	bool operator>= (const measure mea) { return var >= mea.var; };
	bool operator<= (const measure mea) { return var <= mea.var; };
	bool operator== (const measure mea) { return var == mea.var; };
	bool operator!= (const measure mea) { return var != mea.var; };

	measure operator += (const measure mea) { var += mea.var; return *this; };
	measure operator -= (const measure mea) { var -= mea.var; return *this; };
	measure operator *= (const measure mea) { var *= mea.var; return *this; };
	measure operator /= (const measure mea) { var /= mea.var; return *this; };

	friend measure operator + (const measure& A, const measure& B) { measure C(A.var + B.var); return C; };
	friend measure operator - (const measure& A, const measure& B) { measure C(A.var - B.var); return C; };
	friend measure operator * (const measure& A, const measure& B) { measure C(A.var * B.var); return C; };
	friend measure operator / (const measure& A, const measure& B) { measure C(A.var / B.var); return C; };
};


typedef list<measure> Data;
typedef list<measure> Line;
typedef list<measure> Colu;
typedef list<Data> Dete;
