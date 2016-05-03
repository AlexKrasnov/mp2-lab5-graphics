#pragma once
#include <iostream>

template <class T>
class TLink
{
public:
	T val;       
	TLink* next;   
	TLink(T& _val) : val(_val), next(NULL) {}
	TLink(const TLink& L) : val(L.val), next(l.next) {}
	virtual ~TLink() {}
};

template <class T>
class TList
{
	TLink<T> *pFirst;
	TLink<T> *pCurrent;
public:
	TList()
	{
		pCurrent = pFirst = NULL;
	}
	void AddFirst(T _val)
	{
		TLink <T> *tmp;
		tmp = new TLink<T>(_val);
		tmp->next = pFirst;
		pFirst = tmp;
	}
	void AddLast(T _val)
	{
		TLink <T> *tmp;
		tmp = new TLink<T>;
		tmp->val = _val;
		tmp->next = NULL;
		TLink <T> *curr = pFirst;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = tmp;
	}
	bool IsEnd()
	{
		if (pCurrent == NULL)
			return true;
		else return false;
	}
	void Reset()
	{
		if (pFirst != NULL)
			pCurrent = pFirst;
	}
	void GoNext()
	{
		if(pCurrent!=NULL)
			pCurrent = pCurrent->next;
	}
	T GetCurrentVal()
	{
		if (pCurrent != NULL)
			return pCurrent->val;
		else throw "NULL";
	}
};


