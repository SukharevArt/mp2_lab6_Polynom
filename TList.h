#pragma once

#include"Monom.h"

template<class T>
struct TNode {
	T val;
	TNode* pNext;
	TNode() {
		pNext = nullptr;
	}
	TNode(T a) {
		val = a;
		pNext = nullptr;
	}
};

template<class T>
class TList {
protected:
	TNode<T>* pFirst, * pCurr, * pPrev, * pLast, * pStop;
	int len;
public:
	TList() {
		pStop = nullptr;
		len = 0;
		pFirst = pCurr = pPrev = pLast = pStop;
	}
	~TList() {
		while (pFirst != pStop) {
			pLast = pFirst;
			pFirst = pFirst->pNext;
			delete pLast;
		}
	}
	TList( TList& a) {
		if (a.pStop == nullptr)
			pStop = nullptr;
		else {
			pStop = new TNode<T>(pStop->val);
		}
		pFirst = pCurr = pPrev = pLast = pStop;
		len = a.len;
		if (len) {
			pFirst = new TNode<T>(getCurr());
			pCurr = pFirst;
			pFirst = pStop;
			a.goNext();
		}
		for (; !a.isEnd(); a.goNext()) {
			pPrev = pCurr;
			pCurr = new TNode<T>(getCurr());
			pPrev->pNext = pCurr;
			pCurr->pNext = pStop;
		}
		pLast = pPrev;
	}
	TList operator=( TList& a) {
		while (pFirst != pStop) {
			pLast = pFirst;
			pFirst = pFirst->pNext;
			delete pLast;
		}
		pStop = nullptr;
		pFirst = pCurr = pPrev = pLast = pStop;
		len = a.len;
		a.reset();
		if (len) {
			pFirst = new TNode<T>(a.getCurr());
			pCurr = pFirst;
			pFirst->pNext = pStop;
			a.goNext();
		}
		for (; !a.isEnd(); a.goNext()) {
			pPrev = pCurr;
			pCurr = new TNode<T>(a.getCurr());
			pPrev->pNext = pCurr;
			pCurr->pNext = pStop;
		}
		pLast = pPrev;
		pCurr = pFirst;
		pPrev = pStop;
		return *this;
	}

	bool empty() {
		return len == 0;
	}
	void insertFirst(T value) {
		TNode<T>* newnode = new TNode<T>;
		newnode->val = value;
		newnode->pNext = pFirst;
		len++;
		pFirst = newnode;
		if (len == 1) {
			pLast = newnode;
		}
		reset();
	}
	void insertLast(T value) {
		if (len == 0) {
			insertFirst(value);
			return;
		}
		TNode<T>* newnode = new TNode<T>;
		if (pLast == pPrev) {
			pCurr = newnode;
		}
		newnode->val = value;
		newnode->pNext = pStop;
		len++;
		pLast->pNext = newnode;
		pLast = newnode;
	}
	void insertCurr(T value) {
		if (pPrev == pStop) {
			insertFirst(value);
			return;
		}
		if (pCurr == pStop) {
			insertLast(value);
			return;
		}
		TNode<T>* newnode = new TNode<T>;
		newnode->val = value;
		newnode->pNext = pCurr;
		len++;
		pCurr = newnode;
		pPrev->pNext = newnode;
	}
	
	T getFirst() {
		if (pFirst == pStop)
			throw "Empty_List";
		return pFirst->val;
	}
	T getLast() {
		if (pLast == pStop)
			throw "Empty_List";
		return pLast->val;
	}

	void delFirst() {
		if (len == 0)
			throw "Empty_List";
		TNode<T>* tnode = pFirst;
		if (pCurr == pFirst) {
			pCurr = pFirst->pNext;
		}
		pFirst = pFirst->pNext;
		delete tnode;
		len--;
		if (len == 0)
			pLast = pStop;
	}
	void delCurr() {
		if (pCurr == pStop)
			throw "Wrong_position";
		if (pCurr == pFirst) {
			delFirst();
			return;
		}
		if (pCurr == pLast) {
			pLast = pPrev;
		}
		TNode<T>* tnode = pCurr;
		pCurr = pCurr->pNext;
		delete tnode;
		len--;
		pPrev->pNext = pCurr;
	}
	
	void reset() {
		pCurr = pFirst;
		pPrev = pStop;
	}
	void goNext() {
		if (isEnd()) {
			throw "List_already_end";
		}
		pPrev = pCurr;
		pCurr = pCurr->pNext;
	}
	bool isEnd() {
		return pCurr == pStop;
	}
	bool isBegin() {
		return pCurr == pFirst;
	}
	T getCurr() {
		if (pCurr != nullptr)
			return pCurr->val;
		else
			throw "Wrong_position";
	}
};

