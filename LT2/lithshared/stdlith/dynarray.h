//------------------------------------------------------------------
//
//	FILE	  : DynArray.h
//
//	PURPOSE	  : Caching dynamic arrays used everywhere.
//
//	CREATED	  : 5/1/96
//
//	COPYRIGHT : Microsoft 1996 All Rights Reserved
//
//------------------------------------------------------------------


#ifndef __MODYNARRAY_H__
	#define __MODYNARRAY_H__


	#include "memory.h"
	#include "l_allocator.h"
	#include "genlist.h"
	

	// Defines....
	#define CHECK_ARRAY_BOUNDS
	#define CACHE_DEFAULT_SIZE	0


	// Predefined types of arrays.
	#define CMoPtrArray		CMoArray<void*>
	#define CMoDWordArray	CMoArray<DWORD>
	#define CMoWordArray	CMoArray<WORD>
	#define CMoByteArray	CMoArray<unsigned char>
	#define DYNA_TEMPLATE template<class T, class C>


	// This can be used if you don't want the extra 4 bytes of caching info in the array.
	class NoCache
	{
	public:
		DWORD	GetCacheSize() const		{return 0;}
		void	SetCacheSize(DWORD size)	{}
		DWORD	GetWantedCache() const		{return 0;}
		void	SetWantedCache(DWORD size)	{}
	};


	class DefaultCache
	{
	public:
		DWORD	GetCacheSize() const	{return m_CacheSize;}
		void	SetCacheSize(DWORD val)	{m_CacheSize = val;}
		DWORD	GetWantedCache() const	{return m_WantedCache;}
		void	SetWantedCache(DWORD val){m_WantedCache = val;}

	private:		
		DWORD	m_CacheSize;
		DWORD	m_WantedCache;
	};

	
	// This is defined as a separate function because it's called by the virtual
	// GenFindElement and we don't want to generate a bunch of template code for
	// every type of object we use in a list.
	DWORD MoArray_FindElementMemcmp(
		const void *pToFind,
		const void *pArray, 
		DWORD nElements, 
		DWORD elementSize);

	
	template<class T, class C=DefaultCache>
	class CMoArray : public GenList<T>
	{
		public:

			// Constructors					
							CMoArray(CMoArray<T, C> &copyFrom, const T &toAdd)
							{
								Clear();
								Init();
								CopyArray(copyFrom);
								Append(toAdd);
							}

							CMoArray()
							{ 
								Clear();
								Init(); 
							}
							
							CMoArray( DWORD cacheSize )
							{
								Clear();
								Init(0, cacheSize); 
							}
						
			// Destructor
							~CMoArray() { Term(); }

			
			// Member functions
			BOOL			Init(DWORD size = 0, DWORD cacheSize = CACHE_DEFAULT_SIZE);
			void			Term(LAlloc *pAlloc=&g_DefAlloc) { SetSize2(0, pAlloc); }

			// WARNING: use these at your own risk.  If you use CopyPointers, you MUST
			// use TermPointers before modifying the array after that.
			void			CopyPointers(CMoArray<T,C> &other);
			void			TermPointers();

			// Comparison
			BOOL			Compare( const CMoArray<T, C> &other );
			
			// Assignment
			
			// You should use CopyArray whenever possible.
			CMoArray<T, C>&		operator=(const CMoArray<T, C> &other);
			CMoArray<T, C>		operator+(const T &toAdd);
			
			
			BOOL			CopyGenList(const GenList<T> &theList);
			BOOL			CopyArray( const CMoArray<T, C> &other );
			BOOL			CopyArray2( const CMoArray<T, C> &other, LAlloc *pAlloc );
		
			BOOL			AppendArray( const CMoArray<T, C> &other );

			// Find and compare with T::operator==.
			DWORD			FindElement( const T x ) const;
			
			BOOL 			Append( const T &toAdd ) { return Insert(m_nElements, toAdd); }
			BOOL 			Insert( DWORD index, const T &toInsert );
			BOOL 			Insert2( DWORD index, const T &toInsert, LAlloc *pAlloc );
			void 			Remove( DWORD index );
			void 			Remove2( DWORD index, LAlloc *pAlloc );

			// You can use it like a stack with these...
			BOOL			Push( const T &toAdd )  { return Append(toAdd); }
			void			Pop()					{ ASSERT(m_nElements>0); Remove( m_nElements-1 ); }



			// Accessors
			BOOL			IsValid() { return TRUE; }
			
			// Helpers for if you want to wrap around...
			T&				Last()		const	{ ASSERT(m_nElements>0); return m_pArray[ m_nElements-1 ]; }
			DWORD			LastI()		const	{ ASSERT(m_nElements>0); return m_nElements-1; }
			
			T&				Next( DWORD index ) const { return m_pArray[ NextI(index) ]; }
			T&				Prev( DWORD index ) const { return m_pArray[ PrevI(index) ]; }
			DWORD			NextI( DWORD i ) const
			{
				#ifdef CHECK_ARRAY_BOUNDS
					ASSERT( m_nElements > 0 );
				#endif

				if( i < (m_nElements-1) )
					return i+1;
				else
					return 0;
			}

			DWORD			PrevI( DWORD i ) const
			{
				#ifdef CHECK_ARRAY_BOUNDS
					ASSERT( m_nElements > 0 );
				#endif
				
				if( i == 0 )
					return m_nElements - 1;
				else
					return i-1;
			}

			// Number of elements
							operator unsigned long() const { return (unsigned long)m_nElements; }

			// Array-like access.
			T&				operator[]( const DWORD index ) const { return Get(index); }
			
			// Returns FALSE if there isn't enough memory.
			BOOL 			SetSize( DWORD newSize );
			BOOL 			SetSize2( DWORD newSize, LAlloc *pAlloc );

			BOOL 			SetSizeInit( DWORD newSize, T &val );
			BOOL 			SetSizeInit2( DWORD newSize, T val );
			BOOL 			SetSizeInit3( DWORD newSize, T &val, LAlloc *pAlloc );
			BOOL 			SetSizeInit4( DWORD newSize, T val, LAlloc *pAlloc );

			// Same as SetSize but preserves the old contents (ie: sizing from 8 to 4 preserves
			// the first 4 and sizing from 4 to 8 preserves the first 4).
			BOOL			NiceSetSize(DWORD newSize)						{return InternalNiceSetSize(newSize, FALSE, &g_DefAlloc);}
			BOOL			NiceSetSize2(DWORD newSize, LAlloc *pAlloc)		{return InternalNiceSetSize(newSize, FALSE, pAlloc);}
			
			// Same as NiceSetSize, but uses memcpy instead of operator=.
			BOOL			Fast_NiceSetSize(DWORD newSize)						{return InternalNiceSetSize(newSize, TRUE, &g_DefAlloc);}
			BOOL			Fast_NiceSetSize2(DWORD newSize, LAlloc *pAlloc)	{return InternalNiceSetSize(newSize, TRUE, pAlloc);}

			DWORD			GetSize() const { return m_nElements; }

			// Sets the cache size
			void			SetCacheSize( DWORD size )
			{
				m_Cache.SetWantedCache(size);
			}

			// Get and set
			T&				Get( DWORD index ) const
			{
				#ifdef CHECK_ARRAY_BOUNDS
					ASSERT( index < m_nElements );
				#endif
				return m_pArray[index];
			}

			void 			Set( DWORD index, T &data )
			{
				#ifdef CHECK_ARRAY_BOUNDS
					ASSERT( index < m_nElements );
				#endif
				m_pArray[index] = data;
			}

			// Returns a pointer to the internal array..
			T*				GetArray()	{ return m_pArray; }


	// Accessors for MFC compatibility.
	public:

			T&				GetAt( DWORD index ) const		{ return Get(index); }
			void			SetAt( DWORD index, T data )	{ Set(index, data); }

			void			RemoveAll()						{ SetSize(0); }
			BOOL 			Add( const T &toAdd )			{ return Insert(m_nElements, toAdd); }

			// Yes, we can be a hash bucket.
			static void		CheckSupportHashBucket() {}


	// GenList implementation.
	public:

		virtual GenListPos	GenBegin() const
		{
			return GenListPos((DWORD)0);
		}

		virtual BOOL		GenIsValid(const GenListPos &pos) const
		{
			return pos.m_Index < GetSize();
		}

		virtual T			GenGetNext(GenListPos &pos) const
		{
			T& ret = Get(pos.m_Index);
			++pos.m_Index;
			return ret;
		}

		virtual T			GenGetAt(GenListPos &pos) const
		{
			return Get(pos.m_Index);
		}

		virtual BOOL		GenAppend(T &toAppend)
		{
			return Append(toAppend);
		}

		virtual void		GenRemoveAt(GenListPos pos)
		{
			Remove(pos.m_Index);
		}

		virtual void		GenRemoveAll()
		{
			Term();
		}

		virtual DWORD		GenGetSize() const
		{
			return GetSize();
		}

		virtual BOOL		GenCopyList(const GenList<T> &theList)
		{
			GenListPos pos;
			DWORD iCurOut;

			if(!SetSize(theList.GenGetSize()))
				return FALSE;

			iCurOut = 0;
			for(pos=theList.GenBegin(); theList.GenIsValid(pos); )
			{
				// BAD bug in theList!
				if(iCurOut >= GetSize())
				{
					Term();
					return FALSE;
				}

				(*this)[iCurOut] = theList.GenGetNext(pos);
				iCurOut++;
			}

			return TRUE;
		}

		virtual BOOL		GenAppendList(const GenList<T> &theList)
		{
			GenListPos pos;
			DWORD iCurOut, prevSize;

			
			prevSize = GetSize();
			
			if(!NiceSetSize(prevSize + theList.GenGetSize()))
				return FALSE;

			iCurOut = prevSize;
			for(pos=theList.GenBegin(); theList.GenIsValid(pos); )
			{
				// BAD bug in theList!
				if(iCurOut >= GetSize())
				{
					Term();
					return FALSE;
				}

				(*this)[iCurOut] = theList.GenGetNext(pos);
				iCurOut++;
			}

			return TRUE;
		}

		virtual BOOL		GenFindElement(const T &toFind, GenListPos &thePos) const
		{
			thePos.m_Index = MoArray_FindElementMemcmp(
				&toFind,
				m_pArray, 
				m_nElements, 
				sizeof(T));
			
			return thePos.m_Index != BAD_INDEX;
		}

		virtual void		GenSetCacheSize(DWORD size)
		{
			SetCacheSize(size);
		}


	private:

			void 	_InitArray( DWORD wantedCache );
			void	_DeleteAndDestroyArray(LAlloc *pAlloc, DWORD nElements);
			T*		_AllocateTArray( DWORD nElements, LAlloc *pAlloc );

			BOOL	InternalNiceSetSize( DWORD newSize, BOOL bFast, LAlloc *pAlloc );
			inline DWORD	GetNumAllocatedElements()	{return m_nElements + m_Cache.GetCacheSize();}


	private:

			void	Clear()
			{
				m_pArray = 0;
				m_nElements = 0;
				m_Cache.SetCacheSize(0);
				m_Cache.SetWantedCache(0);
			}

			// Member variables
			
			T		*m_pArray;
			DWORD	m_nElements;

			C		m_Cache;

	};

	
	DYNA_TEMPLATE
	BOOL CMoArray<T, C>::Init( DWORD size, DWORD cacheSize )
	{
		Term();
		_InitArray(cacheSize);
		
		return SetSize(size);
	}


	DYNA_TEMPLATE
	void CMoArray<T,C>::CopyPointers(CMoArray<T,C> &other)
	{
		Term();
		m_pArray = other.m_pArray;
		m_nElements = other.m_nElements;
		m_Cache = other.m_Cache;
	}


	DYNA_TEMPLATE
	void CMoArray<T,C>::TermPointers()
	{
		m_pArray = NULL;
		m_nElements = 0;
		m_Cache.SetCacheSize(0);
		m_Cache.SetWantedCache(0);
	}


	DYNA_TEMPLATE
	BOOL CMoArray<T, C>::Compare( const CMoArray<T, C> &other )
	{
		DWORD	i;

		if( m_nElements != other.m_nElements )
			return FALSE;

		for( i=0; i < m_nElements; i++ )
			if( m_pArray[i] != other.m_pArray[i] )
				return FALSE;

		return TRUE;
	}



	template<class T, class C>
	CMoArray<T, C>& CMoArray<T, C>::operator=( const CMoArray<T, C> &other )
	{
		CopyArray(other);
		return *this;
	}

	
	DYNA_TEMPLATE
	CMoArray<T, C> CMoArray<T, C>::operator+(const T &toAdd)
	{
		return CMoArray<T, C>(*this, toAdd);
	}


	DYNA_TEMPLATE
	BOOL CMoArray<T, C>::CopyArray(const CMoArray<T,C> &other)
	{
		return CopyArray2(other, &g_DefAlloc);
	}


	DYNA_TEMPLATE
	BOOL CMoArray<T, C>::CopyArray2(const CMoArray<T,C> &other, LAlloc *pAlloc)
	{
		DWORD i;

		if( m_pArray )
		{
			_DeleteAndDestroyArray(pAlloc, GetNumAllocatedElements());
		}

		m_nElements = other.m_nElements;
		m_Cache.SetCacheSize(other.m_Cache.GetCacheSize());
		m_Cache.SetWantedCache(other.m_Cache.GetWantedCache());

		if( m_nElements + m_Cache.GetCacheSize() > 0  )
		{
			m_pArray = _AllocateTArray( m_nElements + m_Cache.GetCacheSize(), pAlloc );
		}
		else
		{
			m_nElements = 0;
			m_Cache.SetCacheSize(0);
			m_pArray = NULL;
			return TRUE;
		}

		// Could it allocate the array?
		if( !m_pArray )
		{
			m_nElements = 0;
			m_Cache.SetCacheSize(0);
			return FALSE;
		}

		for( i=0; i < m_nElements; i++ )
			m_pArray[i] = other.m_pArray[i];

		return TRUE;
	}


	DYNA_TEMPLATE
	BOOL CMoArray<T, C>::AppendArray( const CMoArray<T, C> &other )
	{
		DWORD			i;

		for( i=0; i < other; i++ )
			if( !Append(other[i]) )
				return FALSE;

		return TRUE;
	}


	DYNA_TEMPLATE
	DWORD CMoArray<T, C>::FindElement( const T x ) const
	{
		DWORD i, ret = BAD_INDEX;

		for( i=0; i < m_nElements; i++ )
		{
			if( m_pArray[i] == x )
			{
				ret = i;
				break;
			}
		}

		return ret;
	}



	DYNA_TEMPLATE
	BOOL CMoArray<T, C>::Insert( DWORD index, const T &toInsert )
	{
		return Insert2(index, toInsert, &g_DefAlloc);
	}



	DYNA_TEMPLATE
	BOOL CMoArray<T, C>::Insert2( DWORD index, const T &toInsert, LAlloc *pAlloc )
	{
		T		*pNewArray;
		DWORD	newSize, i;

		ASSERT( index <= m_nElements );
		if(index > m_nElements)
			return FALSE;

		// Create a new array (possibly).
		newSize = m_nElements + 1;
		
		//if( newSize >= (m_nElements+m_CacheSize) || m_nElements == 0 )
		if( m_Cache.GetCacheSize() == 0 )
		{
			pNewArray = _AllocateTArray( newSize + m_Cache.GetWantedCache(), pAlloc );
			if( !pNewArray )
				return FALSE;

			// Copy the old array into the new one, start inserting at index.
			for( i=0; i < index; i++ )
				pNewArray[i] = m_pArray[i];

			for( i=index; i < m_nElements; i++ )
				pNewArray[i+1] = m_pArray[i];
			
			// Insert the new item into the array
			pNewArray[index] = toInsert;

			// Free the old array and set our pointer to the new one
			if( m_pArray )
			{
				_DeleteAndDestroyArray(pAlloc, GetNumAllocatedElements());
			}

			m_Cache.SetCacheSize(m_Cache.GetWantedCache());
			m_pArray = pNewArray;
		}
		else
		{
			for( i=m_nElements; i > index; i-- )
				m_pArray[i] = m_pArray[i-1];
			
			m_Cache.SetCacheSize(m_Cache.GetCacheSize() - 1);

			m_pArray[index] = toInsert;
		}

		++m_nElements;		

		return TRUE;
	}



	DYNA_TEMPLATE
	void CMoArray<T, C>::Remove( DWORD index )
	{
		Remove2(index, &g_DefAlloc);
	}


	DYNA_TEMPLATE
	void CMoArray<T, C>::Remove2( DWORD index, LAlloc *pAlloc )
	{
		DWORD i, newSize, newAllocSize;
		T *pNewArray;
		BOOL bSlideDown;
												
	
		ASSERT( index < m_nElements && m_pArray );

		bSlideDown = TRUE;
		if( m_Cache.GetCacheSize() >= (m_Cache.GetWantedCache()*2) )
		{
			newSize = m_nElements - 1;
			newAllocSize = newSize + m_Cache.GetWantedCache();
			pNewArray = _AllocateTArray(newAllocSize, pAlloc);

			// Make sure it allocated the array .. if it didn't, just have
			// it slide all the elements down (this guarantees that Remove() 
			// won't fail.)
			if( pNewArray || newAllocSize == 0 )
			{
				for( i=0; i < index; i++ )
					pNewArray[i] = m_pArray[i];

				for( i=index; i < m_nElements-1; i++ )
					pNewArray[i] = m_pArray[i+1];

				_DeleteAndDestroyArray(pAlloc, GetNumAllocatedElements());
				m_pArray = pNewArray;

				m_Cache.SetCacheSize(m_Cache.GetWantedCache());
				bSlideDown = FALSE;
			}
		}


		if( bSlideDown )
		{
			// Slide them all down one.
			m_Cache.SetCacheSize(m_Cache.GetCacheSize() + 1);
			
			for( i=index; i < m_nElements-1; i++ )
				m_pArray[i] = m_pArray[i+1];
		}

		--m_nElements;
	}



	DYNA_TEMPLATE
	BOOL CMoArray<T, C>::SetSize( DWORD newSize )
	{
		return SetSize2(newSize, &g_DefAlloc);
	}


	DYNA_TEMPLATE
	BOOL CMoArray<T, C>::SetSize2( DWORD newSize, LAlloc *pAlloc )
	{
		// Uhhh ok...
		if((newSize == m_nElements) && (newSize != 0))
		{
			return TRUE;
		}

		if( m_pArray )
		{
			_DeleteAndDestroyArray(pAlloc, GetNumAllocatedElements());
		}

		m_nElements = newSize;
		if( newSize > 0 )
		{
			m_pArray = _AllocateTArray( newSize + m_Cache.GetWantedCache(), pAlloc );
			if( !m_pArray )
			{
				m_nElements = 0;
				m_Cache.SetCacheSize(0);
				return FALSE;
			}
			
			m_Cache.SetCacheSize(m_Cache.GetWantedCache());
		}

		return TRUE;
	}


	DYNA_TEMPLATE
	BOOL CMoArray<T, C>::SetSizeInit( DWORD newSize, T &val )
	{
		return SetSizeInit3(newSize, val, &g_DefAlloc);
	}


	DYNA_TEMPLATE
	BOOL CMoArray<T, C>::SetSizeInit2( DWORD newSize, T val )
	{
		return SetSizeInit3(newSize, val, &g_DefAlloc);
	}


	DYNA_TEMPLATE
	BOOL CMoArray<T, C>::SetSizeInit3( DWORD newSize, T &val, LAlloc *pAlloc )
	{
		DWORD i;

		if(!SetSize2(newSize, pAlloc))
			return FALSE;

		for(i=0; i < GetSize(); i++)
		{
			m_pArray[i] = val;
		}
		
		return TRUE;
	}


	DYNA_TEMPLATE
	BOOL CMoArray<T, C>::SetSizeInit4( DWORD newSize, T val, LAlloc *pAlloc )
	{
		return SetSizeInit3(newSize, val, pAlloc);
	}


	DYNA_TEMPLATE
	BOOL CMoArray<T, C>::InternalNiceSetSize( DWORD newSize, BOOL bFast, LAlloc *pAlloc )
	{
		T *pNewArray;
		DWORD i, nToCopy;

		// Trivial reject..
		if(newSize < m_nElements)
		{
			m_Cache.SetCacheSize(m_Cache.GetCacheSize() + (m_nElements - newSize));
			m_nElements = newSize;
			return TRUE;
		}
		else if(newSize > m_nElements && (m_nElements + m_Cache.GetCacheSize()) >= newSize)
		{
			m_Cache.SetCacheSize(m_Cache.GetCacheSize() - (newSize - m_nElements));
			m_nElements = newSize;
			return TRUE;
		}
		else if(newSize == m_nElements)
		{
			// uhhh ok..
			return TRUE;
		}

		pNewArray = _AllocateTArray(newSize + m_Cache.GetWantedCache(), pAlloc);
		if(!pNewArray)
			return FALSE;

		nToCopy = m_nElements;
		if(nToCopy > newSize)
			nToCopy = newSize;

		// Copy as many elements as we can.
		if(bFast)
		{
			memcpy(pNewArray, m_pArray, sizeof(T)*nToCopy);
		}
		else
		{
			for(i=0; i < nToCopy; i++)
			{
				pNewArray[i] = m_pArray[i];
			}
		}
		
		// Get rid of the old array and point at the new one.
		_DeleteAndDestroyArray(pAlloc, GetNumAllocatedElements());
		m_pArray = pNewArray;
		m_nElements = newSize;
		m_Cache.SetCacheSize(m_Cache.GetWantedCache());

		return TRUE;
	}


	DYNA_TEMPLATE
	void CMoArray<T, C>::_InitArray( DWORD wantedCache )
	{
		m_pArray = NULL;
		m_nElements = 0;

		m_Cache.SetWantedCache(wantedCache);
		m_Cache.SetCacheSize(0);
	}



	DYNA_TEMPLATE
	T *CMoArray<T, C>::_AllocateTArray( DWORD nElements, LAlloc *pAlloc )
	{
		T *tPtr = LNew_Array(pAlloc, T, nElements);

		return tPtr;
	}



	DYNA_TEMPLATE
	void CMoArray<T, C>::_DeleteAndDestroyArray(LAlloc *pAlloc, DWORD nElements)
	{
		if(m_pArray)
		{
			LDelete_Array(pAlloc, m_pArray, nElements);
			m_pArray = NULL;
		}

		m_Cache.SetCacheSize(0);
	}


	template<class T, class C, class ToAlloc>
	BOOL AllocateArray2(CMoArray<T, C> &theArray, ToAlloc *pToAlloc, LAlloc *pAllocator)
	{
		DWORD i;

		for(i=0; i < theArray; i++)
		{
			theArray[i] = LNew(pAllocator, ToAlloc);
			if(!theArray[i])
				return FALSE;
		}

		return TRUE;
	}


	template<class T, class C, class ToAlloc>
	BOOL AllocateArray(CMoArray<T, C> &theArray, ToAlloc *pToAlloc)
	{
		return AllocateArray2(theArray, pToAlloc, &g_DefAlloc);
	}


	template<class T, class V>
	void SetArray(T &theArray, V val)
	{
		DWORD i;

		for(i=0; i < theArray; i++)
			theArray[i] = val;
	}


	template<class T>
	void DeleteAndClearArray2( T &theArray, LAlloc *pAlloc )
	{
		DWORD i;

		for( i=0; i < theArray.GetSize(); i++ )
		{
			if(theArray[i])
			{
				LDelete(pAlloc, theArray[i]);
			}
		}

		theArray.SetSize2(0, pAlloc);
	}

	template<class T>
	void DeleteAndClearArray( T &theArray, LAlloc *pAlloc=&g_DefAlloc )
	{
		DeleteAndClearArray2(theArray, pAlloc);
	}


#endif 




