#include "measure.h"


sure complex::GetModulus(){
	sure Modulus = mea * mea;
	for (nume n = 0; n < _i.size(); n++)
		Modulus += _i[n] * _i[n];
	return sqrt(Modulus);
}

complex complex::GetConjugate() {
	complex conjugate(mea, _i);
	for (nume n = 0; n < _i.size(); n++)
		conjugate._i[n] = -_i[n];
	return conjugate;
}

complex complex::operator=(const complex& ijk) {
	complex _ijk(ijk.mea, ijk._i);
	mea = _ijk.mea;
	for (nume n = 0; n < _ijk._i.size(); n++)
		_i.push_back(_ijk._i[n]);
	return *this;
}

bite operator==(const complex& i, const complex& j){
	complex _i(i.mea, i._i);
	complex _j(j.mea, j._i);
	if (_i.mea != _j.mea)
		return false;
	nume isize = _i._i.size();
	nume jsize = _j._i.size();
	nume dimMax = isize > jsize ? isize : jsize;
	for (nume n = 0; n < dimMax; n++)
		if (isize > jsize)
			if (n < jsize) {
				if (_i._i[n] != _j._i[n])
					return false;
			}
			else {
				if (_i._i[n] != 0)
					return false;
			}
		else
			if (n < isize) {
				if (_i._i[n] != _j._i[n])
					return false;
			}
			else {
				if (_j._i[n] != 0)
					return false;
			}
	return true;
}

bite operator!=(const complex& i, const complex& j){
	if (i == j)
		return false;
	return true;
}

complex operator + (const plex& Ju) {
	complex _ju(+Ju.mea, Ju._i);
	for (nume n = 0; n < _ju._i.size(); n++)
		_ju._i[n] = +_ju._i[n];
	return _ju;
}

complex operator - (const plex& To) {
	complex _to(-To.mea, To._i);
	for (nume n = 0; n < _to._i.size(); n++)
		_to._i[n] = -_to._i[n];
	return _to;
}

complex operator+(const complex& i, const complex& j) {
	complex res;
	complex _i(i.mea, i._i);
	complex _j(j.mea, j._i);
	res.mea = _i.mea + _j.mea;
	res._i[0] = _i._i[0] + _j._i[0];
	nume dimMAX = _i._i.size() > _j._i.size() ? _i._i.size() : _j._i.size();
	nume dimMIN = _i._i.size() < _j._i.size() ? _i._i.size() : _j._i.size();
	if (_i._i.size() > _j._i.size())
		for (nume n = 1; n < dimMAX; n++)
			if (n < dimMIN)
				res._i.push_back(_i._i[n] + _j._i[n]);
			else
				res._i.push_back(_i._i[n] + 0);
	if (_i._i.size() < _j._i.size())
		for (nume n = 1; n < dimMAX; n++)
			if (n < dimMIN)
				res._i.push_back(_i._i[n] + _j._i[n]);
			else
				res._i.push_back(0 + _j._i[n]);
	if (_i._i.size() == _j._i.size())
		for (nume n = 1; n < dimMAX; n++)
			res._i.push_back(_i._i[n] + _j._i[n]);
	return res;
}

complex operator-(const complex& i, const complex& j) {
	complex res;
	complex _i(i.mea, i._i);
	complex _j(j.mea, j._i);
	res.mea = _i.mea - _j.mea;
	res._i[0] = _i._i[0] - _j._i[0];
	nume dimMAX = _i._i.size() > _j._i.size() ? _i._i.size() : _j._i.size();
	nume dimMIN = _i._i.size() < _j._i.size() ? _i._i.size() : _j._i.size();
	if (_i._i.size() > _j._i.size())
		for (nume n = 1; n < dimMAX; n++)
			if (n < dimMIN)
				res._i.push_back(_i._i[n] - _j._i[n]);
			else
				res._i.push_back(_i._i[n] - 0);
	if (_i._i.size() < _j._i.size())
		for (nume n = 1; n < dimMAX; n++)
			if (n < dimMIN)
				res._i.push_back(_i._i[n] - _j._i[n]);
			else
				res._i.push_back(0 - _j._i[n]);
	if (_i._i.size() == _j._i.size())
		for (nume n = 1; n < dimMAX; n++)
			res._i.push_back(_i._i[n] - _j._i[n]);
	return res;
}

complex operator*(const complex& i, const complex& j) {
	complex res;
	complex _i(i.mea, i._i);
	complex _j(j.mea, j._i);
	nume dimMAX = _i._i.size() > _j._i.size() ? _i._i.size() : _j._i.size();
	nume dimMIN = _i._i.size() < _j._i.size() ? _i._i.size() : _j._i.size();
	res.mea = _i.mea * _j.mea - _i._i[0] * _j._i[0];
	for (nume n = 1; n < dimMIN; n++)
		res.mea -= (_i._i[n] * _j._i[n]);
	res._i[0] = _i.mea * _j._i[0] + _j.mea * _i._i[0];
	for (nume n = 1; n < dimMIN; n++)
		res._i.push_back(_i.mea * _j._i[n] + _j.mea * _i._i[n]);
	return res;
}

