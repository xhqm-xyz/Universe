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

	SMatrix delline(int n);//n�±�
	SMatrix delcolu(int m);//m�±�
	SMatrix dele(int n, int m);

	double GetDete(int n = 3);							//�õ�����ʽ��ֵ

	SMatrix GetInvMat(int n = 3);							//�����	
	SMatrix GetTraMat(int n = 3);							//ת�þ���
	SMatrix GetAdjMat(int n = 3);							//�������

	static SMatrix GetMatE();					//��λ����
	static SMatrix GetMove(double varX, double varY, double varZ);		//�Ʊ����
	static SMatrix GetFlexible(double varX, double varY, double varZ);	//�ӱ����
	//�����������
	static SMatrix GetRotateX(double var);
	static SMatrix GetRotateY(double var);
	static SMatrix GetRotateZ(double var);
	//����Ť�����
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