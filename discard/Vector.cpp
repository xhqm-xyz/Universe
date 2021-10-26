#include "Vector.h"

Vector::Vector(size dim) :Dimension(dim) {
	for (size i = 0; i < Dimension; i++)
		vec.push_back(0);
}

Vector::Vector(Data meavec) :Dimension(meavec.size()) {
	vec = meavec;
/*	for (size i = 0; i < Dimension; i++)
		vec.push_back(meavec[i]);*/
}

Vector::Vector(measure mea1) : Dimension(1) {
	vec.push_back(mea1);
}

Vector::Vector(measure mea1, measure mea2) : Dimension(2) {
	vec.push_back(mea1);
	vec.push_back(mea2);
}

Vector::Vector(measure mea1, measure mea2, measure mea3) :Dimension(3) {
	vec.push_back(mea1);
	vec.push_back(mea2);
	vec.push_back(mea3);
}

Vector::Vector(measure mea1, measure mea2, measure mea3, measure mea4) :Dimension(4) {
	vec.push_back(mea1);
	vec.push_back(mea2);
	vec.push_back(mea3);
	vec.push_back(mea4);
}

Vector::~Vector() {
	vec.clear();
}

void Vector::SetVect(Vector vect) {
	int dim = Dimension <= vect.Dimension ? Dimension : vect.Dimension;
	for (size i = 0; i < dim; i++)
		vec[i] = vect.vec[i];
}

void Vector::SetVect(measure mea) {
	for (size i = 0; i < Dimension; i++)
		vec[i] = mea;
}

bool Vector::SetVect(measure mea, size n) {
	if (n < 0 || n >= Dimension)
		return false;
	vec[n] = mea;
	return true;
}

bool Vector::SetVect(Data meavec, size n, size m){
	if (n < 0 || m < 0 || n >= Dimension || m >= meavec.size())
		return false;
	m = meavec.size() - m;
	for (size i = 0; i < Dimension - n; i++)
		if (i < m)
			vec[n + i] = meavec[m + i];
		else
			vec[n + i] = 0;
	return true;
}

Data Vector::GetAngle(){
	Data ang(Dimension);
	for (size i = 0; i < Dimension; i++)
		ang[i] = GetAngle(GetVecE(i));
	return Data();
}

Vector Vector::operator=(const Vector vect) {
	vec.clear();
	Dimension = vect.Dimension;
	for (size i = 0; i < Dimension; i++)
		vec.push_back(vect.vec[i]);
	return *this;
}

bool Vector::operator==(const Vector vect) {
	if (Dimension != vect.Dimension)
		return false;
	for (size i = 0; i < Dimension; i++)
		if (vec[i] != vect.vec[i])
			return false;
	return true;
}

bool Vector::operator!=(const Vector vect) {
	if (*this == vect)
		return false;
	return true;
}

Vector operator+(const Vector& A, const Vector& B) {
	Data V;
	size dimMAX = A.Dimension > B.Dimension ? A.Dimension : B.Dimension;
	size dimMIN = A.Dimension < B.Dimension ? A.Dimension : B.Dimension;
	size dim = dimMAX;
	
	if (A.Dimension > B.Dimension)
		for (size i = 0; i < dimMAX; i++)
			if(i < dimMIN)
				V.push_back(A.vec[i] + B.vec[i]);
			else
				V.push_back(A.vec[i] + measure(0));
	if (A.Dimension < B.Dimension)
		for (size i = 0; i < dimMAX; i++)
			if (i < dimMIN)
				V.push_back(A.vec[i] + B.vec[i]);
			else
				V.push_back(measure(0) + B.vec[i]);
	if (A.Dimension == B.Dimension)
		for (size i = 0; i < dim; i++)
			V.push_back(A.vec[i] + B.vec[i]);
	Vector C(dim);
	C.SetVect(V);
	return C;
}

Vector operator-(const Vector& A, const Vector& B){
	Data V;
	size dimMAX = A.Dimension > B.Dimension ? A.Dimension : B.Dimension;
	size dimMIN = A.Dimension < B.Dimension ? A.Dimension : B.Dimension;
	size dim = dimMAX;

	if (A.Dimension > B.Dimension)
		for (size i = 0; i < dimMAX; i++)
			if (i < dimMIN)
				V.push_back(A.vec[i] - B.vec[i]);
			else
				V.push_back(A.vec[i] - measure(0));
	if (A.Dimension < B.Dimension)
		for (size i = 0; i < dimMAX; i++)
			if (i < dimMIN)
				V.push_back(A.vec[i] - B.vec[i]);
			else
				V.push_back(measure(0) - B.vec[i]);
	if (A.Dimension == B.Dimension)
		for (size i = 0; i < dim; i++)
			V.push_back(A.vec[i] - B.vec[i]);
	Vector C(dim);
	C.SetVect(V);
	return C;
}

measure operator*(const Vector& A, const Vector& B) {
	measure modulus;
	size dim = A.Dimension < B.Dimension ? A.Dimension : B.Dimension;
	for (size i = 0; i < dim; i++)
		modulus += (A.vec[i] * B.vec[i]);
	return modulus;
}

measure operator/(const Vector& A, const Vector& B)
{
	return measure();
}

Vector operator+(const measure& a, const Vector& B){
	Vector C(B.Dimension);
	for (size i = 0; i < B.Dimension; i++)
		C.vec[i] = (a + B.vec[i]);
	return C;
}

Vector operator-(const measure& a, const Vector& B){
	Vector C(B.Dimension);
	for (size i = 0; i < B.Dimension; i++)
		C.vec[i] = (a - B.vec[i]);
	return C;
}

Vector operator*(const measure& a, const Vector& B) {
	Vector C(B.Dimension);
	for (size i = 0; i < B.Dimension; i++)
		C.vec[i] = (a * B.vec[i]);
	return C;
}

Vector operator/(const measure& a, const Vector& B) {
	Vector C(B.Dimension);
	for (size i = 0; i < B.Dimension; i++)
		C.vec[i] = (a / B.vec[i]);
	return C;
}

Vector operator+(const Vector& A, const measure& b){
	Vector C(A.Dimension);
	for (size i = 0; i < A.Dimension; i++)
		C.vec[i] = (A.vec[i] + b);
	return C;
}

Vector operator-(const Vector& A, const measure& b){
	Vector C(A.Dimension);
	for (size i = 0; i < A.Dimension; i++)
		C.vec[i] = (A.vec[i] - b);
	return C;
}

Vector operator*(const Vector& A, const measure& b) {
	Vector C(A.Dimension);
	for (size i = 0; i < A.Dimension; i++)
		C.vec[i] = (A.vec[i] * b);
	return C;
}

Vector operator/(const Vector& A, const measure& b) {
	if (A.Dimension == 0)
		return Vector();
	Vector C(A.Dimension);
	for (size i = 0; i < A.Dimension; i++)
		C.vec[i] = (A.vec[i] / b);
	return C;
}
