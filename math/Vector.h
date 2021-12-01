#pragma once
#ifndef UNIVERSE_MATH_VECTOR
#define UNIVERSE_MATH_VECTOR
#include "measure.h"

class Vector
{
protected:
	oned vec;
public:
	Vector(natu dim = 0);
	Vector(oned meavec);
	Vector(sure mea1, sure mea2);
	Vector(sure mea1, sure mea2, sure mea3);
	Vector(sure mea1, sure mea2, sure mea3, sure mea4);
	~Vector() { vec.clear(); };

	void AddDim(sure mea = 0) { vec.push_back(mea); };
	void SubDim() { vec.pop_back(); };

	natu GetDim() { return vec.size(); };
	void Setvect(oned meavec);
	void SetVect(Vector vect);
	oned Getvect(natu n, natu m);
	Vector GetVect(natu n, natu m);


	sure GetModulus() { return sqrt((*this) * (*this)); };			//�õ�������ģ
	Vector GetUnitVec();							//��λ��
	Vector GetTraVec();							//ת������
	Vector GetSubVec();							//��������

public:
	sure& operator[] (const natu& n);

	Vector operator = (const Vector& vect);
	bite operator == (const Vector& vect);
	bite operator != (const Vector& vect);

	friend Vector operator + (const Vector& vect);
	friend Vector operator - (const Vector& vect);

	friend Vector operator + (const Vector& A, const Vector& B);
	friend Vector operator - (const Vector& A, const Vector& B);
	friend sure operator * (const Vector& A, const Vector& B); //�ڻ�
	friend sure operator / (const Vector& A, const Vector& B); //ͶӰ

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