#pragma once
#ifndef UNIVERSE_MATH_POINT
#define UNIVERSE_MATH_POINT
#include "measure.h"

class Point
{
protected:
	oned _pt;
public:
	Point(natu dim = 0);
	Point(oned meavec);
	Point(sure mea1, sure mea2);
	Point(sure mea1, sure mea2, sure mea3);
	Point(sure mea1, sure mea2, sure mea3, sure mea4);
	~Point() { };

	natu GetDim() { return _pt.size(); };
	oned GetData() { return _pt; };

	sure GetModulus();			//到原点的距离

public:
	sure& operator[] (const natu& n);

	Point operator = (const Point& point);
	bite operator == (const Point& point);
	bite operator != (const Point& point);

	friend Point operator + (const Point& A, const Point& B);
	friend Point operator - (const Point& A, const Point& B);

	friend Point operator + (const sure& a, const Point& B);
	friend Point operator - (const sure& a, const Point& B);
	friend Point operator * (const sure& a, const Point& B);
	friend Point operator / (const sure& a, const Point& B);
	friend Point operator + (const Point& A, const sure& b);
	friend Point operator - (const Point& A, const sure& b);
	friend Point operator * (const Point& A, const sure& b);
	friend Point operator / (const Point& A, const sure& b);

	Point operator += (const Point& point) { return *this = *this + point; };
	Point operator -= (const Point& point) { return *this = *this - point; };
	Point operator *= (const sure& mea) { return *this = *this * mea; };
	Point operator /= (const sure& mea) { return *this = *this / mea; };
};

#endif // !UNIVERSE_MATH_POINT