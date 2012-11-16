/****************************************************************************
;
;	MODULE:		LITH (.H)
;
;	PURPOSE:	
;
;	HISTORY:	04/19/98 [blb] 
;
;	NOTICE:		Copyright (c) 1998, MONOLITH, Inc.
;
****************************************************************************/

#ifndef LITH_H
#define LITH_H

// Includes...

#include "..\lith\lithtypes.h"
#include "..\lith\baselist.h"
#include "..\lith\basehash.h"
#include "..\lith\virtlist.h"
#include "..\lith\baselistcounter.h"
#include "..\lith\dprintf.h"


#ifndef NO_PRAGMA_LIBS
	#ifdef _DEBUG
		#pragma comment (lib, "\\Proj\\Libs\\Debug\\lith.lib")
	#else
		#pragma comment (lib, "\\Proj\\Libs\\Release\\lith.lib")
	#endif
#endif



#endif
