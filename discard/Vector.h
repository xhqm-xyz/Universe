#pragma once
#include "measure.h"

class Vector
{
protected:
	Data vec;
	size Dimension; //�㱻������ά�Ƚ��ɱ� ��=�� ����
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
	measure GetVect(size n) { if (n < 0 || n >= Dimension) n = 0; return vec[n]; };	//�õ���n��ά�ȵ�ֵ
	measure GetModulus() { return sqrt(((*this) * (*this)).var); };					//�õ�������ģ

	Vector GetVecE() { return (*this) / GetModulus(); };							//��λ��
	Vector GetVecE(size n) { Vector vecE(Dimension); vecE.SetVect(measure(1), n); return vecE; }; //nά����ĵ�λ����
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
	friend measure operator * (const Vector& A, const Vector& B); //�ڻ�
	friend measure operator / (const Vector& A, const Vector& B); //ͶӰ  δд

	friend Vector operator + (const measure& a, const Vector& B);
	friend Vector operator - (const measure& a, const Vector& B);
	friend Vector operator * (const measure& a, const Vector& B);
	friend Vector operator / (const measure& a, const Vector& B);

	friend Vector operator + (const Vector& A, const measure& b);
	friend Vector operator - (const Vector& A, const measure& b);
	friend Vector operator * (const Vector& A, const measure& b);
	friend Vector operator / (const Vector& A, const measure& b);
};