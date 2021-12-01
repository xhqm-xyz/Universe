
#include "SpaceBase.h"

SPoint Vect2Poit(const SVector& vec) {
	SVector ve = vec;
	return SPoint(ve[0], ve[1], ve[2]);
}

SVector Poit2Vect(const SPoint& pot){
	return SVector(pot.x, pot.y, pot.z);
}

SPoints Vects2Poits(const SVectors& vecs)
{
	SPoints points;
	for (auto &ve : vecs)
		points.push_back(Vect2Poit(ve));
	return points;
}

SVectors Poits2Vects(const SPoints& pots)
{
	SVectors vectors;
	for (auto &pt : pots)
		vectors.push_back(Poit2Vect(pt));
	return vectors;
}

SMatrix Vects2Mart(const SVectors& ves, bool lc)
{
	SMatrix mat;
	if (lc) {
		for (int i = 0; i < ves.size(); i++) {
			if (i == 3) break;
			mat.fillline(i, ves[i]);
		}
	} else {
		for (int i = 3; i < ves.size(); i++) {
			if (i == 4) break;
			mat.fillcove(i, ves[i]);
		}
	}return mat;
}

SVectors Mart2Vects(const SMatrix& mat, bool lc)
{
	SMatrix mt = mat;
	SVectors ves;
	if (lc)
		for (int i = 0; i < 3; i++)
			ves.push_back(SVector(mt[i][0], mt[i][1], mt[i][2]));
	else
		for (int i = 0; i < 3; i++)
			ves.push_back(SVector(mt[0][i], mt[1][i], mt[2][i]));
	return ves;
}



SPoints operator+(const SPoints& pots, const SVector& vec)
{
	SPoints points;
	for (auto& pot : pots)
		points.push_back(pot + vec);
	return points;
}

SPoints operator-(const SPoints& pots, const SVector& vec)
{
	SPoints points;
	for (auto& pot : pots)
		points.push_back(pot - vec);
	return points;
}

SPoints operator*(const SPoints& pots, const SVector& vec)
{
	SPoints points;
	for (auto& pot : pots)
		points.push_back(pot * vec);
	return points;
}

SLines operator+(const SLines& lines, const SVector& vec)
{
	SLines Res;
	for (auto& res : lines)
		Res.push_back(res + vec);
	return Res;
}

SFaces operator+(const SFaces& faces, const SVector& vec)
{
	SFaces Res;
	for (auto& res : faces)
		Res.push_back(res + vec);
	return Res;
}

SCubes operator+(const SCubes& cubes, const SVector& vec)
{
	SCubes Res;
	for (auto& res : cubes)
		Res.push_back(res + vec);
	return Res;
}

SLines operator-(const SLines& lines, const SVector& vec)
{
	SLines Res;
	for (auto& res : lines)
		Res.push_back(res - vec);
	return Res;
}

SFaces operator-(const SFaces& faces, const SVector& vec)
{
	SFaces Res;
	for (auto& res : faces)
		Res.push_back(res - vec);
	return Res;
}

SCubes operator-(const SCubes& cubes, const SVector& vec)
{
	SCubes Res;
	for (auto& res : cubes)
		Res.push_back(res - vec);
	return Res;
}



SPoints operator*(const SPoints& pots, const SMatrix& mat)
{
	SPoints points;
	for (auto &pot : pots)
		points.push_back(pot * mat);
	return points;
}

SPoints operator*(const SMatrix& mat, const SPoints& pots)
{
	SPoints points;
	for (auto &pot : pots)
		points.push_back(mat * pot);
	return points;
}



SLines operator*(const SLines& lines, const SMatrix& mat)
{
	SLines res;
	for (auto &line : lines)
		res.push_back(line * mat);
	return res;
}

SLines operator*(const SMatrix& mat, const SLines& lines)
{
	SLines res;
	for (auto &line : lines)
		res.push_back(mat * line);
	return res;
}



SFaces operator*(const SFaces& faces, const SMatrix& mat)
{
	SFaces res;
	for (auto& face : faces)
		res.push_back(face * mat);
	return res;
}

SFaces operator*(const SMatrix& mat, const SFaces& faces)
{	
	SFaces res;
	for (auto &face : faces)
		res.push_back(mat * face);
	return res;
}



SCubes operator*(const SCubes& cubes, const SMatrix& mat)
{
	SCubes res;
	for (auto& cube : cubes)
		res.push_back(cube * mat);
	return res;
}

SCubes operator*(const SMatrix& mat, const SCubes& cubes)
{
	SCubes res;
	for (auto& cube : cubes)
		res.push_back(mat * cube);
	return res;
}


SVectors operator*(const SVectors& vecs, const SMatrix& mat)
{
	SVectors vectors;
	for (auto &vec : vecs)
		vectors.push_back(vec * mat);
	return vectors;
}

SVectors operator*(const SMatrix& mat, const SVectors& vecs)
{
	SVectors vectors;
	for (auto &vec : vecs)
		vectors.push_back(mat * vec);
	return vectors;
}

SPoints operator+=(SPoints& pots, const SVector& vec)
{
	for (auto& pot : pots)
		pot += vec;
	return pots;
}

SLines operator+=(SLines& lines, const SVector& vec)
{
	for (auto& res : lines)
		res += vec;
	return lines;
}

SFaces operator+=(SFaces& faces, const SVector& vec)
{
	for (auto& res : faces)
		res += vec;
	return faces;
}

SCubes operator+=(SCubes& cubes, const SVector& vec)
{
	for (auto& res : cubes)
		res += vec;
	return cubes;
}

SPoints operator-=(SPoints& pots, const SVector& vec)
{
	for (auto& pot : pots)
		pot -= vec;
	return pots;
}

SLines operator-=(SLines& lines, const SVector& vec)
{
	for (auto& res : lines)
		res -= vec;
	return lines;
}

SFaces operator-=(SFaces& faces, const SVector& vec)
{
	for (auto& res : faces)
		res -= vec;
	return faces;
}

SCubes operator-=(SCubes& cubes, const SVector& vec)
{
	for (auto& res : cubes)
		res -= vec;
	return cubes;
}

SPoints operator*=(SPoints& pots, const SMatrix& mat)
{
	for (auto& pot : pots)
		pot *= mat;
	return pots;
}

SLines operator*=(SLines& lines, const SMatrix& mat)
{
	for (auto& res : lines)
		res *= mat;
	return lines;
}

SFaces operator*=(SFaces& faces, const SMatrix& mat)
{
	for (auto& res : faces)
		res *= mat;
	return faces;
}

SCubes operator*=(SCubes& cubes, const SMatrix& mat)
{
	for (auto& res : cubes)
		res *= mat;
	return cubes;
}
