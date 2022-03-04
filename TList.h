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
		val = T;
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
	TList& operator=( TList& a) {
		while (pFirst != pStop) {
			pLast = pFirst;
			pFirst = pFirst->pNext;
			delete pLast;
		}
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
			reset();
		}
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
		if (pCurr = pFirst) {
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
		TMonom m(0, 0, -1);
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
	void delFirst() {
		TList::delFirst();
		pHead->pNext = pFirst;
	}
};

class TPolinom : public THeadList<TMonom> {
public:
	TPolinom() : THeadList<TMonom>() {
		TMonom m(0, 0, -1);
		pHead->val = m;
	}
	TPolinom(TPolinom& cp) {
		pHead->val = TMonom(0, 0, -1);
		for (cp.reset(); !cp.isEnd(); cp.goNext()) {
			insertLast(cp.getCurr());
		}
	}
	void addMonom(TMonom& a) {
		if (isEnd()||a > getCurr()) {
			reset();
		}
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
	TPolinom operator+(TPolinom& a) {
		TPolinom nw(a);
		for (reset(); !isEnd(); goNext())
			nw.addMonom(getCurr());
		return nw;
	}
	friend ostream& operator<<(ostream& sout, TPolinom& a) {
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

