
// This file defines old things for compatibility.
// Don't use anything in here cuz it's on its way out.

#ifndef __LT_COMPAT_H__
#define __LT_COMPAT_H__


	// These don't exist anymore...
	#define	bc_EngineMessageFn	LTNULL
	#define	bc_ObjectMessageFn	LTNULL

	#define g_pClientDE		g_pLTClient
	#define g_pServerDE		g_pLTServer

	// Old types
	#define ServerShellDE	IServerShell
	#define CServerShellDE	IServerShell
	#define ClientDE		ILTClient
	#define CClientDE		ILTClient
	#define CClientShellDE	IClientShell
	#define ClientShellDE	IClientShell
	#define CommonLT		ILTCommon
	#define ServerDE		ILTServer
	#define CServerDE		ILTServer
	#define Aggregate		IAggregate
	#define CustomDrawLT	ILTCustomDraw
	#define CSBase			ILTCSBase
	#define LightAnimLT		ILTLightAnim
	#define LMessage		ILTMessage
	#define PreLightLT		ILTPreLight
	#define ITexMod			ILTTexMod
	#define LVideoMgr		ILTVideoMgr
	#define MathLT			ILTMath
	#define ModelLT			ILTModel
	#define PhysicsLT		ILTPhysics
	#define SpriteControl	ILTSpriteControl
	#define TransformLT		ILTTransform
	#define DStream			ILTStream
	#define DStream_Read	LTStream_Read
	#define DStream_Write	LTStream_Write
	#define DECLARE_DLINK	DECLARE_LTLINK
	#define DECLARE_DLIST	DECLARE_LTLIST
	#define DLink			LTLink
	#define CheapDLink		CheapLTLink
	#define DList			LTList
	#define AnimTracker		LTAnimTracker
	#define DPlane			LTPlane
	#define CPlane			LTPlane
	#define DRotation		LTRotation
	#define DRect			LTRect
	#define CVector			LTVector
	#define DVector			LTVector
	#define CMatrix			LTMatrix
	#define DMatrix			LTMatrix
	#define DEParticle		LTParticle
	#define DELinePt		LTLinePt
	#define DELine			LTLine
	#define HDELINE			HLTLINE
	#define HDEFONT			HLTFONT
	#define HDECOLOR		HLTCOLOR
	#define DCounter		LTCounter
	#define HSOUNDDE		HLTSOUND
	#define DObject			LTObject
	#define DIntPt			LTIntPt
	#define DECommandStruct		LTCommandStruct
	#define DEEngineVar		LTEngineVar
	#define DRGBColor		LTRGBColor
	#define DGUID			LTGUID
	#define LithVertex		LTVertex

	// Old constants
	#define DNULL	LTNULL
	#define DBOOL	LTBOOL
	#define DTRUE	LTTRUE
	#define DFALSE	LTFALSE
	#define DDWORD	uint32
	#define D_WORD	uint16
	#define DBYTE	uint8
	#define DFLOAT	LTFLOAT

	// Old defines
	#define DDIFF	LTDIFF
	#define DMIN	LTMIN
	#define DMAX	LTMAX
	#define DABS	LTABS
	#define DCLAMP	LTCLAMP
	#define DLERP	LTLERP

	#define DTOCVEC(_vec) 
	#define CTODVEC(_vec) 
	
	// Old result codes
	#define DRESULT							LTRESULT
	#define DE_OK							LT_OK
	#define DE_ERROR						LT_ERROR
	#define DE_FINISHED						LT_FINISHED	
	#define DE_TRIEDTOREMOVECLIENTOBJECT	LT_TRIEDTOREMOVECLIENTOBJECT
	#define DE_NOTINWORLD					LT_NOTINWORLD
	#define DE_MISSINGFILE					LT_MISSINGFILE
	#define DE_MISSINGWORLDMODEL			LT_MISSINGWORLDMODEL
	#define DE_INVALIDMODELFILE				LT_INVALIDMODELFILE
	#define DE_OBJECTNOTINWORLD				LT_OBJECTNOTINWORLD
	#define DE_CANTREMOVESERVEROBJECT		LT_CANTREMOVESERVEROBJECT
	#define DE_CANTLOADGAMERESOURCES		LT_CANTLOADGAMERESOURCES
	#define DE_CANTINITIALIZEINPUT			LT_CANTINITIALIZEINPUT
	#define DE_MISSINGSHELLDLL				LT_MISSINGSHELLDLL
	#define DE_INVALIDSHELLDLL				LT_INVALIDSHELLDLL
	#define DE_INVALIDSHELLDLLVERSION		LT_INVALIDSHELLDLLVERSION
	#define DE_CANTCREATECLIENTSHELL		LT_CANTCREATECLIENTSHELL
	#define DE_UNABLETOINITSOUND			LT_UNABLETOINITSOUND
	#define DE_MISSINGMUSICDLL				LT_MISSINGMUSICDLL
	#define DE_INVALIDMUSICDLL				LT_INVALIDMUSICDLL
	#define DE_UNABLETOINITMUSICDLL			LT_UNABLETOINITMUSICDLL
	#define DE_CANTINITDIRECTPLAY			LT_CANTINITDIRECTPLAY
	#define DE_USERCANCELED					LT_USERCANCELED
	#define DE_MISSINGWORLDFILE				LT_MISSINGWORLDFILE
	#define DE_INVALIDWORLDFILE				LT_INVALIDWORLDFILE
	#define DE_ERRORBINDINGWORLD			LT_ERRORBINDINGWORLD
	#define DE_INVALIDSERVERPACKET			LT_INVALIDSERVERPACKET
	#define DE_MISSINGSPRITEFILE			LT_MISSINGSPRITEFILE
	#define DE_INVALIDSPRITEFILE			LT_INVALIDSPRITEFILE
	#define DE_MISSINGMODELFILE				LT_MISSINGMODELFILE
	#define DE_UNABLETORESTOREVIDEO			LT_UNABLETORESTOREVIDEO
	#define DE_SERVERERROR					LT_SERVERERROR
	#define DE_CANTCREATESERVER				LT_CANTCREATESERVER
	#define DE_ERRORLOADINGRENDERDLL		LT_ERRORLOADINGRENDERDLL
	#define DE_MISSINGCLASS					LT_MISSINGCLASS
	#define DE_CANTCREATESERVERSHELL		LT_CANTCREATESERVERSHELL
	#define DE_INVALIDOBJECTDLL				LT_INVALIDOBJECTDLL
	#define DE_INVALIDOBJECTDLLVERSION		LT_INVALIDOBJECTDLLVERSION
	#define DE_ERRORINITTINGNETDRIVER		LT_ERRORINITTINGNETDRIVER
	#define DE_NOGAMERESOURCES				LT_NOGAMERESOURCES
	#define DE_CANTRESTOREOBJECT			LT_CANTRESTOREOBJECT
	#define DE_NODENOTFOUND					LT_NODENOTFOUND
	#define DE_INVALIDPARAMS				LT_INVALIDPARAMS
	#define DE_NOTFOUND						LT_NOTFOUND
	#define DE_ALREADYEXISTS				LT_ALREADYEXISTS
	#define DE_NOTCONNECTED					LT_NOTCONNECTED
	#define DE_INSIDE						LT_INSIDE
	#define DE_OUTSIDE						LT_OUTSIDE
	#define DE_INVALIDDATA					LT_INVALIDDATA
	#define DE_OUTOFMEMORY					LT_OUTOFMEMORY
	#define DE_MISSINGPALETTE				LT_MISSINGPALETTE
	#define DE_INVALIDVERSION				LT_INVALIDVERSION
	#define DE_NOCHANGE						LT_NOCHANGE
	#define DE_INPUTBUFFEROVERFLOW			LT_INPUTBUFFEROVERFLOW
	#define DE_OVERFLOW						LT_OVERFLOW
	#define DE_KEPTSAMEMODE					LT_KEPTSAMEMODE
	#define DE_NOTINITIALIZED				LT_NOTINITIALIZED
	#define DE_ALREADYIN3D					LT_ALREADYIN3D
	#define DE_NOTIN3D						LT_NOTIN3D
	#define DE_ERRORCOPYINGFILE				LT_ERRORCOPYINGFILE
	#define DE_INVALIDFILE					LT_INVALIDFILE
	#define DE_INVALIDNETVERSION			LT_INVALIDNETVERSION
	#define DE_TIMEOUT						LT_TIMEOUT
	#define DE_CANTBINDTOPORT				LT_CANTBINDTOPORT
	#define DE_REJECTED						LT_REJECTED
	#define DE_NOTSAMEGUID					LT_NOTSAMEGUID
	#define DE_UNSUPPORTED					LT_UNSUPPORTED
	#define DE_INPROGRESS					LT_INPROGRESS
	#define DE_NO3DSOUNDPROVIDER			LT_NO3DSOUNDPROVIDER
	#define DE_YES							LT_YES
	#define DE_NO							LT_NO


	// ------------------------------------------------------------ // 
	// Old macros.. these shouldn't be used in new code.. their
	// respective classes have functions to do the same thing.
	// ------------------------------------------------------------ // 

	#define ROT_COPY(dest, src) ((dest) = (src))
	#define PLANE_COPY(dest, src) ((dest) = (src))

	#define PLANE_SET(plane, _x, _y, _z, _dist) ((plane).Init(LTVector(_x,_y,_z), _dist))

	// Get the distance from a point to a plane.
	#define DIST_TO_PLANE(vec, plane) ( VEC_DOT((plane).m_Normal, (vec)) - (plane).m_Dist )

	// Initializes the rotation to look down the positive Z axis.
	#define ROT_INIT(r) ((r).Init())

	#define MAT_COPY(dest, src) ((dest) = (src))

	#define MAT_SET(dest, \
		e00, e01, e02, e03,\
		e10, e11, e12, e13,\
		e20, e21, e22, e23,\
		e30, e31, e32, e33)\
			(dest).Init(\
				e00, e01, e02, e03,\
				e10, e11, e12, e13,\
				e20, e21, e22, e23,\
				e30, e31, e32, e33)

	#define INITSOUNDINFO_INIT( initSoundInfo ) (initSoundInfo).Init()

	
	// Functions with changed names
	#define DStream_Read	LTStream_Read
	#define DStream_Write	LTStream_Write

#endif  // __LT_COMPAT_H__
