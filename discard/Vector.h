#pragma once
#include "measure.h"

class Vector
{
protected:
	Data vec;
	size Dimension; //点被声明后维度仅可被 “=” 更改
public:
	Vector(size dim = 0);
	Vector(Data meavec);
	Vector(measure mea1);
	Vector(measure mea1, measure mea2);
	Vector(measure mea1, measure mea2, measure mea3);
	Vector(measure mea1, measure mea2, measure mea3, measure mea4);


	void SetVect(Vector vect);
	void SetVect(measure mea);
	bool SetVect(measure mea, size n);
	bool SetVect(Data meavec, size n = 0, size m = 0);
	
	Data GetAngle();
	Data GetVect() { return vec; };
	size GetSize() { return Dimension; };

	measure GetAngle(Vector vect) { acos(((*this * vect) / (GetModulus() * vect.GetModulus())).var); };
	measure GetVect(size n) { if (n < 0 || n >= Dimension) n = 0; return vec[n]; };	//得到第n个维度的值
	measure GetModulus() { return sqrt(((*this) * (*this)).var); };					//得到向量的模

	Vector GetVecE() { return (*this) / GetModulus(); };							//单位化
	Vector GetVecE(size n) { Vector vecE(Dimension); vecE.SetVect(measure(1), n); return vecE; }; //n维方向的单位向量
public:
	Vector operator = (const Vector vect);
	bool operator == (const Vector vect);
	bool operator != (const Vector vect);

	bool operator > (const Vector vect) { return (*this) * (*this) > vect * vect; };
	bool operator < (const Vector vect) { return (*this) * (*this) < vect * vect; };
	bool operator >= (const Vector vect) { return (*this) * (*this) >= vect * vect; };
	bool operator <= (const Vector vect) { return (*this) * (*this) <= vect * vect; };

	Vector operator += (const Vector vect) { return *this = *this + vect; };
	Vector operator -= (const Vector vect) { return *this = *this - vect; };
	Vector operator *= (const Vector vect) { return *this = *this * vect; };
	Vector operator /= (const Vector vect) { return *this = *this / vect; };

	Vector operator += (const measure mea) { return *this = *this + mea; };
	Vector operator -= (const measure mea) { return *this = *this - mea; };
	Vector operator *= (const measure mea) { return *this = *this * mea; };
	Vector operator /= (const measure mea) { return *this = *this / mea; };

	friend Vector operator + (const Vector& A, const Vector& B);
	friend Vector operator - (const Vector& A, const Vector& B);
	friend measure operator * (const Vector& A, const Vector& B); //内积
	friend measure operator / (const Vector& A, const Vector& B); //投影  未写

	friend Vector operator + (const measure& a, const Vector& B);
	friend Vector operator - (const measure& a, const Vector& B);
	friend Vector operator * (const measure& a, const Vector& B);
	friend Vector operator / (const measure& a, const Vector& B);

	friend Vector operator + (const Vector& A, const measure& b);
	friend Vector operator - (const Vector& A, const measure& b);
	friend Vector operator * (const Vector& A, const measure& b);
	friend Vector operator / (const Vector& A, const measure& b);
};