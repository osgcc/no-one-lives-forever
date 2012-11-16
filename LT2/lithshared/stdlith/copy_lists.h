
// This module defines a bunch of functions to convert between the different
// list formats (arrays, linked lists, etc).

#ifndef __COPY_LISTS_H__
#define __COPY_LISTS_H__


	#include "dynarray.h"
	#include "goodlinklist.h"
	#include "stdlithdefs.h"


	template<class T>
	BOOL CopyGListToArray(CGLinkedList<T> &theList, CMoArray<T> &theArray)
	{
		GPOS pos;
		DWORD curOut;

		if(!theArray.SetSize(theList.GetSize()))
			return FALSE;

		curOut = 0;
		for(pos=theList.GetHeadPosition(); pos; )
		{
			theArray[curOut] = theList.GetNext(pos);
			curOut++;
		}

		return TRUE;
	}


	template<class T>
	BOOL CopyArrayToGList(CMoArray<T> &theArray, CGLinkedList<T> &theList)
	{
		DWORD i;

		theList.Term();

		for(i=0; i < theArray.GetSize(); i++)
		{
			theList.Append(theArray[i]);
		}

		return TRUE;
	}


#endif


