//------------------------------------------------------------------
//
//	FILE	  : StdLithDefs.h
//
//	PURPOSE	  : Defines types and stuff for StdLith files.
//
//	CREATED	  : September 7 1996
//
//	COPYRIGHT : Microsoft 1996 All Rights Reserved
//
//------------------------------------------------------------------


#ifndef __STDLITH_DEFS_H__
	#define __STDLITH_DEFS_H__


	// Includes....
	#include <stdio.h>
	#include <string.h>
	#include <assert.h>



	#ifndef BOOL
		#define BOOL	int
	#endif

	#ifndef DWORD
		#define DWORD	unsigned long
	#endif

	#ifndef SDWORD
		#define SDWORD	long
	#endif

	#ifndef WORD
		#define WORD	unsigned short
	#endif

	#ifndef SWORD
		#define SWORD	short
	#endif

	#ifndef BYTE
		#define BYTE	unsigned char
	#endif

	#ifndef SBYTE
		#define SBYTE	char
	#endif

	#ifndef ASSERT
		#define ASSERT assert
	#endif

	#ifndef TRUE
		#define TRUE	1
	#endif

	#ifndef FALSE
		#define FALSE	0
	#endif

	#define	BAD_INDEX	((DWORD)-1)

/*	
	// Stdlith stuff uses these to allocate memory.
	void* dalloc(unsigned long size);
	void dfree(void *ptr);


	// You can use this macro if you don't want to define your own allocators.
	#define IMPLEMENT_DEFAULT_DALLOC() \
		void* dalloc(unsigned long size) {return malloc(size);}\
		void dfree(void *ptr) {if(ptr) free(ptr);}
*/

#endif  // __STDLITH_DEFS_H__



