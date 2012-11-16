/****************************************************************************
;
;	 MODULE:		WonShared (.h)
;
;	PURPOSE:		Implements shared server and client side WON functionality
;
;	HISTORY:		11/18/99  [blg]  This file was created
;
;	COMMENT:		Copyright (c) 1999, Monolith Productions, Inc.
;
****************************************************************************/


#ifndef _WONSHARED_H_
#define _WONSHARED_H_


// Includes...

#include "..\won\wonshared\wondefs.h"
#include "..\won\wonshared\wonnetaddress.h"
#include "..\won\wonshared\wondataobject.h"
#include "..\won\wonshared\wongameheader.h"
#include "..\won\wonshared\wongameplayers.h"
#include "..\won\wonshared\wongamedata.h"
#include "..\won\wonshared\wongameservice.h"


// Libs...

#define USE_WON_DLL		// comment this line out to statically link!

#ifndef NO_PRAGMA_LIBS

#ifdef _DEBUG
#pragma comment (lib, "\\proj\\libs\\debug\\wonshared.lib")
	#ifdef USE_WON_DLL
	#pragma comment (lib, "\\proj\\won\\api\\debug\\wondll.lib")
	#else
	#pragma comment (lib, "\\proj\\won\\api\\debug\\titanapi.lib")
	#endif
#else
#pragma comment (lib, "\\proj\\libs\\release\\wonshared.lib")
	#ifdef USE_WON_DLL
	#pragma comment (lib, "\\proj\\won\\api\\release\\wondll.lib")
	#else
	#pragma comment (lib, "\\proj\\won\\api\\release\\titanapi.lib")
	#endif
#endif

#endif 

#pragma comment (lib, "winmm.lib")




// Classes...

class CWonShared
{
	// Static Member functions...

public:
	static	void			Init();
	static	void			Term();


	// Static member variables...

private:
	static	int				m_nRef;
};


// EOF...

#endif
