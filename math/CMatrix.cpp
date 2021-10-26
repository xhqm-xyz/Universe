#include "cmath"
#include "CMatrix.h"

void CMatrix::setnm()
{
	if (_n < 1)
		_n = 1;
	if (_n > 4)
		_n = 4;
	if (_m < 1)
		_m = 1;
	if (_m > 4)
		_m = 4;
}

void CMatrix::setnm(int& n, int& m)
{
	if (n < 1)
		n = 1;
	if (n > 4)
		n = 4;
	if (m < 1)
		m = 1;
	if (m > 4)
		m = 4;
}

void CMatrix::fill(double var)
{
	for (int i = 0; i < _n; i++)
		for (int j = 0; j < _m; j++)
			_vars[i][j] = var;
}

bool CMatrix::fillline(int n, double var)
{
	if (n < 1 || n > 4)
		return false;
	for (int j = 0; j < 4; j++)
		_vars[n][j] = var;
	return true;

}

bool CMatrix::fillcove(int m, double var)
{
	if (m < 1 || m > 4)
		return false;
	for (int i = 0; i < 4; i++)
		_vars[i][m] = var;
	return true;
}

void CMatrix::copy(CMatrix mat, int n, int m)
{
	_n = n;
	_m = m;
	setnm();
	fill(0);
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= m; j++)
			_vars[i][j] = mat._vars[i][j];
}

CMatrix CMatrix::delline(int n)
{
	CMatrix res = *this;
	if (n < 0 || n > 3)
		return res;
	else {
		for (int i = n; i < 3; i++) {
			res._vars[i][0] = _vars[i + 1][0];
			res._vars[i][1] = _vars[i + 1][1];
			res._vars[i][2] = _vars[i + 1][2];
			res._vars[i][3] = _vars[i + 1][3];
		}res._n--;
		res._vars[3][0] = 0;
		res._vars[3][1] = 0;
		res._vars[3][2] = 0;
		res._vars[3][3] = 0;
	}return res;
}
CMatrix CMatrix::delcolu(int m)
{
	CMatrix res = *this;
	if (m < 0 || m > 3)
		return res;
	else {
		for (int i = m; i < 3; i++) {
			res._vars[0][i] = _vars[0][i + 1];
			res._vars[1][i] = _vars[1][i + 1];
			res._vars[2][i] = _vars[2][i + 1];
			res._vars[3][i] = _vars[3][i + 1];
		}res._m--;
		res._vars[0][3] = 0;
		res._vars[1][3] = 0;
		res._vars[2][3] = 0;
		res._vars[3][3] = 0;
	}return res;
}

CMatrix CMatrix::dele(int n, int m)
{
	return delline(n).delcolu(m);
}

CMatrix::CMatrix(int n, int m, double var)
{
	fill(0);
	_n = n;
	_m = m;
	setnm();
	fill(var);
}



CMatrix::CMatrix(double var)
{
	fill(var);
}



double CMatrix::GetDete()
{
	if (_n != _m)
		return NULL;
	if (_n == 1)
		return _vars[0][0];
	int sig = -1;
	double mea = 0;
	CMatrix copymat;
	copymat = *this;
	for (int i = 0; i < _n; i++) {
		sig = sig * -1;
		mea += (_vars[i][0] * copymat.dele(i, 0).GetDete() * sig);
	}return mea;
}

CMatrix CMatrix::GetMatE()
{
	CMatrix E(_n, _m);
	for (int i = 0; i < 4; i++)
		E._vars[i][i] = 1;
	return E;
}

CMatrix CMatrix::GetTraMat()
{
	CMatrix T(_m, _n);
	for (int i = 0; i < _n; i++)
		for (int j = 0; j < _m; j++)
			T._vars[j][i] = _vars[i][j];
	return T;
}

CMatrix CMatrix::GetAdjMat()
{
	CMatrix A(_n, _m);
	if (_n != _m) {
		A._n = 0;
		A._m = 0;
		return A;
	}
	int sig = -1;
	CMatrix copymat;
	copymat = *this;
	for (int i = 0; i < _n; i++) 
		for (int j = 0; j < _m; j++) {
			sig = sig * -1;
			A._vars[i][j] = copymat.dele(i, j).GetDete() * sig;
		}
	return A;
}

CMatrix CMatrix::GetInvMat()
{
	CMatrix I;
	if (_n != _m) {
		I._n = 0;
		I._m = 0;
		return I;
	}
	return GetAdjMat() / GetDete();
}

CMatrix CMatrix::GetMoveX(double var)
{
	CMatrix res(4, 3);
	res = res.GetMatE();
	res[3][0] = var;
	res[3][3] = var;
	return res;
}

CMatrix CMatrix::GetMoveY(double var)
{
	CMatrix res(4, 3);
	res = res.GetMatE();
	res[3][1] = var;
	res[3][3] = var;
	return res;
}

CMatrix CMatrix::GetMoveZ(double var)
{
	CMatrix res(4, 3);
	res = res.GetMatE();
	res[3][2] = var;
	res[3][3] = var;
	return res;
}

CMatrix CMatrix::GetRotateX(double var)
{
	CMatrix res(3, 3);
	res = res.GetMatE();
	res[1][1] = cos(var);
	res[1][2] = sin(var);
	res[2][1] = -res[1][2];
	res[2][2] = res[1][1];
	return res;
}

CMatrix CMatrix::GetRotateY(double var)
{
	CMatrix res(3, 3);
	res = res.GetMatE();
	res[0][0] = cos(var);
	res[2][0] = sin(var);
	res[0][2] = -res[2][0];
	res[2][2] = res[0][0];
	return res;
}

