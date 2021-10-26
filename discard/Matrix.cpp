#include "Matrix.h"

Matrix::Matrix(Dete matrix) :Dn(matrix.size()), Dm(matrix[0].size()) {
	mat = matrix;
	/*	for (size i = 0; i < Dn; i++)
			mat.push_back(matrix[i]); */
}

Matrix::Matrix(Line matrix) :Dn(matrix.size()), Dm(1) {
	for (size i = 0; i < Dn; i++) {
		mat.push_back(Line());
		mat[0].push_back(matrix[i]);
	}
}

Matrix::Matrix(Vector matrix) : Dn(matrix.GetSize()), Dm(1) {
	Line dat = matrix.GetVect();
	for (size i = 0; i < Dn; i++) {
		mat.push_back(Line());
		mat[0].push_back(dat[i]);
	}
}

Matrix::Matrix(size dn, size dm) :Dn(dn), Dm(dm) {
	Line dat;
	for (size j = 0; j < Dm; j++)
		dat.push_back(0);
	for (size i = 0; i < Dn; i++)
		mat.push_back(dat);
}

void Matrix::SetMatrix(Dete dete){
	size nmin = dete.size() < Dn ? dete.size() : Dn;
	size mmin = dete.size() < Dm ? dete.size() : Dm;
	for (size i = 0; i < nmin; i++)
		for (size j = 0; j < mmin; j++)
			mat[i][j] = dete[i][j];
}

void Matrix::SetMatrix(complex mea){
	for (size i = 0; i < Dn; i++)
		for (size j = 0; j < Dm; j++)
			mat[j][i] = mea;
}

bool Matrix::SetMatrixLine(Line data, size dn){
	if (data.size() != Dm)
		return false;
	for (size j = 0; j < Dm; j++)
		mat[dn][j] = data[j];
	return true;
}

bool Matrix::SetMatrixColu(Line data, size dm){
	if (data.size() != Dn)
		return false;
	for (size i = 0; i < Dn; i++)
			mat[i][dm] = data[i];
	return true;
}

bool Matrix::SetMatrixLine(Vector vec, size dn){
	return SetMatrixLine(vec.GetVect(), dn);
}

bool Matrix::SetMatrixColu(Vector vec, size dm){
	return SetMatrixColu(vec.GetVect(), dm);
}

Vector Matrix::GetLineVector(size dn){
	return mat[dn];
}

Vector Matrix::GetColuVector(size dm){
	Vector colu(Dn);
	for (size i = 0; i < Dn; i++)
		colu.SetVect(mat[i], dm);
	return colu;
}

complex Matrix::GetDete(){
	if (Dn != Dm)
		return NULL;
	if (Dn == 1)
		return mat[0][0];
	complex mea;
	integer sig = -1;
	for (size i = 0; i < Dn; i++)
		mea += (mat[i][0] * Matdellc(i, 0).GetDete() * (sig *= -1));
	return mea;
}

Matrix Matrix::GetTraMat(){
	Matrix matrix(Dm, Dn);
	for (size i = 0; i < Dn; i++)
		for (size j = 0; j < Dm; j++)
			matrix.mat[j][i] = mat[i][j];
	return matrix;
}

Matrix Matrix::GetAdjMat(){
	if (Dn != Dm)
		return Matrix();
	integer sig = -1;
	Matrix matrix(Dn, Dm);
	for (size i = 0; i < Dn; i++)
		for (size j = 0; j < Dm; j++)
			matrix.mat[i][j] = Matdellc(i, j).GetDete() * (sig *= -1);
	return matrix;
}

Matrix Matrix::GetInvMat(){
	if (Dn != Dm)
		return Matrix();
	return GetAdjMat() / GetDete();
}

Matrix Matrix::GetMatE() {
	if (Dn != Dm)
		return Matrix();
	Matrix matrix(Dn, Dm);
	for (size i = 0; i < Dn; i++)
		for (size j = 0; j < Dm; j++)
			if (i == j)
				matrix.mat[i][j] = 1;
			else
				matrix.mat[i][j] = 0;
	return matrix;
}

