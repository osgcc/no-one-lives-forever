// Base LithTech header file

#ifndef __LITHTECH_H__
#define __LITHTECH_H__

// Engine define
#ifndef _LITHTECH_
	#define _LITHTECH_
#endif

// Engine version identifier.
#ifndef _LITHTECH2
	#define _LITHTECH2
#endif

// Main includes
#include "ltbasetypes.h"
#include "ltbasedefs.h"

// Interfaces
#include "iltstream.h"

// Backwards compatibility header include
#ifdef LT15_COMPAT
	#include "compat/ltcompat.h"
#endif


#endif //__LITHTECH_H__