CMatrix CMatrix::GetRotateZ(double var)
{
	CMatrix res(3, 3);
	res = res.GetMatE();
	res[0][0] = cos(var);
	res[0][1] = sin(var);
	res[1][0] = -res[0][1];
	res[1][1] = res[0][0];
	return res;
}

CMatrix CMatrix::GetFlexibleX(double var)
{
	CMatrix res(3, 3);
	res = res.GetMatE();
	res[0][0] = var;
	return res;
}

CMatrix CMatrix::GetFlexibleY(double var)
{
	CMatrix res(3, 3);
	res = res.GetMatE();
	res[1][1] = var;
	return res;
}

CMatrix CMatrix::GetFlexibleZ(double var)
{
	CMatrix res(3, 3);
	res = res.GetMatE();
	res[2][2] = var;
	return res;
}

CMatrix CMatrix::operator=(const CMatrix matrix)
{
	copy(matrix, matrix._n, matrix._m);
	return *this;
}

bool CMatrix::operator==(const CMatrix matrix)
{
	if (_n != matrix._n || _m != matrix._m)
		return false;
	for (int i = 0; i < _n; i++)
		for (int j = 0; j < _m; j++)
			if (_vars[i][j] > matrix._vars[i][j] + PRECI || _vars[i][j] < matrix._vars[i][j] - PRECI)
				return false;
	return true;
}

bool CMatrix::operator!=(const CMatrix matrix)
{
	if (*this == matrix)
		return false;
	return true;
}

CMatrix operator+(const CMatrix& A, const CMatrix& B)
{
	CMatrix add;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			add._vars[i][j] = A._vars[i][j] + B._vars[i][j];
	return add;
}

CMatrix operator-(const CMatrix& A, const CMatrix& B)
{
	CMatrix sub;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			sub._vars[i][j] = A._vars[i][j] - B._vars[i][j];
	return sub;
}

CMatrix operator*(const CMatrix& A, const CMatrix& B)
{
	CMatrix res(A._n, B._m);
	if (A._m != B._n) {
		res._n = 0;
		res._m = 0;
		return res;
	}
	for (int i = 0; i < res._n; i++)
		for (int j = 0; j < res._m; j++)
			for (int k = 0; k < res._m; k++)
				res._vars[i][j] += (A._vars[i][k] * B._vars[k][j]);
	return res;
}

CMatrix operator/(const CMatrix& A, const CMatrix& B)
{
	CMatrix C = B;
	return A * C.GetInvMat();
}

CMatrix operator+(const double& a, const CMatrix& B)
{
	CMatrix matrix = B;
	for (int i = 0; i < matrix._n; i++)
		for (int j = 0; j < matrix._m; j++)
			matrix._vars[i][j] = a + matrix._vars[i][j];
	return matrix;
}

CMatrix operator-(const double& a, const CMatrix& B)
{
	CMatrix matrix = B;
	for (int i = 0; i < matrix._n; i++)
		for (int j = 0; j < matrix._m; j++)
			matrix._vars[i][j] = a - matrix._vars[i][j];
	return matrix;
}

CMatrix operator*(const double& a, const CMatrix& B)
{
	CMatrix matrix = B;
	for (int i = 0; i < matrix._n; i++)
		for (int j = 0; j < matrix._m; j++)
			matrix._vars[i][j] = a * matrix._vars[i][j];
	return matrix;
}

CMatrix operator/(const double& a, const CMatrix& B)
{
	CMatrix matrix = B;
	for (int i = 0; i < matrix._n; i++)
		for (int j = 0; j < matrix._m; j++)
			matrix._vars[i][j] = a / matrix._vars[i][j];
	return matrix;
}

CMatrix operator+(const CMatrix& A, const double& b)
{
	CMatrix matrix = A;
	for (int i = 0; i < matrix._n; i++)
		for (int j = 0; j < matrix._m; j++)
			matrix._vars[i][j] = matrix._vars[i][j] + b;
	return matrix;
}

CMatrix operator-(const CMatrix& A, const double& b)
{
	CMatrix matrix = A;
	for (int i = 0; i < matrix._n; i++)
		for (int j = 0; j < matrix._m; j++)
			matrix._vars[i][j] = matrix._vars[i][j] - b;
	return matrix;
}

CMatrix operator*(const CMatrix& A, const double& b)
{
	CMatrix matrix = A;
	for (int i = 0; i < matrix._n; i++)
		for (int j = 0; j < matrix._m; j++)
			matrix._vars[i][j] = matrix._vars[i][j] * b;
	return matrix;
}

CMatrix operator/(const CMatrix& A, const double& b)
{
	CMatrix matrix = A;
	for (int i = 0; i < matrix._n; i++)
		for (int j = 0; j < matrix._m; j++)
			matrix._vars[i][j] = matrix._vars[i][j] / b;
	return matrix;
}

CMatrix operator^(const CMatrix& A, int n)
{
	CMatrix res = A;
	if (A._m != A._n) {
		res._n = 0;
		res._m = 0;
		return res;
	}
	CMatrix matrixE = res.GetMatE();
	CMatrix matrixI = res.GetInvMat();
	if (n > 0)
		for (int i = 0; i < n; i++)
			matrixE = matrixE * res;
	if (n < 0) {
		n = -n;
		for (int i = 0; i < n; i++)
			matrixE = matrixE * matrixI;
	}return matrixE;
}
