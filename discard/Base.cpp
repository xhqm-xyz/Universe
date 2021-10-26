#include "Base.h"


base::base(){
	bit1 = 0b0;
	bit2 = 0b0;
	bit3 = 0b0;
	bit4 = 0b0;
}

base::base(const int& db){
	if (0 <= db && db <= 9) {  //1-9
		bit1 = (db >> 0) % 2;
		bit2 = (db >> 1) % 2;
		bit3 = (db >> 2) % 2;
		bit4 = (db >> 3) % 2;
	}
	else if (-1 == db) {  //-
		bit1 = 0b1;
		bit2 = 0b1;
		bit3 = 0b0;
		bit4 = 0b0;
	}
	else if (10 == db) {  //+
		bit1 = 0b1;
		bit2 = 0b1;
		bit3 = 0b0;
		bit4 = 0b1;
	}
	else if (11 == db) {  //无穷
		bit1 = 0b1;
		bit2 = 0b0;
		bit3 = 0b1;
		bit4 = 0b0;
	}
	else if (12 == db) {  //左极限
		bit1 = 0b1;
		bit2 = 0b1;
		bit3 = 0b1;
		bit4 = 0b0;
	}
	else if (13 == db) {  //右极限
		bit1 = 0b1;
		bit2 = 0b1;
		bit3 = 0b1;
		bit4 = 0b1;
	}
	else {  //.
		bit1 = 0b1;
		bit2 = 0b0;
		bit3 = 0b1;
		bit4 = 0b1;
	}
}

base::base(const base& db){
	bit1 = db.bit1;
	bit2 = db.bit2;
	bit3 = db.bit3;
	bit4 = db.bit4;
}

base base::operator=(const int& db){
	if (0 <= db && db <= 9) {  //1-9
		bit1 = (db >> 0) % 2;
		bit2 = (db >> 1) % 2;
		bit3 = (db >> 2) % 2;
		bit4 = (db >> 3) % 2;
	}
	else if (-1 == db) {  //-
		bit1 = 0b1;
		bit2 = 0b1;
		bit3 = 0b0;
		bit4 = 0b0;
	}
	else if (10 == db) {  //+
		bit1 = 0b1;
		bit2 = 0b1;
		bit3 = 0b0;
		bit4 = 0b1;
	}
	else if (11 == db) {  //无穷
		bit1 = 0b1;
		bit2 = 0b0;
		bit3 = 0b1;
		bit4 = 0b0;
	}
	else if (12 == db) {  //左极限
		bit1 = 0b1;
		bit2 = 0b1;
		bit3 = 0b1;
		bit4 = 0b0;
	}
	else if (13 == db) {  //右极限
		bit1 = 0b1;
		bit2 = 0b1;
		bit3 = 0b1;
		bit4 = 0b1;
	}
	else {  //.
		bit1 = 0b1;
		bit2 = 0b0;
		bit3 = 0b1;
		bit4 = 0b1;
	}return (*this);
}

base base::operator=(const base& db){
	bit1 = db.bit1;
	bit2 = db.bit2;
	bit3 = db.bit3;
	bit4 = db.bit4;
	return (*this);
}

bool operator==(const base& A, const base& B){
	if (!((!A.bit1 | B.bit1) & (A.bit1 | !B.bit1)))
		return false;
	if (!((!A.bit2 | B.bit2) & (A.bit2 | !B.bit2)))
		return false;
	if (!((!A.bit3 | B.bit3) & (A.bit3 | !B.bit3)))
		return false;
	if (!((!A.bit4 | B.bit4) & (A.bit4 | !B.bit4)))
		return false;
	return true;
}

bool operator!=(const base& A, const base& B){
	if (A == B)
		return false;
	return true;
}

bool operator>(const base& A, const base& B){
	if (!((!A.bit4 | B.bit4) & (A.bit4 | !B.bit4)))
		if (A.bit4 & 0b1)
			return true;
		else
			return false;
	if (!((!A.bit3 | B.bit3) & (A.bit3 | !B.bit3)))
		if (A.bit3 & 0b1)
			return true;
		else
			return false;
	if (!((!A.bit2 | B.bit2) & (A.bit2 | !B.bit2)))
		if (A.bit2 & 0b1)
			return true;
		else
			return false;
	if (!((!A.bit1 | B.bit1) & (A.bit1 | !B.bit1)))
		if (A.bit1 & 0b1)
			return true;
		else
			return false;
	return false;
}

bool operator<(const base& A, const base& B){
	if (!((!A.bit4 | B.bit4) & (A.bit4 | !B.bit4)))
		if (B.bit4 & 0b1)
			return true;
		else
			return false;
	if (!((!A.bit3 | B.bit3) & (A.bit3 | !B.bit3)))
		if (B.bit3 & 0b1)
			return true;
		else
			return false;
	if (!((!A.bit2 | B.bit2) & (A.bit2 | !B.bit2)))
		if (B.bit2 & 0b1)
			return true;
		else
			return false;
	if (!((!A.bit1 | B.bit1) & (A.bit1 | !B.bit1)))
		if (B.bit1 & 0b1)
			return true;
		else
			return false;
	return false;
}

