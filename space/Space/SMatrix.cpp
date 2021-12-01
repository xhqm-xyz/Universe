#include "cmath"
#include "SMatrix.h"

void SMatrix::copy(SMatrix res, int n, int m)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			_vars[i][j] = res[i][j];
}

void SMatrix::fill(double var, int n, int m)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			_vars[i][j] = var;
}

bool SMatrix::fillline(int n, SVector vet)
{
	if (n < 0 || n > 2)
		return false;
	for (int j = 0; j < 3; j++)
		_vars[n][j] = vet[j];
	return true;
}

bool SMatrix::fillcove(int m, SVector vet)
{
	if (m < 0 || m > 2)
		return false;
	for (int i = 0; i < 3; i++)
		_vars[i][m] = vet[i];
	return true;
}

SMatrix SMatrix::delline(int n)
{
	SMatrix res = *this;
	if (n < 0 || n > 2)
		return res;
	else {
		for (int i = n; i < 2; i++) {
			res._vars[i][0] = _vars[i + 1][0];
			res._vars[i][1] = _vars[i + 1][1];
			res._vars[i][2] = _vars[i + 1][2];
		}
		res._vars[2][0] = 0;
		res._vars[2][1] = 0;
		res._vars[2][2] = 0;
	}return res;
}
SMatrix SMatrix::delcolu(int m)
{
	SMatrix res = *this;
	if (m < 0 || m > 2)
		return res;
	else {
		for (int i = m; i < 2; i++) {
			res._vars[0][i] = _vars[0][i + 1];
			res._vars[1][i] = _vars[1][i + 1];
			res._vars[2][i] = _vars[2][i + 1];
		}
		res._vars[0][2] = 0;
		res._vars[1][2] = 0;
		res._vars[2][2] = 0;
	}return res;
}

SMatrix SMatrix::dele(int n, int m)
{
	return delline(n).delcolu(m);
}

SMatrix::SMatrix(double var)
{
	fill(var, 3, 3);
}



double SMatrix::GetDete(int n)
{
	if (n == 1)
		return _vars[0][0];
	int sig = -1;
	double mea = 0;
	SMatrix copymat;
	copymat.copy(*this, n, n);
	for (int i = 0; i < n; i++) {
		sig = sig * -1;
		mea += (_vars[i][0] * copymat.dele(i, 0).GetDete(n - 1) * sig);
	}return mea;
}

SMatrix SMatrix::GetMatE()
{
	SMatrix E;
	for (int i = 0; i < 3; i++)
		E._vars[i][i] = 1;
	return E;
}

SMatrix SMatrix::GetInvMat(int n)
{
	return GetAdjMat(n) / GetDete(n);
}

SMatrix SMatrix::GetTraMat(int n)
{
	SMatrix T;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			T._vars[j][i] = _vars[i][j];
	return T;
}

SMatrix SMatrix::GetAdjMat(int n)
{
	SMatrix A;
	int sig = -1;
	SMatrix copymat;
	copymat.copy(*this, n, n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			sig = sig * -1;
			A._vars[i][j] = copymat.dele(i, j).GetDete(n - 1) * sig;
		}
	return A;
}

SMatrix SMatrix::GetMove(double varX, double varY, double varZ)
{
	SMatrix res;
	res = res.GetMatE();
	for (int i = 0; i < 3; i++) {
		res[0][i] = varX;
		res[1][i] = varY;
		res[2][i] = varZ;
	}
	return res;
}

SMatrix SMatrix::GetFlexible(double varX, double varY, double varZ)
{
	SMatrix res;
	res = res.GetMatE();
	res[0][0] = varX;
	res[1][1] = varY;
	res[2][2] = varZ;
	return res;
}

SMatrix SMatrix::GetRotateX(double var)
{
	SMatrix res;
	res = res.GetMatE();
	res[1][1] = cos(var);
	res[1][2] = sin(var);
	res[2][1] = -res[1][2];
	res[2][2] = res[1][1];
	return res;
}

SMatrix SMatrix::GetRotateY(double var)
{
	SMatrix res;
	res = res.GetMatE();
	res[0][0] = cos(var);
	res[2][0] = sin(var);
	res[0][2] = -res[2][0];
	res[2][2] = res[0][0];
	return res;
}

