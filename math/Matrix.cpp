#include "Matrix.h"

Matrix::Matrix(natu dn, natu dm) :Dn(dn), Dm(dm) {
	for (natu i = 0; i < Dn; i++) {
		oned v;
		mat.push_back(v);
		for (natu j = 0; j < Dm; j++)
			mat[i].push_back(0);
	}
}

Matrix::Matrix(twod matrix) {
	Inti(matrix.size(), matrix[0].size());
	for (natu i = 0; i < Dn; i++)
		for (natu j = 0; j < Dm; j++) 
			mat[i][j] = matrix[i][j];		
}

Matrix::Matrix(oned matrix, bite LC){
	if (LC) {
		Inti(1, matrix.size());
		for (natu j = 0; j < Dm; j++)
			mat[0][j] = matrix[j];
	}
	else {
		Inti(matrix.size(), 1);
		for (natu i = 0; i < Dn; i++)
			mat[i][0] = matrix[i];
	}
}

void Matrix::SetMatrix(twod dete){
	mat = dete;
}

void Matrix::SetMatrix(measure mea){
	for (natu i = 0; i < Dn; i++)
		for (natu j = 0; j < Dm; j++)
			mat[j][i] = mea;
}

bool Matrix::SetMatrixLine(oned data, natu dn){
	if (data.size() != Dm)
		return false;
	for (natu j = 0; j < Dm; j++)
		mat[dn][j] = data[j];
	return true;
}

bool Matrix::SetMatrixColu(oned data, natu dm){
	if (data.size() != Dn)
		return false;
	for (natu i = 0; i < Dn; i++)
			mat[i][dm] = data[i];
	return true;
}

bool Matrix::SetMatrixLine(Vector vec, natu dn){
	return SetMatrixLine(vec.Getvect(0, Dn), dn);
}

bool Matrix::SetMatrixColu(Vector vec, natu dm){
	return SetMatrixColu(vec.Getvect(0, Dn), dm);
}

Vector Matrix::GetLineVector(natu dn){
	Vector vec(mat[dn].size());
	for (natu i = 0; i < vec.GetDim(); i++)
		vec[i] = mat[dn][i];
	return vec;
}

Vector Matrix::GetColuVector(natu dm){
	Vector vec((mat[dm].size()));
	for (natu i = 0; i < vec.GetDim(); i++)
		vec[i] = mat[i][dm];
	return vec;
}

measure Matrix::GetDete(){
	if (Dn != Dm)
		return NULL;
	if (Dn == 1)
		return mat[0][0];
	measure mea = 0;
	integer sig = -1;
	for (natu i = 0; i < Dn; i++)
		mea += (mat[i][0] * Matdellc(i, 0).GetDete() * (sig *= -1));
	return mea;
}

Matrix Matrix::GetTraMat(){
	Matrix matrix(Dm, Dn);
	for (natu i = 0; i < Dn; i++)
		for (natu j = 0; j < Dm; j++)
			matrix.mat[j][i] = mat[i][j];
	return matrix;
}

Matrix Matrix::GetAdjMat(){
	if (Dn != Dm)
		return Matrix();
	integer sig = -1;
	Matrix matrix(Dn, Dm);
	for (natu i = 0; i < Dn; i++)
		for (natu j = 0; j < Dm; j++)
			matrix.mat[i][j] = (Matdellc(i, j).GetDete() * (sig *= -1));
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
	for (natu i = 0; i < Dn; i++)
		for (natu j = 0; j < Dm; j++)
			if (i == j)
				matrix.mat[i][j] = 1;
			else
				matrix.mat[i][j] = 0;
	return matrix;
}

Matrix Matrix::Matdelline(natu n){
	if (Dn == 0)
		return Matrix();
	if (n >= Dn)
		n = Dn - 1;
	Matrix matrix(Dn - 1, Dm);
	for (natu i = 0; i < matrix.Dn; i++)
		for (natu j = 0; j < matrix.Dm; j++)
			if (i < n)
				matrix.mat[i][j] = mat[i][j];
			else
				matrix.mat[i][j] = mat[i + 1][j];
	return matrix;
}

