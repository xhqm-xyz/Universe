#pragma once
#ifndef UNIVERSE_SPACE
#define UNIVERSE_SPACE
#include "Space/Smath.h"
#include "Space/SPoint.h"
#include "Space/SLine.h"
#include "Space/SFace.h"
#include "Space/SCube.h"
#include "Space/SVector.h"
#include "Space/SMatrix.h"

class Sid {
	long long id = 0;
public:
	Sid() { id = (long long)this; }
	Sid(Sid &sid) { id = (long long)this; }
	long long Getid() { return id; }
};

SPoint Vect2Poit(const SVector& vec);
SVector Poit2Vect(const SPoint& pot);
SPoints Vects2Poits(const SVectors& vecs);
SVectors Poits2Vects(const SPoints& pots);
SMatrix Vects2Mart(const SVectors& ves, bool lc = true);//true 行向量 false 列向量
SVectors Mart2Vects(const SMatrix& mat, bool lc = true);//true 行向量 false 列向量

SPoints operator * (const SPoints& pots, const SVector& vec);

SPoints operator + (const SPoints& pots, const SVector& vec);
SPoints operator - (const SPoints& pots, const SVector& vec);
SLines operator + (const SLines& lines, const SVector& vec);
SFaces operator + (const SFaces& faces, const SVector& vec);
SCubes operator + (const SCubes& cubes, const SVector& vec);
SLines operator - (const SLines& lines, const SVector& vec);
SFaces operator - (const SFaces& faces, const SVector& vec);
SCubes operator - (const SCubes& cubes, const SVector& vec);

SPoints operator * (const SPoints& pots, const SMatrix& mat);
SPoints operator * (const SMatrix& mat, const SPoints& pots);
SLines operator * (const SLines& lines, const SMatrix& mat);
SLines operator * (const SMatrix& mat, const SLines& lines);
SFaces operator * (const SFaces& faces, const SMatrix& mat);
SFaces operator * (const SMatrix& mat, const SFaces& faces);
SCubes operator * (const SCubes& cubes, const SMatrix& mat);
SCubes operator * (const SMatrix& mat, const SCubes& cubes);
SVectors operator * (const SVectors& vecs, const SMatrix& mat);
SVectors operator * (const SMatrix& mat, const SVectors& vecs);

SPoints operator += (SPoints& pots, const SVector& vec);
SLines  operator += (SLines& lines, const SVector& vec);
SFaces  operator += (SFaces& faces, const SVector& vec);
SCubes  operator += (SCubes& cubes, const SVector& vec);
SPoints operator -= (SPoints& pots, const SVector& vec);
SLines  operator -= (SLines& lines, const SVector& vec);
SFaces  operator -= (SFaces& faces, const SVector& vec);
SCubes  operator -= (SCubes& cubes, const SVector& vec);

SPoints operator *= (SPoints& pots, const SMatrix& mat);
SLines  operator *= (SLines& lines, const SMatrix& mat);
SFaces  operator *= (SFaces& faces, const SMatrix& mat);
SCubes  operator *= (SCubes& cubes, const SMatrix& mat);
#endif // !UNIVERSE_SPACE