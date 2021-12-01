#include "SCube.h"

SCube::SCube(SPoint top0, SPoint top1, SPoint top2, SPoint top3) {
	top[0] = top0;
	top[1] = top1;
	top[2] = top2;
	top[3] = top3;
}

SCube SCube::operator=(const SCube& cube)
{
	top[0] = cube.top[0];
	top[1] = cube.top[1];
	top[2] = cube.top[2];
	top[3] = cube.top[3];
	return cube;
}

bool SCube::operator==(const SCube& cube)
{
	if (top[0] == cube.top[0] && top[1] == cube.top[1] && top[2] == cube.top[2] && top[3] == cube.top[3])
		return true;
	return false;
}

bool SCube::operator!=(const SCube& cube)
{
	return !(*this == cube);
}

SCube SCube::operator+=(const SVector& vec)
{
	top[0] += vec;
	top[1] += vec;
	top[2] += vec;
	top[3] += vec;
	return *this;
}

SCube SCube::operator-=(const SVector& vec)
{
	top[0] -= vec;
	top[1] -= vec;
	top[2] -= vec;
	top[3] -= vec;
	return *this;
}

SCube SCube::operator*=(const SMatrix& mat)
{
	top[0] *= mat;
	top[1] *= mat;
	top[2] *= mat;
	top[3] *= mat;
	return *this;
}

SCube operator+(const SCube& cube, const SVector& vec)
{
	SPoint res[4];
	res[0] = cube.top[0] + vec;
	res[1] = cube.top[1] + vec;
	res[2] = cube.top[2] + vec;
	res[3] = cube.top[3] + vec;
	SCube cuberes(res[0], res[1], res[2], res[3]);
	cuberes.color = cube.color;
	return cuberes;
}

SCube operator-(const SCube& cube, const SVector& vec)
{
	SPoint res[4];
	res[0] = cube.top[0] - vec;
	res[1] = cube.top[1] - vec;
	res[2] = cube.top[2] - vec;
	res[3] = cube.top[3] - vec;
	SCube cuberes(res[0], res[1], res[2], res[3]);
	cuberes.color = cube.color;
	return cuberes;
}

SCube operator*(const SCube& cube, const SMatrix& mat)
{
	SPoint res[4];
	res[0] = cube.top[0] * mat;
	res[1] = cube.top[1] * mat;
	res[2] = cube.top[2] * mat;
	res[3] = cube.top[3] * mat;
	SCube cuberes(res[0], res[1], res[2], res[3]);
	cuberes.color = cube.color;
	return cuberes;
}

SCube operator*(const SMatrix& mat, const SCube& cube)
{
	SPoint res[4];
	res[0] = mat * cube.top[0];
	res[1] = mat * cube.top[1];
	res[2] = mat * cube.top[2];
	res[3] = mat * cube.top[3];
	SCube cuberes(res[0], res[1], res[2], res[3]);
	cuberes.color = cube.color;
	return cuberes;
}