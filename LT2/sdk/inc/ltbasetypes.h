
#ifndef __LTBASETYPES_H__
#define __LTBASETYPES_H__

	#include <math.h>

	// Portable integer types.	
	typedef unsigned int		uint; // This is guaranteed to be 16 bits or larger.
	typedef char				int8;
	typedef unsigned char		uint8;
	typedef short				int16;
	typedef unsigned short		uint16;
	typedef long				int32;
	typedef unsigned long		uint32;
	typedef __int64				int64;
	typedef unsigned __int64	uint64;

	// Base types.
	typedef unsigned int LTBOOL;
	typedef float LTFLOAT;
	typedef double LTDFLOAT;
	typedef uint32 LTRESULT;

	// Base type values (enumeration emulation)
	// LTBOOL
	#define LTFALSE		0
	#define LTTRUE		1
	// LTRESULT (defined in ltcodes.h)

	// Forward declaration of LTObject
	class LTObject;

	// Handles
	// Object handle definition.
	typedef LTObject* HOBJECT;
	typedef LTObject* HLOCALOBJ;

	// Model handles
	typedef unsigned long HMODELPIECE;
	#define INVALID_MODEL_PIECE ((HMODELPIECE)-1)

	typedef unsigned long HMODELSOCKET;
	#define INVALID_MODEL_SOCKET ((HMODELNODE)-1)

	typedef unsigned long HMODELNODE;
	#define INVALID_MODEL_NODE ((HMODELNODE)-1)

	typedef unsigned long HMODELWEIGHTSET;
	#define INVALID_MODEL_WEIGHTSET ((HMODELWEIGHTSET)-1)

	typedef unsigned long HMODELANIM;
	#define INVALID_MODEL_ANIM ((HMODELANIM)-1)

	// Poly reference
	typedef unsigned long HPOLY;
	#define INVALID_HPOLY 0xFFFFFFFF

	// Globally unique identifier.
	struct LTGUID
	{
		unsigned long	a;
		unsigned short	b;
		unsigned short	c;
		unsigned char   d[8];
	};

	// More complicated types
	#include "ltvector.h"
	#include "ltbbox.h"
	#include "ltrotation.h"
	#include "ltplane.h"
	#include "ltrect.h"
	#include "ltmatrix.h"
	#include "ltlink.h"

	// Structures
	struct PGColor
	{
		float x, y, z; // RGB 0-255
		float a; // Alpha 0-255
	};

	struct LTFloatPt
	{
		float	x, y;
	};

	struct LTIntPt
	{
		LTIntPt(int a = 0, int b = 0) : x(a), y(b) {}
		int	x, y;
	};

	struct LTWarpPt
	{
		float source_x, source_y;
		float dest_x, dest_y;
	};

	struct ArgList
	{
		char **argv;
		int argc;
	};

	// This class represents a position and rotation.  The ILTTransform class
	// can be used to work with them.
	class LTransform
	{
	public:
		LTVector	m_Pos;
		LTRotation	m_Rot;
	};

	// Surface data.
	struct SurfaceData
	{
		LTVector	O, P, Q;				// Texture vectors.
		void		*m_pInternalWorld;		// Don't touch!  (MainWorld* on init).
		void		*m_pInternalWorldBsp;	// Don't touch!  (WorldBsp* on init).
		void		*m_pInternalSurface;	// Don't touch!  (Surface*)
	};

	// Sky definition.
	struct SkyDef
	{
		LTVector	m_Min, m_Max;			// Box corners (in world coordinates).
		LTVector	m_ViewMin, m_ViewMax;	// View min and max.  The viewer's position
											// in the main world is squished into this
											// box so you can get a tiny amount of parallax.
	};

	typedef void (*ConsoleProgramFn)(int argc, char **argv);

	typedef void (*NodeControlFn)(HOBJECT hObj, HMODELNODE hNode, LTMatrix *pGlobalMat, void *pUserData);

	// This is used to distinguish between flag types.
	enum ObjFlagType
	{
		OFT_Flags = 0,	// FLAG_  #defines
		OFT_Flags2		// FLAG2_ #defines
	};

#endif // __LTBASETYPES_H__

