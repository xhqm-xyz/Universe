#pragma once
#ifndef UNIVERSE_SPACE_SVECTOR
#define UNIVERSE_SPACE_SVECTOR
#include "Smath.h"
#include "SPoint.h"
#include "SLine.h"
class SVector{
protected:
	double _vars[3] = { 0,0,0 };
public:
	SVector(double var1 = 0,double var2 = 0, double var3 = 0) { _vars[0] = var1; _vars[1] = var2; _vars[2] = var3; };
	SVector(SPoint star, SPoint end) { _vars[0] = end.x - star.x; _vars[1] = end.y - star.y; _vars[2] = end.z - star.z; };

	SPoint ToPoint(){ return SPoint(_vars[0], _vars[1], _vars[2]); }

	void fill(double var) { _vars[0] = _vars[1] = _vars[2] = var; };
	void copy(SVector vect){ for (int i = 0; i < 3; i++)_vars[i] = vect[i]; };
	double GetModulus() { return sqrt((*this) * (*this)); };
	double& operator[](const int n) { return _vars[n]; };
	bool operator == (const SVector vect) { return (((*this) - vect).GetModulus() <= SPRECI); };
	bool operator != (const SVector vect) { return !(*this == vect); }
	SVector operator + (const SVector vect) { SVector res; for (int i = 0; i < 3; i++) res._vars[i] = +_vars[i]; return res; };
	SVector operator - (const SVector vect) { SVector res; for (int i = 0; i < 3; i++) res._vars[i] = -_vars[i]; return res; };
	SVector operator = (const SVector vect) { for (int i = 0; i < 3; i++) _vars[i] = vect._vars[i]; return vect; };

	friend SVector operator + (const SVector& A, const SVector& B) { SVector C; for (int i = 0; i < 3; i++) C[i] = A._vars[i] + B._vars[i];  return C; };
	friend SVector operator - (const SVector& A, const SVector& B) { SVector C; for (int i = 0; i < 3; i++) C[i] = A._vars[i] - B._vars[i];  return C; };
	friend double operator * (const SVector& A, const SVector& B) { double c = 0; for (int i = 0; i < 3; i++) c = c + (A._vars[i] * B._vars[i]); return c; };
	friend double operator / (const SVector& A, const SVector& B) { double c = 0; for (int i = 0; i < 3; i++) c = c + (A._vars[i] / B._vars[i]); return c; };
	static SVector cross(const SVector& A, const SVector& B) //叉乘
	{ return SVector(A._vars[1]*B._vars[2] - B._vars[1] * A._vars[2], A._vars[2] * B._vars[0] - B._vars[2] * A._vars[0], A._vars[0] * B._vars[1] - B._vars[0] * A._vars[1]); };

	friend SVector operator + (const double& a, const SVector& B) { SVector C; for (int i = 0; i < 3; i++) C[i] = a + B._vars[i];  return C; };
	friend SVector operator - (const double& a, const SVector& B) { SVector C; for (int i = 0; i < 3; i++) C[i] = a - B._vars[i];  return C; };
	friend SVector operator * (const double& a, const SVector& B) { SVector C; for (int i = 0; i < 3; i++) C[i] = a * B._vars[i];  return C; };
	friend SVector operator / (const double& a, const SVector& B) { SVector C; for (int i = 0; i < 3; i++) C[i] = a / B._vars[i];  return C; };
	friend SVector operator + (const SVector& A, const double& b) { SVector C; for (int i = 0; i < 3; i++) C[i] = A._vars[i] + b;  return C; };
	friend SVector operator - (const SVector& A, const double& b) { SVector C; for (int i = 0; i < 3; i++) C[i] = A._vars[i] - b;  return C; };
	friend SVector operator * (const SVector& A, const double& b) { SVector C; for (int i = 0; i < 3; i++) C[i] = A._vars[i] * b;  return C; };
	friend SVector operator / (const SVector& A, const double& b) { SVector C; for (int i = 0; i < 3; i++) C[i] = A._vars[i] / b;  return C; };
	SVector GetUnitVec() { return *this / GetModulus(); };		//单位化
	SVector GetTraVec() { SVector Tra; for (int i = 0; i < 3; i++) Tra[i] = _vars[3 - i - 1]; return Tra; };	//转置向量
	static double GetCos(const SVector& A, const SVector& B) { return (A * B) / (sqrt(A * A) * sqrt(B * B)); }
	static double GetSin(const SVector& A, const SVector& B) { return SVector::cross(A, B).GetModulus() / (sqrt(A * A) * sqrt(B * B)); }
};

typedef std::vector<SVector> SVectors;

#endif // !UNIVERSE_SPACE_SVECTOR