complex operator/(const complex& i, const complex& j){
	complex res;
	complex _i(i.mea, i._i);
	complex _j(j.mea, j._i);
	res = _i * _j.GetConjugate();
	sure div = (_j * _j.GetConjugate()).mea;
	res.mea /= div;
	for (nume n = 0; n < res._i.size(); n++)
		res._i[n] /= div;
	return res;
}

complex operator^(const complex& p, const integer n){
	complex res((inte)1);
	inte _n = n;
	if (_n > 0)
		for (nume i = 0; i < _n; i++)
			res *= p;
	if (_n < 0) {
		_n = -_n;
		for (nume i = 0; i < _n; i++)
			res /= p;
	}return res;
}

inte portion::Minmul(inte n, inte m){
	return ((n * m) / Maxdiv(n, m));
}

inte portion::Maxdiv(inte n, inte m){
	if (n < 0)
		n = -n;
	if (m < 0)
		m = -m;
	if (n == 0 && m == 0)
		return 1;
	if (n == 0)
		return m;
	if (m == 0)
		return n;
	nume i = 0;
	do {
		if (n % 2 == 0 && m % 2 == 0) {
			i++;
			n /= 2;
			m /= 2;
		}
		else
			break;
	} while (true);
	do {
		if (n == m) {
			if (i == 0)
				n *= 1;
			else
				for (nume j = 0; j < i; j++)
					n *= 2;
			return n;
		}
		else if (n > m)
			n = n - m;
		else if (n < m)
			m = m - n;
		else
			return 1;
	} while (true);
}

sure portion::ToSure(port Port) {
	return ((sure)Port._mo / (sure)Port._de);
}

port portion::ToPort(sure Sure) {
	port Port(Sure * 1000000000000000, 1000000000000000);
	Port.reduce();
	return Port;
}


void portion::unredu(natu red){
	_mo *= red;
	_de *= red;
	if (_de == 0)
		_inf = true;
}

void portion::reduce(natu ure){
	if (ure != 0){
		_mo /= ure;
		_de /= ure;
	}else {
		ure = Maxdiv(_mo, _de);
		_mo /= ure;
		_de /= ure;
	}
}

void portion::recport() {
	*this = recport(*this);
}

port portion::recport(port recPort) {
	return portion(recPort._de, recPort._mo);
}

portion portion::operator=(const inte& get){
	_de = 1;
	_mo = get;
	_inf = false;
	return *this;
}

portion portion::operator=(const sure& get){
	*this =  ToPort(get);
	return *this;
}

portion portion::operator=(const port& get){
	_de = get._de;
	_mo = get._mo;
	_inf = get._inf;
	return *this;
}

bite portion::operator==(const port& por){
	if ((*this - por)._mo == 0)
		return true;
	return false;
}

bite portion::operator!=(const port& por){
	if ((*this - por)._mo != 0)
		return true;
	return false;
}

portion operator + (const port& Ju){
	port _Ju(+Ju._mo, Ju._de);
	return _Ju;
}

portion operator - (const port& To){
	port _To(-To._mo, To._de);
	return _To;
}

bite operator>(const port& A, const port& B){
	if ((A - B)._mo > 0)
		return true;
	return false;
}

bite operator<(const port& A, const port& B){
	if ((A - B)._mo < 0)
		return true;
	return false;
}

bite operator>=(const port& A, const port& B){
	if ((A - B)._mo >= 0)
		return true;
	return false;
}

bite operator<=(const port& A, const port& B){
	if ((A - B)._mo <= 0)
		return true;
	return false;
}


portion operator + (const port& _X, const port& _Y){
	portion add(_X._mo * _Y._de + _X._de * _Y._mo, _X._de * _Y._de);
	if (add._de == 0)
		add._inf = true;
	add.reduce();
	return add;
}

portion operator - (const port& _X, const port& _Y){
	portion sub(_X._mo * _Y._de - _X._de * _Y._mo, _X._de * _Y._de);
	if (sub._de == 0)
		sub._inf = true;
	sub.reduce();
	return sub;
}

portion operator * (const port& _X, const port& _Y){
	portion mul(_X._mo * _Y._mo, _X._de * _Y._de);
	if (mul._de == 0)
		mul._inf = true;
	mul.reduce();
	return mul;
}

portion operator / (const port& _X, const port& _Y) {
	portion div(_X._mo * _Y._de, _X._de * _Y._mo);
	if (div._de == 0)
		div._inf = true;
	div.reduce();
	return div;
}

portion operator^(const portion& p, const integer n){
	portion res((inte)1);
	inte _n = n;
	if (_n > 0)
		for (nume i = 0; i < _n; i++)
			res *= p;
	if (_n < 0) {
		_n = -_n;
		for (nume i = 0; i < _n; i++)
			res /= p;
	}return res;
}
