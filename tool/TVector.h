#pragma once
#ifndef UNIVERSE_TEMPLATE_VECTOR
#define UNIVERSE_TEMPLATE_VECTOR
#include "../math/measure.h"
template <class _T>
class TVector
{
	typedef Vect(_T) T_vect;
protected:
	T_vect vec;
	nume Dimension; //向量被声明后维度仅可被 “?=” 更改
public:
	TVector(nume dim = 0);
	TVector(T_vect meavec);
	TVector(_T mea1);
	TVector(_T mea1, _T mea2);
	TVector(_T mea1, _T mea2, _T mea3);
	TVector(_T mea1, _T mea2, _T mea3, _T mea4);
	~TVector() { vec.clear(); };

	nume GetDim() { return Dimension; };
	void Setvect(T_vect meavec);
	void SetVect(TVector<_T> vect);
	T_vect Getvect(nume n, nume m) {
		T_vect data;
		if (n < 0)
			n = 0;
		if (m >= Dimension)
			m = Dimension - 1;
		if (m < 0)
			m = 0;
		if (n >= Dimension)
			n = Dimension - 1;
		if (n <= m)
			for (nume i = n; i <= m; i++)
				data.push_back(vec[i]);
		else
			for (nume i = n; i >= m; i--)
				data.push_back(vec[i]);
		return data;
	};
	TVector<_T> GetVect(nume n, nume m) {
		return TVector<_T>(Getvect(n, m));
	};


	_T GetModulus() { return _T::sqrt((*this) * (*this)); };			//得到向量的模

public:
	_T& operator[] (const nume& n);

	TVector<_T> operator = (const TVector<_T>& vect);
	bite operator == (const TVector<_T>& vect);
	bite operator != (const TVector<_T>& vect);

	friend TVector<_T> operator + (const TVector<_T>& vect) {
		TVector<_T> V(vect.vec);
		for (nume i = 0; i < V.Dimension; i++)
			V[i] = +V[i];
		return V;
	};
	friend TVector<_T> operator - (const TVector<_T>& vect) {
		TVector<_T> V(vect.vec);
		for (nume i = 0; i < V.Dimension; i++)
			V[i] = -V[i];
		return V;
	};

	friend TVector<_T> operator + (const TVector<_T>& A, const TVector<_T>& B) {
		nume dimMAX = A.Dimension > B.Dimension ? A.Dimension : B.Dimension;
		nume dimMIN = A.Dimension < B.Dimension ? A.Dimension : B.Dimension;
		TVector<_T> V(dimMAX);
		TVector<_T> VA(A.vec);
		TVector<_T> VB(B.vec);
		if (A.Dimension > B.Dimension)
			for (nume i = 0; i < dimMAX; i++)
				if (i < dimMIN)
					V[i] = VA[i] + VB[i];
				else
					V[i] = VA[i] + 0;
		if (A.Dimension < B.Dimension)
			for (nume i = 0; i < dimMAX; i++)
				if (i < dimMIN)
					V[i] = VA[i] + VB[i];
				else
					V[i] = 0 + VB.vec[i];
		if (A.Dimension == B.Dimension)
			for (nume i = 0; i < dimMAX; i++)
				V[i] = VA[i] + VB[i];
		return V;
	};
	friend TVector<_T> operator - (const TVector<_T>& A, const TVector<_T>& B) {
		nume dimMAX = A.Dimension > B.Dimension ? A.Dimension : B.Dimension;
		nume dimMIN = A.Dimension < B.Dimension ? A.Dimension : B.Dimension;
		TVector<_T> V(dimMAX);
		TVector<_T> VA(A.vec);
		TVector<_T> VB(B.vec);
		if (A.Dimension > B.Dimension)
			for (nume i = 0; i < dimMAX; i++)
				if (i < dimMIN)
					V[i] = VA[i] - VB[i];
				else
					V[i] = VA.vec[i] - 0;
		if (A.Dimension < B.Dimension)
			for (nume i = 0; i < dimMAX; i++)
				if (i < dimMIN)
					V[i] = VA[i] - VB[i];
				else
					V[i] = 0 - VB[i];
		if (A.Dimension == B.Dimension)
			for (nume i = 0; i < dimMAX; i++)
				V[i] = VA[i] - VB[i];
		return V;
	};
	friend _T operator * (const TVector<_T>& A, const TVector<_T>& B) {
		sure modulus = 0;
		TVector<_T> VA(A.vec);
		TVector<_T> VB(B.vec);
		nume dim = A.Dimension < B.Dimension ? A.Dimension : B.Dimension;
		for (nume i = 0; i < dim; i++)
			modulus = modulus + (VA[i] * VB[i]);
		return modulus;
	}; //内积
	friend _T operator / (const TVector<_T>& A, const TVector<_T>& B) {
		/// <summary>
		/// /////////////////////
		/// </summary>
		/// <param name="A"></param>
		/// <param name="B"></param>
		/// <returns></returns>
		return _T();
	}; //投影

