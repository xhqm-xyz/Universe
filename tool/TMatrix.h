#pragma once
#ifndef UNIVERSE_TEMPLATE_MATRIX
#define UNIVERSE_TEMPLATE_MATRIX
#include "../math/measure.h"
template <class _T>
class TMatrix
{
	typedef Vect(_T) T_vect;
	typedef Dete(_T) T_dete;
protected:
	T_dete mat;
	natu Dn;
	natu Dm;
	template <class _T>
	void Inti(natu dn, natu dm) {
		Dn = dn; Dm = dm;
		for (natu i = 0; i < Dn; i++) {
			mat.push_back(T_vect());
			for (natu j = 0; j < Dm; j++)
				mat[i].push_back(_T());
		}
	}
public:
	TMatrix() :Dn(0), Dm(0) {};
	TMatrix(T_dete matrix);
	TMatrix(natu dn, natu dm);

	natu GetDn() { return Dn; };
	natu GetDm() { return Dm; };

	void SetMatrix(T_dete dete);
	void SetMatrix(_T mea);

	bite SetMatrixLine(T_vect data, natu dn);
	bite SetMatrixColu(T_vect data, natu dm);

	_T GetDete();							//得到行列式的值

	TMatrix<_T> GetMatE();							//单位矩阵
	TMatrix<_T> GetTraMat();							//转置矩阵
	TMatrix<_T> GetAdjMat();							//伴随矩阵
	TMatrix<_T> GetInvMat();							//逆矩阵

	TMatrix<_T> Matdelline(natu n = 0);				//删除矩阵n行
	TMatrix<_T> Matdelcolu(natu m = 0);				//删除矩阵m列
	TMatrix<_T> Matdellc(natu n = 0, natu m = 0);	//删除矩阵n行m列
	TMatrix<_T> Matmer(const TMatrix<_T> matrix, bite ft);		//矩阵的行增ft=1/列增ft=0合并
	TMatrix<_T> Matpar(natu n1, natu m1, natu n2, natu m2);	//截取矩阵(n1,m1)到(n2,m2)部分
	
	T_vect& operator[] (const natu& n);
	TMatrix<_T> operator = (const TMatrix<_T> matrix);
	bite operator == (const TMatrix<_T> matrix);
	bite operator != (const TMatrix<_T> matrix);

	TMatrix<_T> operator += (const TMatrix<_T> matrix) { return *this = *this + matrix; };
	TMatrix<_T> operator -= (const TMatrix<_T> matrix) { return *this = *this - matrix; };
	TMatrix<_T> operator *= (const TMatrix<_T> matrix) { return *this = *this * matrix; };
	TMatrix<_T> operator /= (const TMatrix<_T> matrix) { return *this = *this / matrix; };

