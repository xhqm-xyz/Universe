#pragma once
#ifndef UNIVERSE_LIST
#define UNIVERSE_LIST
typedef unsigned long long natu;	//??????

template <class _CLASS>
class vector
{
protected:
	natu NUM;
	_CLASS CLASS;
	vector* NEXT = nullptr;
	vector(_CLASS data) :CLASS(data), NUM(1) {};

public:
	vector() :NUM(0) {};
	~vector() { };

	bool move(natu n, natu m);
	bool ins(_CLASS data, natu n = 0);
	bool del(natu n = 0);

	void clear();
	void pop_back();
	void push_back(_CLASS data);
	natu size() { return NUM; };
	_CLASS GetData(natu n);
	_CLASS& operator[](const natu& n);
};

template<class _CLASS>
inline _CLASS vector<_CLASS>::GetData(natu  n)
{
	if (n == 0)
		return NEXT->CLASS;
	else
		return NEXT->GetData(--n);
}

template<class _CLASS>
inline bool vector<_CLASS>::move(natu n, natu m)
{
	if (n < 0 || n >= NUM)
		return false;
	if (m < 0 || m >= NUM)
		return false;
	_CLASS ndata(GetData(n));
	_CLASS mdata(GetData(m));

	del(n);
	ins(mdata, n);
	del(m);
	ins(ndata, m);

	return true;
}

template<class _CLASS>
inline bool vector<_CLASS>::ins(_CLASS data, natu n)
{
	if (n < 0 || n > NUM)
		return false;
	if (n == 0) {
		vector* newvector = new vector(data);
		newvector->NUM = NUM;
		newvector->NEXT = NEXT;
		NEXT = newvector;
	}
	else
		NEXT->ins(data, --n);
	NUM++;
	return true;
}

template<class _CLASS>
inline bool vector<_CLASS>::del(natu n)
{
	if (n < 0 || n >= NUM)
		return false;
	if (n == 0) {
		vector* oldvector = NEXT;
		NEXT = NEXT->NEXT;
		oldvector = nullptr;
		delete oldvector;
	}
	else
		NEXT->del(--n);
	NUM--;
	return true;
}

template<class _CLASS>
inline void vector<_CLASS>::clear()
{
	for (;;)
		if (NEXT != nullptr)
			pop_back();
		else
			break;
}

template<class _CLASS>
inline void vector<_CLASS>::pop_back()
{
	if (NUM > 0) {
		if (NEXT->NEXT == nullptr) {
			delete NEXT;
			NEXT = nullptr;
		}
		else
			NEXT->pop_back();
		NUM--;
	}
}

template<class _CLASS>
inline void vector<_CLASS>::push_back(_CLASS data)
{
	NUM++;
	if (NEXT == nullptr)
		NEXT = new vector(data);
	else
		NEXT->push_back(data);
}

template<class _CLASS>
inline _CLASS& vector<_CLASS>::operator[] (const natu& i)
{
	natu n = i;
	if (n < 0 || n >= NUM)
		n = 0;
	if (n == 0)
		return NEXT->CLASS;
	else
		return (*NEXT)[--n];
}

#endif // !UNIVERSE_LIST