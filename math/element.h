#pragma once
#ifndef UNIVERSE_MATH_ELEMENT
#define UNIVERSE_MATH_ELEMENT
#include "measure.h"

template<class _DATACLASS> class Gather;//集合
template<class _DATACLASS> class Graph;//图论

template<class _DATACLASS>
class element
{
private:
	_DATACLASS DATA;
	element* Prior;//上一个
	element* After;//下一个
	vector<element*> Relationship;
public:
	element(_DATACLASS data) :DATA(data) {
		Prior = this;
		After = this;
	}
	_DATACLASS Getdata() { return DATA; };

	//_DATACLASS 必须重载  !=  ==  =
	_DATACLASS operator = (const _DATACLASS& getdata);
	bite operator== (const _DATACLASS& data);
	bite operator!= (const _DATACLASS& data);

	element<_DATACLASS> operator = (const element<_DATACLASS>& getele);
	bite operator== (const element<_DATACLASS>& getele);
	bite operator!= (const element<_DATACLASS>& getele);

	template<class _DATACLASS>
	friend class Gather;
	template<class _DATACLASS>
	friend class Graph;
};

template<class _DATACLASS>
_DATACLASS element<_DATACLASS>::operator=(const _DATACLASS& getdata)
{
	return DATA = getdata;
}

template<class _DATACLASS>
bite element<_DATACLASS>::operator==(const _DATACLASS& data)
{
	if (DATA == data)
		return true;
	else
		return false;
}

template<class _DATACLASS>
bite element<_DATACLASS>::operator!=(const _DATACLASS& data)
{
	if (DATA != data)
		return true;
	else
		return false;
}

template<class _DATACLASS>
element<_DATACLASS> element<_DATACLASS>::operator=(const element<_DATACLASS>& getele)
{
	DATA = getele.DATA;
	return *this;
}

template<class _DATACLASS>
inline bite element<_DATACLASS>::operator==(const element<_DATACLASS>& getele)
{
	if (DATA == getele.DATA)
		return true;
	else
		return false;
}

template<class _DATACLASS>
inline bite element<_DATACLASS>::operator!=(const element<_DATACLASS>& getele)
{
	if (DATA != getele.DATA)
		return true;
	else
		return false;
}

#endif // !UNIVERSE_MATH_ELEMENT