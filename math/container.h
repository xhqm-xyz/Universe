#pragma once
#ifndef UNIVERSE_MATH_CONTAINER
#define UNIVERSE_MATH_CONTAINER
#include "measure.h"
template<class _DATACLASS> class Gather;//集合
template<class _DATACLASS> class Graph;//图论
template<class _DATACLASS> class Tree;//树

class dataid {
	natu id = 0;
public:
	dataid():id(0) { id = (natu)this; }
	natu Getid() { return id; }
};



template<class _DATACLASS>
class container :public dataid
{
private:
	container<_DATACLASS>* Prior;//上一个
	container<_DATACLASS>* After;//下一个
	vector<container<_DATACLASS>*> Relationship;
public:
	container(_DATACLASS data) :DATA(data) {
		Prior = this;
		After = this;
	}
	//_DATACLASS& Getdata() { return DATA; };
	//_DATACLASS 必须重载  !=  ==  =
	_DATACLASS operator = (const _DATACLASS& getdata);
	container<_DATACLASS> operator = (const container<_DATACLASS>& getele);

	bite operator== (const _DATACLASS& data);
	bite operator!= (const _DATACLASS& data);
	bite operator== (const container<_DATACLASS>& getele);
	bite operator!= (const container<_DATACLASS>& getele);
	container<_DATACLASS>* operator[](natu n) { return Relationship[n]; }

	_DATACLASS DATA;
	template<class _DATACLASS>
	friend class Gather;
	template<class _DATACLASS>
	friend class Graph;
	template<class _DATACLASS> 
	friend class Tree;
};

template<class _DATACLASS>
_DATACLASS container<_DATACLASS>::operator=(const _DATACLASS& getdata)
{
	return DATA = getdata;
}

template<class _DATACLASS>
inline bite container<_DATACLASS>::operator==(const _DATACLASS& data)
{
	return (DATA == data);
}

template<class _DATACLASS>
inline bite container<_DATACLASS>::operator!=(const _DATACLASS& data)
{
	return !(DATA == data);
}

template<class _DATACLASS>
container<_DATACLASS> container<_DATACLASS>::operator=(const container<_DATACLASS>& getele)
{
	DATA = getele.DATA;
	return *this;
}

template<class _DATACLASS>
inline bite container<_DATACLASS>::operator==(const container<_DATACLASS>& getele)
{
	return (DATA == getele.DATA);
}

template<class _DATACLASS>
inline bite container<_DATACLASS>::operator!=(const container<_DATACLASS>& getele)
{
	return !(DATA == getele.DATA);
}

#endif // !UNIVERSE_MATH_CONTAINER