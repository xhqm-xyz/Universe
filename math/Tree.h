#pragma once
#ifndef UNIVERSE_MATH_TREE
#define UNIVERSE_MATH_TREE
#define TreeNode container
#include "container.h"

template<class _DATACLASS>
class Tree
{
private:
    natu _NodeNum = 0;
    TreeNode<_DATACLASS>* _Root = nullptr;//根节点 Root.Prior = this
    TreeNode<_DATACLASS>* _Node = nullptr;
public:
	~Tree() { clear(); };
    Tree() {};
    Tree(_DATACLASS data):_NodeNum(1) { _Root = new TreeNode<_DATACLASS>(data); _Node = _Root; };
    Tree(TreeNode<_DATACLASS> data) :_NodeNum(1) {  _Root = new TreeNode<_DATACLASS>(data.DATA); _Node = _Root; };

    _DATACLASS RootData();//返回根节点
    _DATACLASS NodeData(natu i = 0);//返回_Node下第i个子节点 0是父节点
    _DATACLASS ParentData();//返回父节点
    _DATACLASS BrotherData(natu i = 0);//返回_Node第i个兄弟节点 0是本节点
    TreeNode* NowNodeData();//返回父节点

    TreeNode* Inster(_DATACLASS data);//插入到_Node下子节点 并返回data所在子节点
    TreeNode* Delete(_DATACLASS data);//删除_Node 并返回其父节点
    TreeNode* Updata(_DATACLASS data);//更新 并返回本节点
    TreeNode* Select(_DATACLASS data, bite dl = true);//返回_Node下第一个data所在节点 true深度 false广度
    TreeNode** SelectAll(_DATACLASS data, bite dl = true);//返回_Node下所有data所在节点 true深度 false广度


    Tree CopyTree(TreeNode<_DATACLASS>* node);
    Tree MoveTree(TreeNode<_DATACLASS>* node);
    Tree DropTree(TreeNode<_DATACLASS>* node);
    Tree InteTree(TreeNode<_DATACLASS>* node);
	//void clear();


	//natu GetPotential() { return Potential; };
	//element<_DATACLASS>* GetElement() { return ELE; };
 //   _DATACLASS& operator[](const natu& n) {
 //       for (natu i = 0; i < n; i++)
 //           if (ELE != nullptr) ELE = ELE->Prior;
 //       return ELE->DATA;
 //   }

	//void operator ++ ()  { if (ELE != nullptr) ELE = ELE->Prior; };//前缀++
	//void operator -- ()  { if (ELE != nullptr) ELE = ELE->After; };//前缀--
	//void operator ++(int){ if (ELE != nullptr) ELE = ELE->Prior; };//后缀++
	//void operator --(int){ if (ELE != nullptr) ELE = ELE->After; };//后缀--

	//friend bite operator > (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B) { return A.Potential > B.Potential; };//比较势
	//friend bite operator < (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B) { return A.Potential < B.Potential; };//比较势
	//friend bite operator>= (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B) { return A.Potential >=B.Potential; };//比较势
	//friend bite operator<= (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B) { return A.Potential <=B.Potential; };//比较势

 //   template<class _DATACLASS>
	//friend bite operator== (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B);
 //   template<class _DATACLASS>
	//friend bite operator!= (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B);

 //   friend void operator + (Gather<_DATACLASS>& A, const _DATACLASS b){ A.AddOneElement(b); };
	//friend void operator - (Gather<_DATACLASS>& A, const _DATACLASS b){ A.SubOneElement(b); };



	//friend Gather<_DATACLASS> operator + (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B){//和集
 //       Gather<_DATACLASS> Acopy(A.ELE);
 //       Gather<_DATACLASS> Bcopy(B.ELE);
 //       for (natu i = 0; i < Bcopy.GetPotential(); i++) {
 //           Bcopy++;
 //           Acopy.AddOneElement(Bcopy.GetElement()->Getdata());
 //       }Bcopy.clear();
 //       return Acopy;
 //   }
 //   friend Gather<_DATACLASS> operator - (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B){//差集
 //       Gather<_DATACLASS> Acopy(A.ELE);
 //       Gather<_DATACLASS> Bcopy(B.ELE);
 //       for (natu i = 0; i < Bcopy.GetPotential(); i++) {
 //           Bcopy++;
 //           Acopy.SubOneElement(Bcopy.GetElement()->Getdata());
 //       }Bcopy.clear();
 //       return Acopy;
 //   }
	//friend Gather<_DATACLASS> operator * (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B)//交集
 //   { return A - (A - B); }
	//friend Gather<_DATACLASS> operator / (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B)//余集
 //   { return A - B; }


	//Gather<_DATACLASS> operator+= (const Gather<_DATACLASS>& gat) { return *this = *this + gat; };
	//Gather<_DATACLASS> operator-= (const Gather<_DATACLASS>& gat) { return *this = *this - gat; };
	//Gather<_DATACLASS> operator*= (const Gather<_DATACLASS>& gat) { return *this = *this * gat; };
	//Gather<_DATACLASS> operator/= (const Gather<_DATACLASS>& gat) { return *this = *this / gat; };
 //   Gather<_DATACLASS> operator = (const Gather<_DATACLASS>& gat);
};
/*
template<class _DATACLASS>
Gather<_DATACLASS> Gather<_DATACLASS>::operator = (const Gather<_DATACLASS>& gat)
{
    Gather<_DATACLASS> copy(gat.ELE);
    clear();
    for (nume i = 0; i < copy.Potential; i++) {
        copy++;
        AddOneElement(copy.ELE->Getdata());
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
    for (nume i = 0; i < Potential; i++) {
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
    element<_DATACLASS>* _p = gat.ELE;
    for (nume i = 0; i < gat.Potential; i++) {
        if (FindElement(_p->Getdata()))
            _p = _p->Prior;
        else
            return false;
    }FindElement(FIRST);
    return true;
}

template<class _DATACLASS>
bite Gather<_DATACLASS>::SubNowElement()
{
    element<_DATACLASS>* Oldelement = NULL;
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
    element<_DATACLASS>* Newelement = new element<_DATACLASS>(data);
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
*/
#endif // !UNIVERSE_MATH_TREE