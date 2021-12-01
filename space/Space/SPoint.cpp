#include "SPoint.h"
#include "SVector.h"
#include "SMatrix.h"

double SPoint::GetModulus() {
	double modulus = 0;
	modulus += (x * x);
	modulus += (y * y);
	modulus += (z * z);
	return sqrt(modulus);
}

SPoint SPoint::operator=(const SPoint& point) {
	x = point.x;
	y = point.y;
	z = point.z;
	color = point.color;
	return point;
}

bool SPoint::operator==(const SPoint& point) {
	SPoint len(point.x - x, point.y - y, point.z - z);
	return len.GetModulus() <= SPRECI ? true : false;
}

bool SPoint::operator!=(const SPoint& point) {
	return !(*this == point);
}

SPoint SPoint::operator+=(const SVector& vec)
{
	SVector v = vec;
	x = x + v[0];
	y = y + v[1];
	z = z + v[2];
	return *this;
}

SPoint SPoint::operator-=(const SVector& vec)
{
	SVector v = vec;
	x = x * v[0];
	y = y * v[1];
	z = z * v[2];
	return *this;
}

SPoint SPoint::operator*=(const SMatrix& mat)
{
	SMatrix m = mat;
	x = x * m[0][0] + y * m[1][0] + z * m[2][0];
	y = x * m[0][1] + y * m[1][1] + z * m[2][1];
	z = x * m[0][2] + y * m[1][2] + z * m[2][2];
	return *this;
	return SPoint();
}

SPoint operator+(const SPoint& pot, const SVector& vec)
{
	SVector ve = vec;
	SPoint res(pot.x + ve[0], pot.y + ve[1], pot.z + ve[2]);
	res.color = pot.color;
	return res;
}

SPoint operator-(const SPoint& pot, const SVector& vec)
{
	SVector ve = vec;
	SPoint res(pot.x - ve[0], pot.y - ve[1], pot.z - ve[2]);
	res.color = pot.color;
	return res;
}

SPoint operator*(const SPoint& pot, const SVector& vec)
{
	SVector ve = vec;
	SPoint res(pot.x * ve[0], pot.y * ve[1], pot.z * ve[2]);
	res.color = pot.color;
	return res;
}

SPoint operator*(const SPoint& pot, const SMatrix& mat)
{
	SVector res(pot.x, pot.y, pot.z);
	SPoint pt = (res * mat).ToPoint();
	pt.color = pot.color;
	return pt;
}

SPoint operator*(const SMatrix& mat, const SPoint& pot)
{
	SVector res(pot.x, pot.y, pot.z);
	SPoint pt = (mat * res).ToPoint();
	pt.color = pot.color;
	return pt;
}