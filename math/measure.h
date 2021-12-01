#pragma once
#include "../DEFMACRO"
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
constexpr auto XPi = 3.141592653578;
constexpr auto XPRECI = 0.00000000001;
#define XMAX(val1, val2) (val1 > val2) ? val1 : val2
#define XMIN(val1, val2) (val1 < val2) ? val1 : val2
#define XEqual(val1, val2, preci) ((1 + preci >= (val1 / val2) && (val1 / val2) >= 1 - preci)) ? true : false
#define XEqualDouble(val1, val2) XEqual(val1, val2, XPRECI)

typedef unsigned long long natural;	//��Ȼ��
typedef long long integer;			//����
typedef double measure;				//ʵ��
typedef bool bytebit;				//��ֵ
typedef char symbols;				//����
class portion;						//����
class complex;						//����

typedef natural natu;	//��Ȼ��
typedef integer inte;	//����
typedef measure sure;	//ʵ��
typedef bytebit bite;	//���
typedef symbols sign;	//����
typedef portion port;	//����
typedef complex plex;	//����

#define Oned(_T) vector<_T>
#define Twod(_T) vector<vector<_T>>
#define Thrd(_T) vector<vector<vector<_T>>>
#define Foud(_T) vector<vector<vector<vector<_T>>>>

typedef Oned(natural) onenatu;
typedef Twod(natural) twonatu;
typedef Thrd(natural) thrnatu;
typedef Foud(natural) founatu;

typedef Oned(integer) oneinte;
typedef Twod(integer) twointe;
typedef Thrd(integer) thrinte;
typedef Foud(integer) fouinte;

typedef Oned(measure) onesure;
typedef Twod(measure) twosure;
typedef Thrd(measure) thrsure;
typedef Foud(measure) fousure;

typedef Oned(symbols) onesign;
typedef Twod(symbols) twosign;
typedef Thrd(symbols) thrsign;
typedef Foud(symbols) fousign;

typedef Oned(portion) oneport;
typedef Twod(portion) twoport;
typedef Thrd(portion) thrport;
typedef Foud(portion) fouport;

typedef Oned(complex) oneplex;
typedef Twod(complex) twoplex;
typedef Thrd(complex) thrplex;
typedef Foud(complex) fouplex;

typedef onesure oned;
typedef twosure twod;
typedef thrsure thrd;
typedef fousure foud;

#define Vect Oned
#define Dete Twod
#define Volu Thrd



class portion
{
protected:
	inte _mo;
	natu _de;
	bite _inf = false;
public:
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
protected:
	sure mea;
	oned _i;
public:
	complex(sure me, oned i) :mea(me) {
		if (i.size() == 0)
			_i.push_back(0);
		for (natu n = 0; n < i.size(); n++)
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

	friend complex operator + (const complex&);
	friend complex operator - (const complex&);

	friend complex operator + (const complex& i, const complex& j);
	friend complex operator - (const complex& i, const complex& j);
	friend complex operator * (const complex& i, const complex& j);
	friend complex operator / (const complex& i, const complex& j);

	complex operator += (const complex& Plex) { return *this = *this + Plex; };
	complex operator -= (const complex& Plex) { return *this = *this - Plex; };
	complex operator *= (const complex& Plex) { return *this = *this * Plex; };
	complex operator /= (const complex& Plex) { return *this = *this / Plex; };

	friend complex operator^ (const complex& p, const integer n);
};

#endif // !UNIVERSE_MEASURE