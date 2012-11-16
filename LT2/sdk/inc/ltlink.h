
// This is for simple but very convenient doubly linked lists..
// You need a LTLink for the list head, and this just defines
// really common routines to insert, remove, and tie off.

#ifndef __LTLINK_H__
#define __LTLINK_H__


	class LTLink;


	#include "ltbasetypes.h"


	// This goes thru and C++ deletes everything in a list.
	// You need a LTLink *pCur, *pNext;
	#define CPP_DELETELIST(_list_pointer, type) \
	{\
		pCur = (_list_pointer)->m_Head.m_pNext;\
		while(pCur != &(_list_pointer)->m_Head)\
		{\
			pNext = pCur->m_pNext;\
			delete ((type*)pCur->m_pData);\
			pCur = pNext;\
		}\
		dl_InitList(_list_pointer);\
	}


	// Use these to declare blank LTLinks and LTLists.
	#define DECLARE_LTLINK(name) \
		LTLink name(LTLink_Init);

	#define DECLARE_LTLIST(name) \
		LTList name(LTLink_Init);


	typedef enum
	{
		LTLink_Init=0
	} LTLinkCommand;



	// Use LTLink whenever you need m_pData but you can use this if you have a list head.
	class CheapLTLink
	{
	public:
		
		void		Init();
		void		Term();
		void		Remove();
		void		TieOff();
		void		AddAfter(CheapLTLink *pLink);
		void		AddBefore(CheapLTLink *pLink);
		LTLink*		operator[](unsigned long i);
		inline LTLink*		AsDLink()	{return (LTLink*)this;}
		inline LTLink*		AsLTLink()	{return (LTLink*)this;}
		LTBOOL		IsTiedOff();

	public:

		LTLink	*m_pPrev, *m_pNext;
	};


	class LTLink : public CheapLTLink
	{
	public:

		inline	LTLink() {}
		inline	LTLink(LTLinkCommand cmd)
		{
			TieOff();
		}

		inline void	Init2(void *pData)
		{
			TieOff();
			m_pData = pData;
		}


	public:
		void	*m_pData;
	};


	inline void CheapLTLink::Init()
	{
		TieOff();
	}

	inline void CheapLTLink::Term()
	{
		Remove();
	}

	inline void CheapLTLink::Remove()
	{
		m_pPrev->m_pNext = m_pNext;
		m_pNext->m_pPrev = m_pPrev;
		TieOff();
	}

	inline void CheapLTLink::TieOff()
	{
		m_pPrev = m_pNext = (LTLink*)this;
	}

	inline void CheapLTLink::AddAfter(CheapLTLink *pLink)
	{
		pLink->m_pPrev = (LTLink*)this;
		pLink->m_pNext = m_pNext;
		pLink->m_pPrev->m_pNext = pLink->m_pNext->m_pPrev = (LTLink*)pLink;
	}

	inline void	CheapLTLink::AddBefore(CheapLTLink *pLink)
	{
		pLink->m_pPrev = m_pPrev;
		pLink->m_pNext = (LTLink*)this;
		pLink->m_pPrev->m_pNext = pLink->m_pNext->m_pPrev = (LTLink*)pLink;
	}

	// Makes it easy to traverse the list in either direction.
	inline LTLink* CheapLTLink::operator[](unsigned long i)
	{
		return ((LTLink**)this)[i];
	}

	inline LTBOOL CheapLTLink::IsTiedOff()
	{
		return m_pPrev == this && m_pNext == this;
	}


	inline void dl_TieOff(CheapLTLink *pLink)
	{
		pLink->TieOff();
	}

	inline void dl_Insert(CheapLTLink *pAfter, CheapLTLink *pLink)
	{
		pAfter->AddAfter(pLink);
	}

	inline void dl_Remove(CheapLTLink *pLink)
	{
		pLink->Remove();
	}


	// You can use this list structure to wrap up a linked list
	// if you want to keep a count of the elements.
	class LTList
	{
	public:

						LTList()
						{
							m_Head.TieOff();
							m_nElements = 0;
						}
						
						LTList(LTLinkCommand cmd)
						{
							m_Head.TieOff();
							m_nElements = 0;
						}

		unsigned long	m_nElements;
		LTLink			m_Head;
	};

	inline void dl_InitList(LTList *pList)
	{
		dl_TieOff(&pList->m_Head);
		pList->m_nElements = 0;
	}

	inline void dl_AddAfter(LTList *pList, LTLink *pAfter, LTLink *pLink, void *pObj)
	{
		pLink->m_pData = pObj;
		dl_Insert(pAfter, pLink);
		++pList->m_nElements;
	}

	inline void dl_AddBefore(LTList *pList, LTLink *pBefore, LTLink *pLink, void *pObj)
	{
		dl_AddAfter(pList, pBefore->m_pPrev, pLink, pObj);
	}

	inline void dl_AddHead(LTList *pList, LTLink *pLink, void *pObj)
	{
		dl_AddAfter(pList, &pList->m_Head, pLink, pObj);
	}

	inline void dl_AddTail(LTList *pList, LTLink *pLink, void *pObj)
	{
		dl_AddAfter(pList, pList->m_Head.m_pPrev, pLink, pObj);
	}

	inline void dl_RemoveAt(LTList *pList, LTLink *pLink)
	{
		dl_Remove(pLink);
		--pList->m_nElements;
	}


#endif  // __LTLINK_H__