	friend TVector<_T> operator * (const _T& a, const TVector<_T>& B) {
		TVector<_T> VB(B.vec);
		for (nume i = 0; i < VB.Dimension; i++)
			VB[i] = a * VB[i];
		return VB;
	};
	friend TVector<_T> operator / (const _T& a, const TVector<_T>& B) {
		TVector<_T> VB(B.vec);
		for (nume i = 0; i < VB.Dimension; i++)
			VB[i] = a / VB[i];
		return VB;
	};
	friend TVector<_T> operator * (const TVector<_T>& A, const _T& b) {
		TVector<_T> VA(A.vec);
		for (nume i = 0; i < VA.Dimension; i++)
			VA[i] = VA[i] * b;
		return VA;
	};
	friend TVector<_T> operator / (const TVector<_T>& A, const _T& b) {
		TVector<_T> VA(A.vec);
		for (nume i = 0; i < VA.Dimension; i++)
			VA[i] = VA[i] / b;
		return VA;
	};

	TVector<_T> operator += (const TVector<_T>& vect) { return *this = *this + vect; };
	TVector<_T> operator -= (const TVector<_T>& vect) { return *this = *this - vect; };
	TVector<_T> operator *= (const _T& mea) { return *this = *this * mea; };
	TVector<_T> operator /= (const _T& mea) { return *this = *this / mea; };

	bite operator > (const TVector<_T> vect) { return (*this) * (*this) > vect * vect; };
	bite operator < (const TVector<_T> vect) { return (*this) * (*this) < vect * vect; };
	bite operator>= (const TVector<_T> vect) { return (*this) * (*this) >= vect * vect; };
	bite operator<= (const TVector<_T> vect) { return (*this) * (*this) <= vect * vect; };
};

template <class _T>
inline TVector<_T>::TVector(nume dim) :Dimension(dim) {
	for (nume i = 0; i < Dimension; i++)
		vec.push_back(_T());
}

template <class _T>
inline TVector<_T>::TVector(T_vect meavec) :Dimension(meavec.size()) {
	for (nume i = 0; i < Dimension; i++)
		vec.push_back(meavec[i]);
}

template <class _T>
inline TVector<_T>::TVector(_T mea1) : Dimension(1) {
	vec.push_back(mea1);
}

template <class _T>
inline TVector<_T>::TVector(_T mea1, _T mea2) : Dimension(2) {
	vec.push_back(mea1);
	vec.push_back(mea2);
}

template <class _T>
inline TVector<_T>::TVector(_T mea1, _T mea2, _T mea3) :Dimension(3) {
	vec.push_back(mea1);
	vec.push_back(mea2);
	vec.push_back(mea3);
}

template <class _T>
inline TVector<_T>::TVector(_T mea1, _T mea2, _T mea3, _T mea4) :Dimension(4) {
	vec.push_back(mea1);
	vec.push_back(mea2);
	vec.push_back(mea3);
	vec.push_back(mea4);
}

template <class _T>
void TVector<_T>::Setvect(T_vect meavec) {
	nume dim = Dimension <= meavec.size() ? Dimension : meavec.size();
	for (nume i = 0; i < dim; i++)
		vec[i] = meavec[i];
}

template <class _T>
void TVector<_T>::SetVect(TVector<_T> vect) {
	Setvect(vect.vec);
}

template <class _T>
_T& TVector<_T>::operator[](const nume& n) {
	if (n < 0 || n >= Dimension)
		return vec[0];
	return vec[n];
}

template <class _T>
TVector<_T> TVector<_T>::operator=(const TVector<_T>& vect) {
	vec.clear();
	TVector<_T> Ve(vect.vec);
	Dimension = vect.Dimension;
	for (nume i = 0; i < Dimension; i++)
		vec.push_back(Ve[i]);
	return *this;
}

template <class _T>
bite TVector<_T>::operator==(const TVector<_T>& vect) {
	TVector<_T> Ve(vect.vec);
	if (Dimension != Ve.Dimension)
		return false;
	for (nume i = 0; i < Dimension; i++)
		if (vec[i] != Ve.vec[i])
			return false;
	return true;
}

template <class _T>
bite TVector<_T>::operator!=(const TVector<_T>& vect) {
	if (*this == vect)
		return false;
	return true;
}
#endif // !UNIVERSE_TEMPLATE_VECTOR