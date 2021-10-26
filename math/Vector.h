#pragma once
#ifndef UNIVERSE_MATH_VECTOR
#define UNIVERSE_MATH_VECTOR
#include "measure.h"

class Vector
{
protected:
	vect vec;
	nume Dimension; //向量被声明后维度仅可被 “?=” 更改
public:
	Vector(nume dim = 0);
	Vector(vect meavec);
	//Vector(sure mea1);
	Vector(sure mea1, sure mea2);
	Vector(sure mea1, sure mea2, sure mea3);
	Vector(sure mea1, sure mea2, sure mea3, sure mea4);
	~Vector() { vec.clear(); };

	nume GetDim() { return Dimension; };
	void Setvect(vect meavec);
	void SetVect(Vector vect);
	vect Getvect(nume n, nume m);
	Vector GetVect(nume n, nume m);


	sure GetModulus() { return sqrt((*this) * (*this)); };			//得到向量的模

public:
	sure& operator[] (const nume& n);

	Vector operator = (const Vector& vect);
	bite operator == (const Vector& vect);
	bite operator != (const Vector& vect);

	friend Vector operator + (const Vector& vect);
	friend Vector operator - (const Vector& vect);

	friend Vector operator + (const Vector& A, const Vector& B);
	friend Vector operator - (const Vector& A, const Vector& B);
	friend sure operator * (const Vector& A, const Vector& B); //内积
	friend sure operator / (const Vector& A, const Vector& B); //投影

	friend Vector operator * (const sure& a, const Vector& B);
	friend Vector operator / (const sure& a, const Vector& B);
	friend Vector operator * (const Vector& A, const sure& b);
	friend Vector operator / (const Vector& A, const sure& b);

	Vector operator += (const Vector& vect) { return *this = *this + vect; };
	Vector operator -= (const Vector& vect) { return *this = *this - vect; };
	Vector operator *= (const sure& mea) { return *this = *this * mea; };
	Vector operator /= (const sure& mea) { return *this = *this / mea; };

	bite operator > (const Vector vect) { return (*this) * (*this) > vect * vect; };
	bite operator < (const Vector vect) { return (*this) * (*this) < vect * vect; };
	bite operator >= (const Vector vect) { return (*this) * (*this) >= vect * vect; };
	bite operator <= (const Vector vect) { return (*this) * (*this) <= vect * vect; };
};

#endif // !UNIVERSE_MATH_VECTOR