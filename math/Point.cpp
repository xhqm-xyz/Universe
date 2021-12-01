#include "Point.h"

Point::Point(natu dim) {
	for (natu i = 0; i < dim; i++)
		_pt.push_back(0);
}

Point::Point(oned meavec) {
	for (auto mea : meavec)
		_pt.push_back(mea);
}

Point::Point(sure mea1, sure mea2) {
	_pt.push_back(mea1);
	_pt.push_back(mea2);
}

Point::Point(sure mea1, sure mea2, sure mea3){
	_pt.push_back(mea1);
	_pt.push_back(mea2);
	_pt.push_back(mea3);
}

Point::Point(sure mea1, sure mea2, sure mea3, sure mea4) {
	_pt.push_back(mea1);
	_pt.push_back(mea2);
	_pt.push_back(mea3);
	_pt.push_back(mea4);
}

sure Point::GetModulus(){
	sure modulus = 0;
	for (auto mea : _pt)
		modulus += (mea * mea);
	return sqrt(modulus);
}

sure& Point::operator[](const natu& n) {
	return _pt[n];
}

Point Point::operator=(const Point& point) {
	_pt.clear();
	for (auto mea : point._pt)
		_pt.push_back(mea);
	return *this;
}

bite Point::operator==(const Point& point) {
	if (_pt.size() != point._pt.size())
		return false;
	Point Pt = point;
	for (auto it = (_pt.begin()), pit = (Pt._pt.begin()); (it != _pt.end() && pit != point._pt.end()); it++, pit++)
		if (*it - *pit <= XPRECI || *pit - *it <= XPRECI)
			return false;
	return true;
}

bite Point::operator!=(const Point& point) {
	return !(*this == point);
}

Point operator+(const Point& A, const Point& B) {
	Point Pres;
	for (auto ait = A._pt.begin(), bit = B._pt.begin(); (ait != A._pt.end() && bit != B._pt.end()); ait++, bit++)
		Pres._pt.push_back(*ait + *bit);
	return Pres;
}

Point operator-(const Point& A, const Point& B) {
	Point Pres;
	for (auto ait = A._pt.begin(), bit = B._pt.begin(); (ait != A._pt.end() && bit != B._pt.end()); ait++, bit++)
		Pres._pt.push_back(*ait - *bit);
	return Pres;
}

Point operator+(const sure& a, const Point& B){
	Point Pres;
	for (auto mea : B._pt)
		Pres._pt.push_back(a + mea);
	return Pres;
}

Point operator-(const sure& a, const Point& B){
	Point Pres;
	for (auto mea : B._pt)
		Pres._pt.push_back(a - mea);
	return Pres;
}


Point operator*(const sure& a, const Point& B) {
	Point Pres;
	for (auto mea : B._pt)
		Pres._pt.push_back(a * mea);
	return Pres;
}

Point operator/(const sure& a, const Point& B) {
	Point Pres;
	for (auto mea : B._pt)
		Pres._pt.push_back(a / mea);
	return Pres;
}

Point operator+(const Point& A, const sure& b){
	Point Pres;
	for (auto mea : A._pt)
		Pres._pt.push_back(mea + b);
	return Pres;
}

Point operator-(const Point& A, const sure& b){
	Point Pres;
	for (auto mea : A._pt)
		Pres._pt.push_back(mea - b);
	return Pres;
}

Point operator*(const Point& A, const sure& b) {
	Point Pres;
	for (auto mea : A._pt)
		Pres._pt.push_back(mea * b);
	return Pres;
}

Point operator/(const Point& A, const sure& b) {
	Point Pres;
	for (auto mea : A._pt)
		Pres._pt.push_back(mea / b);
	return Pres;
}