#pragma once
#ifndef UNIVERSE_SPACE_SFACE
#define UNIVERSE_SPACE_SFACE
#include "Smath.h"
#include "SPoint.h"
#include "SLine.h"
#include "SVector.h"

class SFace {
public:
	SRGB color;
	SPoint A;
	SPoint B;
	SPoint C;
public:
	SFace(SPoint ptA = SPoint(), SPoint ptB = SPoint(), SPoint ptC = SPoint()) { A = ptA; B = ptB; C = ptC; };
	SFace(SPoints pts) { A = pts[0]; B = pts[1]; C = pts[2]; };
	~SFace() { };

	double ABLength();
	double BCLength();
	double CALength();
	double AngleA();
	double AngleB();
	double AngleC();
	double GetArea();
	double LenFace(SPoint point);
	bool InFace(SPoint point);
	bool InFace(SLine line);
	bool InFace(SFace face);
	//bool InFace(SCurveline Curveline);
	SFace operator = (const SFace& face);
	bool operator == (const SFace& face);
	bool operator != (const SFace& face);
	SFace operator += (const SVector& vec);
	SFace operator -= (const SVector& vec);
	SFace operator *= (const SMatrix& mat);
	friend SFace operator + (const SFace& face, const SVector& vec);
	friend SFace operator - (const SFace& face, const SVector& vec);
	friend SFace operator * (const SFace& face, const SMatrix& mat);
	friend SFace operator * (const SMatrix& mat, const SFace& face);
};

typedef std::vector<SFace> SFaces;
typedef SFaces CurveFace;

class SCurveface {

public:
	SRGB color;
	CurveFace faces;
public:
	SCurveface() {};
	~SCurveface() { faces.clear(); };
	void push_back(SFace face);


	double GetArea();
	double LenCurve(SPoint point);
	bool InCurveface(SPoint point);


	SFace operator[](const int n);
	SCurveface operator = (const SCurveface& curveface);
	bool operator == (const SCurveface& curveface);
	bool operator != (const SCurveface& curveface);
	SCurveface operator += (const SVector& vec);
	SCurveface operator -= (const SVector& vec);
	SCurveface operator *= (const SMatrix& mat);
};
#endif // !UNIVERSE_SPACE_SFACE