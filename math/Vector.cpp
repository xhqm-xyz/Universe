#include "Vector.h"

Vector::Vector(natu dim) {
	for (natu i = 0; i < dim; i++)
		vec.push_back(0);
}

Vector::Vector(oned meavec) {
	for (auto mea : meavec)
		vec.push_back(mea);
}


Vector::Vector(sure mea1, sure mea2) {
	vec.push_back(mea1);
	vec.push_back(mea2);
}

Vector::Vector(sure mea1, sure mea2, sure mea3) {
	vec.push_back(mea1);
	vec.push_back(mea2);
	vec.push_back(mea3);
}

Vector::Vector(sure mea1, sure mea2, sure mea3, sure mea4) {
	vec.push_back(mea1);
	vec.push_back(mea2);
	vec.push_back(mea3);
	vec.push_back(mea4);
}

void Vector::Setvect(oned meavec){
	natu dim = vec.size();
	vec.clear();
	for (auto mea : meavec) {
		vec.push_back(mea);
		if (0 == dim--)
			break;
	}
}

void Vector::SetVect(Vector vect){
	Setvect(vect.vec);
}

oned Vector::Getvect(natu n, natu m){
	oned data;
	if (n < 0)
		n = 0;
	if (m >= vec.size())
		m = vec.size() - 1;
	if (m < 0)
		m = 0;
	if (n >= vec.size())
		n = vec.size() - 1;
	if (n <= m)
		for (natu i = n; i <= m; i++)
			data.push_back(vec[i]);
	else
		for (natu i = n; i >= m; i--)
			data.push_back(vec[i]);
	return data;
}

Vector  Vector::GetVect(natu n, natu m){
	return Vector(Getvect(n, m));
}

Vector Vector::GetUnitVec()
{
	Vector Unit;
	Unit = *this / GetModulus();
	return Unit;
}

Vector Vector::GetTraVec()
{
	Vector Tra(vec.size());
	auto tra = Tra.vec.end();
	for (auto it = vec.begin(); it != vec.end(); it++)
		*(--tra) = *it;
	return Tra;
}

Vector Vector::GetSubVec()
{
	Vector Sub;
	for (auto mea : vec)
		Sub.vec.push_back(-mea);
	return Sub;
}

sure& Vector::operator[](const natu& n){
	return vec[n];
}

Vector Vector::operator=(const Vector& vect) {
	vec.clear();
	for (auto mea : vect.vec)
		vec.push_back(mea);
	return *this;
}

bite Vector::operator==(const Vector& vect) {
	if (vec.size() != vect.vec.size())
		return false;
	Vector V = vect;
	for (auto it = (vec.begin()), vit = (V.vec.begin()); (it != vec.end() && vit != vect.vec.end()); it++, vit++)
		//if (*it - *vit <= XH_PRECI || *vit - *it <= XH_PRECI)
		if(XEqualDouble(*it, *vit))
			return false;
	return true;
}

bite Vector::operator!=(const Vector& vect) {
	return !(*this == vect);
}

Vector operator+(const Vector& vect){
	Vector V;
	for (auto mea : vect.vec)
		V.vec.push_back(+mea);
	return V;
}

Vector operator-(const Vector& vect){
	Vector V;
	for (auto mea : vect.vec)
		V.vec.push_back(-mea);
	return V;
}

Vector operator+(const Vector& A, const Vector& B) {
	Vector Vres;
	for (auto ait = A.vec.begin(), bit = B.vec.begin(); (ait != A.vec.end() && bit != B.vec.end()); ait++, bit++)
		Vres.vec.push_back(*ait + *bit);
	return Vres;
}

Vector operator-(const Vector& A, const Vector& B){
	Vector Vres;
	for (auto ait = A.vec.begin(), bit = B.vec.begin(); (ait != A.vec.end() && bit != B.vec.end()); ait++, bit++)
		Vres.vec.push_back(*ait - *bit);
	return Vres;
}

sure operator*(const Vector& A, const Vector& B) {
	sure modulus = 0;
	for (auto ait = A.vec.begin(), bit = B.vec.begin(); (ait != A.vec.end() && bit != B.vec.end()); ait++, bit++)
		modulus += (*ait * *bit);
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
	Vector Vres;
	for (auto mea : B.vec)
		Vres.vec.push_back(a * mea);
	return Vres;
}

Vector operator/(const sure& a, const Vector& B) {
	Vector Vres;
	for (auto mea : B.vec)
		Vres.vec.push_back(a / mea);
	return Vres;
}

Vector operator*(const Vector& A, const sure& b) {
	Vector Vres;
	for (auto mea : A.vec)
		Vres.vec.push_back(mea * b);
	return Vres;
}

Vector operator/(const Vector& A, const sure& b) {
	Vector Vres;
	for (auto mea : A.vec)
		Vres.vec.push_back(mea / b);
	return Vres;
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