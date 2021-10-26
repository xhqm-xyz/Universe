#include "cmath"
#include "CVector.h"

CVector CVector::GetUnitVec()
{
	return CVector();
}

CVector CVector::GetTraVec()
{
	CVector Tra(_n);
	for (int i = 0; i < _n; i++)
		Tra[i] = _vars[_n - i - 1];
	return Tra;
}

CVector CVector::GetSubVec()
{
	CVector Sub(_n);
	for (int i = 0; i < _n; i++)
		Sub[i] = -_vars[i];
	return Sub;
}

bool CVector::operator==(const CVector vect)
{
	if (_n != vect._n)
		return false;
	for (int i = 0; i < _n; i++)
		if (_vars[i] > vect._vars[i] + PRECI || _vars[i] < vect._vars[i] - PRECI)
			return false;
	return true;
}

bool CVector::operator!=(const CVector vect)
{
	if (*this == vect)
		return false;
	return true;
}

CVector CVector::GetVecE(int n)
{
	if (n < 1)n = 1;
	if (n > 4)n = 4;
	CVector res(4);
	res[n - 1] = 1;
	return res;
}