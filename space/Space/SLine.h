#pragma once
#ifndef UNIVERSE_SPACE_SLINE
#define UNIVERSE_SPACE_SLINE
#include "Smath.h"
#include "SPoint.h"
#include "SVector.h"
class SLine {
public:
	SRGB color;
	SPoint star;
	SPoint end;
public:
	SLine(SPoint ptstar = SPoint(), SPoint ptend = SPoint()) { star = ptstar; end = ptend; };
	SLine(SPoints pts) { star = pts[0]; end = pts[1]; };
	~SLine() { };

	double GetLength();
	double AngleLine(SLine line);
	double LenLine(SPoint point);
	bool InLine(SPoint point);
	bool InLine(SLine line);
	SLine operator = (const SLine& line);
	bool operator == (const SLine& line);
	bool operator != (const SLine& line);
	SLine operator += (const SVector& vec);
	SLine operator -= (const SVector& vec);
	SLine operator *= (const SMatrix& mat);
	friend SLine operator + (const SLine& line, const SVector& vec);
	friend SLine operator - (const SLine& line, const SVector& vec);
	friend SLine operator * (const SLine& line, const SMatrix& mat);
	friend SLine operator * (const SMatrix& mat, const SLine& line);
};

typedef std::vector<SLine> SLines;
typedef SLines CurveLine;

class SCurveline {
public:
	SRGB color;
	CurveLine lines;
public:
	SCurveline() {};
	SCurveline(SLines lines);
	SCurveline(SPoints pts);
	~SCurveline() { lines.clear(); };
	void push_back(SPoint point);


	double GetLength();
	double LenCurveline(SPoint point);
	bool InCurveline(SPoint point);
	bool InCurveline(SLine line);

	SLine& operator[](const int n);
	SCurveline operator = (const SCurveline& curveline);
	bool operator == (const SCurveline& curveline);
	bool operator != (const SCurveline& curveline);
	SCurveline operator += (const SVector& vec);
	SCurveline operator -= (const SVector& vec);
	SCurveline operator *= (const SMatrix& mat);
};
#endif // !UNIVERSE_SPACE_SLINE