Matrix Matrix::Matdelline(size n){
	if (Dn == 0)
		return Matrix();
	if (n >= Dn)
		n = Dn - 1;
	Matrix matrix(Dn - 1, Dm);
	for (size i = 0; i < matrix.Dn; i++)
		for (size j = 0; j < matrix.Dm; j++)
			if (i < n)
				matrix.mat[i][j] = mat[i][j];
			else
				matrix.mat[i][j] = mat[i + 1][j];
}

Matrix Matrix::Matdelcolu(size m){
	if (Dm == 0)
		return Matrix();
	if (m >= Dm)
		m = Dm - 1;
	Matrix matrix(Dn, Dm - 1);
	for (size i = 0; i < matrix.Dn; i++)
		for (size j = 0; j < matrix.Dm; j++)
			if (j < m)
				matrix.mat[i][j] = mat[i][j];
			else
				matrix.mat[i][j] = mat[i][j + 1];
}

Matrix Matrix::Matdellc(size n, size m){
	return Matdelline(n).Matdelcolu(m);
}

Matrix Matrix::Matmer(const Matrix matrix, bool ft){
	size nmin = matrix.Dn < Dn ? matrix.Dn : Dn;
	size mmin = matrix.Dm < Dm ? matrix.Dm : Dm;

	if (ft){
		Matrix mer(matrix.Dn + Dn, mmin);
		for (size i = 0; i < mer.Dn; i++)
			for (size j = 0; j < mer.Dm; j++)
				if (i < Dn)
					mer.mat[i][j] = mat[i][j];
				else
					mer.mat[i][j] = matrix.mat[i - Dn][j];
		return mer;
	}
	else {
		Matrix mer(nmin, matrix.Dm + Dm);
		for (size i = 0; i < mer.Dn; i++)
			for (size j = 0; j < mer.Dm; j++)
				if (j < Dm)
					mer.mat[i][j] = mat[i][j];
				else
					mer.mat[i][j] = matrix.mat[i][j - Dm];
		return mer;
	}
}

Matrix Matrix::Matpar(size n1, size m1, size n2, size m2){
	if (n1 >= n2 || m1 >= m2)
		return Matrix();
	Matrix matrix(n2 - n1, m2 - m1);
	for (size i = 0; i < matrix.Dn; i++)
		for (size j = 0; j < matrix.Dm; j++)
			matrix.mat[i][j] = mat[n1 + i][m1 + j];
	return matrix;
}


Matrix Matrix::operator=(const Matrix matrix){
	for (size i = 0; i < Dn; i++)
		mat[i].clear();
	mat.clear();

	Dn = matrix.Dn;
	Dm = matrix.Dm;
	for (size i = 0; i < Dn; i++)
		for (size j = 0; j < Dm; j++) {
			mat.push_back(Line());
			mat[i].push_back(matrix.mat[i][j]);
		}
	return *this;
}

bool Matrix::operator==(const Matrix matrix){
	if(Dn!= matrix.Dn||Dm != matrix.Dm)
		return false;
	for (size i = 0; i < Dn; i++)
		for (size j = 0; j < Dm; j++)
			if (mat[i][j] != matrix.mat[i][j])
				return false;
	return true;
}

bool Matrix::operator!=(const Matrix matrix) {
	if (*this == matrix)
		return false;
	return true;
}

Matrix operator+(const Matrix& A, const Matrix& B){
	size nmax = A.Dn > B.Dn ? A.Dn : B.Dn;
	size mmax = A.Dm > B.Dm ? A.Dm : B.Dm;
	Matrix C(nmax, mmax);
	for (size i = 0; i < A.Dn; i++)
		for (size j = 0; j < A.Dm; j++)
			C.mat[i][j] = A.mat[i][j];
	for (size i = 0; i < B.Dn; i++)
		for (size j = 0; j < B.Dm; j++)
			C.mat[i][j] += B.mat[i][j];
	return C;
}