SMatrix SMatrix::GetRotateZ(double var)
{
	SMatrix res;
	res = res.GetMatE();
	res[0][0] = cos(var);
	res[0][1] = sin(var);
	res[1][0] = -res[0][1];
	res[1][1] = res[0][0];
	return res;
}

SMatrix SMatrix::operator=(const SMatrix matrix)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			_vars[i][j] = matrix._vars[i][j];
	return matrix;
}

SMatrix operator+(const SMatrix& A, const SMatrix& B)
{
	SMatrix add;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			add._vars[i][j] = A._vars[i][j] + B._vars[i][j];
	return add;
}

SMatrix operator-(const SMatrix& A, const SMatrix& B)
{
	SMatrix sub;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			sub._vars[i][j] = A._vars[i][j] - B._vars[i][j];
	return sub;
}

SMatrix operator*(const SMatrix& A, const SMatrix& B)
{
	SMatrix res;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				res._vars[i][j] += (A._vars[i][k] * B._vars[k][j]);
	return res;
}

SMatrix operator/(const SMatrix& A, const SMatrix& B)
{
	SMatrix C = B;
	return A * C.GetInvMat();
}

SMatrix operator+(const double& a, const SMatrix& B)
{
	SMatrix matrix = B;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			matrix._vars[i][j] = a + matrix._vars[i][j];
	return matrix;
}

SMatrix operator-(const double& a, const SMatrix& B)
{
	SMatrix matrix = B;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			matrix._vars[i][j] = a - matrix._vars[i][j];
	return matrix;
}

SMatrix operator*(const double& a, const SMatrix& B)
{
	SMatrix matrix = B;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			matrix._vars[i][j] = a * matrix._vars[i][j];
	return matrix;
}

SMatrix operator/(const double& a, const SMatrix& B)
{
	SMatrix matrix = B;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			matrix._vars[i][j] = a / matrix._vars[i][j];
	return matrix;
}

SMatrix operator+(const SMatrix& A, const double& b)
{
	SMatrix matrix = A;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			matrix._vars[i][j] = matrix._vars[i][j] + b;
	return matrix;
}

SMatrix operator-(const SMatrix& A, const double& b)
{
	SMatrix matrix = A;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			matrix._vars[i][j] = matrix._vars[i][j] - b;
	return matrix;
}

SMatrix operator*(const SMatrix& A, const double& b)
{
	SMatrix matrix = A;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			matrix._vars[i][j] = matrix._vars[i][j] * b;
	return matrix;
}

SMatrix operator/(const SMatrix& A, const double& b)
{
	SMatrix matrix = A;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			matrix._vars[i][j] = matrix._vars[i][j] / b;
	return matrix;
}

SMatrix operator^(const SMatrix& A, int n)
{
	SMatrix res = A;
	SMatrix matrixE = res.GetMatE();
	SMatrix matrixI = res.GetInvMat();
	if (n > 0)
		for (int i = 0; i < n; i++)
			matrixE = matrixE * res;
	if (n < 0) {
		n = -n;
		for (int i = 0; i < n; i++)
			matrixE = matrixE * matrixI;
	}return matrixE;
}

SVector operator*(SVector A, const SMatrix& B)
{
	double mea[3] = { 0,0,0 };
	mea[0] = A[0] * B._vars[0][0] + A[1] * B._vars[1][0] + A[2] * B._vars[2][0];
	mea[1] = A[0] * B._vars[0][1] + A[1] * B._vars[1][1] + A[2] * B._vars[2][1];
	mea[2] = A[0] * B._vars[0][2] + A[1] * B._vars[1][2] + A[2] * B._vars[2][2];
	return SVector(mea[0], mea[1], mea[2]);
}

SVector operator*(const SMatrix& A, SVector B)
{
	double mea[3] = { 0,0,0 };
	mea[0] = A._vars[0][0] * B[0] + A._vars[0][1] * B[1] + A._vars[0][2] * B[2];
	mea[1] = A._vars[1][0] * B[0] + A._vars[1][1] * B[1] + A._vars[1][2] * B[2];
	mea[2] = A._vars[2][0] * B[0] + A._vars[2][1] * B[1] + A._vars[2][2] * B[2];
	return SVector(mea[0], mea[1], mea[2]);
}
