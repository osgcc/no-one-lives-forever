/****************************************************************************
;
;	MODULE:		LithTmpl (.H)
;
;	PURPOSE:	Includes all of the different class header files in the lib
;
;	HISTORY:	04/19/98 [blb] 
;
;	NOTICE:		Copyright (c) 1998, MONOLITH, Inc.
;
****************************************************************************/

#ifndef LithTmpl_H
#define LithTmpl_H

#include "..\lith\lithbaselist.h"
#include "..\lith\lithsimpary.h"
#include "..\lith\lithsimparystat.h"
#include "..\lith\lithchunkallocator.h"

// Console libs

//#ifdef _CONSOLE
//#ifdef _DEBUG
//#pragma comment (lib, "\\Proj\\Libs\\Debug Console\\lith.lib")
//#else
//#pragma comment (lib, "\\Proj\\Libs\\Release Console\\lith.lib")
//#endif

// Windows libs

//#else
#ifndef NO_PRAGMA_LIBS
	#ifdef _DEBUG
		#pragma comment (lib, "\\Proj\\Libs\\Debug\\lith.lib")
	#else
		#pragma comment (lib, "\\Proj\\Libs\\Release\\lith.lib")
	#endif
#endif

//#endif

#endif