Matrix operator-(const Matrix& A, const Matrix& B){
	size nmax = A.Dn > B.Dn ? A.Dn : B.Dn;
	size mmax = A.Dm > B.Dm ? A.Dm : B.Dm;
	Matrix C(nmax, mmax);
	for (size i = 0; i < A.Dn; i++)
		for (size j = 0; j < A.Dm; j++)
			C.mat[i][j] = A.mat[i][j];
	for (size i = 0; i < B.Dn; i++)
		for (size j = 0; j < B.Dm; j++)
			C.mat[i][j] -= B.mat[i][j];
	return C;
}

Matrix operator*(const Matrix& A, const Matrix& B){
	if (A.Dm != B.Dn)
		return Matrix();
	Matrix C(B.Dm, A.Dn);
	for (size i = 0; i < C.Dn; i++)
		for (size j = 0; j < C.Dm; j++)
			C.mat[i][j] = A.mat[i][j] + B.mat[i][j];  ////////
	return C;
}

Matrix operator/(const Matrix& A, const  Matrix& B){
	Matrix C = B;
	return A * C.GetInvMat();
}

Matrix operator+(const complex& a, const Matrix& B){
	Matrix C;
	for (size i = 0; i < B.Dn; i++)
		for (size j = 0; j < B.Dm; j++)
			C.mat[i][j] = a + B.mat[i][j];
	return C;
}

Matrix operator-(const complex& a, const Matrix& B){
	Matrix C;
	for (size i = 0; i < B.Dn; i++)
		for (size j = 0; j < B.Dm; j++)
			C.mat[i][j] = a - B.mat[i][j];
	return C;
}

Matrix operator*(const complex& a, const Matrix& B){
	Matrix C;
	for (size i = 0; i < B.Dn; i++)
		for (size j = 0; j < B.Dm; j++)
			C.mat[i][j] = a * B.mat[i][j];
	return C;
}

Matrix operator/(const complex& a, const Matrix& B){
	Matrix C;
	for (size i = 0; i < B.Dn; i++)
		for (size j = 0; j < B.Dm; j++)
			C.mat[i][j] = a / B.mat[i][j];
	return C;
}

Matrix operator+(const Matrix& A, const complex& b){
	Matrix C;
	for (size i = 0; i < A.Dn; i++)
		for (size j = 0; j < A.Dm; j++)
			C.mat[i][j] = A.mat[i][j] + b;
	return C;
}

Matrix operator-(const Matrix& A, const complex& b){
	Matrix C;
	for (size i = 0; i < A.Dn; i++)
		for (size j = 0; j < A.Dm; j++)
			C.mat[i][j] = A.mat[i][j] - b;
	return C;
}

Matrix operator*(const Matrix& A, const complex& b){
	Matrix C;
	for (size i = 0; i < A.Dn; i++)
		for (size j = 0; j < A.Dm; j++)
			C.mat[i][j] = A.mat[i][j] * b;
	return C;
}

Matrix operator/(const Matrix& A, const complex& b){
	if (b == complex(0))
		return Matrix();
	Matrix C;
	for (size i = 0; i < A.Dn; i++)
		for (size j = 0; j < A.Dm; j++)
			C.mat[i][j] = A.mat[i][j] / b;
	return C;
}

Matrix operator^(const Matrix& A, integer n){
	if (A.Dn != A.Dm)
		return Matrix();
	Matrix matrixA = A;
	Matrix matrixE = matrixA.GetMatE();
	Matrix matrixI = matrixA.GetInvMat();
	if (n > 0)
		for (size i = 0; i < +n.var; i++)
			matrixE *= matrixA;
	if (n < 0)
		for (size i = 0; i > -n.var; i++)
			matrixE *= matrixI;
	return matrixE;
}