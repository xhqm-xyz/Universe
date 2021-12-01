#pragma once
#ifndef UNIVERSE_SPACE_SMATRIX
#define UNIVERSE_SPACE_SMATRIX
#include "Smath.h"
#include "SVector.h"
class SMatrix
{
public:
	SMatrix(double var = 0);
	
	void copy(SMatrix res, int n, int m);
	void fill(double var,int n, int m);
	bool fillline(int n, SVector vet);
	bool fillcove(int m, SVector vet);

	SMatrix delline(int n);//n下标
	SMatrix delcolu(int m);//m下标
	SMatrix dele(int n, int m);

	double GetDete(int n = 3);							//得到行列式的值

	SMatrix GetInvMat(int n = 3);							//逆矩阵	
	SMatrix GetTraMat(int n = 3);							//转置矩阵
	SMatrix GetAdjMat(int n = 3);							//伴随矩阵

	static SMatrix GetMatE();					//单位矩阵
	static SMatrix GetMove(double varX, double varY, double varZ);		//移变矩阵
	static SMatrix GetFlexible(double varX, double varY, double varZ);	//抻变矩阵
	//三个旋变矩阵
	static SMatrix GetRotateX(double var);
	static SMatrix GetRotateY(double var);
	static SMatrix GetRotateZ(double var);
	//三个扭变矩阵
	static SMatrix GetTwistX(double var);
	static SMatrix GetTwistY(double var);
	static SMatrix GetTwistZ(double var);

	double* operator[](const int n) { return _vars[n]; };
	SMatrix operator = (const SMatrix matrix);

	friend SMatrix operator + (const SMatrix& A, const SMatrix& B);
	friend SMatrix operator - (const SMatrix& A, const SMatrix& B);
	friend SMatrix operator * (const SMatrix& A, const SMatrix& B);
	friend SMatrix operator / (const SMatrix& A, const SMatrix& B);

	friend SMatrix operator + (const double& a, const SMatrix& B);
	friend SMatrix operator - (const double& a, const SMatrix& B);
	friend SMatrix operator * (const double& a, const SMatrix& B);
	friend SMatrix operator / (const double& a, const SMatrix& B);

	friend SMatrix operator + (const SMatrix& A, const double& b);
	friend SMatrix operator - (const SMatrix& A, const double& b);
	friend SMatrix operator * (const SMatrix& A, const double& b);
	friend SMatrix operator / (const SMatrix& A, const double& b);
	friend SMatrix operator ^ (const SMatrix& A, int n);

	friend SVector operator * (SVector a, const SMatrix& B);
	friend SVector operator * (const SMatrix& A, SVector b);
protected:
	double _vars[3][3];
};
#endif // !UNIVERSE_SPACE_SMATRIX