template<class T>
class THeadList :public TList<T> {
protected:
	TNode<T>* pHead;
public:
	THeadList() {
		TMonom m(-1, 0, 0);
		pHead = new TNode<T>;
		pHead->val = m;
		pHead->pNext = pHead;
		pFirst = pStop = pCurr = pLast = pPrev = pHead;
		len = 0;
	}
	~THeadList() {
		while (pFirst != pStop) {
			delFirst();
		}
		delete pHead;
	}
	void insertFirst(T a) {
		TList::insertFirst(a);
		pHead->pNext = pFirst;
	}
	void insertCurr(T value) {
		if (pPrev == pStop) {
			insertFirst(value);
			return;
		}
		if (pCurr == pStop) {
			insertLast(value);
			return;
		}
		TNode<T>* newnode = new TNode<T>;
		newnode->val = value;
		newnode->pNext = pCurr;
		len++;
		pCurr = newnode;
		pPrev->pNext = newnode;
	}
	void delFirst() {
		TList::delFirst();
		pHead->pNext = pFirst;
	}
	void delCurr() {
		if (pCurr == pStop)
			throw "Wrong_position";
		if (pCurr == pFirst) {
			delFirst();
			return;
		}
		if (pCurr == pLast) {
			pLast = pPrev;
		}
		TNode<T>* tnode = pCurr;
		pCurr = pCurr->pNext;
		delete tnode;
		len--;
		pPrev->pNext = pCurr;
	}
};

class TPolynom : public THeadList<TMonom> {
public:
	TPolynom() : THeadList<TMonom>() {
	}
	TPolynom(TPolynom& cp) {
		pHead->val = TMonom(0, 0, -1);
		for (cp.reset(); !cp.isEnd(); cp.goNext()) {
			insertLast(cp.getCurr());
		}
	}
	void addMonom(TMonom& a) {
		reset();
		while (a < getCurr())
			goNext();
		if (a == getCurr()) {
			pCurr->val = pCurr->val + a;
		}
		else {
			insertCurr(a);
		}
		if (getCurr().coeff == 0) {
			delCurr();
		}
	}
	TPolynom operator+(TPolynom& a) {
		TPolynom nw(a);
		reset();
		nw.reset();
		while (!isEnd()) {
			if (nw.getCurr() > getCurr()) {
				nw.goNext();
			}
			else {
				if (nw.getCurr() == getCurr()) {
					nw.pCurr->val.coeff += pCurr->val.coeff;
				}
				else {
					nw.insertCurr(getCurr());
				}
				if (nw.getCurr().coeff == 0) {
					nw.delCurr();
				}
				goNext();
			}
		}
		return nw;
	}
	TPolynom operator=(TPolynom& a) {
		while (pFirst != pStop) {
			while (pFirst != pStop) {
				TNode<TMonom>* b;
				b = pFirst;
				pFirst = pFirst->pNext;
				delete b;
			}
		}
		pFirst = pCurr = pPrev = pLast = pStop;
		len = a.len;
		a.reset();
		if (len) {
			pFirst = new TNode<TMonom>(a.getCurr());
			pCurr = pFirst;
			pFirst->pNext = pStop;
			a.goNext();
		}
		for (; !a.isEnd(); a.goNext()) {
			pPrev = pCurr;
			pCurr = new TNode<TMonom>(a.getCurr());
			pPrev->pNext = pCurr;
			pCurr->pNext = pStop;
		}
		pLast = pPrev;
		pCurr = pFirst;
		pPrev = pStop;
		return *this;
	}
	TPolynom operator-(TPolynom& a) {
		TPolynom nw(a*(-1));
		reset();
		nw.reset();
		while (!isEnd()) {
			if (nw.getCurr() > getCurr()) {
				nw.goNext();
			}
			else {
				if (nw.getCurr() == getCurr()) {
					nw.pCurr->val.coeff += pCurr->val.coeff;
				}
				else {
					nw.insertCurr(getCurr());
				}
				if (nw.getCurr().coeff == 0) {
					nw.delCurr();
				}
				goNext();
			}
		}
		return nw;
	}
	TPolynom operator*(int a) {
		TPolynom e(*this);
		for (e.reset(); !e.isEnd(); e.goNext()) {
			e.pCurr->val.coeff *= a;
		}
		return e;
	}
	TPolynom operator*(double a) {
		TPolynom e(*this);
		for (e.reset(); !e.isEnd(); e.goNext()) {
			e.pCurr->val.coeff *= a;
		}
		return e;
	}
	bool operator==(const TPolynom& a)const {
		if (len != a.len) {
			return false;
		}
		TNode<TMonom> *tt=pFirst, *aa=a.pFirst;
		for (int i = 0; i < len ; i++ ) {
			if (tt->val != aa->val|| tt->val.coeff != aa->val.coeff)
				return false;
			tt = tt->pNext;
			aa = aa->pNext;
		}
		return true;
	}
	bool operator!=(const TPolynom& a)const {
		if (len != a.len) {
			return true;
		}
		TNode<TMonom> *tt=pFirst, *aa=a.pFirst;
		for (int i = 0; i < len ; i++ ) {
			if (tt->val != aa->val || tt->val.coeff != aa->val.coeff)
				return true;
			tt = tt->pNext;
			aa = aa->pNext;
		}
		return false;
	}

	friend std::ostream& operator<<(std::ostream& sout, TPolynom& a) {
		a.reset();
		if (a.isEnd()) {
			sout << 0;
		}
		else {
			sout << a.getCurr();
			a.goNext();
		}

		for (; !a.isEnd(); a.goNext()) {
			if (a.getCurr().coeff > 0)
				sout << '+';
			sout << a.getCurr();
		}
		return sout;
	}
};

