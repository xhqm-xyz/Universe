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
    TreeNode<_DATACLASS>* _Root = nullptr;//���ڵ� Root.Prior = this
    TreeNode<_DATACLASS>* _Node = nullptr;
public:
	~Tree() { clear(); };
    Tree() {};
    Tree(_DATACLASS data):_NodeNum(1) { _Root = new TreeNode<_DATACLASS>(data); _Node = _Root; };
    Tree(TreeNode<_DATACLASS> data) :_NodeNum(1) {  _Root = new TreeNode<_DATACLASS>(data.DATA); _Node = _Root; };

    _DATACLASS RootData();//���ظ��ڵ�
    _DATACLASS NodeData(natu i = 0);//����_Node�µ�i���ӽڵ� 0�Ǹ��ڵ�
    _DATACLASS ParentData();//���ظ��ڵ�
    _DATACLASS BrotherData(natu i = 0);//����_Node��i���ֵܽڵ� 0�Ǳ��ڵ�
    TreeNode* NowNodeData();//���ظ��ڵ�

    TreeNode* Inster(_DATACLASS data);//���뵽_Node���ӽڵ� ������data�����ӽڵ�
    TreeNode* Delete(_DATACLASS data);//ɾ��_Node �������丸�ڵ�
    TreeNode* Updata(_DATACLASS data);//���� �����ر��ڵ�
    TreeNode* Select(_DATACLASS data, bite dl = true);//����_Node�µ�һ��data���ڽڵ� true��� false���
    TreeNode** SelectAll(_DATACLASS data, bite dl = true);//����_Node������data���ڽڵ� true��� false���


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

	//void operator ++ ()  { if (ELE != nullptr) ELE = ELE->Prior; };//ǰ׺++
	//void operator -- ()  { if (ELE != nullptr) ELE = ELE->After; };//ǰ׺--
	//void operator ++(int){ if (ELE != nullptr) ELE = ELE->Prior; };//��׺++
	//void operator --(int){ if (ELE != nullptr) ELE = ELE->After; };//��׺--

	//friend bite operator > (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B) { return A.Potential > B.Potential; };//�Ƚ���
	//friend bite operator < (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B) { return A.Potential < B.Potential; };//�Ƚ���
	//friend bite operator>= (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B) { return A.Potential >=B.Potential; };//�Ƚ���
	//friend bite operator<= (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B) { return A.Potential <=B.Potential; };//�Ƚ���

 //   template<class _DATACLASS>
	//friend bite operator== (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B);
 //   template<class _DATACLASS>
	//friend bite operator!= (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B);

 //   friend void operator + (Gather<_DATACLASS>& A, const _DATACLASS b){ A.AddOneElement(b); };
	//friend void operator - (Gather<_DATACLASS>& A, const _DATACLASS b){ A.SubOneElement(b); };



	//friend Gather<_DATACLASS> operator + (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B){//�ͼ�
 //       Gather<_DATACLASS> Acopy(A.ELE);
 //       Gather<_DATACLASS> Bcopy(B.ELE);
 //       for (natu i = 0; i < Bcopy.GetPotential(); i++) {
 //           Bcopy++;
 //           Acopy.AddOneElement(Bcopy.GetElement()->Getdata());
 //       }Bcopy.clear();
 //       return Acopy;
 //   }
 //   friend Gather<_DATACLASS> operator - (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B){//�
 //       Gather<_DATACLASS> Acopy(A.ELE);
 //       Gather<_DATACLASS> Bcopy(B.ELE);
 //       for (natu i = 0; i < Bcopy.GetPotential(); i++) {
 //           Bcopy++;
 //           Acopy.SubOneElement(Bcopy.GetElement()->Getdata());
 //       }Bcopy.clear();
 //       return Acopy;
 //   }
	//friend Gather<_DATACLASS> operator * (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B)//����
 //   { return A - (A - B); }
	//friend Gather<_DATACLASS> operator / (const Gather<_DATACLASS>& A, const Gather<_DATACLASS>& B)//�༯
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

typedef Gather<bytebit> GatherB;//��ֵ��
typedef Gather<symbols> GatherS;//���ż�
typedef Gather<complex> GatherC;//������
typedef Gather<portion> GatherP;//������
typedef Gather<measure> GatherR;//ʵ����
typedef Gather<integer> GatherZ;//������
typedef Gather<natural> GatherN;//��Ȼ����
*/
#endif // !UNIVERSE_MATH_TREE