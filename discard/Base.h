#pragma once
#include <vector>
#include "../tool/list.h"

/*
0b0000  0
0b0001  1
0b0010  2
0b0011  3
0b0100  4
0b0101  5
0b0110  6
0b0111  7
0b1000  8
0b1001  9
0b1010  无穷大 11

0b1011  . all
0b1100  - -1
0b1101  + 10
0b1110  左极限 12
0b1111  右极限 13
*/
struct base{
	base();
	base(const int& db);
	base(const base& db);

	unsigned car : 1;
	unsigned bit1 : 1;
	unsigned bit2 : 1;
	unsigned bit3 : 1; 
	unsigned bit4 : 1;

	base operator = (const int& db);
	base operator = (const base& db);
};//只允许Base类使用
bool operator== (const base& A, const base& B);
bool operator!= (const base& A, const base& B);
bool operator > (const base& A, const base& B);
bool operator < (const base& A, const base& B);
bool operator>= (const base& A, const base& B);
bool operator<= (const base& A, const base& B);

base operator>> (base& A, const int& i);
base operator<< (base& A, const int& i);

base operator + (const base& A, const base& B);
base operator - (const base& A, const base& B);

class Base
{
private:
	size num;
	base dat;
	Base* pnext = nullptr;
public:
	Base(base data = 0) :num(1), dat(data) {};
	~Base() { clear(); };

	Base* pop_back();
	Base* push_back();
	Base* push_back(base bas);
	size GetSize() { return num; };
	base GetData() { return dat; };
	void clear();
};

Base* Base::pop_back(){
	if (pnext == nullptr)
		return this;
	else {
		num--;
		if (pnext->pnext == nullptr) {
			delete pnext;
			return this;
		}else
			return pnext->pop_back();
	}
}

Base* Base::push_back() {
	if (pnext == nullptr)
		return this;
	else
		return pnext->push_back();
}

Base* Base::push_back(base bas) {
	num++;
	if (pnext == nullptr)
		return pnext = new Base(bas);
	else
		return pnext->push_back(bas);
}

void Base::clear(){
	for (;;)
		if (pop_back() == this)
			return;
};