Matrix Matrix::Matdelcolu(natu m){
	if (Dm == 0)
		return Matrix();
	if (m >= Dm)
		m = Dm - 1;
	Matrix matrix(Dn, Dm - 1);
	for (natu i = 0; i < matrix.Dn; i++)
		for (natu j = 0; j < matrix.Dm; j++)
			if (j < m)
				matrix.mat[i][j] = mat[i][j];
			else
				matrix.mat[i][j] = mat[i][j + 1];
	return matrix;
}

Matrix Matrix::Matdellc(natu n, natu m){
	return Matdelline(n).Matdelcolu(m);
}

Matrix Matrix::Matmer(const Matrix matrix, bite ft){
	natu nmin = matrix.Dn < Dn ? matrix.Dn : Dn;
	natu mmin = matrix.Dm < Dm ? matrix.Dm : Dm;
	Matrix copymat(matrix.mat);
	if (ft){
		Matrix mer(matrix.Dn + Dn, mmin);
		for (natu i = 0; i < mer.Dn; i++)
			for (natu j = 0; j < mer.Dm; j++)
				if (i < Dn)
					mer.mat[i][j] = mat[i][j];
				else
					mer.mat[i][j] = copymat.mat[i - Dn][j];
		return mer;
	}
	else {
		Matrix mer(nmin, matrix.Dm + Dm);
		for (natu i = 0; i < mer.Dn; i++)
			for (natu j = 0; j < mer.Dm; j++)
				if (j < Dm)
					mer.mat[i][j] = mat[i][j];
				else
					mer.mat[i][j] = copymat.mat[i][j - Dm];
		return mer;
	}
}

Matrix Matrix::Matpar(natu n1, natu m1, natu n2, natu m2){
	if (n1 >= n2 || m1 >= m2)
		return Matrix();
	Matrix matrix(n2 - n1, m2 - m1);
	for (natu i = 0; i < matrix.Dn; i++)
		for (natu j = 0; j < matrix.Dm; j++)
			matrix.mat[i][j] = mat[n1 + i][m1 + j];
	return matrix;
}


oned& Matrix::operator[](const natu& n){
	return mat[n];
}

Matrix Matrix::operator=(const Matrix matrix){
	for (natu i = 0; i < Dn; i++)
		mat[i].clear();
	mat.clear();
	Matrix copymat(matrix.mat);
	Dn = matrix.Dn;
	Dm = matrix.Dm;
	for (natu i = 0; i < Dn; i++) {
		oned v;
		mat.push_back(v);
		for (natu j = 0; j < Dm; j++)
			mat[i].push_back(copymat.mat[i][j]);
	}return *this;
}

bite Matrix::operator==(const Matrix matrix){
	Matrix copymat(matrix.mat);
	if(Dn!= matrix.Dn||Dm != matrix.Dm)
		return false;
	for (natu i = 0; i < Dn; i++)
		for (natu j = 0; j < Dm; j++)
			if (copymat.mat[i][j] - XPRECI < mat[i][j] || mat[i][j] > copymat.mat[i][j] + XPRECI)
				return false;
	return true;
}

bite Matrix::operator!=(const Matrix matrix) {
	if (*this == matrix)
		return false;
	return true;
}

Matrix operator+(const Matrix& A, const Matrix& B){
	natu nmax = A.Dn > B.Dn ? A.Dn : B.Dn;
	natu mmax = A.Dm > B.Dm ? A.Dm : B.Dm;
	Matrix C(nmax, mmax);
	Matrix copyA(A.mat);
	Matrix copyB(B.mat);
	for (natu i = 0; i < A.Dn; i++)
		for (natu j = 0; j < A.Dm; j++)
			C.mat[i][j] = copyA.mat[i][j];
	for (natu i = 0; i < B.Dn; i++)
		for (natu j = 0; j < B.Dm; j++)
			C.mat[i][j] += copyB.mat[i][j];
	return C;
}

