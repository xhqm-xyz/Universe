#include "Vector.h"

Vector::Vector(nume dim) :Dimension(dim) {
	for (nume i = 0; i < Dimension; i++)
		vec.push_back(0);
}

Vector::Vector(vect meavec) :Dimension(meavec.size()) {
	for (nume i = 0; i < Dimension; i++)
		vec.push_back(meavec[i]);
}

//Vector::Vector(sure mea1) : Dimension(1) {
//	vec.push_back(mea1);
//}

Vector::Vector(sure mea1, sure mea2) : Dimension(2) {
	vec.push_back(mea1);
	vec.push_back(mea2);
}

Vector::Vector(sure mea1, sure mea2, sure mea3) :Dimension(3) {
	vec.push_back(mea1);
	vec.push_back(mea2);
	vec.push_back(mea3);
}

Vector::Vector(sure mea1, sure mea2, sure mea3, sure mea4) :Dimension(4) {
	vec.push_back(mea1);
	vec.push_back(mea2);
	vec.push_back(mea3);
	vec.push_back(mea4);
}

void Vector::Setvect(vect meavec){
	nume dim = Dimension <= meavec.size() ? Dimension : meavec.size();
	for (nume i = 0; i < dim; i++)
		vec[i] = meavec[i];
}

void Vector::SetVect(Vector vect){
	Setvect(vect.vec);
}

vect Vector::Getvect(nume n, nume m){
	vect data;
	if (n < 0)
		n = 0;
	if (m >= Dimension)
		m = Dimension - 1;
	if (m < 0)
		m = 0;
	if (n >= Dimension)
		n = Dimension - 1;
	if (n <= m)
		for (nume i = n; i <= m; i++)
			data.push_back(vec[i]);
	else
		for (nume i = n; i >= m; i--)
			data.push_back(vec[i]);
	return data;
}

Vector  Vector::GetVect(nume n, nume m){
	return Vector(Getvect(n, m));
}

sure& Vector::operator[](const nume& n){
	if (n < 0 || n >= Dimension) 
		return vec[0];
	return vec[n];
}

Vector Vector::operator=(const Vector& vect) {
	vec.clear();
	Vector Ve(vect.vec);
	Dimension = vect.Dimension;
	for (nume i = 0; i < Dimension; i++)
		vec.push_back(Ve[i]);
	return *this;
}

bite Vector::operator==(const Vector& vect) {
	Vector Ve(vect.vec);
	if (Dimension != Ve.Dimension)
		return false;
	for (nume i = 0; i < Dimension; i++)
		if(Ve.vec[i] - PRECI < vec[i] || vec[i] > Ve.vec[i] + PRECI)
			return false;
	return true;
}

bite Vector::operator!=(const Vector& vect) {
	if (*this == vect)
		return false;
	return true;
}

Vector operator+(const Vector& vect){
	Vector V(vect.vec);
	for (nume i = 0; i < V.Dimension; i++)
		V[i] = +V[i];
	return V;
}

Vector operator-(const Vector& vect){
	Vector V(vect.vec);
	for (nume i = 0; i < V.Dimension; i++)
		V[i] = -V[i];
	return V;
}

Vector operator+(const Vector& A, const Vector& B) {
	nume dimMAX = A.Dimension > B.Dimension ? A.Dimension : B.Dimension;
	nume dimMIN = A.Dimension < B.Dimension ? A.Dimension : B.Dimension;
	Vector V(dimMAX);
	Vector VA(A.vec);
	Vector VB(B.vec);
	if (A.Dimension > B.Dimension)
		for (nume i = 0; i < dimMAX; i++)
			if(i < dimMIN)
				V[i] = VA[i] + VB[i];
			else
				V[i] = VA[i] + 0;
	if (A.Dimension < B.Dimension)
		for (nume i = 0; i < dimMAX; i++)
			if (i < dimMIN)
				V[i] = VA[i] + VB[i];
			else
				V[i] = 0 + VB.vec[i];
	if (A.Dimension == B.Dimension)
		for (nume i = 0; i < dimMAX; i++)
			V[i] = VA[i] + VB[i];
	return V;
}

Vector operator-(const Vector& A, const Vector& B){
	nume dimMAX = A.Dimension > B.Dimension ? A.Dimension : B.Dimension;
	nume dimMIN = A.Dimension < B.Dimension ? A.Dimension : B.Dimension;
	Vector V(dimMAX);
	Vector VA(A.vec);
	Vector VB(B.vec);
	if (A.Dimension > B.Dimension)
		for (nume i = 0; i < dimMAX; i++)
			if(i < dimMIN)
				V[i] = VA[i] - VB[i];
			else
				V[i] = VA.vec[i] - 0;
	if (A.Dimension < B.Dimension)
		for (nume i = 0; i < dimMAX; i++)
			if (i < dimMIN)
				V[i] = VA[i] - VB[i];
			else
				V[i] = 0 - VB[i];
	if (A.Dimension == B.Dimension)
		for (nume i = 0; i < dimMAX; i++)
			V[i] = VA[i] - VB[i];
	return V;
}

sure operator*(const Vector& A, const Vector& B) {
	sure modulus = 0;
	Vector VA(A.vec);
	Vector VB(B.vec);
	nume dim = A.Dimension < B.Dimension ? A.Dimension : B.Dimension;
	for (nume i = 0; i < dim; i++)
		modulus += (VA[i] * VB[i]);
	return modulus;
}

sure operator/(const Vector& A, const Vector& B)
{
	/// <summary>
	/// /////////////////////
	/// </summary>
	/// <param name="A"></param>
	/// <param name="B"></param>
	/// <returns></returns>
	return sure(0);
}


Vector operator*(const sure& a, const Vector& B) {
	Vector VB(B.vec);
	for (nume i = 0; i < VB.Dimension; i++)
		VB[i] = a * VB[i];
	return VB;
}

Vector operator/(const sure& a, const Vector& B) {
	Vector VB(B.vec);
	for (nume i = 0; i < VB.Dimension; i++)
		VB[i] = a / VB[i];
	return VB;
}

Vector operator*(const Vector& A, const sure& b) {
	Vector VA(A.vec);
	for (nume i = 0; i < VA.Dimension; i++)
		VA[i] = VA[i] * b;
	return VA;
}

Vector operator/(const Vector& A, const sure& b) {
	Vector VA(A.vec);
	for (nume i = 0; i < VA.Dimension; i++)
		VA[i] = VA[i] / b;
	return VA;
}


//bite Vector::Setvect(vect meavec, nume n, nume m) {
//	if (n < 0 || m < 0 || n >= Dimension || m >= meavec.size())
//		return false;
//	m = meavec.size() - m;
//	for (nume i = 0; i < Dimension - n; i++)
//		if (i < m)
//			vec[n + i] = meavec[m + i];
//		else
//			vec[n + i] = 0;
//	return true;
//}