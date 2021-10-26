#ifndef UNIVERSE_MATH_CMATRIX
#define UNIVERSE_MATH_CMATRIX
#pragma once
#include "element.h"
//constexpr auto Pi = 3.141592653578;
//constexpr auto PRECI = 0.00000000001;
class CMatrix
{
public:
	CMatrix(int n, int m, double var = 0);
	CMatrix(double var = 0);
	
	void fill(double var);
	bool fillline(int n, double var);
	bool fillcove(int m, double var);
	void copy(CMatrix mat,int n = 4,int m = 4);
	CMatrix delline(int n);//n下标
	CMatrix delcolu(int m);//m下标
	CMatrix dele(int n, int m);

	int Get_n() { return _n; }
	int Get_m() { return _m; }
	void Set_n(int n) { _n = n; setnm(); }
	void Set_m(int m) { _m = m; setnm(); }
	void Get_nm(int& n, int& m) { n = _n; m = _m; }
	void Set_nm(int n, int m) { _n = n; _m = m; setnm(); }

	double GetDete();							//得到行列式的值

	CMatrix GetMatE();								//单位矩阵
	CMatrix GetTraMat();							//转置矩阵
	CMatrix GetAdjMat();							//伴随矩阵
	CMatrix GetInvMat();							//逆矩阵

	//三个移变矩阵
	static CMatrix GetMoveX(double var);
	static CMatrix GetMoveY(double var);
	static CMatrix GetMoveZ(double var);
	//三个旋变矩阵
	static CMatrix GetRotateX(double var);
	static CMatrix GetRotateY(double var);
	static CMatrix GetRotateZ(double var);
	//三个抻变矩阵
	static CMatrix GetFlexibleX(double var);
	static CMatrix GetFlexibleY(double var);
	static CMatrix GetFlexibleZ(double var);
	//三个扭变矩阵
	static CMatrix GetTwistX(double var);
	static CMatrix GetTwistY(double var);
	static CMatrix GetTwistZ(double var);

	double* operator[](const int n) { return _vars[n]; };

	CMatrix operator = (const CMatrix matrix);
	bool operator == (const CMatrix matrix);
	bool operator != (const CMatrix matrix);

	friend CMatrix operator + (const CMatrix& A, const CMatrix& B);
	friend CMatrix operator - (const CMatrix& A, const CMatrix& B);
	friend CMatrix operator * (const CMatrix& A, const CMatrix& B);
	friend CMatrix operator / (const CMatrix& A, const CMatrix& B);

	friend CMatrix operator + (const double& a, const CMatrix& B);
	friend CMatrix operator - (const double& a, const CMatrix& B);
	friend CMatrix operator * (const double& a, const CMatrix& B);
	friend CMatrix operator / (const double& a, const CMatrix& B);

	friend CMatrix operator + (const CMatrix& A, const double& b);
	friend CMatrix operator - (const CMatrix& A, const double& b);
	friend CMatrix operator * (const CMatrix& A, const double& b);
	friend CMatrix operator / (const CMatrix& A, const double& b);
	friend CMatrix operator ^ (const CMatrix& A, int n);
protected:
	void setnm();
	void setnm(int& n, int& m);

	int _n = 4;
	int _m = 4;
	double _vars[4][4];
};
#endif // !UNIVERSE_MATH_CMATRIX