Matrix operator-(const Matrix& A, const Matrix& B){
	natu nmax = A.Dn > B.Dn ? A.Dn : B.Dn;
	natu mmax = A.Dm > B.Dm ? A.Dm : B.Dm;
	Matrix C(nmax, mmax);
	Matrix copyA(A.mat);
	Matrix copyB(B.mat);
	for (natu i = 0; i < A.Dn; i++)
		for (natu j = 0; j < A.Dm; j++)
			C.mat[i][j] = copyA.mat[i][j];
	for (natu i = 0; i < B.Dn; i++)
		for (natu j = 0; j < B.Dm; j++)
			C.mat[i][j] -= copyB.mat[i][j];
	return C;
}

Matrix operator*(const Matrix& A, const Matrix& B){
	Matrix copyA(A.mat);
	Matrix copyB(B.mat);
	if (A.Dm != B.Dn)
		return Matrix();
	Matrix C(B.Dm, A.Dn);
	for (natu i = 0; i < C.Dn; i++)
		for (natu j = 0; j < C.Dm; j++)
			for(natu k = 0; k < C.Dn; k++)
				C.mat[i][j] += copyA.mat[i][k] * copyB.mat[k][j];
	return C;
}

Matrix operator/(const Matrix& A, const  Matrix& B){
	Matrix C = B;
	return A * C.GetInvMat();
}

Matrix operator+(const measure& a, const Matrix& B){
	Matrix copy(B.mat);
	for (natu i = 0; i < B.Dn; i++)
		for (natu j = 0; j < B.Dm; j++)
			copy.mat[i][j] = a + copy.mat[i][j];
	return copy;
}

Matrix operator-(const measure& a, const Matrix& B){
	Matrix copy(B.mat);
	for (natu i = 0; i < B.Dn; i++)
		for (natu j = 0; j < B.Dm; j++)
			copy.mat[i][j] = a - copy.mat[i][j];
	return copy;
}

Matrix operator*(const measure& a, const Matrix& B){
	Matrix copy(B.mat);
	for (natu i = 0; i < B.Dn; i++)
		for (natu j = 0; j < B.Dm; j++)
			copy.mat[i][j] = a * copy.mat[i][j];
	return copy;
}

Matrix operator/(const measure& a, const Matrix& B){
	Matrix copy(B.mat);
	for (natu i = 0; i < B.Dn; i++)
		for (natu j = 0; j < B.Dm; j++)
			copy.mat[i][j] = a / copy.mat[i][j];
	return copy;
}

Matrix operator+(const Matrix& A, const measure& b){
	Matrix copy(A.mat);
	for (natu i = 0; i < A.Dn; i++)
		for (natu j = 0; j < A.Dm; j++)
			copy.mat[i][j] = copy.mat[i][j] + b;
	return copy;
}

Matrix operator-(const Matrix& A, const measure& b){
	Matrix copy(A.mat);
	for (natu i = 0; i < A.Dn; i++)
		for (natu j = 0; j < A.Dm; j++)
			copy.mat[i][j] = copy.mat[i][j] - b;
	return copy;
}

Matrix operator*(const Matrix& A, const measure& b){
	Matrix copy(A.mat);
	for (natu i = 0; i < A.Dn; i++)
		for (natu j = 0; j < A.Dm; j++)
			copy.mat[i][j] = copy.mat[i][j] * b;
	return copy;
}

Matrix operator/(const Matrix& A, const measure& b){
	if (b == measure(0))
		return Matrix();
	Matrix copy(A.mat);
	for (natu i = 0; i < A.Dn; i++)
		for (natu j = 0; j < A.Dm; j++)
			copy.mat[i][j] = copy.mat[i][j] / b;
	return copy;
}

Matrix operator^(const Matrix& A, integer n){
	if (A.Dn != A.Dm)
		return Matrix();
	Matrix matrixA(A.mat);
	Matrix matrixE = matrixA.GetMatE();
	Matrix matrixI = matrixA.GetInvMat();
	if (n > 0)
		for (natu i = 0; i < n; i++)
			matrixE *= matrixA;
	if (n < 0) {
		n = -n;
		for (natu i = 0; i < n; i++)
			matrixE *= matrixI;
	}return matrixE;
}