	friend TMatrix<_T> operator + (const TMatrix<_T>& A, const TMatrix<_T>& B){
		natu nmax = A.Dn > B.Dn ? A.Dn : B.Dn;
		natu mmax = A.Dm > B.Dm ? A.Dm : B.Dm;
		TMatrix<_T> C(nmax, mmax);
		TMatrix<_T> copyA(A.mat);
		TMatrix<_T> copyB(B.mat);
		for (natu i = 0; i < A.Dn; i++)
			for (natu j = 0; j < A.Dm; j++)
				C.mat[i][j] = copyA.mat[i][j];
		for (natu i = 0; i < B.Dn; i++)
			for (natu j = 0; j < B.Dm; j++)
				C.mat[i][j] = C.mat[i][j] + copyB.mat[i][j];
		return C;
	}
	friend TMatrix<_T> operator - (const TMatrix<_T>& A, const TMatrix<_T>& B){
		natu nmax = A.Dn > B.Dn ? A.Dn : B.Dn;
		natu mmax = A.Dm > B.Dm ? A.Dm : B.Dm;
		TMatrix<_T> C(nmax, mmax);
		TMatrix<_T> copyA(A.mat);
		TMatrix<_T> copyB(B.mat);
		for (natu i = 0; i < A.Dn; i++)
			for (natu j = 0; j < A.Dm; j++)
				C.mat[i][j] = copyA.mat[i][j];
		for (natu i = 0; i < B.Dn; i++)
			for (natu j = 0; j < B.Dm; j++)
				C.mat[i][j] = C.mat[i][j] - copyB.mat[i][j];
		return C;
	}
	friend TMatrix<_T> operator * (const TMatrix<_T>& A, const TMatrix<_T>& B) {
		TMatrix<_T> copyA(A.mat);
		TMatrix<_T> copyB(B.mat);
		if (A.Dm != B.Dn)
			return TMatrix<_T>();
		TMatrix<_T> C(B.Dm, A.Dn);
		for (natu i = 0; i < C.Dn; i++)
			for (natu j = 0; j < C.Dm; j++)
				for (natu k = 0; k < C.Dn; k++)
					C.mat[i][j] = C.mat[i][j] + copyA.mat[i][k] * copyB.mat[k][j];
		return C;
	}
	friend TMatrix<_T> operator / (const TMatrix<_T>& A, const TMatrix<_T>& B) {
		TMatrix<_T> C = B;
		return A * C.GetInvMat();
	}
	friend TMatrix<_T> operator+(const _T& a, const TMatrix<_T>& B) {
		TMatrix<_T> copy(B.mat);
		for (natu i = 0; i < B.Dn; i++)
			for (natu j = 0; j < B.Dm; j++)
				copy.mat[i][j] = a + copy.mat[i][j];
		return copy;
	}
	friend TMatrix<_T> operator-(const _T& a, const TMatrix<_T>& B) {
		TMatrix<_T> copy(B.mat);
		for (natu i = 0; i < B.Dn; i++)
			for (natu j = 0; j < B.Dm; j++)
				copy.mat[i][j] = a - copy.mat[i][j];
		return copy;
	}
	friend TMatrix<_T> operator*(const _T& a, const TMatrix<_T>& B) {
		TMatrix<_T> copy(B.mat);
		for (natu i = 0; i < B.Dn; i++)
			for (natu j = 0; j < B.Dm; j++)
				copy.mat[i][j] = a * copy.mat[i][j];
		return copy;
	}
	friend TMatrix<_T> operator/(const _T& a, const TMatrix<_T>& B) {
		TMatrix<_T> copy(B.mat);
		for (natu i = 0; i < B.Dn; i++)
			for (natu j = 0; j < B.Dm; j++)
				copy.mat[i][j] = a / copy.mat[i][j];
		return copy;
	}
	friend TMatrix<_T> operator+(const TMatrix<_T>& A, const _T& b) {
		TMatrix<_T> copy(A.mat);
		for (natu i = 0; i < A.Dn; i++)
			for (natu j = 0; j < A.Dm; j++)
				copy.mat[i][j] = copy.mat[i][j] + b;
		return copy;
	}
	friend TMatrix<_T> operator-(const TMatrix<_T>& A, const _T& b) {
		TMatrix<_T> copy(A.mat);
		for (natu i = 0; i < A.Dn; i++)
			for (natu j = 0; j < A.Dm; j++)
				copy.mat[i][j] = copy.mat[i][j] - b;
		return copy;
	}
	friend TMatrix<_T> operator*(const TMatrix<_T>& A, const _T& b) {
		TMatrix<_T> copy(A.mat);
		for (natu i = 0; i < A.Dn; i++)
			for (natu j = 0; j < A.Dm; j++)
				copy.mat[i][j] = copy.mat[i][j] * b;
		return copy;
	}
	friend TMatrix<_T> operator/(const TMatrix<_T>& A, const _T& b) {
		if (b == _T(0))
			return TMatrix<_T>();
		TMatrix<_T> copy(A.mat);
		for (natu i = 0; i < A.Dn; i++)
			for (natu j = 0; j < A.Dm; j++)
				copy.mat[i][j] = copy.mat[i][j] / b;
		return copy;
	}
};

