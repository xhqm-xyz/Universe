#pragma once
#ifndef UNIVERSE_SPACE_SPOINT
#define UNIVERSE_SPACE_SPOINT
#include "Smath.h"
class SVector;
class SMatrix;
class SPoint {
public:
	SRGB color;
	double x;
	double y;
	double z;
public:
	SPoint(double meax = 0, double meay = 0, double meaz = 0) { x = meax; y = meay; z = meaz; };
	~SPoint() { };

	double GetModulus();			//到原点的距离
	SPoint operator = (const SPoint& point);
	bool operator == (const SPoint& point);
	bool operator != (const SPoint& point);
	SPoint operator += (const SVector& vec);
	SPoint operator -= (const SVector& vec);
	SPoint operator *= (const SMatrix& mat);
	friend SPoint operator + (const SPoint& pot, const SVector& vec);//点移动
	friend SPoint operator - (const SPoint& pot, const SVector& vec);//点移动
	friend SPoint operator * (const SPoint& pot, const SVector& vec);//点缩放
	friend SPoint operator * (const SPoint& pot, const SMatrix& mat);
	friend SPoint operator * (const SMatrix& mat, const SPoint& pot);
};

typedef std::vector<SPoint> SPoints;
#endif // !UNIVERSE_SPACE_SPOINT