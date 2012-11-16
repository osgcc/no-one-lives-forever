// mfcstub.h - Stub header file for duplicating the needed functionality to 
//		remove MFC from a project with as minimal an amount of change as possible

#ifndef __MFCSTUB_H__
#define __MFCSTUB_H__

// This define will keep anything from being defined or linked in if MFC isn't used
#if !defined(__AFX_H__)

// stdlith dependency
#include "..\stdlith\stdlith.h"

// Some headers that MFC automatically includes for you
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <crtdbg.h>

#include "..\mfcstub\mfcs_types.h"
#include "..\mfcstub\mfcs_point.h"
#include "..\mfcstub\mfcs_rect.h"
#include "..\mfcstub\mfcs_string.h"
#include "..\mfcstub\mfcs_misc.h"

#ifndef NO_PRAGMA_LIBS
	#if defined(_DEBUG)
		#pragma comment (lib, "\\proj\\libs\\debug\\mfcstub.lib")
	#else
		#pragma comment (lib, "\\proj\\libs\\release\\mfcstub.lib")
	#endif
#endif


#endif // __AFX_H__

#endif // __MFCSTUB_H__