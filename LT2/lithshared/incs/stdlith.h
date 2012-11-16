//------------------------------------------------------------------
//
//	FILE	  : StdLith.h
//
//	PURPOSE	  : Includes all the useful files for your
//              programming pleasure.
//
//	CREATED	  : August 20 1996
//
//	COPYRIGHT : Microsoft 1996 All Rights Reserved
//
//------------------------------------------------------------------

#ifndef __STDLITH_H__
	#define __STDLITH_H__


	// Includes....
	#include "../stdlith/stdlithdefs.h"
	#include "../stdlith/lithexception.h"
	#include "../stdlith/memory.h"

	#include "../stdlith/dynarray.h"
	
	#include "../stdlith/linklist.h"
	#include "../stdlith/goodlinklist.h"
	#include "../stdlith/multilinklist.h"
	#include "../stdlith/fastlinklist.h"
	#include "../stdlith/genhash.h"
	#include "../stdlith/glink.h"

	#include "../stdlith/stringholder.h"
	#include "../stdlith/morect.h"

	#include "../stdlith/abstractio.h"
	#include "../stdlith/fileio.h"
	#include "../stdlith/memoryio.h"
	#include "../stdlith/compressedio.h"

	#include "../stdlith/object_bank.h"
	#include "../stdlith/struct_bank.h"

	#include "../stdlith/helpers.h"
	#include "../stdlith/copy_lists.h"


	#ifndef NO_PRAGMA_LIBS
		#ifdef STDLITH_ALLOC_OVERRIDE
			// Use the 'allocator override' versions.
			#ifdef STDLITH_MFC
				#if defined( _DEBUG ) && defined( _AFXDLL )
					#pragma comment (lib, "\\proj\\libs\\debug\\StdLithMFCDLL_alloc.lib")
				#elif defined( _DEBUG ) && !defined( _AFXDLL )
					#pragma comment (lib, "\\proj\\libs\\debug\\StdLithMFC_alloc.lib")
				#elif !defined( _DEBUG ) && defined( _AFXDLL )
					#pragma comment (lib, "\\proj\\libs\\release\\StdLithMFCDLL_alloc.lib")
				#elif !defined( _DEBUG ) && !defined( _AFXDLL )
					#pragma comment (lib, "\\proj\\libs\\release\\StdLithMFC_alloc.lib")
				#endif
			#else
				#ifdef _DEBUG
					#pragma comment (lib, "\\proj\\libs\\debug\\StdLith_alloc.lib")
				#else
					#pragma comment (lib, "\\proj\\libs\\release\\StdLith_alloc.lib")
				#endif
			#endif
		#else
			#ifdef STDLITH_MFC
				#if defined( _DEBUG ) && defined( _AFXDLL )
					#pragma comment (lib, "\\proj\\libs\\debug\\StdLithMFCDLL.lib")
				#elif defined( _DEBUG ) && !defined( _AFXDLL )
					#pragma comment (lib, "\\proj\\libs\\debug\\StdLithMFC.lib")
				#elif !defined( _DEBUG ) && defined( _AFXDLL )
					#pragma comment (lib, "\\proj\\libs\\release\\StdLithMFCDLL.lib")
				#elif !defined( _DEBUG ) && !defined( _AFXDLL )
					#pragma comment (lib, "\\proj\\libs\\release\\StdLithMFC.lib")
				#endif
			#else
				#ifdef _DEBUG
					#pragma comment (lib, "\\proj\\libs\\debug\\StdLith.lib")
				#else
					#pragma comment (lib, "\\proj\\libs\\release\\StdLith.lib")
				#endif
			#endif
		#endif
	#endif


#endif
