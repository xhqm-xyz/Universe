#pragma once
#ifndef UNIVERSE_MEASURE
#define UNIVERSE_MEASURE
#define ONED 1
#define TWOD 2
#define THRD 3
#define FOUD 4
#include <cmath>
#include <ctime>
#include <thread>
#include <map>
#include <list>
#include <vector>
#include <iostream>
using namespace std;
constexpr auto Pi = 3.141592653578;
constexpr auto PRECI = 0.00000000001;

typedef unsigned long long counter;	//������
typedef unsigned long long natural;	//��Ȼ��
typedef long long integer;			//����
typedef double measure;				//ʵ��
typedef bool bytebit;				//��ֵ
typedef char symbols;				//����
class portion;						//����
class complex;						//����

typedef counter nume;	//������
typedef natural natu;	//��Ȼ��
typedef integer inte;	//����
typedef measure sure;	//ʵ��
typedef bytebit bite;	//���
typedef symbols sign;	//����
typedef portion port;	//����
typedef complex plex;	//����

#define Oned(_T) vector<_T>
#define Vect(_T) vector<_T>
#define Twod(_T) vector<vector<_T>>
#define Dete(_T) vector<vector<_T>>
#define Thrd(_T) vector<vector<vector<_T>>>
#define Volu(_T) vector<vector<vector<_T>>>
#define Foud(_T) vector<vector<vector<vector<_T>>>>

typedef vector<natural> onenatu;
typedef vector<onenatu> twonatu;
typedef vector<twonatu> thrnatu;
typedef vector<thrnatu> founatu;
typedef onenatu::iterator one_natuiter;
typedef twonatu::iterator two_natuiter;
typedef thrnatu::iterator thr_natuiter;
typedef founatu::iterator fou_natuiter;

typedef vector<integer> oneinte;
typedef vector<oneinte> twointe;
typedef vector<twointe> thrinte;
typedef vector<thrinte> fouinte;
typedef oneinte::iterator one_inteiter;
typedef twointe::iterator two_inteiter;
typedef thrinte::iterator thr_inteiter;
typedef fouinte::iterator fou_inteiter;

typedef vector<measure> onesure;
typedef vector<onesure> twosure;
typedef vector<twosure> thrsure;
typedef vector<thrsure> fousure;
typedef onesure::iterator one_sureiter;
typedef twosure::iterator two_sureiter;
typedef thrsure::iterator thr_sureiter;
typedef fousure::iterator fou_sureiter;

typedef vector<symbols> onesign;
typedef vector<onesign> twosign;
typedef vector<twosign> thrsign;
typedef vector<thrsign> fousign;
typedef onesign::iterator one_signiter;
typedef twosign::iterator two_signiter;
typedef thrsign::iterator thr_signiter;
typedef fousign::iterator fou_signiter;

typedef vector<portion> oneport;
typedef vector<oneport> twoport;
typedef vector<twoport> thrport;
typedef vector<thrport> fouport;
typedef oneport::iterator one_portiter;
typedef twoport::iterator two_portiter;
typedef thrport::iterator thr_portiter;
typedef fouport::iterator fou_portiter;

typedef vector<complex> oneplex;
typedef vector<oneplex> twoplex;
typedef vector<twoplex> thrplex;
typedef vector<thrplex> fouplex;
typedef oneplex::iterator one_plexiter;
typedef twoplex::iterator two_plexiter;
typedef thrplex::iterator thr_plexiter;
typedef fouplex::iterator fou_plexiter;

typedef onesure oned;
typedef onesure vect;
typedef twosure twod;
typedef twosure dete;
typedef thrsure thrd;
typedef thrsure volu;
typedef fousure foud;

class portion
{
protected:
	inte _mo;
	natu _de;
	bite _inf = false;
public:
	portion(sure po) :_de(1) { *this = ToPort(po); };
	portion(inte mo = 0, inte de = 1) {
		if (de > 0) {
			_mo = mo;
			_de = de;
		}
		if (de < 0) {
			_mo = -mo;
			_de = -de;
		}
		if (_de == 0) {
			_mo = mo;
			_de = de;
			_inf = true;
		}reduce();
	};
	void recport();						//����
	static port recport(port recPort);	//����
	static inte Minmul(inte n, inte m);	//��С������
	static inte Maxdiv(inte n, inte m);	//���Լ��
	static sure ToSure(port Port);	//����ת���
	static port ToPort(sure Sure);	//���ת����
	void unredu(natu red = 1);	//��ȱ任
	void reduce(natu ure = 0);	//Լ�ֱ任
	inte getmo() { return _mo; };
	inte getde() { return _de; };

	portion operator = (const inte& get);
	portion operator = (const sure& get);
	portion operator = (const port& get);

	bite operator== (const port& por);
	bite operator!= (const port& por);

	friend portion operator + (const port&);
	friend portion operator - (const port&);

	friend bite operator > (const port& A, const port& B);
	friend bite operator < (const port& A, const port& B);
	friend bite operator>= (const port& A, const port& B);
	friend bite operator<= (const port& A, const port& B);

	friend portion operator + (const port&, const port&);
	friend portion operator - (const port&, const port&);
	friend portion operator * (const port&, const port&);
	friend portion operator / (const port&, const port&);

	portion operator += (const port& Port) { return *this = *this + Port; };
	portion operator -= (const port& Port) { return *this = *this - Port; };
	portion operator *= (const port& Port) { return *this = *this * Port; };
	portion operator /= (const port& Port) { return *this = *this / Port; };
};


class complex
{
public:
	sure mea;
	oned _i;

	complex(sure me, oned i) :mea(me) {
		if (i.size() == 0)
			_i.push_back(0);
		for (nume n = 0; n < i.size(); n++)
			_i.push_back(i[n]);
	};
	complex(sure me = 0, sure i = 0) :mea(me) {
		_i.push_back(i);
	};
	complex(sure me, sure i, sure j) :mea(me) {
		_i.push_back(i);
		_i.push_back(j);
	};
	complex(sure me, sure i, sure j, sure k) :mea(me) {
		_i.push_back(i);
		_i.push_back(j);
		_i.push_back(k);
	};
	~complex() { };

	sure GetModulus();			//�õ�������ģ
	complex GetConjugate();

	complex operator = (const complex& ijk);
	friend bite operator == (const complex& i, const complex& j);
	friend bite operator != (const complex& i, const complex& j);

	friend complex operator + (const plex&);
	friend complex operator - (const plex&);

	friend complex operator + (const complex& i, const complex& j);
	friend complex operator - (const complex& i, const complex& j);
	friend complex operator * (const complex& i, const complex& j);
	friend complex operator / (const complex& i, const complex& j);

	complex operator += (const plex& Plex) { return *this = *this + Plex; };
	complex operator -= (const plex& Plex) { return *this = *this - Plex; };
	complex operator *= (const plex& Plex) { return *this = *this * Plex; };
	complex operator /= (const plex& Plex) { return *this = *this / Plex; };

	friend complex operator^ (const complex& p, const integer n);
};

#endif // !UNIVERSE_MEASURE