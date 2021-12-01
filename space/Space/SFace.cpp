#include "SFace.h"

double SFace::ABLength() {
	SLine AB(A, B);
	return AB.GetLength();
}

double SFace::BCLength() {
	SLine BC(B, C);
	return BC.GetLength();
}

double SFace::CALength() {
	SLine CA(C, A);
	return CA.GetLength();
}

double SFace::AngleA()
{
	SVector ab(A, B);
	SVector ac(A, C);
	return acos(SVector::GetCos(ab, ac));
}
double SFace::AngleB()
{
	SVector bc(B, C);
	SVector ba(B, A);
	return acos(SVector::GetCos(bc, ba));
}
double SFace::AngleC()
{
	SVector ca(C, A);
	SVector cb(C, B);
	return acos(SVector::GetCos(ca, cb));
}

double SFace::GetArea() {
	SLine edge(B, C);
	return (edge.LenLine(A) * edge.GetLength()) / 2;
}

double SFace::LenFace(SPoint point)
{
	return 0.0;
}

bool SFace::InFace(SPoint point)
{
	double AreaAll = GetArea();
	double AreaA = SFace(point, B, C).GetArea();
	double AreaB = SFace(A, point, C).GetArea();
	double AreaC = SFace(A, B, point).GetArea();
	double Area = AreaA + AreaB + AreaC;
	return (Area / AreaAll > 1 + SPRECI) ? false : true;
}

bool SFace::InFace(SLine line)
{
	if (InFace(line.star) && InFace(line.end))
		return true;
	return false;
}

bool SFace::InFace(SFace face)
{
	if (InFace(face.A) && InFace(face.B) && InFace(face.C))
		return true;
	return false;
}

//bool SFace::InFace(SCurveline Curveline)
//{
//	for (auto& line : Curveline.lines)
//		if (!InFace(line))
//			return false;
//	return true;
//}



SFace SFace::operator=(const SFace& face) {
	A = face.A;
	B = face.B;
	C = face.C;
	return face;
}



bool SFace::operator==(const SFace& face) {
	if (A == face.A && B == face.B && C == face.C)
		return true;
	return false;
}

bool SFace::operator!=(const SFace& face)
{
	return !(*this == face);
}

SFace SFace::operator+=(const SVector& vec)
{
	A += vec;
	B += vec;
	C += vec;
	return *this;
}

SFace SFace::operator-=(const SVector& vec)
{
	A -= vec;
	B -= vec;
	C -= vec;
	return *this;
}

SFace SFace::operator*=(const SMatrix& mat)
{
	A *= mat;
	B *= mat;
	C *= mat;
	return *this;
}

SFace operator+(const SFace& face, const SVector& vec)
{
	SPoint A = face.A + vec;
	SPoint B = face.B + vec;
	SPoint C = face.C + vec;
	SFace res(A, B, C);
	res.color = face.color;
	return res;
}

SFace operator-(const SFace& face, const SVector& vec)
{
	SPoint A = face.A - vec;
	SPoint B = face.B - vec;
	SPoint C = face.C - vec;
	SFace res(A, B, C);
	res.color = face.color;
	return res;
}

SFace operator*(const SFace& face, const SMatrix& mat)
{
	SPoint A = face.A * mat;
	SPoint B = face.B * mat;
	SPoint C = face.C * mat;
	SFace res(A, B, C);
	res.color = face.color;
	return res;
}

SFace operator*(const SMatrix& mat, const SFace& face)
{
	SPoint A = mat * face.A;
	SPoint B = mat * face.B;
	SPoint C = mat * face.C;
	SFace res(A, B, C);
	res.color = face.color;
	return res;
}


void SCurveface::push_back(SFace face)
{
	faces.push_back(face);
}

double SCurveface::GetArea()
{
	double Area = 0;
	for (auto& face : faces)
		Area += face.GetArea();
	return Area;
}

bool SCurveface::InCurveface(SPoint point)
{
	for (auto& face : faces)
		if (face.InFace(point))
			return true;
	return false;
}

SFace SCurveface::operator[](const int n)
{
	return faces[n];
}

SCurveface SCurveface::operator=(const SCurveface& curveface)
{
	faces = curveface.faces;
	return curveface;
}

bool SCurveface::operator==(const SCurveface& curveface)
{
	if (curveface.faces.size() != faces.size())
		return false;
	auto face1 = faces.begin();
	auto face2 = curveface.faces.begin();
	for (; face1 != faces.end(); face1++, face2++)
		if (face1 != face2)
			return false;
	return true;
}

bool SCurveface::operator!=(const SCurveface& curveface)
{
	return !(*this == curveface);
}

SCurveface SCurveface::operator+=(const SVector& vec)
{
	for (auto& face : faces)
		face += vec;
	return *this;
}

SCurveface SCurveface::operator-=(const SVector& vec)
{
	for (auto& face : faces)
		face -= vec;
	return *this;
}

SCurveface SCurveface::operator*=(const SMatrix& mat)
{
	for (auto& face : faces)
		face *= mat;
	return *this;
}