bool operator>=(const base& A, const base& B){
	if (!((!A.bit4 | B.bit4) & (A.bit4 | !B.bit4)))
		if (A.bit4 & 0b1)
			return true;
		else
			return false;
	if (!((!A.bit3 | B.bit3) & (A.bit3 | !B.bit3)))
		if (A.bit3 & 0b1)
			return true;
		else
			return false;
	if (!((!A.bit2 | B.bit2) & (A.bit2 | !B.bit2)))
		if (A.bit2 & 0b1)
			return true;
		else
			return false;
	if (!((!A.bit1 | B.bit1) & (A.bit1 | !B.bit1)))
		if (A.bit1 & 0b1)
			return true;
		else
			return false;
	return true;
}

bool operator<=(const base& A, const base& B){
	if (!((!A.bit4 | B.bit4) & (A.bit4 | !B.bit4)))
		if (B.bit4 & 0b1)
			return true;
		else
			return false;
	if (!((!A.bit3 | B.bit3) & (A.bit3 | !B.bit3)))
		if (B.bit3 & 0b1)
			return true;
		else
			return false;
	if (!((!A.bit2 | B.bit2) & (A.bit2 | !B.bit2)))
		if (B.bit2 & 0b1)
			return true;
		else
			return false;
	if (!((!A.bit1 | B.bit1) & (A.bit1 | !B.bit1)))
		if (B.bit1 & 0b1)
			return true;
		else
			return false;
	return true;
}

base operator>>(base& A, const int& i){
	for (int j = 0; j < i; j++) {
		A.bit1 = A.bit2;
		A.bit2 = A.bit3;
		A.bit3 = A.bit4;
		A.bit4 = 0b0;
	}return A;
}

base operator<<(base& A, const int& i){
	for (int j = 0; j < i; j++) {
		A.bit1 = 0b0;
		A.bit2 = A.bit1;
		A.bit3 = A.bit2;
		A.bit4 = A.bit3;
	}return A;
}

base operator+(const base& A, const base& B) {
	base C;
	C.bit1 = !((!A.bit1 | B.bit1) & (A.bit1 | !B.bit1));
	C.bit1 = !((!C.bit1 | C.car) & (C.bit1 | !C.car));
	if (A.bit1 & 0b1)
		C.car = 0b1;
	C.bit2 = !((!A.bit2 | B.bit2) & (A.bit2 | !B.bit2));
	C.bit2 = !((!C.bit2 | C.car) & (C.bit2 | !C.car));
	if (A.bit2 & 0b1)
		C.car = 0b1;
	C.bit3 = !((!A.bit3 | B.bit3) & (A.bit3 | !B.bit3));
	C.bit3 = !((!C.bit3 | C.car) & (C.bit3 | !C.car));
	if (A.bit3 & 0b1)
		C.car = 0b1;
	C.bit4 = !((!A.bit4 | B.bit4) & (A.bit4 | !B.bit4));
	C.bit4 = !((!C.bit4 | C.car) & (C.bit4 | !C.car));
	if (A.bit4 & 0b1)
		C.car = 0b1;
	return C;
}

base operator-(const base& A, const base& B) {
	base C;
	if (A > B) {
		C = A;
		C.bit1 = !((!C.bit1 | C.car) & (C.bit1 | !C.car));
		C.bit1 = !((!A.bit1 | B.bit1) & (A.bit1 | !B.bit1));
		if (B.bit1 & 0b1)
			C.car = 0b1;
		C.bit2 = !((!C.bit2 | C.car) & (C.bit2 | !C.car));
		C.bit2 = !((!A.bit2 | B.bit2) & (A.bit2 | !B.bit2));
		if (B.bit2 & 0b1)
			C.car = 0b1;
		C.bit3 = !((!C.bit3 | C.car) & (C.bit3 | !C.car));
		C.bit3 = !((!A.bit3 | B.bit3) & (A.bit3 | !B.bit3));
		if (B.bit3 & 0b1)
			C.car = 0b1;
		C.bit4 = !((!C.bit4 | C.car) & (C.bit4 | !C.car));
		C.bit4 = !((!A.bit4 | B.bit4) & (A.bit4 | !B.bit4));
		if (B.bit4 & 0b1)
			C.car = 0b1;
	}
	if (A < B) {
		C = B;
		C.bit1 = !((!C.bit1 | C.car) & (C.bit1 | !C.car));
		C.bit1 = !((!A.bit1 | B.bit1) & (A.bit1 | !B.bit1));
		if (B.bit1 & 0b1)
			C.car = 0b1;
		C.bit2 = !((!C.bit2 | C.car) & (C.bit2 | !C.car));
		C.bit2 = !((!A.bit2 | B.bit2) & (A.bit2 | !B.bit2));
		if (B.bit2 & 0b1)
			C.car = 0b1;
		C.bit3 = !((!C.bit3 | C.car) & (C.bit3 | !C.car));
		C.bit3 = !((!A.bit3 | B.bit3) & (A.bit3 | !B.bit3));
		if (B.bit3 & 0b1)
			C.car = 0b1;
		C.bit4 = !((!C.bit4 | C.car) & (C.bit4 | !C.car));
		C.bit4 = !((!A.bit4 | B.bit4) & (A.bit4 | !B.bit4));
		if (B.bit4 & 0b1)
			C.car = 0b1;
	}return C;
}
