#pragma once
#ifndef UNIVERSE_SPACE_SCUBE
#define UNIVERSE_SPACE_SCUBE
#include "Smath.h"
#include "SPoint.h"
#include "SLine.h"
#include "SFace.h"
class SCube
{
public:
	SRGB color;
	SPoint top[4];
public:
	SCube(SPoint top0 = SPoint(), SPoint top1 = SPoint(), SPoint top2 = SPoint(), SPoint top3 = SPoint());
	~SCube(){};

	double GetVolume();			//体积
	SCube operator = (const SCube& cube);
	bool operator == (const SCube& cube);
	bool operator != (const SCube& cube);
	SCube operator += (const SVector& vec);
	SCube operator -= (const SVector& vec);
	SCube operator *= (const SMatrix& mat);
	friend SCube operator + (const SCube& cube, const SVector& vec);//点移动
	friend SCube operator - (const SCube& cube, const SVector& vec);//点移动
	friend SCube operator * (const SCube& cube, const SMatrix& mat);
	friend SCube operator * (const SMatrix& mat, const SCube& cube);
};
typedef std::vector<SCube> SCubes;

#endif // !UNIVERSE_SPACE_SCUBE