template <class _T>
inline TMatrix<_T>::TMatrix(T_dete matrix) :Dn(matrix.size()), Dm(matrix[0].size()) {
	Inti<_T>(matrix.size(), matrix[0].size());
	for (natu i = 0; i < Dn; i++)
		for (natu j = 0; j < Dm; j++)
			mat[i][j] = matrix[i][j];
}
template <class _T>
inline TMatrix<_T>::TMatrix(natu dn, natu dm) :Dn(dn), Dm(dm) {
	Inti<_T>(dn, dm);
}
template <class _T>
void TMatrix<_T>::SetMatrix(T_dete dete) {
	natu nmin = dete.size() < Dn ? dete.size() : Dn;
	natu mmin = dete.size() < Dm ? dete.size() : Dm;
	for (natu i = 0; i < nmin; i++)
		for (natu j = 0; j < mmin; j++)
			mat[i][j] = dete[i][j];
}
template <class _T>
void TMatrix<_T>::SetMatrix(_T mea) {
	for (natu i = 0; i < Dn; i++)
		for (natu j = 0; j < Dm; j++)
			mat[j][i] = mea;
}
template <class _T>
bool TMatrix<_T>::SetMatrixLine(T_vect data, natu dn) {
	if (data.size() != Dm)
		return false;
	for (natu j = 0; j < Dm; j++)
		mat[dn][j] = data[j];
	return true;
}
template <class _T>
bool TMatrix<_T>::SetMatrixColu(T_vect data, natu dm) {
	if (data.size() != Dn)
		return false;
	for (natu i = 0; i < Dn; i++)
		mat[i][dm] = data[i];
	return true;
}
template <class _T>
_T TMatrix<_T>::GetDete() {
	if (Dn != Dm)
		return NULL;
	if (Dn == 1)
		return mat[0][0];
	_T mea = _T();
	integer sig = -1;
	for (natu i = 0; i < Dn; i++)
		mea += (mat[i][0] * Matdellc(i, 0).GetDete() * (sig *= -1));
	return mea;
}
template <class _T>
TMatrix<_T> TMatrix<_T>::GetTraMat() {
	TMatrix<_T> matrix(Dm, Dn);
	for (natu i = 0; i < Dn; i++)
		for (natu j = 0; j < Dm; j++)
			matrix.mat[j][i] = mat[i][j];
	return matrix;
}
template <class _T>
TMatrix<_T> TMatrix<_T>::GetAdjMat() {
	if (Dn != Dm)
		return TMatrix<_T>();
	integer sig = -1;
	TMatrix<_T> matrix(Dn, Dm);
	for (natu i = 0; i < Dn; i++)
		for (natu j = 0; j < Dm; j++)
			matrix.mat[i][j] = Matdellc(i, j).GetDete() * (sig *= -1);
	return matrix;
}
template <class _T>
TMatrix<_T> TMatrix<_T>::GetInvMat() {
	if (Dn != Dm)
		return TMatrix<_T>();
	return GetAdjMat() / GetDete();
}
template <class _T>
TMatrix<_T> TMatrix<_T>::GetMatE() {
	if (Dn != Dm)
		return TMatrix<_T>();
	TMatrix<_T> matrix(Dn, Dm);
	for (natu i = 0; i < Dn; i++)
		for (natu j = 0; j < Dm; j++)
			if (i == j)
				matrix.mat[i][j] = 1;
			else
				matrix.mat[i][j] = 0;
	return matrix;
}
template <class _T>
TMatrix<_T> TMatrix<_T>::Matdelline(natu n) {
	if (Dn == 0)
		return TMatrix<_T>();
	if (n >= Dn)
		n = Dn - 1;
	TMatrix<_T> matrix(Dn - 1, Dm);
	for (natu i = 0; i < matrix.Dn; i++)
		for (natu j = 0; j < matrix.Dm; j++)
			if (i < n)
				matrix.mat[i][j] = mat[i][j];
			else
				matrix.mat[i][j] = mat[i + 1][j];
	return matrix;
}
template <class _T>
TMatrix<_T> TMatrix<_T>::Matdelcolu(natu m) {
	if (Dm == 0)
		return TMatrix<_T>();
	if (m >= Dm)
		m = Dm - 1;
	TMatrix<_T> matrix(Dn, Dm - 1);
	for (natu i = 0; i < matrix.Dn; i++)
		for (natu j = 0; j < matrix.Dm; j++)
			if (j < m)
				matrix.mat[i][j] = mat[i][j];
			else
				matrix.mat[i][j] = mat[i][j + 1];
	return matrix;
}
template <class _T>
TMatrix<_T> TMatrix<_T>::Matdellc(natu n, natu m) {
	return Matdelline(n).Matdelcolu(m);
}
template <class _T>
TMatrix<_T> TMatrix<_T>::Matmer(const TMatrix<_T> matrix, bite ft) {
	natu nmin = matrix.Dn < Dn ? matrix.Dn : Dn;
	natu mmin = matrix.Dm < Dm ? matrix.Dm : Dm;
	TMatrix<_T> copymat(matrix.mat);
	if (ft) {
		TMatrix<_T> mer(matrix.Dn + Dn, mmin);
		for (natu i = 0; i < mer.Dn; i++)
			for (natu j = 0; j < mer.Dm; j++)
				if (i < Dn)
					mer.mat[i][j] = mat[i][j];
				else
					mer.mat[i][j] = copymat.mat[i - Dn][j];
		return mer;
	}
	else {
		TMatrix<_T> mer(nmin, matrix.Dm + Dm);
		for (natu i = 0; i < mer.Dn; i++)
			for (natu j = 0; j < mer.Dm; j++)
				if (j < Dm)
					mer.mat[i][j] = mat[i][j];
				else
					mer.mat[i][j] = copymat.mat[i][j - Dm];
		return mer;
	}
}
template <class _T>
TMatrix<_T> TMatrix<_T>::Matpar(natu n1, natu m1, natu n2, natu m2) {
	if (n1 >= n2 || m1 >= m2)
		return TMatrix<_T>();
	TMatrix<_T> matrix(n2 - n1, m2 - m1);
	for (natu i = 0; i < matrix.Dn; i++)
		for (natu j = 0; j < matrix.Dm; j++)
			matrix.mat[i][j] = mat[n1 + i][m1 + j];
	return matrix;
}
template<class _T>
inline vector<_T>& TMatrix<_T>::operator[](const natu& n)
{
	return mat[n];
}
template <class _T>
inline TMatrix<_T> TMatrix<_T>::operator=(const TMatrix<_T> matrix) {
	for (natu i = 0; i < Dn; i++)
		mat[i].clear();
	mat.clear();
	TMatrix<_T> copymat(matrix.mat);
	Dn = matrix.Dn;
	Dm = matrix.Dm;
	for (natu i = 0; i < Dn; i++)
		for (natu j = 0; j < Dm; j++) {
			mat.push_back(T_vect());
			mat[i].push_back(copymat.mat[i][j]);
		}
	return *this;
}
template <class _T>
bite TMatrix<_T>::operator==(const TMatrix<_T> matrix) {
	TMatrix<_T> copymat(matrix.mat);
	if (Dn != matrix.Dn || Dm != matrix.Dm)
		return false;
	for (natu i = 0; i < Dn; i++)
		for (natu j = 0; j < Dm; j++)
			if (mat[i][j] != copymat.mat[i][j])
				return false;
	return true;
}
template <class _T>
bite TMatrix<_T>::operator!=(const TMatrix<_T> matrix) {
	if (*this == matrix)
		return false;
	return true;
}
#endif // !UNIVERSE_TEMPLATE_MATRIX