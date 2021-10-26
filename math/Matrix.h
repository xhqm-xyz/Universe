#pragma once
#ifndef UNIVERSE_MATH_MATRIX
#define UNIVERSE_MATH_MATRIX
#include "Vector.h"

class Matrix
{
protected:
	dete mat;
	nume Dn;
	nume Dm;
	void Inti(nume dn, nume dm) {
		Dn = dn; Dm = dm;
		for (nume i = 0; i < Dn; i++) {
			vect v;
			mat.push_back(v);
			for (nume j = 0; j < Dm; j++)
				mat[i].push_back(0);
		}
	}
public:
	Matrix() :Dn(0), Dm(0) {};
	Matrix(nume dn, nume dm);
	Matrix(dete matrix);
	Matrix(vect matrix, bite LC = true); //T设行,F设列

		//三个移变矩阵
	static Matrix GetMoveX(sure var);
	static Matrix GetMoveY(sure var);
	static Matrix GetMoveZ(sure var);
	//三个旋变矩阵
	static Matrix GetRotateX(sure var);
	static Matrix GetRotateY(sure var);
	static Matrix GetRotateZ(sure var);
	//三个抻变矩阵
	static Matrix GetFlexibleX(sure var);
	static Matrix GetFlexibleY(sure var);
	static Matrix GetFlexibleZ(sure var);
	//三个扭变矩阵
	static Matrix GetTwistX(sure var) { return Matrix(3, 3); };
	static Matrix GetTwistY(sure var) { return Matrix(3, 3); };
	static Matrix GetTwistZ(sure var) { return Matrix(3, 3); };
	nume GetDn() { return Dn; };
	nume GetDm() { return Dm; };


	dete GetDetemat() { return mat; };
	void SetMatrix(dete dete);
	void SetMatrix(measure mea);
	void SetMatrix(measure mea, nume dn, nume dm) { mat[dn][dm] = mea; };

	bite SetMatrixLine(vect data, nume dn);
	bite SetMatrixColu(vect data, nume dm);
	bite SetMatrixLine(Vector vec, nume dn);
	bite SetMatrixColu(Vector vec, nume dm);

	Vector GetLineVector(nume dn);
	Vector GetColuVector(nume dm);

	measure GetMatr(nume dn, nume dm) { return mat[dn][dm]; };
	measure GetDete();							//得到行列式的值

	Matrix GetMatE();							//单位矩阵
	Matrix GetTraMat();							//转置矩阵
	Matrix GetAdjMat();							//伴随矩阵
	Matrix GetInvMat();							//逆矩阵

	Matrix Matdelline(nume n = 0);				//删除矩阵n行
	Matrix Matdelcolu(nume m = 0);				//删除矩阵m列
	Matrix Matdellc(nume n = 0, nume m = 0);	//删除矩阵n行m列
	Matrix Matmer(const Matrix matrix, bite ft);		//矩阵的行增ft=1/列增ft=0合并
	Matrix Matpar(nume n1, nume m1, nume n2, nume m2);	//截取矩阵(n1,m1)到(n2,m2)部分
	
	vect& operator[] (const nume& n);
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