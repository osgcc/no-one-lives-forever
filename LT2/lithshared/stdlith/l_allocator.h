
// This module declares a standard allocation wrapper that can be derived
// from.  Most stdlith functionality supports the use of allocators.

// The LAlloc class can be derived from to define your own memory allocator.

// In order to use LAllocs, you must use the LNew, LDelete, LNew_Array, and LDelete_Array
// macros.  The only way these differ from operator new and operator delete
// is that when you're deleting an array, you must pass in the number of elements
// in the array.  This makes it so it doesn't have to store an extra (almost always
// redundant) DWORD with each array allocation.

#ifndef __L_ALLOCATOR_H__
#define __L_ALLOCATOR_H__

	
	#include <stdlib.h>
	#include "stdlithdefs.h"


	// If you define STDLITH_ALLOC_OVERRIDE in your project settings, you can 
	// implement these functions.	
	extern void* DefStdlithAlloc(DWORD size);
	extern void  DefStdlithFree(void *ptr);

	// LAlloc class with default implementations of Alloc and Free.
	// NOTE: LAllocs MUST return NULL for allocation sizes of 0.
	class LAlloc
	{
	public:
		virtual			~LAlloc() {}
		
		virtual void*	Alloc(DWORD size)	{return DefStdlithAlloc(size);}
		virtual void	Free(void *ptr)		{DefStdlithFree(ptr);}
	};


	// This allocator tallies up a bunch of useful data.
	class LAllocCount : public LAlloc
	{
	public:

						LAllocCount(LAlloc *pDelegate);

		void			ClearCounts();

		virtual void*	Alloc(DWORD size);
		virtual void	Free(void *ptr);


	public:

		// Total allocations/frees.
		DWORD		m_nTotalAllocations;
		DWORD		m_nTotalFrees;

		// Total amount of memory allocated (this might overflow...)
		DWORD		m_TotalMemoryAllocated;

		// Current number of active allocations.
		DWORD		m_nCurrentAllocations;

		// Number of times Alloc failed (if you try to allocate 0 and it returns
		// NULL, that is not considered a failure).
		DWORD		m_nAllocationFailures;


	private:

		LAlloc		*m_pDelegate;
	};


	// This allocator is useful if you know exactly how much memory something will use.
	// This will allocate one big block and just allocate memory out of it until it
	// runs out.  This will NOT free memory (ie: Free() just returns).
	class LAllocSimpleBlock : public LAlloc
	{
	public:

						LAllocSimpleBlock();
		virtual			~LAllocSimpleBlock();

		// Allocates the block and prepares for allocations.
		// NOTE: it hangs onto the delegate until its destructor or
		// when Term is called.
		BOOL			Init(LAlloc *pDelegate, DWORD blockSize);
		void			Term();


	// Overrides.
	public:

		virtual void*	Alloc(DWORD size);
		virtual void	Free(void *ptr);

	// Functions specific to LAllocSimpleBlock
		DWORD			GetBlockSize() const { return m_BlockSize; };

	private:

		void			Clear();


	private:

		LAlloc			*m_pDelegate;
		BYTE			*m_pBlock;
		DWORD			m_CurBlockPos;
		DWORD			m_BlockSize;
	};


	// This always exists and can be passed into things that require an allocator.
	extern LAlloc g_DefAlloc;


	// Use these to allocate classes with LAllocs.
	#define LNew(pAllocator, type) \
		BaseNew(pAllocator, (type*)0, 1);

	// Initialize with 1 pointer parameter to the constructor.
	#define LNew_1P(pAllocator, type, p1) \
		BaseNew_1P(pAllocator, (type*)0, 1, p1);

	// Initialize with 2 pointers to the constructor.
	#define LNew_2P(pAllocator, type, p1, p2) \
		BaseNew_2P(pAllocator, (type*)0, 1, p1, p2);

	#define LDelete(pAllocator, ptr) \
		BaseDelete(pAllocator, ptr, 1);

	#define LNew_Array(pAllocator, type, nElements) \
		BaseNew(pAllocator, (type*)0, nElements);

	#define LDelete_Array(pAllocator, ptr, nElements) \
		BaseDelete(pAllocator, ptr, nElements);


	// Placement new..
	class DummyClassBlahBlah
	{
	public:
		int asdf;
	};

	inline void* operator new(size_t size, void *ptr, DummyClassBlahBlah *pBlah)
	{
		return ptr;
	}

	#if _MSC_VER != 1100
		inline void operator delete(void *pDataPtr, void *ptr, DummyClassBlahBlah *pBlah)
		{
		}
	#endif


	// The macros call these, which allocate and construct elements.
	template<class T>
	inline T* BaseNew(LAlloc *pAlloc, T *dummy, DWORD nElements)
	{
		T *ptr, *pTemp;

		ptr = (T*)pAlloc->Alloc(sizeof(T) * nElements);
		if(!ptr)
			return NULL;

		// Construct elements.
		pTemp = ptr;
		while(nElements)
		{
			--nElements;
			::new(pTemp, (DummyClassBlahBlah*)0) T;
			++pTemp;
		}

		return ptr;
	}

	template<class T, class P1>
	inline T* BaseNew_1P(LAlloc *pAlloc, T *dummy, DWORD nElements, P1 *p1)
	{
		T *ptr, *pTemp;

		ptr = (T*)pAlloc->Alloc(sizeof(T) * nElements);
		if(!ptr)
			return NULL;

		// Construct elements.
		pTemp = ptr;
		while(nElements)
		{
			--nElements;
			::new(pTemp, (DummyClassBlahBlah*)0) T(p1);
			++pTemp;
		}

		return ptr;
	}

	template<class T, class P1, class P2>
	inline T* BaseNew_2P(LAlloc *pAlloc, T *dummy, DWORD nElements, P1 *p1, P2 *p2)
	{
		T *ptr, *pTemp;

		ptr = (T*)pAlloc->Alloc(sizeof(T) * nElements);
		if(!ptr)
			return NULL;

		// Construct elements.
		pTemp = ptr;
		while(nElements)
		{
			--nElements;
			::new(pTemp, (DummyClassBlahBlah*)0) T(p1, p2);
			++pTemp;
		}

		return ptr;
	}

	template<class T>
	inline void	BaseDelete(LAlloc *pAlloc, T *ptr, DWORD nElements)
	{
		T *pTemp;

		if(!ptr)
			return;

		// Destruct elements.
		pTemp = ptr;
		while(nElements)
		{
			--nElements;
			pTemp->~T();
			++pTemp;
		}

		pAlloc->Free(ptr);
	}



#endif


