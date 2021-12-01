#include "SVector.h"

//SVector::SVector(double var1, double var2, double var3, double var4)
//{
//	_vars[0] = var1;
//	_vars[1] = var2;
//	_vars[2] = var3;
//	_vars[3] = var4;
//}
//
//SVector::SVector(SEquation equa)
//{
//	_vars[0] = equa.a;
//	_vars[1] = equa.b;
//	_vars[2] = equa.c;
//	_vars[3] = equa.d;
//}
//
//SVector::SVector(SPoint point)
//{
//	_vars[0] = point.x;
//	_vars[1] = point.y;
//	_vars[2] = point.z;
//	_vars[3] = 1;
//}
//
//void SVector::fill(double var)
//{
//	_vars[0] = _vars[1] = _vars[2] = _vars[3] = var;
//}
//
//double SVector::GetModulus()
//{
//	return sqrt((*this) * (*this));
//}
//
//double& SVector::operator[](const int n)
//{
//	return _vars[n];
//}
//
//bool SVector::operator==(const SVector vect)
//{
//	return (((*this) - vect).GetModulus() <= SPRECI);
//}
//
//bool SVector::operator!=(const SVector vect)
//{
//	return !(*this == vect);
//}

//SVector SVector::operator+(const SVector vect)
//{
//	SVector res; 
//	for (int i = 0; i < 4; i++) 
//		res._vars[i] = +_vars[i];
//	return res;
//}
