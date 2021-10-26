#pragma once
#include "measure.h"
#include "Vector.h"
typedef std::vector<complex> Line;
typedef std::vector<Line> Dete;

class Matrix
{
protected:
	Dete mat;
	size Dn;
	size Dm;
public:
	Matrix(Dete matrix);
	Matrix(Line matrix);
	Matrix(Vector matrix);
	Matrix(size dn = 0, size dm = 0);

	void SetMatrix(Dete dete);
	void SetMatrix(complex mea);
	void SetMatrix(complex mea, size dn, size dm) { mat[dn][dm] = mea; };

	bool SetMatrixLine(Line data, size dn);
	bool SetMatrixColu(Line data, size dm);
	bool SetMatrixLine(Vector vec, size dn);
	bool SetMatrixColu(Vector vec, size dm);

	Vector GetLineVector(size dn);
	Vector GetColuVector(size dm);

	complex GetMatr(size dn, size dm) { return mat[dn][dm]; };
	complex GetDete();							//�õ�����ʽ��ֵ

	Matrix GetMatE();							//��λ����
	Matrix GetTraMat();							//ת�þ���
	Matrix GetAdjMat();							//�������
	Matrix GetInvMat();							//�����

	Matrix Matdelline(size n = 0);				//ɾ������n��
	Matrix Matdelcolu(size m = 0);				//ɾ������m��
	Matrix Matdellc(size n = 0, size m = 0);	//ɾ������n��m��
	Matrix Matmer(const Matrix matrix, bool ft);		//���������ft=1/����ft=0�ϲ�
	Matrix Matpar(size n1, size m1, size n2, size m2);	//��ȡ����(n1,m1)��(n2,m2)����
	

	Matrix operator = (const Matrix matrix);
	bool operator == (const Matrix matrix);
	bool operator != (const Matrix matrix);


	Matrix operator += (const complex mea) { return *this = *this + mea; };
	Matrix operator -= (const complex mea) { return *this = *this - mea; };
	Matrix operator *= (const complex mea) { return *this = *this * mea; };
	Matrix operator /= (const complex mea) { return *this = *this / mea; };

	Matrix operator += (const Matrix matrix) { return *this = *this + matrix; };
	Matrix operator -= (const Matrix matrix) { return *this = *this - matrix; };
	Matrix operator *= (const Matrix matrix) { return *this = *this * matrix; };
	Matrix operator /= (const Matrix matrix) { return *this = *this / matrix; };

	friend Matrix operator + (const Matrix& A, const Matrix& B);
	friend Matrix operator - (const Matrix& A, const Matrix& B);
	friend Matrix operator * (const Matrix& A, const Matrix& B);
	friend Matrix operator / (const Matrix& A, const Matrix& B);

	friend Matrix operator + (const complex& a, const Matrix& B);
	friend Matrix operator - (const complex& a, const Matrix& B);
	friend Matrix operator * (const complex& a, const Matrix& B);
	friend Matrix operator / (const complex& a, const Matrix& B);

	friend Matrix operator + (const Matrix& A, const complex& b);
	friend Matrix operator - (const Matrix& A, const complex& b);
	friend Matrix operator * (const Matrix& A, const complex& b);
	friend Matrix operator / (const Matrix& A, const complex& b);

	friend Matrix operator ^ (const Matrix& A, const integer n);
};