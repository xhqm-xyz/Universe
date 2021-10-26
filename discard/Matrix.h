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
	complex GetDete();							//得到行列式的值

	Matrix GetMatE();							//单位矩阵
	Matrix GetTraMat();							//转置矩阵
	Matrix GetAdjMat();							//伴随矩阵
	Matrix GetInvMat();							//逆矩阵

	Matrix Matdelline(size n = 0);				//删除矩阵n行
	Matrix Matdelcolu(size m = 0);				//删除矩阵m列
	Matrix Matdellc(size n = 0, size m = 0);	//删除矩阵n行m列
	Matrix Matmer(const Matrix matrix, bool ft);		//矩阵的行增ft=1/列增ft=0合并
	Matrix Matpar(size n1, size m1, size n2, size m2);	//截取矩阵(n1,m1)到(n2,m2)部分
	

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