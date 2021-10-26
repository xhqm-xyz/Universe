#ifndef UNIVERSE_MATH_CVECTOR
#define UNIVERSE_MATH_CVECTOR
#pragma once
#include "element.h"
//constexpr auto Pi = 3.141592653578;
//constexpr auto PRECI = 0.00000000001;
class CVector
{
public:
	CVector(int n, double var = 0) :_n(n) { fill(0); set(); for (int i = 0; i < n; i++) _vars[i] = var; };
	CVector(double var1 = 0):_n(1) { fill(0); _vars[0] = var1; };
	CVector(double var1,double var2) :_n(2) { fill(0); _vars[0] = var1; _vars[1] = var2; };
	CVector(double var1,double var2, double var3) :_n(3) { fill(0); _vars[0] = var1; _vars[1] = var2; _vars[2] = var3; };
	CVector(double var1,double var2, double var3, double var4) :_n(4) { fill(0); _vars[0] = var1; _vars[2] = var3; _vars[3] = var4; };


	int Get_n() { return _n; }
	void Set_n(int n) { _n = n; set(); }	
	void fill(double var) { _vars[0] = _vars[1] = _vars[2] = _vars[3] = var; };
	void copy(CVector mat,int n = 4){ if (n > 4) n = 4; for (int i = 0; i < n; i++)_vars[i] = mat[i]; };
	double GetModulus() { return sqrt((*this) * (*this)); };//得到行列式的值

	CVector GetUnitVec();							//单位化
	CVector GetTraVec();							//转置向量
	CVector GetSubVec();							//反向向量
	static CVector GetVecE(int n = 1);
	double& operator[](const int n) { return _vars[n]; };

	bool operator == (const CVector vect);
	bool operator != (const CVector vect);
	CVector operator + (const CVector vect) { CVector C(4); for (int i = 0; i < _n; i++) C[i] = +_vars[i]; return C; };
	CVector operator - (const CVector vect) { CVector C(4); for (int i = 0; i < _n; i++) C[i] = -_vars[i]; return C; };
	CVector operator = (const CVector vect) { _n = vect._n; for (int i = 0; i < vect._n; i++) _vars[i] = vect._vars[i]; return *this; };

	friend CVector operator + (const CVector& A, const CVector& B) { CVector C(4); for (int i = 0; i < 4; i++) C[i] = A._vars[i] + B._vars[i];  return C; };
	friend CVector operator - (const CVector& A, const CVector& B) { CVector C(4); for (int i = 0; i < 4; i++) C[i] = A._vars[i] - B._vars[i];  return C; };
	friend double operator * (const CVector& A, const CVector& B) { double c = 0; for (int i = 0; i < 4; i++) c = c + (A._vars[i] * B._vars[i]); return c; };
	friend double operator / (const CVector& A, const CVector& B) { double c = 0; for (int i = 0; i < 4; i++) c = c + (A._vars[i] / B._vars[i]); return c; };

	friend CVector operator + (const double& a, const CVector& B) { CVector C(4); for (int i = 0; i < 4; i++) C[i] = a + B._vars[i];  return C; };
	friend CVector operator - (const double& a, const CVector& B) { CVector C(4); for (int i = 0; i < 4; i++) C[i] = a - B._vars[i];  return C; };
	friend CVector operator * (const double& a, const CVector& B) { CVector C(4); for (int i = 0; i < 4; i++) C[i] = a * B._vars[i];  return C; };
	friend CVector operator / (const double& a, const CVector& B) { CVector C(4); for (int i = 0; i < 4; i++) C[i] = a / B._vars[i];  return C; };

	friend CVector operator + (const CVector& A, const double& b) { CVector C(4); for (int i = 0; i < 4; i++) C[i] = A._vars[i] + b;  return C; };
	friend CVector operator - (const CVector& A, const double& b) { CVector C(4); for (int i = 0; i < 4; i++) C[i] = A._vars[i] - b;  return C; };
	friend CVector operator * (const CVector& A, const double& b) { CVector C(4); for (int i = 0; i < 4; i++) C[i] = A._vars[i] * b;  return C; };
	friend CVector operator / (const CVector& A, const double& b) { CVector C(4); for (int i = 0; i < 4; i++) C[i] = A._vars[i] / b;  return C; };

protected:
	int _n = 4;
	double _vars[4];
	void set() { if (_n < 1)_n = 1; if (_n > 4)_n = 4; };
};

#endif // !UNIVERSE_MATH_CVECTOR