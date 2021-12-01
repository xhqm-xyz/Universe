#pragma once
#ifndef UNIVERSE_MATH_MATRIX
#define UNIVERSE_MATH_MATRIX
#include "measure.h"
#include "Vector.h"

class Matrix
{
protected:
	twod mat;
	natu Dn;
	natu Dm;
	void Inti(natu dn, natu dm) {
		Dn = dn; Dm = dm;
		for (natu i = 0; i < Dn; i++) {
			oned v;
			mat.push_back(v);
			for (natu j = 0; j < Dm; j++)
				mat[i].push_back(0);
		}
	}
public:
	Matrix() :Dn(0), Dm(0) {};
	Matrix(natu dn, natu dm);
	Matrix(twod matrix);
	Matrix(oned matrix, bite LC = true); //T����,F����

	
	static Matrix GetMove(sure var, natu d);//�Ʊ����
	static Matrix GetRotate(sure var, natu d);//�������
	static Matrix GetFlexible(sure var, natu d);//�ӱ����
	static Matrix GetTwist(sure var, natu d);//Ť�����

	natu GetDn() { return Dn; };
	natu GetDm() { return Dm; };


	twod GetDetemat() { return mat; };
	void SetMatrix(twod dete);
	void SetMatrix(measure mea);
	void SetMatrix(measure mea, natu dn, natu dm) { mat[dn][dm] = mea; };

	bite SetMatrixLine(oned data, natu dn);
	bite SetMatrixColu(oned data, natu dm);
	bite SetMatrixLine(Vector vec, natu dn);
	bite SetMatrixColu(Vector vec, natu dm);

	Vector GetLineVector(natu dn);
	Vector GetColuVector(natu dm);

	measure GetMatr(natu dn, natu dm) { return mat[dn][dm]; };
	measure GetDete();							//�õ�����ʽ��ֵ

	Matrix GetMatE();							//��λ����
	Matrix GetTraMat();							//ת�þ���
	Matrix GetAdjMat();							//�������
	Matrix GetInvMat();							//�����

	Matrix Matdelline(natu n = 0);				//ɾ������n��
	Matrix Matdelcolu(natu m = 0);				//ɾ������m��
	Matrix Matdellc(natu n = 0, natu m = 0);	//ɾ������n��m��
	Matrix Matmer(const Matrix matrix, bite ft);		//���������ft=1/����ft=0�ϲ�
	Matrix Matpar(natu n1, natu m1, natu n2, natu m2);	//��ȡ����(n1,m1)��(n2,m2)����
	
	oned& operator[] (const natu& n);
	Matrix operator = (const Matrix matrix);
	bite operator == (const Matrix matrix);
	bite operator != (const Matrix matrix);


	Matrix operator += (const measure mea) { return *this = *this + mea; };
	Matrix operator -= (const measure mea) { return *this = *this - mea; };
	Matrix operator *= (const measure mea) { return *this = *this * mea; };
	Matrix operator /= (const measure mea) { return *this = *this / mea; };

	Matrix operator += (const Matrix matrix) { return *this = *this + matrix; };
	Matrix operator -= (const Matrix matrix) { return *this = *this - matrix; };
	Matrix operator *= (const Matrix matrix) { return *this = *this * matrix; };
	Matrix operator /= (const Matrix matrix) { return *this = *this / matrix; };

	friend Matrix operator + (const Matrix& A, const Matrix& B);
	friend Matrix operator - (const Matrix& A, const Matrix& B);
	friend Matrix operator * (const Matrix& A, const Matrix& B);
	friend Matrix operator / (const Matrix& A, const Matrix& B);

	friend Matrix operator + (const measure& a, const Matrix& B);
	friend Matrix operator - (const measure& a, const Matrix& B);
	friend Matrix operator * (const measure& a, const Matrix& B);
	friend Matrix operator / (const measure& a, const Matrix& B);

	friend Matrix operator + (const Matrix& A, const measure& b);
	friend Matrix operator - (const Matrix& A, const measure& b);
	friend Matrix operator * (const Matrix& A, const measure& b);
	friend Matrix operator / (const Matrix& A, const measure& b);

	friend Matrix operator ^ (const Matrix& A, const integer n);
};

#endif // !UNIVERSE_MATH_MATRIX