#pragma once
#ifndef UNIVERSE_MATH_GATHER
#define UNIVERSE_MATH_GATHER
#define Element container
#include "container.h"

template<class _DATACLASS>
class Gather
{
private:
	natu Potential;//势
    Element<_DATACLASS>* ELE = nullptr;
public:
	~Gather() { clear(); };
	Gather() :Potential(0) {};
	Gather(Element<_DATACLASS>* data){
        if (data != NULL)
            for (; AddOneElement(data->DATA);)
                data = data->Prior;
	};

	void clear();
	bite SubNowElement();//删除当前元素
	bite SubOneElement(_DATACLASS data);//减所有data
	bite AddOneElement(_DATACLASS data);//加一个data
	bite FindElement(_DATACLASS data);
	bite FindGather(const Gather<_DATACLASS>& gat);

	natu GetPotential() { return Potential; };
    Element<_DATACLASS>* GetElement() { return ELE; };
    _DATACLASS& operator[](const natu& n) {
        for (natu i = 0; i < n; i++)
            if (ELE != nullptr) ELE = ELE->Prior;
        return ELE->DATA;
    }

	void operator ++ ()  { if (ELE != nullptr) ELE = ELE->Prior; };//前缀++
	void operator -- ()  { if (ELE != nullptr) ELE = ELE->After; };//前缀--
	void operator ++(int){ if (ELE != nullptr) ELE = ELE->Prior; };//后缀++
	void operator --(int){ if (ELE != nullptr) ELE = ELE->After; };//后缀--

	friend bite operator > (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B) { return A.Potential > B.Potential; };//比较势
	friend bite operator < (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B) { return A.Potential < B.Potential; };//比较势
	friend bite operator>= (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B) { return A.Potential >=B.Potential; };//比较势
	friend bite operator<= (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B) { return A.Potential <=B.Potential; };//比较势

    
    template<class _DATACLASS> friend bite operator== (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B);
    template<class _DATACLASS> friend bite operator!= (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B);

    friend void operator + (Gather<_DATACLASS>& A, const _DATACLASS b){ A.AddOneElement(b); };
	friend void operator - (Gather<_DATACLASS>& A, const _DATACLASS b){ A.SubOneElement(b); };



	friend Gather<_DATACLASS> operator + (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B){//和集
        Gather<_DATACLASS> Acopy(A.ELE);
        Gather<_DATACLASS> Bcopy(B.ELE);
        for (natu i = 0; i < Bcopy.GetPotential(); i++) {
            Bcopy++;
            Acopy.AddOneElement(Bcopy.GetElement()->DATA);
        }Bcopy.clear();
        return Acopy;
    }
    friend Gather<_DATACLASS> operator - (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B){//差集
        Gather<_DATACLASS> Acopy(A.ELE);
        Gather<_DATACLASS> Bcopy(B.ELE);
        for (natu i = 0; i < Bcopy.GetPotential(); i++) {
            Bcopy++;
            Acopy.SubOneElement(Bcopy.GetElement()->DATA);
        }Bcopy.clear();
        return Acopy;
    }
	friend Gather<_DATACLASS> operator * (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B)//交集
    { return A - (A - B); }
	friend Gather<_DATACLASS> operator / (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B)//余集
    { return A - B; }


	Gather<_DATACLASS> operator+= (const Gather<_DATACLASS>& gat) { return *this = *this + gat; };
	Gather<_DATACLASS> operator-= (const Gather<_DATACLASS>& gat) { return *this = *this - gat; };
	Gather<_DATACLASS> operator*= (const Gather<_DATACLASS>& gat) { return *this = *this * gat; };
	Gather<_DATACLASS> operator/= (const Gather<_DATACLASS>& gat) { return *this = *this / gat; };
    Gather<_DATACLASS> operator = (const Gather<_DATACLASS>& gat);
};

template<class _DATACLASS>
Gather<_DATACLASS> Gather<_DATACLASS>::operator = (const Gather<_DATACLASS>& gat)
{
    Gather<_DATACLASS> copy(gat.ELE);
    clear();
    for (natu i = 0; i < copy.Potential; i++) {
        copy++;
        AddOneElement(copy.ELE->DATA);
    }return copy;
}


template<class _DATACLASS>
void Gather<_DATACLASS>::clear()
{
    for (; 0 < Potential;)
        SubNowElement();
}

template<class _DATACLASS>
bite Gather<_DATACLASS>::FindElement(_DATACLASS data)
{
    for (natu i = 0; i < Potential; i++) {
        if (*ELE == data)
            return true;
        ELE = ELE->Prior;
    }return false;
}

template<class _DATACLASS>
bite Gather<_DATACLASS>::FindGather(const Gather<_DATACLASS>& gat)
{
    if (Potential < gat.Potential)
        return false;
    if (gat.Potential == 0)
        return true;
    _DATACLASS FIRST = ELE->DATA;
    Element<_DATACLASS>* _p = gat.ELE;
    for (natu i = 0; i < gat.Potential; i++) {
        if (FindElement(_p->DATA))
            _p = _p->Prior;
        else
            return false;
    }FindElement(FIRST);
    return true;
}

template<class _DATACLASS>
bite Gather<_DATACLASS>::SubNowElement()
{
    Element<_DATACLASS>* Oldelement = NULL;
    if (ELE != NULL) {
        Oldelement = ELE->Prior;
        ELE->After->Prior = ELE->Prior;
        ELE->Prior->After = ELE->After;
        delete ELE;
        ELE = Oldelement;
        Potential--;
        if (Potential == 0)
            ELE = NULL;
        return true;
    }return false;
}

template<class _DATACLASS>
bite Gather<_DATACLASS>::SubOneElement(_DATACLASS data)
{
    if (FindElement(data))
        return SubNowElement();
    else
        return false;
}

template<class _DATACLASS>
bite Gather<_DATACLASS>::AddOneElement(_DATACLASS data)
{
    if (FindElement(data))
        return false;
    Element<_DATACLASS>* Newelement = new Element<_DATACLASS>(data);
    if (ELE != NULL) {
        Newelement->After = ELE;
        Newelement->Prior = ELE->Prior;
        Newelement->After->Prior = Newelement;
        Newelement->Prior->After = Newelement;
    }ELE = Newelement;
    Newelement = NULL;
    Potential++;
    return true;
}



template<class _DATACLASS>
bite operator==(const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B)
{
    if (A.Potential != B.Potential)
        return false;
    Gather<_DATACLASS> Acopy(A.ELE);
    Gather<_DATACLASS> Bcopy(B.ELE);
    if (Acopy.FindGather(Bcopy) && Bcopy.FindGather(Acopy))
        return true;
    Acopy.clear();
    Bcopy.clear();
    return false;
}

template<class _DATACLASS>
bite operator!=(const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B)
{
    if (A == B)
        return false;
    return true;
}

typedef Gather<bytebit> GatherB;//真值集
typedef Gather<symbols> GatherS;//符号集
typedef Gather<complex> GatherC;//复数集
typedef Gather<portion> GatherP;//分数集
typedef Gather<measure> GatherR;//实数集
typedef Gather<integer> GatherZ;//整数集
typedef Gather<natural> GatherN;//自然数集

#endif // !UNIVERSE_MATH_GATHER